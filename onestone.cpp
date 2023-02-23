#include"onestone.h"
onestone::onestone(int X, int Y, int Color, int Direct) : x(X), y(Y), color(Color), direct(Direct), sum1(0){}
onestone::onestone(int X, int Y, int Color) : x(X), y(Y), color(Color), direct(4), sum1(0){}
void onestone::SetSum1(int color)
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (stone[i][j] == color&&stone[i + 1][j] == 0 && stone[i+1][j + 1] == 0 && stone[i][j + 1] == 0 && stone[i - 1][j + 1] == 0&&stone[i-1][j]==0 && stone[i - 1][j - 1] == 0 &&stone[i][j-1]==0&& stone[i + 1][j - 1] == 0
				&&stone[i + 2][j] == 0 && stone[i + 2][j + 2] == 0 && stone[i][j + 2] == 0 && stone[i - 2][j + 2] == 0 && stone[i - 2][j] == 0 && stone[i - 2][j - 2] == 0 && stone[i][j - 2] == 0 && stone[i + 2][j - 2] == 0)
			{
				sum1++;
				x = i;
				y = j;			
			}
		}
	}
}
void onestone::ResetSum1(int color){ sum1 = 0; }
int onestone::GetSum1(int color){ return sum1; }
int onestone::GetX(){ return x; }
int onestone::GetY(){ return y; }