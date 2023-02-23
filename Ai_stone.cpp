#include"Ai_stone.h"		
Ai_stone::Ai_stone(int A, int B, int Color)
{
	x = A;
	y = B;
	value1 = 0;
	color = Color;
}
Ai_stone::Ai_stone(Ai_stone &p)
{
	x = p.x;
	y = p.y;
	color = p.color;
	value1 = p.value1;
}
void Ai_stone::SetStone(int a, int b, int Color)
{
	x = a;
	y = b;
	color = Color;
}
int Ai_stone::GetStonex()
{
	return x;
}
int Ai_stone::GetStoney()
{
	return y;
}
int Ai_stone::GetStonecolor()
{
	return color;
}
void Ai_stone::SetValue1()
{
	value1 = 0;
}
