#include"else.h"
using namespace std;
int ox(int i){ return i * 40 - 13; }
int oy(int j){ return j * 40 - 13; }
int ii(int x)
{
	if ((x - 360) % 40 >= 20)
		return (x - 360) / 40 + 1;
	else
		return (x - 360) / 40;
}
int ij(int y)
{
	if ((y - 80) % 40 >= 20)
		return (y - 80) / 40 + 1;
	else
		return (y - 80) / 40;
}
int tx(int x)
{
	if ((x - 360) % 40 >= 20)
		return (x - 360) + 40 - (x - 360) % 40 - 13;
	else
		return (x - 360) - (x - 360) % 40 - 13;
}
int ty(int y)
{
	if ((y - 80) % 40 >= 20)
		return (y - 80) + 40 - (y - 80) % 40 - 13;
	else
		return (y - 80) - (y - 80) % 40 - 13;
}