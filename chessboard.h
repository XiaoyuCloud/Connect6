#include<iostream>
#include <graphics.h>
#include <conio.h>
#include <fstream>
#include"else.h"
#include"onestone.h"
//#include"Ai_stone.h"
//�Ժ���n4b���󣬰���ͻ�º���

#define n1b 1;
#define n2bl 30;             //���
#define n2bd 10;            //����
#define n3b 100;                                                                          //����������
#define n4b 1200;                                    //
#define n5b 5000;
#define n6b 5000;

#define n1w 3;
#define n2wl 100;
#define n2wd 30;
#define n3w 1000;                                                                          //����������
#define n4w 1150;                                                                          //�Գ��帳ֵ������һ���ܳ�����
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
	void initboard();                      // ��ʼ������
public:
	void imgboard();                      //�γ�����ͼ�ν���
public:
	void SetHumcolor(int a);              //����Ϊ���úͷ�����Һ͵��Ե�������ɫ,�Լ�����˳��
	void SetComcolot(int a);
	void SetFl(int a);
	int GetHumcolor();
	int GetComcolor();
	int GetFl();
public:
	void SeekMax1(int *step,int *valstep);                                         //  //Ѱ��stonex�����,����һ���ӵ�ֵ
	void SeekMax2(int *step,int Step,int *valstep,int Valstep);                                         // //  //Ѱ��stonex�����,���������ӵ�ֵ
	void SeekMaxFive(int *step,int *valstep);                                      //�ҳ�stonex��������
	void SeekMax25(int *step1, int *step2, int Depth,int maxmin,int *valstep1,int *valstep2);                                      //�ҳ�stonex��������
public:
	void SeekLine(int color);
	int GetSum(int color, int x);
public:
	void Makenextmove(int *coord, int step, int Depth,int maxmin);                                  //ת��step������
	void Maketextstep(int *coord, int step,int color);
	void Maketextstepreal(int *coord);                                          //�������
	void UnMakenextmove(int *coord);                                  //ת��step������
	int Alphabeta(int v1Alpha, int v1Beta, int Depth, int maxmin,int step);           //��
	int Alphabeta1(int v1Alpha, int v1Beta, int Depth, int maxmin, int step);           //��
	int Evaluate(int *v1, int valstep);
	int Evaluate1(int *v1,int valstep);
	void complex(int *coordh,int *coordc,int *c4, int *c5,int *h5,int *c6, int *h6);
public:
	int GetStonex(int i, int j);
public:
	void SetNull();                                            //���ҿ�Ѩ���Խ���ͶӰ����ά��������
	void ResetStonex();                               //�Դ洢��Ѩֵ��stonex[19][19]����
public:
	void Set0();														 //��stonex���̣�stonexb���̣�stonexw��������ȫ������
	void SetNew();                                                       //������NewBegin������                               
public:
	void hummove();
	void commove();
	void NewBegin(int *fb);                                              //����fb��������ʹ��NEW֮����Ⱥ���
	void Loss();
	void BackMove();
	void Save1();                   //�浵λ��
	void Save2();                   //�浵,��ɫ
	void Read1();                   //����λ��
	void Read2();                   //�浵��ɫ
private:
	onestone one;                          //һ�������γɵĶ���
private:
	int humcolor;                          //��Һ͵��Ե�������ɫ������˳��fl=1��������С�fl=��
	int comcolor;
	int fl;                               //��ʾ�Ⱥ���    fl=1;�������У�fl=2����������
	int way;                              //��ʾ��ս��ʽ��way=1���˻���ս��way=2�����˶�ս��
	int grade;                            //��ʾ�Ѷȵȼ�
private:
	int sum[2][6];                            
};