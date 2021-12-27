#include<iostream> 
#include<stdlib.h> 

using namespace std;

const int c = 9;
const int r = 9;

void fill(int arr[][c]);
void check_bomb(int arr[][c]);
void check_wrap(int arr[][c]);
void check_strip(int arr[][c]);
void simple(int arr[][c]);
void special_move(int arr[][c], int i, int j);
void striped_special(int arr[][c], int i, int j);
void wrapped_special(int arr[][c], int i, int j);
void bomb_special(int arr[][c], int i, int j);

int main()
{
    int arr[r][c] = { 0 };

    fill(arr);
    return 0;
}

void fill(int arr[][c])
{
    for (int j = 0; j < r; j++)
    {
        for (int k = 0; k < c; k++)
        {
            if (arr[0][k] == 0)
                arr[0][k] = rand() % 5 + 1;
            if (arr[j][k] == 0)
            {
                int i = 1;
                while (j - i >= 0) {
                    arr[j - i + 1][k] = arr[j - i][k];
                    arr[j - i][k] = 0;
                    i++;
                }
            }
            if (arr[0][k] == 0)
                arr[0][k] = rand() % 5 + 1;
        }
    }
    for (int j = 0; j < r; j++)
    {
        for (int k = 0; k < c; k++)
        {
            cout << arr[j][k];
        }
        cout << endl;
    }
}
void check_bomb(int arr[][c])    //value of candybomb(21)
{
    for (int i = 0; i < c; i++) //check color_bomb in column
    {
        for (int j = 0; j < r - 4; j++) {
            int temp = 6;
            if (arr[j][i] < 21)
                temp = (arr[j][i] % 5);

            if ((arr[j + 1][i] % 5) == temp && (arr[j + 2][i] % 5) == temp && (arr[j + 3][i] % 5) == temp && (arr[j + 4][i] % 5) == temp && arr[j + 1][i] < 21 && arr[j + 2][i] < 21 && arr[j + 3][i] < 21 && arr[j + 4][i] < 21) {
                if (arr[j + 2][i] > 5)
                {
                    special_move(arr, (j + 2), i);
                    arr[j + 2][i] = 21;
                    special_move(arr, (j + 2), i);
                }
                else
                    arr[j + 2][i] = 21;
                special_move(arr, j, i);
                special_move(arr, (j + 1), i);
                special_move(arr, (j + 3), i);
                special_move(arr, (j + 4), i);
            }
        }
    }
    for (int j = 0; j < r; j++) //check color_bomb in row
    {
        for (int i = 0; i < c - 4; i++) {
            int temp = 6;
            if (arr[j][i] < 21)
                temp = (arr[j][i] % 5);
            if ((arr[j][i + 1] % 5) == temp && (arr[j][i + 2] % 5) == temp && (arr[j][i + 3] % 5) == temp && (arr[j][i + 4] % 5) == temp && arr[j][i + 1] < 21 && arr[j][i + 2] < 21 && arr[j][i + 3] < 21 && arr[j][i + 4] < 21) {
                if (arr[j][i+2] > 5)
                {
                    special_move(arr, j,( i+2));
                    arr[j][i+2] = 21;
                    special_move(arr, j, (i + 2));
                }
                else
                    arr[j][i+2] = 21;
                special_move(arr, j, i);
                special_move(arr, j, (i + 1));
                special_move(arr, j, (i + 3));
                special_move(arr, j, (i + 4));
            }
        }
    }
}
void check_wrap(int arr[][c])    //value of wrapped candy(16-20)
{
    for (int j = 0; j < r; j++)
    {
        for (int i = 0; i < c - 2; i++) {
            int temp = 6;
            if (arr[j][i] != 21)
                temp = (arr[j][i] % 5);
            if ((arr[j][i + 1] % 5) == temp && (arr[j][i + 2] % 5) == temp && arr[j][i + 1] < 21 && arr[j][i + 2] < 21) {
                if ((j + 2) < r && (arr[j + 1][i] % 5) == temp && (arr[j + 2][i] % 5) == temp && (arr[j + 1][i]) < 21 && (arr[j + 2][i] < 21))
                {
                    if (arr[j][i] > 5)
                    {
                        special_move(arr, j, i);
                        arr[j][i] = temp + 16;
                        special_move(arr, j, i);
                    }
                    else
                        arr[j][i] = temp + 16;
                    special_move(arr, (j+1), i);
                    special_move(arr, (j + 2), i);
                    special_move(arr, j, (i+1));
                    special_move(arr, j, (i+2));
                }
                else if ((j + 2) < r && (arr[j + 1][i + 1] % 5) == temp && (arr[j + 2][i + 1] % 5) == temp && (arr[j + 1][i + 1]) < 21 && (arr[j + 2][i + 1] < 21))
                {
                    if (arr[j][i+1] > 5)
                    {
                        special_move(arr, j, (i+1));
                        arr[j][i+1] = temp + 16;
                        special_move(arr, j, (i + 1));
                    }
                    else
                        arr[j][i + 1] = temp + 16;
                    special_move(arr, (j+1), (i + 1));
                    special_move(arr, j, (i + 2));
                    special_move(arr, (j+2), (i + 1));
                    special_move(arr, j, i);
                }
                else if ((j + 2) < r && (arr[j + 1][i + 2] % 5) == temp && (arr[j + 2][i + 2] % 5) == temp && (arr[j + 1][i + 2]) < 21 && (arr[j + 2][i + 2] < 21))
                {
                    if (arr[j][i + 2] > 5)
                    {
                        special_move(arr, j, (i + 2));
                        arr[j][i + 2] = temp + 16;
                        special_move(arr, j, (i + 2));
                    }
                    else
                        arr[j][i + 2] = temp + 16;
                    special_move(arr, (j+1), (i + 2));
                    special_move(arr, (j + 2), (i + 2));
                    special_move(arr, j, (i + 1));
                    special_move(arr, j, i);
                }
                else if ((j + 1) < r && (j - 1) >= 0 && (arr[j + 1][i] % 5) == temp && (arr[j - 1][i] % 5) == temp && (arr[j + 1][i]) < 21 && (arr[j - 1][i] < 21))
                {
                    if (arr[j][i] > 5)
                    {
                        special_move(arr, j, i);
                        arr[j][i] = temp + 16;
                        special_move(arr, j, i);
                    }
                    else
                        arr[j][i] = temp + 16;
                    special_move(arr, (j + 1), i);
                    special_move(arr, (j - 1), i);
                    special_move(arr, j, (i + 1));
                    special_move(arr, j, (i + 2));
                }
                else if ((j + 1) < r && (j - 1) >= 0 && (arr[j + 1][i + 1] % 5) == temp && (arr[j - 1][i + 1] % 5) == temp && (arr[j + 1][i + 1]) < 21 && (arr[j - 1][i + 1] < 21))
                {
                    if (arr[j][i+1] > 5)
                    {
                        special_move(arr, j, (i + 1));
                        arr[j][i+1] = temp + 16;
                        special_move(arr, j, (i+1));
                    }
                    else
                        arr[j][i + 1] = temp + 16;
                    special_move(arr, (j + 1), (i + 1));
                    special_move(arr, (j - 1), (i + 1));
                    special_move(arr, j, i);
                    special_move(arr, j, (i + 2));
                }
                else if ((j + 1) < r && (j - 1) >= 0 && (arr[j + 1][i + 2] % 5) == temp && (arr[j - 1][i + 2] % 5) == temp && (arr[j + 1][i + 2]) < 21 && (arr[j - 1][i + 2] < 21))
                {
                    if (arr[j][i + 2] > 5)
                    {
                        special_move(arr, j, (i + 2));
                        arr[j][i + 2] = temp + 16;
                        special_move(arr, j, (i + 2));
                    }
                    else
                        arr[j][i + 2] = temp + 16;
                    special_move(arr, (j + 1), (i + 2));
                    special_move(arr, (j - 1), (i + 2));
                    special_move(arr, j, i);
                    special_move(arr, j, (i + 1));
                }
                else if ((j - 2) >= 0 && (arr[j - 1][i] % 5) == temp && (arr[j - 2][i] % 5) == temp && (arr[j - 1][i]) < 21 && (arr[j - 2][i] < 21))
                {
                    if (arr[j][i] > 5)
                    {
                        special_move(arr, j, i);
                        arr[j][i] = temp + 16;
                        special_move(arr, j, i);
                    }
                    else
                        arr[j][i] = temp + 16;
                    special_move(arr, (j - 2), i);
                    special_move(arr, (j - 1), i);
                    special_move(arr, j, (i + 1));
                    special_move(arr, j , (i + 2));
                }
                else if ((j - 2) >= 0 && (arr[j - 1][i + 1] % 5) == temp && (arr[j - 2][i + 1] % 5) == temp && (arr[j - 1][i + 1]) < 21 && (arr[j - 2][i + 1] < 21))
                {
                    if (arr[j][i+1] > 5)
                    {
                        special_move(arr, j, (i + 1));
                        arr[j][i+1] = temp + 16;
                        special_move(arr, j, (i+1));
                    }
                    else
                        arr[j][i + 1] = temp + 16;
                    special_move(arr, (j - 2), (i + 1));
                    special_move(arr, (j - 1), (i + 1));
                    special_move(arr, j, i);
                    special_move(arr, j, (i + 2));
                }
                else if ((j - 2) >= 0 && (arr[j - 1][i + 2] % 5) == temp && (arr[j - 2][i + 2] % 5) == temp && (arr[j - 1][i + 2]) < 21 && (arr[j - 2][i + 2] < 21))
                {
                    if (arr[j][i + 2] > 5)
                    {
                        special_move(arr, j, (i + 2));
                        arr[j][i + 2] = temp + 16;
                        special_move(arr, j, (i + 2));
                    }
                    else
                        arr[j][i + 2] = temp + 16;
                    special_move(arr, (j - 2), (i + 2));
                    special_move(arr, (j - 1), (i + 2));
                    special_move(arr, j, (i + 1));
                    special_move(arr, j, i);
                }
            }
        }
    }
}
void check_strip(int arr[][c])   //value of horizontal stripe(6-10) and vertical stripe(11-15)
{

    for (int i = 0; i < c; i++) //check in column(horizontal stripe)
    {
        for (int j = 0; j < r - 3; j++) {
            int temp = 6;
            if (arr[j][i] != 21)
                temp = (arr[j][i] % 5);

            if ((arr[j + 1][i] % 5) == temp && (arr[j + 2][i] % 5) == temp && (arr[j + 3][i] % 5) == temp && arr[j + 1][i] < 21 && arr[j + 2][i] < 21 && arr[j + 3][i] < 21) {
                if(arr[j+2][i]>5)
                { 
                    special_move(arr, (j+2), i);
                    arr[j + 2][i] = temp + 6;
                    special_move(arr, (j + 2), i);
                }
                else
                    arr[j + 2][i] = temp + 6;
                special_move(arr, (j + 1), i);
                special_move(arr, (j + 3), i);
                special_move(arr, j , i);
            }
        }
    }
    for (int j = 0; j < r; j++) //check in row(vertical stripe)
    {
        for (int i = 0; i < c - 3; i++) {
            int temp = 6;
            if (arr[j][i] != 21)
                temp = (arr[j][i] % 5);
            if ((arr[j][i + 1] % 5) == temp && (arr[j][i + 2] % 5) == temp && (arr[j][i + 3] % 5) == temp && arr[j][i + 1] < 21 && arr[j][i + 2] < 21 && arr[j][i + 3] < 21) {
                if (arr[j][i + 2] > 5)
                {
                    special_move(arr, j, (i+2));
                    arr[j][i + 2] = temp + 11;
                    special_move(arr, j, (i + 2));
                }
                else
                    arr[j][i + 2] = temp + 11;
                special_move(arr, j, (i + 1));
                special_move(arr, j, (i + 3));
                special_move(arr, j, i );
            }
        }
    }
}
void simple(int arr[][c])
{
    for (int j = 0; j < r; j++)
    {
        for (int i = 0; i < c - 2; i++)
        {
            int temp = 6;
            if (arr[j][i] < 21)
                temp = (arr[j][i] % 5);
            if ((arr[j][i + 1] % 5) == temp && (arr[j][i + 2] % 5) == temp && arr[j][i + 1] < 21 && arr[j][i + 2] < 21)
            {
                special_move(arr, j, i);
                special_move(arr, j, (i + 1));
                special_move(arr, j, (i + 2));
            }
        }
    }
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < r - 2; j++)
        {
            int temp = 6;
            if (arr[j][i] < 21)
                temp = (arr[j][i] % 5);
            if ((arr[j + 1][i] % 5) == temp && (arr[j + 2][i] % 5) == temp && arr[j + 1][i] < 21 && arr[j + 2][i] < 21)
            {
                special_move(arr, j, i);
                special_move(arr, (j + 1), i);
                special_move(arr, (j + 2), i);
            }
        }
    }
}
void special_move(int arr[][c], int i, int j)
{
    if (arr[i][j] < 6 && arr[i][j]>=0)
        arr[i][j] = 0;
    else if (arr[i][j] < 16)
        striped_special(arr, i, j);
    else if (arr[i][j] < 21)
        wrapped_special(arr, i, j);
    else
        bomb_special(arr, i, j);
}
void striped_special(int arr[][c], int i, int j)
{
    if (arr[i][j] > 5 && arr[i][j] < 11)	//h_striped
    {
        arr[i][j] = 0;
        for (int k = 0; k < c; k++)
            special_move(arr, i, k);
    }
    if (arr[i][j] > 10 && arr[i][j] < 16)	//v_striped
    {
        arr[i][j] = 0;
        for (int k = 0; k < r; k++)
            special_move(arr, k, j);
    }
}
void wrapped_special(int arr[][c], int i, int j)
{
    if (arr[i][j] > 15 && arr[i][j] < 21)
    {
        arr[i][j] = -1;

        if (i - 1 >= 0) {
            special_move(arr, (i - 1), j);
            if (j + 1 < c)
            {
                special_move(arr, (i - 1), (j + 1));

                special_move(arr, i, (j + 1));
            }
            if (j - 1 >= 0)
            {
                special_move(arr, (i - 1), (j - 1));

                special_move(arr, i, (j - 1));
            }
        }
        if (i + 1 < r)
        {
            special_move(arr, (i + 1), j);
            if (j + 1 < c)
                special_move(arr, (i + 1), (j + 1));
            if (j - 1 >= 0)
                special_move(arr, (i + 1), (j - 1));
        }

    }
    fill(arr);
    for (int k = 1; k < r; k++)
        if (arr[k][j] == -1)
        {
            arr[k][j] = 0;

            if (k - 1 >= 0) {
                special_move(arr, (k - 1), j);
                if (j + 1 < c)
                {
                    special_move(arr, k, (j + 1));

                    special_move(arr, (k-1), (j + 1));
                }
                if (j - 1 >= 0)
                {
                    special_move(arr, (k - 1), (j - 1));

                    special_move(arr, k, (j - 1));
                }
            }
            if (k + 1 < r)
            {
                special_move(arr, (k + 1), j);
                if (j + 1 < c)
                    special_move(arr, (k + 1), (j + 1));
            
                if (j - 1 >= 0)
                    special_move(arr, (k + 1), (j - 1));         
            }
        }
}
void bomb_special(int arr[][c], int i, int j)
{
    arr[i][j] = 0;
    int temp = ((i * j) % 5);
    for (int m = 0; m < r; m++)
    {
        for (int n = 0; n < c; n++)
        {
            if ((arr[m][n]) % 5 == temp && arr[m][n] < 21)
                special_move(arr, m, n);
        }
    }
}
