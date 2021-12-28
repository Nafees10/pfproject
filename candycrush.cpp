#include<iostream> 
#include<stdlib.h> 

using namespace std;

const int c = 9;
const int r = 9;

void checkoverall(int arr[][c],int r1,int c1,int r2,int c2); //checks if special candies are moved or not
void special_special(int arr[][c], int r1, int c1, int r2, int c2); // effect of two special candies mixed together 
void fill(int arr[][c]);//after any combinations fills grid again
void check_bomb(int arr[][c]);//checks if any color bomb is forming
void check_wrap(int arr[][c]);//checks for wrapped candy
void check_strip(int arr[][c]);//checks formation of striped candy
void simple(int arr[][c]);//checks any combination
void special_move(int arr[][c], int i, int j);//choosing between functions of special candies or 0
void striped_special(int arr[][c], int i, int j);// special effect of striped
void wrapped_special(int arr[][c], int i, int j);//special effect of wrapped
void bomb_special(int arr[][c], int i, int j);//special effect of bomb if exploded due to other candy's special effect

int main()
{
    int arr[r][c] = { 0 };
    
    
    fill(arr);
    arr[3][3] = 19;
    arr[3][4] = 16;
    check_bomb(arr);
    fill(arr);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
    system("pause");
    checkoverall(arr, 3,3, 3, 4);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cout << arr[i][j]<<" ";
        cout << endl;
    }
    
    return 0;
}

