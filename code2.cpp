#include<iostream> 
#include<stdlib.h> 
using namespace std;
const int c = 6;
void check_bomb(int arr[][c], int r);
void check_wrap(int arr[][c], int r);
void check_strip(int arr[][c], int r);
void simple(int arr[][c], int r);
int main()
{
    int r = 6;
    int arr[6][c] = { 0 };
    
    
    check_bomb(arr, r);
    for (int j = 0; j < r; j++)
    {
        for (int k = 0; k < c; k++)
        {
            cout << arr[j][k];
        }
        cout << endl;
    }
    return 0;
}

void check_bomb(int arr[][c], int r)    //value of candybomb(21)
{
    for(int i = 0; i < c; i++) //check color_bomb in column
    {
        for (int j = 0; j < r-4; j++) {
            int temp = 6;
            if(arr[j][i]!=21)
                temp = (arr[j][i]%5);
  
            if ((arr[j+1][i]%5) == temp && (arr[j+2][i ]%5) == temp && (arr[j+3][i ]%5) == temp && (arr[j + 4][i ]%5) == temp && arr[j + 1][i]<21&& arr[j + 2][i] < 21 && arr[j + 3][i] < 21 && arr[j + 4][i] < 21){
                arr[j+2][i] = 21;  
                arr[j+1][i] = 0;
                arr[j+3][i] = 0;
                arr[j+4][i] = 0;
                arr[j][i] = 0;
            }
        }        
    }
    for (int j = 0; j < r; j++) //check color_bomb in row
    {
        for (int i = 0; i < c-4; i++) {
            int temp = 6;
            if (arr[j][i] != 21)
                temp = (arr[j][i] % 5);
            if ((arr[j][i + 1] % 5) == temp && (arr[j][i + 2] % 5) == temp && (arr[j][i + 3] % 5) == temp && (arr[j][i + 4] % 5) == temp && arr[j][i + 1] < 21 && arr[j][i + 2] < 21 && arr[j][i + 3] < 21 && arr[j][i + 4] < 21) {
                arr[j][i + 2] = 21;
                arr[j][i] = 0;
                arr[j][i + 1] = 0;
                arr[j][i + 3] = 0;
                arr[j][i + 4] = 0;
            }
        }
    }
}
void check_wrap(int arr[][c], int r)    //value of wrapped candy(16-20)
{
    for (int j = 0; j < r; j++) 
    {
        for (int i = 0; i < c - 2; i++) {
            int temp = 6;
            if (arr[j][i] != 21)
                temp = (arr[j][i] % 5);
            if ((arr[j][i + 1] % 5) == temp && (arr[j][i + 2] % 5) == temp && arr[j][i + 1] < 21 && arr[j][i + 2] < 21 ) {
                if ((j+2)<r&&(arr[j + 1][i] % 5) == temp && (arr[j + 2][i] % 5) == temp && (arr[j + 1][i] ) < 21 && (arr[j + 2][i]  < 21))
                {
                    arr[j][i] = temp + 16;
                    arr[j + 1][i] = 0;
                    arr[j + 2][i] = 0;
                    arr[j][i+1] = 0;
                    arr[j][i+2] = 0;
                }
                else if ((j + 2) < r && (arr[j + 1][i+1] % 5) == temp && (arr[j + 2][i+1] % 5) == temp && (arr[j + 1][i+1] ) < 21 && (arr[j + 2][i+1]  < 21))
                {
                    arr[j][i+1] = temp + 16;
                    arr[j + 1][i+1] = 0;
                    arr[j + 2][i+1] = 0;
                    arr[j][i ] = 0;
                    arr[j][i + 2] = 0;
                }
                else if ((j + 2) < r && (arr[j + 1][i +2] % 5) == temp && (arr[j + 2][i +2] % 5) == temp && (arr[j + 1][i + 2] ) < 21 && (arr[j + 2][i + 2]  < 21))
                {
                    arr[j][i + 2] = temp + 16;
                    arr[j + 1][i + 2] = 0;
                    arr[j + 2][i + 2] = 0;
                    arr[j][i+1] = 0;
                    arr[j][i ] = 0;
                }
                else if ((j + 1) < r && (j - 1) >=0 && (arr[j + 1][i ] % 5) == temp && (arr[j - 1][i ] % 5) == temp && (arr[j + 1][i ] ) < 21 && (arr[j -1][i ]  < 21))
                {
                    arr[j][i ] = temp + 16;
                    arr[j + 1][i ] = 0;
                    arr[j -1][i ] = 0;
                    arr[j][i + 1] = 0;
                    arr[j][i+2] = 0;
                }
                else if ((j + 1) < r && (j - 1) >= 0 && (arr[j + 1][i+1] % 5) == temp && (arr[j - 1][i+1] % 5) == temp && (arr[j + 1][i+1] ) < 21 && (arr[j - 1][i+1]  < 21))
                {
                    arr[j][i+1] = temp + 16;
                    arr[j + 1][i+1] = 0;
                    arr[j - 1][i+1] = 0;
                    arr[j][i ] = 0;
                    arr[j][i + 2] = 0;
                }
                else if ((j + 1) < r && (j - 1) >= 0 && (arr[j + 1][i + 2] % 5) == temp && (arr[j - 1][i + 2] % 5) == temp && (arr[j + 1][i + 2]) < 21 && (arr[j - 1][i + 2] < 21))
                {
                    arr[j][i+2] = temp + 16;
                    arr[j + 1][i+2] = 0;
                    arr[j - 1][i+2] = 0;
                    arr[j][i ] = 0;
                    arr[j][i + 1] = 0;
                }
                else if ((j - 2) >= 0 && (arr[j -1][i ] % 5) == temp && (arr[j-2][i ] % 5) == temp && (arr[j -1][i]) < 21 && (arr[j - 2][i ] < 21))
                {
                    arr[j][i] = temp + 16;
                    arr[j -2][i] = 0;
                    arr[j - 1][i] = 0;
                    arr[j][i + 1] = 0;
                    arr[j][i + 2] = 0;
                }
                else if ((j - 2) >= 0 && (arr[j - 1][i+1] % 5) == temp && (arr[j - 2][i+1] % 5) == temp && (arr[j - 1][i+1]) < 21 && (arr[j - 2][i+1] < 21))
                {
                    arr[j][i+1] = temp + 16;
                    arr[j - 2][i+1] = 0;
                    arr[j - 1][i+1] = 0;
                    arr[j][i ] = 0;
                    arr[j][i + 2] = 0;
                }
                else if ((j - 2) >= 0 && (arr[j - 1][i+2] % 5) == temp && (arr[j - 2][i+2] % 5) == temp && (arr[j - 1][i+2]) < 21 && (arr[j - 2][i+2] < 21))
                {
                    arr[j][i+2] = temp + 16;
                    arr[j - 2][i+2] = 0;
                    arr[j - 1][i+2] = 0;
                    arr[j][i + 1] = 0;
                    arr[j][i] = 0;
                }
            }
        }
    }
}
void check_strip(int arr[][c], int r)   //value of horizontal stripe(6-10) and vertical stripe(11-15)
{

    for (int i = 0; i < c; i++) //check color_bomb in column(horizontal stripe)
    {
        for (int j = 0; j < r - 3; j++) {
            int temp = 6;
            if (arr[j][i] != 21)
                temp = (arr[j][i] % 5);

            if ((arr[j + 1][i] % 5) == temp && (arr[j + 2][i] % 5) == temp && (arr[j + 3][i] % 5) == temp  && arr[j + 1][i] < 21 && arr[j + 2][i] < 21 && arr[j + 3][i] < 21 ) {
                arr[j + 2][i] = temp+6;
                arr[j + 1][i] = 0;
                arr[j + 3][i] = 0;
                arr[j][i] = 0;
            }
        }
    }
    for (int j = 0; j < r; j++) //check color_bomb in row(vertical stripe)
    {
        for (int i = 0; i < c - 3; i++) {
            int temp = 6;
            if (arr[j][i] != 21)
                temp = (arr[j][i] % 5);
            if ((arr[j][i + 1] % 5) == temp && (arr[j][i + 2] % 5) == temp && (arr[j][i + 3] % 5) == temp && arr[j][i + 1] < 21 && arr[j][i + 2] < 21 && arr[j][i + 3] < 21 ) {
                arr[j][i + 2] = temp+11;
                arr[j][i] = 0;
                arr[j][i + 1] = 0;
                arr[j][i + 3] = 0;
                arr[j][i + 4] = 0;
            }
        }
    }
}
void simple(int arr[][c], int r)
{
    for (int j = 0; j < r; j++)
    {
        for (int i = 0; i < c - 2; i++) {
            int temp = 6;
            if (arr[j][i] != 21)
                temp = (arr[j][i] % 5);
            if ((arr[j][i + 1] % 5) == temp && (arr[j][i + 2] % 5) == temp && arr[j][i + 1] < 21 && arr[j][i + 2] < 21)
            {
                arr[j][i] = 0;
                arr[j][i + 1] = 0;
                arr[j][i + 2] = 0;
            }
        }
        for (int i = 0; i < c; i++)
        {
            for (int j = 0; j < r - 2; j++)
            {
                int temp = 6;
                if (arr[j][i] != 21)
                    temp = (arr[j][i] % 5);
                if ((arr[j + 1][i] % 5) == temp && (arr[j + 2][i] % 5) == temp && arr[j + 1][i] < 21 && arr[j + 2][i] < 21)
                {
                    arr[j][i] = 0;
                    arr[j + 1][i] = 0;
                    arr[j + 2][i] = 0;
                }
            }
        }
    }
}