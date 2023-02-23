#include<iostream>
using namespace std;
class Ai_stone
{
public:
	Ai_stone(int A, int B, int Color);
	Ai_stone(){};
	~Ai_stone(){}
	Ai_stone(Ai_stone &p);
public:
	void SetStone(int a, int b, int Color);
	void SetValue1();
	int GetStonex();
	int GetStoney();
	int GetStonecolor();

public:
	friend class sixstones;
private:
	int value1;
	int color;
	int x, y;
	//	int direct;                                            
	//	int involve;
};