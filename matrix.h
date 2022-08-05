#include <iostream>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

class matrix
{
public:
    int row;
    int column;
    vector <vector <int>> m;

    matrix() {};

    matrix(int r, int c)
    {
        row = r;
        column = c;

        for (int i = 0; i < r; i++)
        {
            m.push_back(vector<int>());
        }

        for (int j = 0; j < c; j++)
        {
            for (int i = 0; i < m.size(); i++)
            {
                m[i].push_back(0);
            }
        }
    }
};

matrix multiply(matrix a, matrix b)
{
    int i, j, k;
    int tem = 0;
    int index = 0;
    matrix temp(a.row, b.column);

    if (a.column != b.row)
    {
        cout << "ERROR";
    }
    else
    {
        for (i = 0; i < a.row; i++)
        {
            for (j = 0; j < b.column; j++)
            {
                for (k = 0; k < a.column; k++)
                {
                    tem = a.m[i][k] * b.m[k][j];
                    index = index + tem;
                    tem = 0;
                }

                temp.m[i][j] = index % 2;
                index = 0;
            }
        }
    }

    return temp;
}

matrix addition(matrix a, matrix b)
{
    matrix temp(a.row, a.column);
    int i, j;

    if (a.row != b.row || a.column != b.column)
    {
        cout << "ERROR";
    }
    else
    {
        for (i = 0; i < a.row; i++)
        {
            for (j = 0; j < a.column; j++)
            {
                temp.m[i][j] = (a.m[i][j] + b.m[i][j]) % 2;
            }
        }
    }

    return temp;
}

matrix transpose(matrix a)
{
    matrix temp(a.column, a.row);
    int i, j;

    for (i = 0; i < a.row; i++)
    {
        for (j = 0; j < a.column; j++)
        {
            temp.m[j][i] = a.m[i][j];
        }
    }

    return temp;
}

void print(matrix a)
{
    int i, j;

    for (i = 0; i < a.row; i++)
    {
        for (j = 0; j < a.column; j++)
        {

            cout << a.m[i][j] << "  ";
        }

        cout << endl;
    }
}