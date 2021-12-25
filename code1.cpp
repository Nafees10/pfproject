//#include<iostream> 
//#include<stdlib.h> 
//using namespace std;
//const int c = 6;
//void fill(int arr[][c], int r);
//int main()
//{
//    int arr[6][c] = { 0 };
//    
//    fill(arr, 6);
//    return 0;
//}
//
//void fill(int arr[][c], int r)
//{
//    for (int j = 0; j < r; j++)
//    {
//        for (int k = 0; k < c; k++)
//        {
//            if (arr[0][k] == 0)
//                arr[0][k] = rand() % 5 + 1;
//            if (arr[j][k] == 0)
//            {
//                int i = 1;
//                while (j - i >= 0) {
//                    arr[j - i + 1][k] = arr[j - i][k];
//                    arr[j - i][k] = 0;
//                    i++;
//                }
//            }
//            if (arr[0][k] == 0)
//                arr[0][k] = rand() % 5 + 1;
//        }
//    }
//    for (int j = 0; j < r; j++)
//    {
//        for (int k = 0; k < c; k++)
//        {
//            cout << arr[j][k];
//        }
//        cout << endl;
//    }
//}