void checkoverall(int arr[][c], int r1, int c1, int r2, int c2)
{
    if ((arr[r1][c1] > 5 && arr[r2][c2] > 5) || arr[r1][c1]==21||arr[r2][c2]==21)
        special_special(arr, r1, c1, r2, c2);
    else
    {
        check_bomb(arr);
        check_wrap(arr);
        check_strip(arr);
        simple(arr);
    }
}
void special_special(int arr[][c], int r1, int c1, int r2, int c2)
{
    if (arr[r1][c1] > 5 && arr[r1][c1] < 16 && arr[r2][c2]>5 && arr[r2][c2] < 16)
    {
        arr[r1][c1] = 0;
        arr[r2][c2] = 0;
        for (int k = 0; k < c; k++)
            special_move(arr, r2, k);
        for (int k = 0; k < r; k++)
            special_move(arr, k, c2);
    }
    if ((arr[r1][c1] > 5 && arr[r1][c1] < 16 && arr[r2][c2]>15 && arr[r2][c2] < 21) || (arr[r2][c2] > 5 && arr[r2][c2] < 16 && arr[r1][c1]>15 && arr[r1][c1] < 21))
    {
        arr[r1][c1] = 0;
        arr[r2][c2] = 0;
        for (int k = 0; k < c; k++)
            special_move(arr, r2, k);
        for (int k = 0; k < r; k++)
            special_move(arr, k, c2);
        if (r2 + 1 < r)
        {
            for (int k = 0; k < c; k++)
                special_move(arr, (r2+1), k);
        }
        if (r2 - 1 >= 0)
        {
            for (int k = 0; k < c; k++)
                special_move(arr, (r2 - 1), k);
        }
        if (c2 + 1 < r)
        {
            for (int k = 0; k < r; k++)
                special_move(arr, k, (c2+1));
        }
        if (c2 - 1 >= 0)
        {
            for (int k = 0; k < r; k++)
                special_move(arr, k, (c2-1));
        }
    }
    if (arr[r1][c1] > 15 && arr[r1][c1] < 21 && arr[r2][c2] > 15 && arr[r2][c2] < 21)
    {
        arr[r1][c1] = -2;
        arr[r2][c2] = -2;
        if (c1 + 1 < c)
            special_move(arr, r1, (c1 + 1));
        if (c1 - 1 >= 0)
            special_move(arr, r1, (c1 - 1));
        if (c1 + 2 < c)
            special_move(arr, r1, (c1 + 2));
        if (c1 - 2 >= 0)
            special_move(arr, r1, (c1 - 2));

        if (r1 - 1 >= 0) {
            special_move(arr, (r1 - 1), c1);
            if (c1 + 1 < c)
                special_move(arr, (r1-1), (c1 + 1));
            if (c1 - 1 >= 0)
                special_move(arr, (r1-1), (c1 - 1));
            if (c1 + 2 < c)
                special_move(arr, (r1-1), (c1 + 2));
            if (c1 - 2 >= 0)
                special_move(arr, (r1-1), (c1 - 2));
        }
        if (r1 + 1 < r)
        {
            special_move(arr, (r1 + 1), c1);
            if (c1 + 1 < c)
                special_move(arr, (r1 + 1), (c1 + 1));
            if (c1 - 1 >= 0)
                special_move(arr, (r1 + 1), (c1 - 1));
            if (c1 + 2 < c)
                special_move(arr, (r1 + 1), (c1 + 2));
            if (c1 - 2 >= 0)
                special_move(arr, (r1 + 1), (c1 - 2));
        }
        if (r1 - 2 >= 0) {
            special_move(arr, (r1 - 2), c1);
            if (c1 + 1 < c)
                special_move(arr, (r1 - 2), (c1 + 1));
            if (c1 - 1 >= 0)
                special_move(arr, (r1 - 2), (c1 - 1));
            if (c1 + 2 < c)
                special_move(arr, (r1 - 2), (c1 + 2));
            if (c1 - 2 >= 0)
                special_move(arr, (r1 - 2), (c1 - 2));
        }
        if (r1 + 2 >= 0) {
            special_move(arr, (r1 + 2), c1);
            if (c1 + 1 < c)
                special_move(arr, (r1 + 2), (c1 + 1));
            if (c1 - 1 >= 0)
                special_move(arr, (r1 + 2), (c1 - 1));
            if (c1 + 2 < c)
                special_move(arr, (r1 + 2), (c1 + 2));
            if (c1 - 2 >= 0)
                special_move(arr, (r1 + 2), (c1 - 2));
        }
        if (c2 + 1 < c)
            special_move(arr, r2, (c2 + 1));
        if (c2 - 1 >= 0)
            special_move(arr, r2, (c2 - 1));
        if (c2 + 2 < c)
            special_move(arr, r2, (c2 + 2));
        if (c2 - 2 >= 0)
            special_move(arr, r2, (c2 - 2));

        if (r2 - 1 >= 0) {
            special_move(arr, (r2 - 1), c2);
            if (c2 + 1 < c)
                special_move(arr, (r2 - 1), (c2 + 1));
            if (c2 - 1 >= 0)
                special_move(arr, (r2 - 1), (c2 - 1));
            if (c2 + 2 < c)
                special_move(arr, (r2 - 1), (c2 + 2));
            if (c2 - 2 >= 0)
                special_move(arr, (r2 - 1), (c2 - 2));
        }
        if (r2 + 1 < r)
        {
            special_move(arr, (r2 + 1), c2);
            if (c2 + 1 < c)
                special_move(arr, (r2 + 1), (c2 + 1));
            if (c2 - 1 >= 0)
                special_move(arr, (r2 + 1), (c2 - 1));
            if (c2 + 2 < c)
                special_move(arr, (r2 + 1), (c2 + 2));
            if (c2 - 2 >= 0)
                special_move(arr, (r2 + 1), (c2 - 2));
        }
        if (r2 - 2 >= 0) {
            special_move(arr, (r2 - 2), c2);
            if (c2 + 1 < c)
                special_move(arr, (r2 - 2), (c2 + 1));
            if (c2 - 1 >= 0)
                special_move(arr, (r2 - 2), (c2 - 1));
            if (c2 + 2 < c)
                special_move(arr, (r2 - 2), (c2 + 2));
            if (c2 - 2 >= 0)
                special_move(arr, (r2 - 2), (c2 - 2));
        }
        if (r2 + 2 >= 0) {
            special_move(arr, (r2 + 2), c2);
            if (c2 + 1 < c)
                special_move(arr, (r2 + 2), (c2 + 1));
            if (c2 - 1 >= 0)
                special_move(arr, (r2 + 2), (c2 - 1));
            if (c2 + 2 < c)
                special_move(arr, (r2 + 2), (c2 + 2));
            if (c2 - 2 >= 0)
                special_move(arr, (r2 + 2), (c2 - 2));
        }
        fill(arr);
        while (arr[r1][c1] != -2)
            r1++;
        while (arr[r2][c2] != -2)
            r2++;
        arr[r1][c1] = 0;
        arr[r2][c2] = 0;

        if (c1 + 1 < c)
            special_move(arr, r1, (c1 + 1));
        if (c1 - 1 >= 0)
            special_move(arr, r1, (c1 - 1));
        if (c1 + 2 < c)
            special_move(arr, r1, (c1 + 2));
        if (c1 - 2 >= 0)
            special_move(arr, r1, (c1 - 2));

        if (r1 - 1 >= 0) {
            special_move(arr, (r1 - 1), c1);
            if (c1 + 1 < c)
                special_move(arr, (r1 - 1), (c1 + 1));
            if (c1 - 1 >= 0)
                special_move(arr, (r1 - 1), (c1 - 1));
            if (c1 + 2 < c)
                special_move(arr, (r1 - 1), (c1 + 2));
            if (c1 - 2 >= 0)
                special_move(arr, (r1 - 1), (c1 - 2));
        }
        if (r1 + 1 < r)
        {
            special_move(arr, (r1 + 1), c1);
            if (c1 + 1 < c)
                special_move(arr, (r1 + 1), (c1 + 1));
            if (c1 - 1 >= 0)
                special_move(arr, (r1 + 1), (c1 - 1));
            if (c1 + 2 < c)
                special_move(arr, (r1 + 1), (c1 + 2));
            if (c1 - 2 >= 0)
                special_move(arr, (r1 + 1), (c1 - 2));
        }
        if (r1 - 2 >= 0) {
            special_move(arr, (r1 - 2), c1);
            if (c1 + 1 < c)
                special_move(arr, (r1 - 2), (c1 + 1));
            if (c1 - 1 >= 0)
                special_move(arr, (r1 - 2), (c1 - 1));
            if (c1 + 2 < c)
                special_move(arr, (r1 - 2), (c1 + 2));
            if (c1 - 2 >= 0)
                special_move(arr, (r1 - 2), (c1 - 2));
        }
        if (r1 + 2 >= 0) {
            special_move(arr, (r1 + 2), c1);
            if (c1 + 1 < c)
                special_move(arr, (r1 + 2), (c1 + 1));
            if (c1 - 1 >= 0)
                special_move(arr, (r1 + 2), (c1 - 1));
            if (c1 + 2 < c)
                special_move(arr, (r1 + 2), (c1 + 2));
            if (c1 - 2 >= 0)
                special_move(arr, (r1 + 2), (c1 - 2));
        }
        if (c2 + 1 < c)
            special_move(arr, r2, (c2 + 1));
        if (c2 - 1 >= 0)
            special_move(arr, r2, (c2 - 1));
        if (c2 + 2 < c)
            special_move(arr, r2, (c2 + 2));
        if (c2 - 2 >= 0)
            special_move(arr, r2, (c2 - 2));

        if (r2 - 1 >= 0) {
            special_move(arr, (r2 - 1), c2);
            if (c2 + 1 < c)
                special_move(arr, (r2 - 1), (c2 + 1));
            if (c2 - 1 >= 0)
                special_move(arr, (r2 - 1), (c2 - 1));
            if (c2 + 2 < c)
                special_move(arr, (r2 - 1), (c2 + 2));
            if (c2 - 2 >= 0)
                special_move(arr, (r2 - 1), (c2 - 2));
        }
        if (r2 + 1 < r)
        {
            special_move(arr, (r2 + 1), c2);
            if (c2 + 1 < c)
                special_move(arr, (r2 + 1), (c2 + 1));
            if (c2 - 1 >= 0)
                special_move(arr, (r2 + 1), (c2 - 1));
            if (c2 + 2 < c)
                special_move(arr, (r2 + 1), (c2 + 2));
            if (c2 - 2 >= 0)
                special_move(arr, (r2 + 1), (c2 - 2));
        }
        if (r2 - 2 >= 0) {
            special_move(arr, (r2 - 2), c2);
            if (c2 + 1 < c)
                special_move(arr, (r2 - 2), (c2 + 1));
            if (c2 - 1 >= 0)
                special_move(arr, (r2 - 2), (c2 - 1));
            if (c2 + 2 < c)
                special_move(arr, (r2 - 2), (c2 + 2));
            if (c2 - 2 >= 0)
                special_move(arr, (r2 - 2), (c2 - 2));
        }
        if (r2 + 2 >= 0) {
            special_move(arr, (r2 + 2), c2);
            if (c2 + 1 < c)
                special_move(arr, (r2 + 2), (c2 + 1));
            if (c2 - 1 >= 0)
                special_move(arr, (r2 + 2), (c2 - 1));
            if (c2 + 2 < c)
                special_move(arr, (r2 + 2), (c2 + 2));
            if (c2 - 2 >= 0)
                special_move(arr, (r2 + 2), (c2 - 2));
        }
    }
    if ((arr[r1][c1] == 21 && arr[r2][c2] < 5 && arr[r2][c2] > 0) || (arr[r2][c2] == 21 && arr[r1][c1] < 5 && arr[r1][c1] > 0))
    {
        int temp = arr[r1][c1] % 5 + 1;
        if (arr[r1][c1] > arr[r2][c2])
            temp = arr[r2][c2] % 5 + 1;
        arr[r1][c1] = 0;
        arr[r2][c2] = 0;
        for (int row = 0; row < r; row++)
        {
            for (int col = 0; col < c; col++)
            {
                if(arr[row][col]!=21 && (arr[row][col]%5+1==temp))
                    special_move(arr, row, col);
            }
        }
            
    }
    if ((arr[r1][c1] == 21 && arr[r2][c2] > 5 && arr[r2][c2] < 16) || (arr[r2][c2] == 21 && arr[r1][c1] < 16 && arr[r1][c1] > 5))
    {
        int temp = arr[r1][c1] % 5 + 1;
        if (arr[r1][c1] > arr[r2][c2])
            temp = arr[r2][c2] % 5 + 1;
        arr[r1][c1] = 0;
        arr[r2][c2] = 0;
        bool b = 0;
        for (int row = 0; row < r; row++)
        {
            for (int col = 0; col < c; col++)
            {
                if (arr[row][col] != 21 && (arr[row][col] % 5 + 1 == temp))
                { 
                    if (arr[row][col] > 15)
                        arr[row][col] -= 5;
                    else if (arr[row][col] < 6)
                    {
                        if (!b)
                        {
                            b = 1;
                            arr[row][col] += 5;
                        }
                        else
                        {
                            b = 0;
                            arr[row][col] += 10;
                        }
                    }
                    special_move(arr, row, col);
                }
                    
            }
        }

    }
    if ((arr[r1][c1] == 21 && arr[r2][c2] > 15 && arr[r2][c2] < 21) || (arr[r2][c2] == 21 && arr[r1][c1] > 15 && arr[r1][c1] < 21))
    {
        int temp = arr[r1][c1] % 5 + 1;
        if (arr[r1][c1] > arr[r2][c2])
            temp = arr[r2][c2] % 5 + 1;
        arr[r1][c1] = 0;
        arr[r2][c2] = 0;
        
        for (int row = 0; row < r; row++)
        {
            for (int col = 0; col < c; col++)
            {
                if (arr[row][col] != 21 && (arr[row][col] % 5 + 1 == temp))
                {
                    while (arr[row][col] < 16)
                        arr[row][col] += 5;
                    special_move(arr, row, col);
                }

            }
        }

    }
    if (arr[r1][c1] == 21 && arr[r2][c2] == 21)
        arr = { 0 };
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
        for (int i = 0; i < c - 2; i++) {
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
    else if(arr[i][j]==21)
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
        if (j + 1 < c)
            special_move(arr, i, (j + 1));
        if (j - 1 >= 0)
            special_move(arr, i, (j - 1));
        if (i - 1 >= 0) {
            special_move(arr, (i - 1), j);
            if (j + 1 < c)
                special_move(arr, (i - 1), (j + 1));
            if (j - 1 >= 0)
                special_move(arr, (i - 1), (j - 1));
        }
        if (i + 1 < r)
        {
            special_move(arr, (i + 1), j);
            if (j + 1 < c)
                special_move(arr, (i + 1), (j + 1));
            if (j - 1 >= 0)
                special_move(arr, (i + 1), (j - 1));
        }
        fill(arr);
        for (int k = 1; k < r; k++) {
            if (arr[k][j] == -1)
            {
                arr[k][j] = 0;
                if (j + 1 < c)
                    special_move(arr, k, (j + 1));
                if (j - 1 >= 0)
                    special_move(arr, k, (j - 1));
                if (k - 1 >= 0) {
                    special_move(arr, (k - 1), j);
                    if (j + 1 < c)
                        special_move(arr, (k - 1), (j + 1));
                    if (j - 1 >= 0)
                        special_move(arr, (k - 1), (j - 1));
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
