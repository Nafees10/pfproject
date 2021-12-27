const int c = 6;
const int r = 6;
void special_move(int arr[][c], int i, int j);
void striped_special(int arr[][c], int i, int j);
void wrapped_special(int arr[][c], int i, int j);
void bomb_special(int arr[][c], int i, int j);

void special_move(int arr[][c], int i, int j)
{
	if (arr[i][j] < 16)
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
		{
			if (arr[i][k] <= 5)
				arr[i][k] = 0;
			else
				special_move(arr, i, k);
		}
	}
	if (arr[i][j] > 10 && arr[i][j] < 16)	//v_striped
	{
		arr[i][j] = 0;
		for (int k = 0; k < r; k++)
		{
			if (arr[k][j] <= 5)
				arr[k][j] = 0;
			else
				special_move(arr, k, j);
		}
	}
}
void wrapped_special(int arr[][c], int i, int j)
{
	if (arr[i][j] > 15 && arr[i][j] < 21)
	{
		arr[i][j] = -1;
		
		if (i - 1 >= 0) {
			if (arr[i - 1][j] <= 5)
				arr[i - 1][j] = 0;
			else
				special_move(arr, (i-1), j);
			if (j + 1 < c)
			{
				if (arr[i - 1][j+1] <= 5)
					arr[i - 1][j+1] = 0;
				else
					special_move(arr, (i - 1), (j+1));
				if (arr[i][j + 1] <= 5)
					arr[i][j + 1] = 0;
				else
					special_move(arr, i, (j + 1));
			}
			if (j - 1 >=0)
			{
				if (arr[i - 1][j - 1] <= 5)
					arr[i - 1][j - 1] = 0;
				else
					special_move(arr, (i - 1), (j - 1));
				if (arr[i ][j - 1] <= 5)
					arr[i ][j - 1] = 0;
				else
					special_move(arr, i , (j - 1));
			}
		}
		if (i + 1 < r)
		{
			if(arr[i+1][j] <= 5)
				arr[i +1][j] = 0;
			else
				special_move(arr, (i - 1), j);
			if (j + 1 < c)
			{
				if (arr[i + 1][j + 1] <= 5)
					arr[i + 1][j + 1] = 0;
				else
					special_move(arr, (i + 1), (j + 1));
			}
			if (j - 1 >= 0)
			{
				if (arr[i +1][j - 1] <= 5)
					arr[i +1][j - 1] = 0;
				else
					special_move(arr, (i +1), (j - 1));
			}
		}
		
	}
	fill(arr, r);
	for(int k=1;k<r;k++)
		if (arr[k][j] == -1)
		{
			arr[k][j]=0;

			if (k- 1 >= 0) {
				if (arr[k- 1][j] <= 5)
					arr[k - 1][j] = 0;
				else
					special_move(arr, (k - 1), j);
				if (k + 1 < c)
				{
					if (arr[k-1][j + 1] <= 5)
						arr[k - 1][j + 1] = 0;
					else
						special_move(arr, (k - 1), (j + 1));
					if (arr[k][j + 1] <= 5)
						arr[k][j + 1] = 0;
					else
						special_move(arr, k, (j + 1));
				}
				if (j - 1 >= 0)
				{
					if (arr[k-1][j - 1] <= 5)
						arr[k-1][j - 1] = 0;
					else
						special_move(arr, (k - 1), (j - 1));
					if (arr[k][j - 1] <= 5)
						arr[k][j - 1] = 0;
					else
						special_move(arr, k, (j - 1));
				}
			}
			if (k + 1 < r)
			{
				if (arr[k + 1][j] <= 5)
					arr[k + 1][j] = 0;
				else
					special_move(arr, (k - 1), j);
				if (k + 1 < c)
				{
					if (arr[k + 1][j + 1] <= 5)
						arr[k + 1][j + 1] = 0;
					else
						special_move(arr, (k + 1), (j + 1));
				}
				if (j - 1 >= 0)
				{
					if (arr[k + 1][j - 1] <= 5)
						arr[k + 1][j - 1] = 0;
					else
						special_move(arr, (k + 1), (j - 1));
				}
			}
		}
}
void bomb_special(int arr[][c], int i, int j)
{

}
