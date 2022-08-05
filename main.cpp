#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "golay.h"

using namespace std;

int main()
{   
    matrix gen = create_G();
    matrix par = create_B();
    matrix gen_t = transpose(gen);
    matrix message = generate_message();

    cout << endl << "message m:         ";
    print(message);

    matrix encoded_message = multiply(message,gen);

    cout << endl << "encoded message:   ";
    print(encoded_message);

    matrix recieved_message = set_errors(encoded_message);

    cout << endl << "recieved message:  ";
    print(recieved_message);

    matrix syndrome = multiply(recieved_message, gen_t);

    cout << endl << "syndrome:   "; 
    print(syndrome);
    cout << "weight of syndrome is " <<
 				weight(syndrome) << endl; 

    matrix sB = multiply(syndrome,par);

    cout << endl << "sB:    "; 
    print(sB);
    cout  << "weight of sB is " << weight(sB) << endl;

    vector<int> s_with_B = weight_with_B(syndrome, par);
    vector<int> sB_with_B = weight_with_B(sB, par);
    matrix error(1, 24);

    if(weight(syndrome) <= 3)
    {
        for(int i = 0; i < syndrome.m[0].size() ; i++)
        {
            if(syndrome.m[0][i] == 1)
            {
                error.m[0][i] = 1;
            }
        }
    }

    else if(weight(sB) <= 3)
    {        
        for(int i = 0; i < sB.m[0].size() ; i++)
        {
            if(sB.m[0][i] == 1)
            {
                error.m[0][i + 12] = 1;
            }
        }
    }

    else
    {
        for (int i = 0; i < 12; i++)
        {
            if (s_with_B[i] <= 2)
            {
                error.m[0][i + 12] = 1;

                matrix temp(1, 12);
                matrix s_row(1, 12);
                for (int j = 0; j < 12; j++) {
                    temp.m[0][j] = par.m[i][j];
                    s_row = addition(temp, syndrome);
                    error.m[0][j] = s_row.m[0][j];
                }

            }

            if (sB_with_B[i] <= 2)
            {
                error.m[0][i] = 1;

                matrix temp(1, 12);
                matrix sB_row(1, 12);
                for (int j = 0; j < 12; j++) {
                    temp.m[0][j] = par.m[i][j];
                    sB_row = addition(temp, sB);
                    error.m[0][j + 12] = sB_row.m[0][j];
                }

            }

        }

    }

    cout << endl <<"the error vector is:    "; 
    print(error);

    matrix original_message = addition(recieved_message,error); 

    if(original_message.m == encoded_message.m)
    {
        cout << endl <<
		 "Transmitance and error correcting successful." << endl;
    }
    else 
    {
        cout << "error in transmittance or error correcting."	
														 << endl;
    }
    
    cout << endl << "calculated encoded message:   ";
    print(original_message);
    cout << "  original encoded message:   ";
    print(encoded_message); 

    cout << endl << "calculated message m :   ";
    for(int i = 0 ; i < 12 ; i++)
    {
        cout << original_message.m[0][i] << "  ";
    }
    cout << endl << "  original message m :   ";
    for(int i = 0 ; i < 12 ; i++)
    {
        cout << message.m[0][i] << "  ";
    }
  
    return 0;
}
