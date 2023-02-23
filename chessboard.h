#include<iostream>
#include <graphics.h>
#include <conio.h>
#include <fstream>
#include"else.h"
#include"onestone.h"
//#include"Ai_stone.h"
//对黑棋n4b增大，白起就会堵黑棋

#define n1b 1;
#define n2bl 30;             //活二
#define n2bd 10;            //死二
#define n3b 100;                                                                          //连三变连四
#define n4b 1200;                                    //
#define n5b 5000;
#define n6b 5000;

#define n1w 3;
#define n2wl 100;
#define n2wd 30;
#define n3w 1000;                                                                          //连三变连四
#define n4w 1150;                                                                          //对冲五赋值，即下一子能成连五
#define n5w 9000;
#define n6w 9000;

using namespace std;

class chessboard
{
public:
	chessboard();
	chessboard(onestone One);
	~chessboard(){}
public:
	void Ai_computer1(int x, int y);
public:
	void initboard();                      // 初始化棋盘
public:
	void imgboard();                      //形成棋盘图形界面
public:
	void SetHumcolor(int a);              //此组为设置和返回玩家和电脑的棋子颜色,以及先行顺序
	void SetComcolot(int a);
	void SetFl(int a);
	int GetHumcolor();
	int GetComcolor();
	int GetFl();
public:
	void SeekMax1(int *step,int *valstep);                                         //  //寻找stonex的最大,并赋一个子的值
	void SeekMax2(int *step,int Step,int *valstep,int Valstep);                                         // //  //寻找stonex的最大,并赋两个子的值
	void SeekMaxFive(int *step,int *valstep);                                      //找出stonex最大的五组
	void SeekMax25(int *step1, int *step2, int Depth,int maxmin,int *valstep1,int *valstep2);                                      //找出stonex最大的五组
public:
	void SeekLine(int color);
	int GetSum(int color, int x);
public:
	void Makenextmove(int *coord, int step, int Depth,int maxmin);                                  //转换step的坐标
	void Maketextstep(int *coord, int step,int color);
	void Maketextstepreal(int *coord);                                          //真的下子
	void UnMakenextmove(int *coord);                                  //转换step的坐标
	int Alphabeta(int v1Alpha, int v1Beta, int Depth, int maxmin,int step);           //守
	int Alphabeta1(int v1Alpha, int v1Beta, int Depth, int maxmin, int step);           //攻
	int Evaluate(int *v1, int valstep);
	int Evaluate1(int *v1,int valstep);
	void complex(int *coordh,int *coordc,int *c4, int *c5,int *h5,int *c6, int *h6);
public:
	int GetStonex(int i, int j);
public:
	void SetNull();                                            //查找空穴并对将其投影至三维进行评估
	void ResetStonex();                               //对存储空穴值得stonex[19][19]清零
public:
	void Set0();														 //将stonex棋盘，stonexb棋盘，stonexw棋盘数据全部清零
	void SetNew();                                                       //包含在NewBegin函数中                               
public:
	void hummove();
	void commove();
	void NewBegin(int *fb);                                              //参数fb用来决定使用NEW之后的先后手
	void Loss();
	void BackMove();
	void Save1();                   //存档位置
	void Save2();                   //存档,颜色
	void Read1();                   //复盘位置
	void Read2();                   //存档颜色
private:
	onestone one;                          //一个棋子形成的对象
private:
	int humcolor;                          //玩家和电脑的棋子颜色和先行顺序，fl=1，玩家先行。fl=，
	int comcolor;
	int fl;                               //表示先后手    fl=1;黑子先行，fl=2，白子先行
	int way;                              //表示对战方式，way=1，人机对战；way=2，人人对战；
	int grade;                            //表示难度等级
private:
	int sum[2][6];                            
};