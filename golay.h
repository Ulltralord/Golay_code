#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <math.h>
#include <string>
#include "matrix.h"

using namespace std;

matrix create_B() {
    matrix matrix_B(12, 12);
    int temp[12][12] =
    {
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0 }, 
    { 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 }, 
    { 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1 }, 
    { 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0 }, 
    { 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1 }, 
    { 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1 }, 
    { 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1 }, 
    { 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0 }, 
    { 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0 }, 
    { 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0 }, 
    { 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1 }, 
    };


    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            matrix_B.m[i][j] = temp[i][j];
        }
    }
    return matrix_B;
}

matrix create_G() {
    matrix matrix_G(12, 24);
    int temp[12][24] =
    {
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
 1, 1, 1, 1, 1 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1,
 0, 0, 0, 1, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0,
 0, 0, 1, 0, 1 },
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0,
 0, 1, 0, 1, 1 },
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
 1, 0, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
 0, 1, 1, 0, 1 },
    { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0,
 1, 1, 0, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1,
 1, 0, 1, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1,
 0, 1, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0,
 1, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1
, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1,
 1, 0, 0, 0, 1 },
    };
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 24; j++) {
            matrix_G.m[i][j] = temp[i][j];
        }
    }
    return matrix_G;
}

matrix generate_message()
{
    matrix message(1,12);

    srand(time(NULL));

    for (int i = 0; i < 12; i++) {
        message.m[0][i] = rand() % 2;
    }

    return message;
}  

matrix set_errors(matrix m) {

    srand(time(NULL));

    matrix with_errors = m;

    int err_num = rand() % 4;

    for (int i = 0; i < err_num; i++) {
        
        int num = rand() % 24;
        with_errors.m[0][num] = (with_errors.m[0][num] 
														+ 1) % 2;
    }

    cout << endl << "number of errors during 
	transmission were: " << err_num << endl;
    return with_errors;
}
                                     
int weight(matrix a)
{
    int temp = 0;
    int i;

    for(i = 0 ; i < a.m[0].size() ; i++)
    {
        if(a.m[0][i] == 1)
        {
            temp++;
        }
    }

    return temp;
}

vector<int> weight_with_B(matrix a, matrix b) {
    matrix temp_a = a;
    matrix temp_b = b;
    matrix temp_row(1, 12);

    vector<int> row_weight;

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {

            temp_b.m[i][j] = temp_b.m[i][j] + temp_a.m[0][j];
            temp_row.m[0][j] = temp_b.m[i][j];
        }

        row_weight.push_back(weight(temp_row));
    }
    return row_weight;
}