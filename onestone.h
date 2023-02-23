#include<iostream>
using namespace std;
extern int N ;
extern int STEP[361];
extern int stone[19][19];
extern int stonex[19][19];
extern int stonexb[19][19];
extern int stonexw[19][19];
extern int firststone[8][19][19];
class onestone
{
public:
	onestone(int X, int Y, int Color, int Direct);
	onestone(int X, int Y, int Color);
	onestone(){}
	~onestone(){}
public:
	void SetSum1(int color);
	void ResetSum1(int color);
	int GetSum1(int color);
public:
	int GetX();
	int GetY();
private:
	int sum1;
	int x, y;
	int color;
	int direct;
};