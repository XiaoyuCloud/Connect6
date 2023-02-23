#include"chessboard.h"
int N;
int STEP[361];
int stone[19][19];
int stonex[19][19];
int stonexb[19][19];
int stonexw[19][19];
int firststone[8][19][19];				//存储首子的位置方向和值，黑子为正，白子为负,黑子1，白子用2
int mvBesth=7240;
int mvBestc = 7240;
chessboard::chessboard(onestone One) :one(One), humcolor(1), comcolor(2), fl(1), way(1), grade(3)
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
			stonex[i][j] = 0;
	}
	for (int c = 0; c < 2; c++)
	{
		for (int x = 0; x < 6; x++)
			sum[c][x] = 0;
	}
}
void chessboard::Set0()                                   //将stonex棋盘，stonexb棋盘，stonexw,firststone棋盘数据全部清零
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			stonex[i][j] = 0;
			stonexb[i][j] = 0;
			stonexw[i][j] = 0;
		}
	}
	for (int c = 0; c < 2; c++)
	{
		for (int x = 0; x < 7; x++)
		{
			sum[c][x] = 0;
		}
	}
	for (int direct = 0; direct < 8; direct++)
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
				firststone[direct][i][j] = 0;
		}
	}
}
void chessboard::Save1()
{
	ofstream in;
	in.open("存档.txt", ios::trunc); //ios::trunc表示在打开文件前将文件清空,由于是写入,文件不存在则创建
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			in <<stone[i][j] << " ";
		}
		cout << endl;
	}
	in.close();
}
void chessboard::Save2()
{
	ofstream in;
	in.open("颜色.txt", ios::trunc); //ios::trunc表示在打开文件前将文件清空,由于是写入,文件不存在则创建
	in << humcolor << " " << comcolor<<" "<<grade;
	in.close();
}
void chessboard::Read1()
{
	IMAGE imgb;
	IMAGE imgw;
	IMAGE img;
	loadimage(&img, _T("棋盘.jpg"));
	putimage(-16, -16, &img);
	loadimage(&imgb, _T("black.jpg"));
	loadimage(&imgw, _T("white.jpg"));
	ifstream ifile("存档.txt");
	if (!ifile)
	{
		cerr << "error." << endl;
	}
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			ifile >> stone[i][j];
		}
	}
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (stone[i][j] == 1)
			{
				putimage(ox(j), oy(i), &imgb);
			}
			else if (stone[i][j] == 2)
			{
				putimage(ox(j), oy(i), &imgw);
			}
		}
	}
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			stonex[i][j] = 0;
			stonexb[i][j] = 0;
			stonexw[i][j] = 0;
		}
	}
	for (int c = 0; c < 2; c++)
	{
		for (int x = 0; x < 7; x++)
		{
			sum[c][x] = 0;
		}
	}
	for (int direct = 0; direct < 8; direct++)
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
				firststone[direct][i][j] = 0;
		}
	}
}
void chessboard::Read2()
{
	ifstream ifile("颜色.txt");
	int color[3];
	if (!ifile)
	{
		cerr << "error." << endl;
	}
	for (int i = 0; i < 3; i++)
	{
			ifile >> color[i];
	}
	humcolor = color[0];
	comcolor = color[1];
	grade = color[2];
}
void chessboard::BackMove()
{
	IMAGE img;
	loadimage(&img, _T("小棋盘.jpg"));
	int p = (STEP[N] - (STEP[N]) % 19) / 19;
	int q = (STEP[N]) % 19;
	stone[p][q] = 0;
	putimage(ox(q), oy(p)-1, &img);
	N = N - 1;
}
void chessboard::SetHumcolor(int a)                     //此组为设置和返回玩家和电脑的棋子颜色,以及先行顺序
{
	humcolor = a;
}
void chessboard::SetComcolot(int a)
{
	comcolor = a;
}
void chessboard::SetFl(int a){ fl = a; }
int chessboard::GetHumcolor(){ return humcolor; }
int chessboard::GetComcolor(){ return comcolor; }
int chessboard::GetFl(){ return fl; }
void chessboard::Ai_computer1(int i, int j)
{
	IMAGE imgw1;
	IMAGE imgw2;
	if (comcolor == 2)
	{
		loadimage(&imgw2, _T("white.jpg"));                                        //注意加载的图片要依据选择的黑白子颜色而定
		putimage(ox(j), oy(i), &imgw2);
	}
	if (comcolor == 1)
	{
		loadimage(&imgw1, _T("black.jpg"));                                        //注意加载的图片要依据选择的黑白子颜色而定
		putimage(ox(j), oy(i), &imgw1);
	}
	stone[i][j] = comcolor;
}
void chessboard::SetNew()
{
	humcolor = comcolor = 0;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			stone[i][j] = 0;
			stonex[i][j] = 0;
			stonexb[i][j] = 0;
			stonexw[i][j] = 0;
		}
	}
	for (int c = 0; c < 2; c++)
	{
		for (int x = 0; x < 7; x++)
		{
			sum[c][x] = 0;
		}
	}
	for (int direct = 0; direct < 8; direct++)
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
				firststone[direct][i][j] = 0;
		}
	}
}
void chessboard::Loss()
{
	IMAGE img;
	loadimage(&img, _T("棋盘.jpg"));
	putimage(-16, -16, &img);
	HWND wnd = GetHWnd();
	MessageBox(wnd, TEXT("你认输了！"), TEXT("结果"), MB_OK | MB_ICONWARNING);
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			stone[i][j] = 0;
			stonex[i][j] = 0;
			stonexb[i][j] = 0;
			stonexw[i][j] = 0;
		}
	}
	for (int c = 0; c < 2; c++)
	{
		for (int x = 0; x < 7; x++)
		{
			sum[c][x] = 0;
		}
	}
	for (int direct = 0; direct < 8; direct++)
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
				firststone[direct][i][j] = 0;
		}
	}
}
void chessboard::NewBegin(int *fb)
{
	IMAGE img;
	loadimage(&img, _T("棋盘.jpg"));
	putimage(-16, -16, &img);
	SetNew();
	HWND wnd = GetHWnd();
	if (MessageBox(wnd, TEXT("人机对战请选“是”，人人对战请选“否”。"), TEXT("选择对战方式"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		if (MessageBox(wnd, TEXT(" 选择黑子请点“是”，选择白子请点“否”。"), TEXT("选择黑白子"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			humcolor = 1;
			comcolor = 2;
			*fb = 1;
		}
		else
		{
			humcolor = 2;
			comcolor = 1;
			*fb = 2;
		}
		way = 1;
		if (MessageBox(wnd, TEXT(" 是否选择高难度。"), TEXT("选择难度"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			grade = 3;
		}
		else if (MessageBox(wnd, TEXT(" 是否选择中难度。"), TEXT("选择难度"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			grade = 2;
		}
		else if (MessageBox(wnd, TEXT(" 是否选择低难度。"), TEXT("选择难度"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			grade = 1;
		}
	}
	else
	{
		humcolor = 1;
		comcolor = 2;
		fl = 1;
		way = 2;
	}
}
void chessboard::hummove()                                                            //参考http://tieba.baidu.com/p/1745203754
{
	IMAGE img1;
	IMAGE img2;
	MOUSEMSG m;	
	int flag = 0;
	loadimage(&img1, _T("black.jpg"));
	loadimage(&img2, _T("white.jpg"));
	if (fl == 1||fl==-1)                                                                       //fl=1,则黑子先行一步，再令fl=0，之后黑子一直走两步
	{
		while (true)
		{
			m = GetMouseMsg(); // 获取鼠标消息
			//记录第一次鼠标坐标
			int fb = 0;
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (m.x >= 360 && m.x <= 1080 && m.y >= 80 && m.y <= 800)
				{
					if (stone[ij(m.y)][ii(m.x)] == 0)
					{
						if (humcolor == 1)
						{
							putimage(tx(m.x), ty(m.y), &img1);
						}
						else
						{
							putimage(tx(m.x), ty(m.y), &img2);
						}
						stone[ij(m.y)][ii(m.x)] = humcolor;
						STEP[N] = ij(m.y) * 19 + ii(m.x);
						N++;
						fl = 0;
					}                                                                       //注意行列变换
				}
				else
				{
					fl = 1;
				}
				if (m.x >= 90 && m.x <= 270 && m.y >= 60 && m.y <= 180)
				{
					NewBegin(&fb);
					if (fb == 1)
					{
						fl = -1;
					}
					else if (fb == 2)
					{
						fl = -2;
					}
				}
				if (m.x >= 90 && m.x <= 270 && m.y >= 240 && m.y <= 360)
				{
					BackMove();
					fl = -2;
				}
				if (m.x >= 90 && m.x <= 270 && m.y >= 420 && m.y <= 540)
				{
					Loss();
					if (comcolor == 2)
					{
						fl = -1;
					}
					else if (comcolor == 2)
					{
						fl = -2;
					}

				}
				if (m.x >= 90 && m.x <= 270 && m.y >= 600 && m.y <= 720)
				{
					Save1();
					Save2();
					fl = -1;
				}
				if (m.x >= 90 && m.x <= 270 && m.y >= 780 && m.y <= 900)
				{
					Read1();
					Read2();
					int nh = 0, nc = 0;
					for (int i = 0; i < 19; i++)
					{
						for (int j = 0; j < 19; j++)
						{
							if (stone[i][j] == humcolor)
							{
								nh++;
							}
							else if (stone[i][j] == comcolor)
							{
								nc++;
							}
						}
					}
					if (nh == nc - 1)
					{
						fl = -2;
					}
					else if (nh==nc)
					{
						fl = -3;
					}
				}
			}
			if (fl == 0||fl==-1||fb==2||fl==-2)
			{
				break;
			}
		}
	}
	else
	{
		    int fb=0;
			while (flag != 2&&fl!=-1&&fb!=2)
			{
				m = GetMouseMsg(); // 获取鼠标消息
				//记录第一次鼠标坐标
				if (m.uMsg == WM_LBUTTONDOWN&& flag == 0)
				{
					if (m.x >= 360 && m.x <= 1080 && m.y >= 80 && m.y <= 800)
					{
						if (stone[ij(m.y)][ii(m.x)] == 0)
						{
							if (humcolor == 1)
							{
								putimage(tx(m.x), ty(m.y), &img1);
							}
							else
							{
								putimage(tx(m.x), ty(m.y), &img2);
							}
							stone[ij(m.y)][ii(m.x)] = humcolor;
							STEP[N] = ij(m.y) * 19 + ii(m.x);
							N++;
							flag = 1;
						}                                   //注意行列变换
					}
					else
					{
						flag = 0;
					}
					if (m.x >= 90 && m.x <= 270 && m.y >= 60 && m.y <= 180)
					{
						NewBegin(&fb);
						if (fb == 1)
						{
							fl = -1;
						}
						else if (fb == 2)
						{
							fl = -2;
						}
					}                                                                        //注意行列变换
					if (m.x >= 90 && m.x <= 270 && m.y >= 240 && m.y <= 360)
					{
						BackMove();
						fl = -2;
						flag = 2;
					}
					if (m.x >= 90 && m.x <= 270 && m.y >= 420 && m.y <= 540)
					{
						Loss();
						if (comcolor == 2)
						{
							fl = -1;

						}
						else if (comcolor ==2)
						{
							fl = -2;
						}
						flag = 2;
					}
					if (m.x >= 90 && m.x <= 270 && m.y >= 600 && m.y <= 720)
					{
						Save1();
						Save2();
					}
					if (m.x >= 90 && m.x <= 270 && m.y >= 780 && m.y <= 900)
					{
						Read1();
						Read2();
					}
					if (m.x >= 90 && m.x <= 270 && m.y >= 780 && m.y <= 900)
					{
						Read1();
						Read2();
						int nh = 0, nc = 0;
						for (int i = 0; i < 19; i++)
						{
							for (int j = 0; j < 19; j++)
							{
								if (stone[i][j] == humcolor)
								{
									nh++;
								}
								else if (stone[i][j] == comcolor)
								{
									nc++;
								}
							}
						}
						if (nh == nc - 1)
						{
							flag = 0;
						}
						else if (nh == nc)
						{
							flag = 1;
						}
					}
				}
				//记录第二次鼠标坐标
				else if (m.uMsg == WM_LBUTTONDOWN&& flag == 1)
				{
					int cundang = 0;//用来控制存档
					if (m.x >= 360 && m.x <= 1080 && m.y >= 80 && m.y <= 800)
					{
						if (stone[ij(m.y)][ii(m.x)] == 0)
						{
							if (humcolor == 1)
							{
								putimage(tx(m.x), ty(m.y), &img1);
							}
							else
							{
								putimage(tx(m.x), ty(m.y), &img2);
							}
							stone[ij(m.y)][ii(m.x)] = humcolor;
							STEP[N] = ij(m.y) * 19 + ii(m.x);
							N++;
							fl = 3;
						}                                 //注意行列变换
					}
					else
					{
						fl = 1;
					}
					if (m.x >= 90 && m.x <= 270 && m.y >= 60 && m.y <= 180)
					{
						int fb;
						NewBegin(&fb);
						if (fb == 1)
						{
							fl = -1;
						}
						else if (fb == 2)
						{
							fl = -2;
						}
					}
					if (m.x >= 90 && m.x <= 270 && m.y >= 240 && m.y <= 360)
					{
						BackMove();
						fl = -2;
					}
					if (m.x >= 90 && m.x <= 270 && m.y >= 420 && m.y <= 540)
					{
						Loss();
						if (comcolor == 2)
						{
							fl = -1;
						}
						else if (comcolor == 2)
						{
							fl = -2;
						}
					}
					if (m.x >= 90 && m.x <= 270 && m.y >= 600 && m.y <= 720)
					{
						Save1();
						Save2();
						cundang = 1;
					}
					if (m.x >= 90 && m.x <= 270 && m.y >= 780 && m.y <= 900)
					{
						Read1();
						Read2();
						int nb = 0, nw = 0;
						for (int i = 0; i < 19; i++)
						{
							for (int j = 0; j < 19; j++)
							{
								if (stone[i][j] == 1)
								{
									nb++;
								}
								else if (stone[i][j] == 2)
								{
									nw++;
								}
							}
						}
						if (nb == nw - 1)
						{
							flag = 1;
						}
						else if (nb == nw)
						{
							flag = 0;
						}
					}
					if (cundang == 1)
					{
						flag = 1;
					}
					else 
					{
						flag = 2;
					}
				}
			}
	}
}
void chessboard::initboard()
{
	for (int i = 0; i < 19; i++)                                 //依行逐次向下，int stone[18][19]表示18行19列的矩阵，恰好与x轴Y轴颠倒，18对应Y轴，19对应X轴
	{
		for (int j = 0; j < 19; j++)                             //依列逐次向右

			stone[i][j] = 0;                                     //整体上先从左向右扫，再下移一行，再从左向右扫，继续
	}
}
int chessboard::GetSum(int color, int x)
{
	if (color == 1)
	{
		return sum[0][x-1];
	}
	else
	{
		return sum[1][x-1];
	}
}
void chessboard::ResetStonex()                                 //对stonex进行清零
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
			stonex[i][j] = 0;
	}
}
int chessboard::GetStonex(int i, int j)                      //返回大棋盘某点的值
{
	return stonex[i][j];
}

void chessboard::SeekLine(int color)
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (i <= 13 && stone[i][j] == color && stone[i + 1][j] == color && stone[i + 2][j] == color && stone[i + 3][j] == color && stone[i + 4][j] == color && stone[i + 5][j] == color)
			{
				sum[color - 1][5]++;
			}
			if (i <= 13&&j<=13 && stone[i][j] == color && stone[i + 1][j+1] == color && stone[i + 2][j+2] == color && stone[i + 3][j+3] == color && stone[i + 4][j+4] == color && stone[i + 5][j+5] == color)
			{
				sum[color - 1][5]++;
			}
			if (j <= 13 && stone[i][j] == color && stone[i][j + 1] == color && stone[i][j + 2] == color && stone[i][j + 3] == color && stone[i][j + 4] == color && stone[i][j + 5] == color)
			{
				sum[color - 1][5]++;
			}
			if (i >=5&& j <= 13 && stone[i][j] == color && stone[i - 1][j + 1] == color && stone[i - 2][j + 2] == color && stone[i - 3][j + 3] == color && stone[i - 4][j + 4] == color && stone[i - 5][j + 5] == color)
			{
				sum[color - 1][5]++;
			}
		}
	}
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (stone[i][j] != 0)
			{
				for (int x = 2; x <= 5; x++)
				{
					for (int direct = 0; direct < 4; direct++)
					{
						if (direct == 0)																//方向为0
						{
							if (i == 0)                                                                 //寻连x
							{
								int s = 0;
								for (int n = 0; n <= x - 2; n++)
								{

									if (stone[i + n][j] == color&&stone[i + n + 1][j] == color)
									{
										s++;
									}
								}
								if (stone[i + x][j] == 0&&s == x - 1)
								{
									if (color == humcolor)
									{
										firststone[direct][i][j] = x + 1;
										firststone[direct+4][i+x-1][j] = x + 1;
										sum[humcolor-1][x - 1]++;
									}
									else
									{
										firststone[direct][i][j] = -x - 1;
										firststone[direct + 4][i + x - 1][j] = -x - 1;
										sum[comcolor-1][x - 1]++;
									}
								}
							}

							if (i >= 1 && i <= 18 - x)
							{
								int s = 0;
								for (int n = 0; n <= x - 2; n++)
								{
									if (stone[i + n][j] == color&&stone[i + n + 1][j] == color)
									{
										s++;
									}
								}
								if (color == humcolor)
								{
									if ((!(stone[i-1][j] == humcolor || stone[i+x][j] == humcolor)) && (stone[i-1][j] != comcolor || stone[i+x][j] != comcolor) && s == x - 1)
									{
										firststone[direct][i][j] = x + 1;
										firststone[direct + 4][i+x-1][j] = x + 1;
										sum[humcolor-1][x - 1]++;
									}
								}
								if (color == comcolor)
								{
									if ((!(stone[i-1][j] == comcolor || stone[i+x][j] == comcolor)) && (stone[i-1][j] != humcolor || stone[i+x][j] != humcolor) && s == x - 1)
									{
										firststone[direct][i][j] = -x - 1;
										firststone[direct + 4][i+x-1][j] = -x - 1;
										sum[comcolor-1][x - 1]++;                                                              //此处有问题
									}
								}
							}
							if (i == 19 - x)
							{
								int s = 0;
								for (int n = 0; n <= x - 2; n++)
								{
									if (stone[i + n][j] == color&&stone[i + n + 1][j] == color)
									{
										s++;
									}
									if (stone[i - 1][j] == 0&&s == x-1)
									{
										if (color == humcolor)
										{
											firststone[direct][i][j] = x + 1;
											firststone[direct + 4][i + x - 1][j] = x + 1;
											sum[humcolor-1][x - 1]++;
										}
										else
										{
											firststone[direct][i][j] = -x - 1;
											firststone[direct + 4][i + x - 1][j] = -x - 1;
											sum[comcolor-1][x - 1]++;
										}
									}
								}
							}
						}
						if (direct == 1)																//方向为1，注意先不考虑角落之只能形成连二而不能形成连三了
						{
							if (i == 0 || j == 0)
							{
								int s = 0;
								for (int n = 0; n <= x - 2; n++)
								{

									if (stone[i + n][j + n] == color&&stone[i + n + 1][j + n + 1] == color)
									{
										s++;
									}
								}
								if (stone[i + x][j + x] == 0&&s == x - 1)
								{
									if (color == humcolor)
									{
										firststone[direct][i][j] = x + 1;
										firststone[direct+4][i+x-1][j+x-1] = x + 1;
										sum[humcolor-1][x - 1]++;
									}
									else
									{
										firststone[direct][i][j] = -x - 1;
										firststone[direct + 4][i + x - 1][j+x-1] = -x - 1;
										sum[comcolor-1][x - 1]++;
									}
								}

							}

							if (i >= 1 && i <= 18 - x&&j >= 1 && j <= 18 - x)
							{
								int s = 0;
								for (int n = 0; n <= x - 2; n++)
								{
									if (stone[i + n][j + n] == color&&stone[i + n + 1][j + n + 1] == color)
									{
										s++;
									}
								}
								if (color == humcolor)
								{
									if ((!(stone[i-1][j - 1] == humcolor || stone[i+x][j + x] == humcolor)) && (stone[i-1][j - 1] != comcolor || stone[i+x][j + x] != comcolor) && s == x - 1)
									{
										firststone[direct][i][j] = x + 1;
										firststone[direct + 4][i+x-1][j + x - 1] = x + 1;
										sum[humcolor-1][x - 1]++;
									}
								}
								if (color == comcolor)
								{
									if ((!(stone[i-1][j - 1] == comcolor || stone[i+x][j + x] == comcolor)) && (stone[i-1][j - 1] != humcolor || stone[i+x][j + x] != humcolor) && s == x - 1)
									{
										firststone[direct][i][j] = -x - 1;
										firststone[direct + 4][i+x-1][j + x - 1] = -x - 1;
										sum[comcolor-1][x - 1]++;                                                             
									}
								}
							}
							if (i == 19 - x || j == 19 - x)
							{
								int s = 0;
								for (int n = 0; n <= x - 2; n++)
								{
									if (stone[i + n][j + n] == color&&stone[i + n + 1][j + n + 1] == color)
									{
										s++;
									}
									if (stone[i - 1][j - 1] == 0&&s == x-1)
									{
										if (color == humcolor)
										{
											firststone[direct][i][j] = x + 1;
											firststone[direct + 4][i + x - 1][j + x - 1] = x + 1;
											sum[humcolor-1][x - 1]++;
										}
										else
										{
											firststone[direct][i][j] = -x - 1;
											firststone[direct + 4][i + x - 1][j+x-1] = -x - 1;
											sum[comcolor-1][x - 1]++;
										}
									}
								}
							}
						}
							if (direct == 2)																//方向为2
							{
								if (j == 0)
								{
									int s = 0;
									for (int n = 0; n <= x - 2; n++)
									{

										if (stone[i][j+n] == color&&stone[i][j+n+1] == color)
										{
											s++;
										}
									}
									if (stone[i][j+x] == 0&&s == x - 1)
									{
										if (color == humcolor)
										{
											firststone[direct][i][j] = x + 1;
											firststone[direct+4][i][j+x-1] = x + 1;
											sum[humcolor-1][x - 1]++;
										}
										else
										{
											firststone[direct][i][j] = -x - 1;
											firststone[direct + 4][i][j+x-1] = -x - 1;
											sum[comcolor-1][x - 1]++;
										}
									}
								}

								if (j >= 1 && j <= 18 - x)
								{
									int s = 0;
									for (int n = 0; n <= x - 2; n++)
									{
										if (stone[i][j + n] == color&&stone[i][j + n + 1] == color)
										{
											s++;
										}
									}
									if (color == humcolor)
									{
										if ((!(stone[i][j - 1] == humcolor || stone[i][j + x] == humcolor)) && (stone[i][j - 1] != comcolor || stone[i][j + x] != comcolor) && s == x - 1)
										{
												firststone[direct][i][j] = x + 1;
												firststone[direct + 4][i][j + x - 1] = x + 1;
												sum[humcolor-1][x - 1]++;
										}
									}
									if (color==comcolor)
									{
										if ((!(stone[i][j - 1] == comcolor || stone[i][j + x] == comcolor)) && (stone[i][j - 1] != humcolor || stone[i][j + x] != humcolor) && s == x - 1)
										{
											firststone[direct][i][j] = -x - 1;
											firststone[direct + 4][i][j+x-1] = -x - 1;
											sum[comcolor-1][x - 1]++;                                                              //此处有问题
										}
									}
								}
								if (j == 19 - x)
								{
									int s = 0;
									for (int n = 0; n <= x - 2; n++)
									{
										if (stone[i][j + n] == color&&stone[i][j + n + 1] == color)
										{
											s++;
										}
										if (stone[i][j-1] == 0&&s == x-1)
										{
											if (color == humcolor)
											{
												firststone[direct][i][j] = x + 1;
												firststone[direct + 4][i][j + x-1] = x + 1;
												sum[humcolor-1][x - 1]++;
											}
											else
											{
												firststone[direct][i][j] = -x - 1;
												firststone[direct + 4][i][j+x-1] = -x - 1;
												sum[comcolor-1][x - 1]++;
											}
										}
									}
								}
							}
							if (direct == 3)																//方向为3，注意先不考虑角落之只能形成连二而不能形成连三了
							{
								if (i == 18 || j == 0)
								{
									int s = 0;
									for (int n = 0; n <= x - 2; n++)
									{

										if (stone[i - n][j + n] == color&&stone[i - n - 1][j + n + 1] == color)
										{
											s++;
										}
									}
									if (stone[i - x][j + x] == 0&&s == x - 1)
									{
										if (color == humcolor)
										{
											firststone[direct][i][j] = x + 1;
											firststone[direct+4][i-x+1][j+x-1] = x + 1;
											sum[humcolor-1][x - 1]++;
										}
										else
										{
											firststone[direct][i][j] = -x - 1;
											firststone[direct + 4][i - x + 1][j+x-1] = -x - 1;
											sum[comcolor-1][x - 1]++;
										}
									}

								}

								if (i >= x && i <= 17&&j >= 1 && j <= 18 - x)
								{
									int s = 0;
									for (int n = 0; n <= x - 2; n++)
									{
										if (stone[i - n][j + n] == color&&stone[i - n - 1][j + n + 1] == color)
										{
											s++;
										}
									}
									if (color == humcolor)
									{
										if ((!(stone[i + 1][j - 1] == humcolor || stone[i - x][j + x] == humcolor)) && (stone[i + 1][j - 1] != comcolor || stone[i - x][j + x] != comcolor) && s == x - 1)
										{
											firststone[direct][i][j] = x + 1;
											firststone[direct + 4][i - x + 1][j + x - 1] = x + 1;
											sum[humcolor-1][x - 1]++;
										}
									}
									if (color == comcolor)
									{
										if ((!(stone[i + 1][j - 1] == comcolor|| stone[i - x][j + x] == comcolor)) && (stone[i + 1][j - 1] != humcolor || stone[i - x][j + x] != humcolor) && s == x - 1)
										{
											firststone[direct][i][j] = -x - 1;
											firststone[direct + 4][i - x + 1][j + x - 1] = -x - 1;
											sum[comcolor-1][x - 1]++;
										}
									}
								}
								if (i == x-1 || j == 19 - x)
								{
									int s = 0;
									for (int n = 0; n <= x - 2; n++)
									{
										if (stone[i - n][j + n] == color&&stone[i - n - 1][j + n + 1] == color)
										{
											s++;
										}
										if (stone[i + 1][j - 1] == 0&&s == x-1)
										{
											if (color == humcolor)
											{
												firststone[direct][i][j] = x + 1;
												firststone[direct + 4][i - x+1][j + x-1] = x + 1;
												sum[humcolor-1][x - 1]++;
											}
											else
											{
												firststone[direct][i][j] = -x - 1;
												firststone[direct + 4][i - x + 1][j + x - 1] = -x - 1;
												sum[comcolor-1][x - 1]++;
											}
										}
									}
								}
							}
				    }
				}
			}
		}
	}
}
void chessboard::SetNull()												//要注意写清零回复函数
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)                                   //这里的考虑只考虑了【1,17】内区域的空子
		{
			
			if (i == 0)
			{
				for (int x = 1; x <= 6; x++)
				{
					if (x == 1)
					{
						int k = 0;
						//int k[3] = { 0, 0, 0 };                                              //记录与周围子可形成的连二的个数,k{0]死，k[1]眠，k[2]活
						int b = 0;
						int w = 0;						                                       //如果正负相等，还涉及到一个黑子白子优先选则问题
						if (stone[i][j] + stone[i + 1][j] == 1)						//还涉及到比较大小的问题
							k++;
						if (stone[i][j] + stone[i][j + 1] == 1)
							k++;
						if (stone[i][j] + stone[i][j - 1] == 1)
							k++;
						if (stone[i][j] + stone[i + 1][j + 1] == 1)
							k++;
						if (stone[i][j] + stone[i + 1][j - 1] == 1)
							k++;
						b = 1 * k;
						k = 0;
						if (stone[i][j] + stone[i + 1][j] == 2)
							k++;
						if (stone[i][j] + stone[i][j + 1] == 2)
							k++;
						if (stone[i][j] + stone[i][j - 1] == 2)
							k++;
						if (stone[i][j] + stone[i + 1][j + 1] == 2)
							k++;
						if (stone[i][j] + stone[i + 1][j - 1] == 2)
							k++;
						w = 1 * k;
						stonex[i][j] = b + w;
						stonexb[i][j] = b;
						stonexw[i][j] = w;
					}
				}
			}
			
			if (i >= 1 && i <= 17 && j >= 1 && j <= 17 && stone[i][j] == 0 && (stone[i + 1][j] != 0 || stone[i][j + 1] != 0 || stone[i - 1][j] != 0 || stone[i][j - 1] != 0 || stone[i + 1][j + 1] != 0 || stone[i + 1][j - 1] != 0 || stone[i - 1][j + 1] != 0 || stone[i - 1][j - 1] != 0))
			{
				for (int x = 1; x <= 6; x++)
				{
					if (x == 1)                                                     
					{
						int k=0;
						//int k[3] = { 0, 0, 0 };                                              //记录与周围子可形成的连二的个数,k{0]死，k[1]眠，k[2]活
						int b=0;
						int w = 0;						                                       //如果正负相等，还涉及到一个黑子白子优先选则问题
						if (stone[i][j] + stone[i + 1][j] == 1)						//还涉及到比较大小的问题
							k++;
						if (stone[i][j] + stone[i][j + 1] == 1)
							k++;
						if (stone[i][j] + stone[i - 1][j] == 1)
							k++;
						if (stone[i][j] + stone[i][j - 1] == 1)
							k++;
						if (stone[i][j] + stone[i + 1][j + 1] == 1)
							k++;
						if (stone[i][j] + stone[i - 1][j + 1] == 1)
							k++;
						if (stone[i][j] + stone[i - 1][j - 1] == 1)
							k++;
						if (stone[i][j] + stone[i + 1][j - 1] == 1)
							k++;
						b = 1*k;
						k = 0;
						if (stone[i][j] + stone[i + 1][j] == 2)
							k++;
						if (stone[i][j] + stone[i][j + 1] == 2)
							k++;
						if (stone[i][j] + stone[i - 1][j] == 2)
							k++;
						if (stone[i][j] + stone[i][j - 1] == 2)
							k++;
						if (stone[i][j] + stone[i + 1][j + 1] == 2)
							k++;
						if (stone[i][j] + stone[i - 1][j + 1] == 2)
							k++;
						if (stone[i][j] + stone[i - 1][j - 1] == 2)
							k++;
						if (stone[i][j] + stone[i + 1][j - 1] == 2)
							k++;
						w = 3 * k;
						stonex[i][j] = b + w;
						stonexb[i][j] = b;
						stonexw[i][j] = w;
					}
					if (x == 2)                                               //冲连三，x=2表示首子为连二
					{
						for (int direct = 0; direct < 4; direct++)
						{
							firststone[direct][i][j] = 1;
							firststone[direct+4][i][j] = 1;
							if (direct == 0)
							{
								if ((i <= 17-x && stone[i + 1][j] != 2 && stone[i + 2][j] != 2 && stone[i + 3][j] != 2 ) || (i >= x+1 && stone[i - 1][j] != 2 && stone[i - 2][j] != 2 && stone[i - 3][j] != 2 ))
								{
									if (i == x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i > x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j] == x + 2 && stone[i - 3][j] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
										if (firststone[direct][i][j] + firststone[direct][i - x][j] == x + 2 && stone[i - 3][j] == 2)
										{
											stonex[i][j] += n2bd;
											stonexb[i][j] += n2bd;
										}

									}
									if (i == (x / 2))
									{
										if (firststone[direct][i][j] + stone[i - 1][j] == 2 && firststone[direct][i][j] + stone[i + 1][j] == 2 && stone[i + 2][j] == 0)//注意comcolor与humcolor的转换
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i >= ((x / 2) + 1) && i <= (18 - (x / 2) - 1))
									{
										if (firststone[direct][i][j] + stone[i - 1][j] == 2 && firststone[direct][i][j] + stone[i + 1][j] == 2 && stone[i - 2][j] == 0 && stone[i + 2][j] == 0)//注意comcolor与humcolor的转换
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
										if (firststone[direct][i][j] + stone[i - 1][j] == 2 && firststone[direct][i][j] + stone[i + 1][j] == 2 && ((stone[i - 2][j] == 2 && stone[i + 2][j] == 0) || (stone[i - 2][j] == 0 && stone[i + 2][j] == 2)))//注意comcolor与humcolor的转换
										{
											stonex[i][j] += n2bd;
											stonexb[i][j] += n2bd;
										}
									}
									if (i == (18 - x / 2))
									{
										if (firststone[direct][i][j] + stone[i - 1][j] == 2 && firststone[direct][i][j] + stone[i + 1][j] == 2 && stone[i - 2][j] == 0)//注意comcolor与humcolor的转换
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i == 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i < 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == x + 2 && stone[i + x + 1][j] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == x + 2 && stone[i + x + 1][j] == 2)
										{
											stonex[i][j] += n2bd;
											stonexb[i][j] += n2bd;
										}
									}
								}
							}
							if (direct == 1)
							{
								if ((i <= 17 - x &&j <= 17 - x&& stone[i + 1][j + 1] != 2 && stone[i + 2][j + 2] != 2 && stone[i + 3][j + 3] != 2) || (i >= x + 1 && j >= x + 1 && stone[i - 1][j - 1] != 2 && stone[i - 2][j - 2] != 2 && stone[i - 3][j - 3] != 2))
								{
									if (i == x&&j >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i > x&&j == x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i > x&&j > x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == x + 2 && stone[i - 3][j - 3] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
										if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == x + 2 && stone[i - 3][j - 3] == 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i == (x / 2) && j >= (x / 2) && j <= (17 - x / 2))
									{
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 2 && firststone[direct][i][j] + stone[i + 1][j + 1] == 2 && stone[i + 2][j + 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i > (x / 2) && i <= (17 - x / 2) && j == x / 2)
									{
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 2 && firststone[direct][i][j] + stone[i + 1][j + 1] == 2 && stone[i + 2][j + 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i >= ((x / 2) + 1) && i <= (18 - (x / 2) - 1) && j >= ((x / 2) + 1) && j <= (18 - (x / 2) - 1))
									{
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 2 && firststone[direct][i][j] + stone[i + 1][j + 1] == 2 && stone[i - 2][j - 2] == 0 && stone[i + 2][j + 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 2 && firststone[direct][i][j] + stone[i + 1][j + 1] == 2 && ((stone[i - 2][j - 2] == 2 && stone[i + 2][j + 2] == 0) || (stone[i - 2][j - 2] == 0 && stone[i + 2][j + 2] == 2)))
										{
											stonex[i][j] += n2bd;
											stonexb[i][j] += n2bd;
										}
									}
									if (i == (18 - x / 2) && j >= x / 2 + 1 && j <= (18 - x / 2))
									{
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 2 && firststone[direct][i][j] + stone[i + 1][j + 1] == 2 && stone[i - 2][j - 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i >= x / 2 + 1 && i < (18 - x / 2) && j == (18 - x / 2))
									{
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 2 && firststone[direct][i][j] + stone[i + 1][j + 1] == 2 && stone[i - 2][j - 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i == 18 - x&&j <= 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i < 18 - x&&j == 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i < 18 - x&&j < 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == x + 2 && stone[i + x + 1][j + x + 1] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == x + 2 && stone[i + x + 1][j + x + 1] == 2)
										{
											stonex[i][j] += n2bd;
											stonexb[i][j] += n2bd;
										}
									}
								}
							}
							if (direct == 2)
							{
								if ((j <= 17 - x&& stone[i][j + 1] != 2 && stone[i][j + 2] != 2 && stone[i][j + 3] != 2) || (j >= x + 1 && stone[i][j - 1] != 2 && stone[i][j - 2] != 2 && stone[i][j - 3] != 2))
								{
									if (j == x)
									{
										if (firststone[direct][i][j] + firststone[direct][i][j - x] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (j > x)
									{
										if (firststone[direct][i][j] + firststone[direct][i][j - x] == x + 2 && stone[i][j - 3] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
										if (firststone[direct][i][j] + firststone[direct][i][j - x] == x + 2 && stone[i][j - 3] == 2)
										{
											stonex[i][j] += n2bd;
											stonexb[i][j] += n2bd;
										}
									}
									if (j == x / 2)
									{
										if (firststone[direct][i][j] + stone[i][j - 1] == 2 && firststone[direct][i][j] + stone[i][j + 1] == 2 && stone[i][j + 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (j >= ((x / 2) + 1) && j <= (18 - (x / 2) - 1))
									{
										if (firststone[direct][i][j] + stone[i][j - 1] == 2 && firststone[direct][i][j] + stone[i][j + 1] == 2 && ((stone[i][j - 2] == 2 && stone[i][j + 2] == 0) || (stone[i][j - 2] == 0 && stone[i][j + 2] == 2)))
										{
											stonex[i][j] += n2bd;
											stonexb[i][j] += n2bd;
										}
										if (firststone[direct][i][j] + stone[i][j - 1] == 2 && firststone[direct][i][j] + stone[i][j + 1] == 2 && stone[i][j - 2] == 0 && stone[i][j + 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (j == 18 - x / 2)
									{
										if (firststone[direct][i][j] + stone[i][j - 1] == 2 && firststone[direct][i][j] + stone[i][j + 1] == 2 && stone[i][j - 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (j == 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (j < 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == x + 2 && stone[i][j + x + 1] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == x + 2 && stone[i][j + x + 1] == 2)
										{
											stonex[i][j] += n2bd;
											stonexb[i][j] += n2bd;
										}
									}
								}
							}
							if (direct == 3)
							{
								if ((i >= x + 1 && j <= 17 - x&& stone[i - 1][j + 1] != 2 && stone[i - 2][j + 2] != 2 && stone[i - 3][j + 3] != 2) || (i <= 17 - x && j >= x + 1 && stone[i + 1][j - 1] != 2 && stone[i + 2][j - 2] != 2 && stone[i + 3][j - 3] != 2))
								{
									if (i == 18 - x && j >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i < 18 - x && j == x)
									{
										if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i < 18 - x && j > x)
									{
										if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == x + 2 && stone[i + x + 1][j + x + 1] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
										if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == x + 2 && stone[i + x + 1][j + x + 1] == 2)
										{
											stonex[i][j] += n2bd;
											stonexb[i][j] += n2bd;
										}
									}
									if (i == x / 2 && j >= x / 2 + 1 && j <= 18 - x / 2)                                                         //注意
									{
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 2 && firststone[direct][i][j] + stone[i - 1][j + 1] == 2 && stone[i + 2][j - 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i >= x / 2 + 1 && i <= 18 - x / 2 && j == x / 2)
									{
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 2 && firststone[direct][i][j] + stone[i - 1][j + 1] == 2 && stone[i - 2][j + 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i >= ((x / 2) + 1) && i <= (18 - (x / 2) - 1) && j >= ((x / 2) + 1) && j <= (18 - (x / 2) - 1))
									{
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 2 && firststone[direct][i][j] + stone[i - 1][j + 1] == 2 && ((stone[i + 2][j - 2] == 2 && stone[i - 2][j + 2] == 0) || (stone[i + 2][j - 2] == 0 && stone[i - 2][j + 2] == 2)))
										{
											stonex[i][j] += n2bd;
											stonexb[i][j] += n2bd;
										}
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 2 && firststone[direct][i][j] + stone[i - 1][j + 1] == 2 && stone[i + 2][j - 2] == 0 && stone[i - 2][j + 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i == 18 - x / 2 && j >= x / 2 + 1 && j <= 17 - x / 2)
									{
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 2 && firststone[direct][i][j] + stone[i - 1][j + 1] == 2 && stone[i - 2][j + 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i >= x / 2 + 1 && i <= 17 - x / 2 && j == 18 - x / 2)
									{
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 2 && firststone[direct][i][j] + stone[i - 1][j + 1] == 2 && stone[i + 2][j - 2] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i == x&&j < 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i > x&&j == 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == x + 2)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
									}
									if (i > x&&j < 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == x + 2 && stone[i - x - 1][j + x + 1] == 0)
										{
											stonex[i][j] += n2bl;
											stonexb[i][j] += n2bl;
										}
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == x + 2 && stone[i - x - 1][j + x + 1] == 2)
										{
											stonex[i][j] += n2bd;
											stonexb[i][j] += n2bd;
										}
									}
								}
							}
							firststone[direct][i][j] = -1;
							firststone[direct + 4][i][j] = -1;
							if (direct == 0)
							{
								if ((i <= 17 - x && stone[i + 1][j] != 1 && stone[i + 2][j] != 1 && stone[i + 3][j] != 1) || (i >= x + 1 && stone[i - 1][j] != 1 && stone[i - 2][j] != 1 && stone[i - 3][j] != 1))
								{
									if (i == x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i > x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j] == -x - 2 && stone[i - x - 1][j] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
										if (firststone[direct][i][j] + firststone[direct][i - x][j] == -x - 2 && stone[i - x - 1][j] == 1)
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
									}
									if (i == (x / 2))
									{
										if (firststone[direct][i][j] + stone[i - 1][j] == 1 && firststone[direct][i][j] + stone[i + 1][j] == 1 && stone[i + 2][j] == 0)//注意comcolor与humcolor的转换
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i >= ((x / 2) + 1) && i <= (18 - (x / 2) - 1))
									{
										if (firststone[direct][i][j] + stone[i - 1][j] == 1 && firststone[direct][i][j] + stone[i + 1][j] == 1 && ((stone[i - 2][j] == 1 && stone[i + 2][j] == 0) || (stone[i - 2][j] == 0 && stone[i + 2][j] == 1)))//注意comcolor与humcolor的转换
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
										if (firststone[direct][i][j] + stone[i - 1][j] == 1 && firststone[direct][i][j] + stone[i + 1][j] == 1 && stone[i - 2][j] == 0 && stone[i + 2][j] == 0)//注意comcolor与humcolor的转换
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i == (18 - x / 2))
									{
										if (firststone[direct][i][j] + stone[i - 1][j] == 1 && firststone[direct][i][j] + stone[i + 1][j] == 1 && stone[i - 2][j] == 0)//注意comcolor与humcolor的转换
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i == 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i < 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == -x - 2 && stone[i + x + 1][j] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == -x - 2 && stone[i + x + 1][j] == 1)
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
									}
								}
							}
							if (direct == 1)
							{
								if ((i <= 17 - x &&j <= 17 - x&& stone[i + 1][j + 1] != 1 && stone[i + 2][j + 2] != 1 && stone[i + 3][j + 3] != 1) || (i >= x + 1 && j >= x + 1 && stone[i - 1][j - 1] != 1 && stone[i - 2][j - 2] != 1 && stone[i - 3][j - 3] != 1))
								{
									if (i == x&&j >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i > x&&j == x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i > x&&j > x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == -x - 2 && stone[i - x - 1][j - x - 1] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
										if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == -x - 2 && stone[i - x - 1][j - x - 1] == 1)
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
									}
									if (i == (x / 2) && j >= (x / 2) && j <= (17 - x / 2))
									{
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 1 && firststone[direct][i][j] + stone[i + 1][j + 1] == 1 && stone[i + 2][j + 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i > (x / 2) && i <= (17 - x / 2) && j == x / 2)
									{
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 1 && firststone[direct][i][j] + stone[i + 1][j + 1] == 1 && stone[i + 2][j + 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i >= ((x / 2) + 1) && i <= (18 - (x / 2) - 1) && j >= ((x / 2) + 1) && j <= (18 - (x / 2) - 1))
									{
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 1 && firststone[direct][i][j] + stone[i + 1][j + 1] == 1 && ((stone[i - 2][j - 2] == 1 && stone[i + 2][j + 2] == 0) || (stone[i - 2][j - 2] == 0 && stone[i + 2][j + 2] == 1)))
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 1 && firststone[direct][i][j] + stone[i + 1][j + 1] == 1 && stone[i - 2][j - 2] == 0 && stone[i + 2][j + 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}

									}
									if (i == (18 - x / 2) && j >= x / 2 + 1 && j <= (18 - x / 2))
									{
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 1 && firststone[direct][i][j] + stone[i + 1][j + 1] == 1 && stone[i - 2][j - 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i >= x / 2 + 1 && i < (18 - x / 2) && j == (18 - x / 2))
									{
										if (firststone[direct][i][j] + stone[i - 1][j - 1] == 1 && firststone[direct][i][j] + stone[i + 1][j + 1] == 1 && stone[i - 2][j - 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i < 18 - x&&j == 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i == 18 - x&&j <= 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i < 18 - x&&j < 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == -x - 2 && stone[i + x + 1][j + x + 1] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == -x - 2 && stone[i + x + 1][j + x + 1] == 1)
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
									}
								}
							}
							if (direct == 2)
							{
								if ((j <= 17 - x&& stone[i][j + 1] != 1 && stone[i][j + 2] != 1 && stone[i][j + 3] != 1) || (j >= x + 1 && stone[i][j - 1] != 1 && stone[i][j - 2] != 1 && stone[i][j - 3] != 1))
								{
									if (j == x)
									{
										if (firststone[direct][i][j] + firststone[direct][i][j - x] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (j > x)
									{
										if (firststone[direct][i][j] + firststone[direct][i][j - x] == -x - 2 && stone[i][j - x - 1] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
										if (firststone[direct][i][j] + firststone[direct][i][j - x] == -x - 2 && stone[i][j - x - 1] == 1)
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
									}
									if (j == x / 2)
									{
										if (firststone[direct][i][j] + stone[i][j - 1] == 1 && firststone[direct][i][j] + stone[i][j + 1] == 1 && stone[i][j + 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (j >= ((x / 2) + 1) && j <= (18 - (x / 2) - 1))
									{
										if (firststone[direct][i][j] + stone[i][j - 1] == 1 && firststone[direct][i][j] + stone[i][j + 1] == 1 && ((stone[i][j - 2] == 1 && stone[i][j + 2] == 0) || (stone[i][j - 2] == 0 && stone[i][j + 2] == 1)))
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
										if (firststone[direct][i][j] + stone[i][j - 1] == 1 && firststone[direct][i][j] + stone[i][j + 1] == 1 && stone[i][j - 2] == 0 && stone[i][j + 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (j == 18 - x / 2)
									{
										if (firststone[direct][i][j] + stone[i][j - 1] == 1 && firststone[direct][i][j] + stone[i][j + 1] == 1 && stone[i][j - 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (j == 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (j < 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == -x - 2 && stone[i][j + x + 1] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == -x - 2 && stone[i][j + x + 1] == 1)
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
									}
								}
							}
							if (direct == 3)
							{
								if ((i >= x + 1 && j <= 17 - x&& stone[i - 1][j + 1] != 1 && stone[i - 2][j + 2] != 1 && stone[i - 3][j + 3] != 1) || (i <= 17 - x && j >= x + 1 && stone[i + 1][j - 1] != 1 && stone[i + 2][j - 2] != 1 && stone[i + 3][j - 3] != 1))
								{
									if (i == 18 - x && j >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i < 18 - x && j == x)
									{
										if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i < 18 - x && j > x)
									{
										if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == -x - 2 && stone[i + x + 1][j - x - 1] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
										if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == -x - 2 && stone[i + x + 1][j - x - 1] == 1)
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
									}
									if (i == x / 2 && j >= x / 2 + 1 && j <= 18 - x / 2)                                                         //注意
									{
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 1 && firststone[direct][i][j] + stone[i - 1][j + 1] == 1 && stone[i + 2][j - 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i >= x / 2 + 1 && i <= 18 - x / 2 && j == x / 2)
									{
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 1 && firststone[direct][i][j] + stone[i - 1][j + 1] == 1 && stone[i - 2][j + 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i >= ((x / 2) + 1) && i <= (18 - (x / 2) - 1) && j >= ((x / 2) + 1) && j <= (18 - (x / 2) - 1))
									{
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 1 && firststone[direct][i][j] + stone[i - 1][j + 1] == 1 && ((stone[i + 2][j - 2] == 1 && stone[i - 2][j + 2] == 0) || (stone[i + 2][j - 2] == 0 && stone[i - 2][j + 2] == 1)))
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 1 && firststone[direct][i][j] + stone[i - 1][j + 1] == 1 && stone[i + 2][j - 2] == 0 && stone[i - 2][j + 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i == 18 - x / 2 && j >= x / 2 + 1 && j <= 17 - x / 2)
									{
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 1 && firststone[direct][i][j] + stone[i - 1][j + 1] == 1 && stone[i - 2][j + 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i >= x / 2 + 1 && i <= 17 - x / 2 && j == 18 - x / 2)
									{
										if (firststone[direct][i][j] + stone[i + 1][j - 1] == 1 && firststone[direct][i][j] + stone[i - 1][j + 1] == 1 && stone[i + 2][j - 2] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i == x&&j <= 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i > x&&j == 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == -x - 2)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
									}
									if (i > x&&j < 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == -x - 2 && stone[i - x - 1][j + x + 1] == 0)
										{
											stonex[i][j] += n2wl;
											stonexw[i][j] += n2wl;
										}
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == -x - 2 && stone[i - x - 1][j + x + 1] == 1)
										{
											stonex[i][j] += n2wd;
											stonexw[i][j] += n2wd;
										}
									}
								}
							}
							firststone[direct][i][j] = 0;
							firststone[direct + 4][i][j] = 0;
						}
					}
					if (x == 3)															//冲连四
					{
						for (int direct = 0; direct < 4; direct++)
						{
							firststone[direct][i][j] = 1;
							firststone[direct + 4][i][j] = 1;
							if (direct == 0)
							{
								if ((i <= 17 - x && stone[i + 1][j] != 2 && stone[i + 2][j] != 2) || (i >= x + 1 && stone[i - 1][j] != 2 && stone[i - 2][j] != 2))
								{
									if (i >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j] == x + 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (i > x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j] == x + 2 && stone[i + 1][j] == 0)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (i >= x - 1 && i <= 17)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x + 1][j] == x + 1 && firststone[direct][i][j] + stone[i + 1][j] == 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (i <= 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == x + 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (i >= 1 && i <= (18 - x))
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x - 1][j] == x + 1 && firststone[direct + 4][i][j] + stone[i - 1][j] == 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
								}
							}
							if (direct == 1)
							{
								if ((i <= 17 - x &&j <= 17 - x&& stone[i + 1][j + 1] != 2 && stone[i + 2][j + 2] != 2) || (i >= x + 1 && j >= x + 1 && stone[i - 1][j - 1] != 2 && stone[i - 2][j - 2] != 2))
								{
									if (i >= x&&j >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == x + 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (i >= x - 1 && i <= 17 && j >= x - 1 && j <= 17)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x + 1][j - x + 1] == x + 1 && firststone[direct][i][j] + stone[i + 1][j + 1] == 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (i <= 18 - x&&j <= 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == x + 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (i >= 1 && i <= (18 - x) && j >= 1 && j <= (18 - x))
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x - 1][j + x - 1] == x + 1 && firststone[direct + 4][i][j] + stone[i - 1][j - 1] == 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
								}
							}
							if (direct == 2)
							{
								if ((j <= 17 - x&& stone[i][j + 1] != 2 && stone[i][j + 2] != 2) || (j >= x + 1 && stone[i][j - 1] != 2 && stone[i][j - 2] != 2))
								{
									if (j >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i][j - x] == x + 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (j >= x - 1 && j <= 17)
									{
										if (firststone[direct][i][j] + firststone[direct][i][j - x + 1] == x + 1 && firststone[direct][i][j] + stone[i][j + 1] == 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (j <= 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == x + 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (j >= 1 && j <= (18 - x))
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x - 1] == x + 1 && firststone[direct + 4][i][j] + stone[i][j - 1] == 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
								}
							}
							if (direct == 3)
							{
								if ((i >= x + 1 && j <= 17 - x&& stone[i - 1][j + 1] != 2 && stone[i - 2][j + 2] != 2) || (i <= 17 - x && j >= x + 1 && stone[i + 1][j - 1] != 2 && stone[i + 2][j - 2] != 2))
								{
									if (i <= 18 - x && j >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == x + 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (i >= 1 && i <= (18 - x) && j >= x - 1 && j <= 17)
									{
										if (firststone[direct][i][j] + firststone[direct][i + x - 1][j - x + 1] == x + 1 && firststone[direct][i][j] + stone[i - 1][j + 1] == 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (i >= x&&j <= 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == x + 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
									if (i >= x - 1 && i <= 17 && j >= 1 && j <= (18 - x))
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x + 1][j + x - 1] == x + 1 && firststone[direct + 4][i][j] + stone[i + 1][j - 1] == 2)
										{
											stonex[i][j] += n3b;
											stonexb[i][j] += n3b;
										}
									}
								}
							}
							firststone[direct][i][j] = -1;
							firststone[direct + 4][i][j] = -1;
							if (direct == 0)
							{
								if ((i <= 17 - x && stone[i + 1][j] != 1 && stone[i + 2][j] != 1) || (i >= x + 1 && stone[i - 1][j] != 1 && stone[i - 2][j] != 1))
								{
									if (i >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j] == -x - 2)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
									if (i >= x - 1 && i <= 17)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x + 1][j] == -x - 1 && firststone[direct][i][j] + stone[i + 1][j] == 1)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
									if (i <= 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == -x - 2)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
									if (i >= 1 && i <= (18 - x))
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x - 1][j] == -x - 1 && firststone[direct + 4][i][j] + stone[i - 1][j] == 1)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
								}
							}
							if (direct == 1)
							{
								if ((i <= 17 - x &&j <= 17 - x&& stone[i + 1][j + 1] != 1 && stone[i + 2][j + 2] != 1) || (i >= x + 1 && j >= x + 1 && stone[i - 1][j - 1] != 1 && stone[i - 2][j - 2] != 1))
								{
									if (i >= x&&j >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == -x - 2)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
									if (i >= x - 1 && i <= 17 && j >= x - 1 && j <= 17)
									{
										if (firststone[direct][i][j] + firststone[direct][i - x + 1][j - x + 1] == -x - 1 && firststone[direct][i][j] + stone[i + 1][j + 1] == 1)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
									if (i <= 18 - x&&j <= 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == -x - 2)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
									if (i >= 1 && i <= (18 - x) && j >= 1 && j <= (18 - x))
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x - 1][j + x - 1] == -x - 1 && firststone[direct + 4][i][j] + stone[i - 1][j - 1] == 1)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
								}
							}
							if (direct == 2)
							{
								if ((j <= 17 - x&& stone[i][j + 1] != 1 && stone[i][j + 2] != 1) || (j >= x + 1 && stone[i][j - 1] != 1 && stone[i][j - 2] != 1))
								{
									if (j >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i][j - x] == -x - 2)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
									if (j >= x - 1 && j <= 17)
									{
										if (firststone[direct][i][j] + firststone[direct][i][j - x + 1] == -x - 1 && firststone[direct][i][j] + stone[i][j + 1] == 1)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
									if (j <= 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == -x - 2)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
									if (j >= 1 && j <= (18 - x))
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x - 1] == -x - 1 && firststone[direct + 4][i][j] + stone[i][j - 1] == 1)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
								}
							}
							if (direct == 3)
							{
								if ((i >= x + 1 && j <= 17 - x&& stone[i - 1][j + 1] != 1 && stone[i - 2][j + 2] != 1) || (i <= 17 - x && j >= x + 1 && stone[i + 1][j - 1] != 1 && stone[i + 2][j - 2] != 1))
								{
									if (i <= 18 - x && j >= x)
									{
										if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == -x - 2)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
									if (i >= 1 && i <= (18 - x) && j >= x - 1 && j <= 17)
									{
										if (firststone[direct][i][j] + firststone[direct][i + x - 1][j - x + 1] == -x - 1 && firststone[direct][i][j] + stone[i - 1][j + 1] == 1)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
									if (i >= x&&j <= 18 - x)
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == -x - 2)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;                                      //此处有问题
										}
									}
									if (i >= x - 1 && i <= 17 && j >= 1 && j <= (18 - x))
									{
										if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x + 1][j + x - 1] == -x - 1 && firststone[direct + 4][i][j] + stone[i + 1][j - 1] == 1)
										{
											stonex[i][j] += n3w;
											stonexw[i][j] += n3w;
										}
									}
								}
							}
							firststone[direct][i][j] = 0;
							firststone[direct + 4][i][j] = 0;
						}
					}
					if (x == 4)                                                                                      //四冲五，赋n5
					{
						for (int direct = 0; direct < 4; direct++)
						{
							firststone[direct][i][j] = 1;
							firststone[direct + 4][i][j] = 1;
							if (direct == 0)
							{
								if (i >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j] == x + 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i >= x - 1 && i <= 17)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x + 1][j] == x + 1 && firststone[direct][i][j] + stone[i + 1][j] == 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i >= 2 && i <= 16)
								{
									if (firststone[direct][i - 2][j] == 3 && firststone[direct][i + 2][j] == 3)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == x + 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i >= 1 && i <= (18 - x))
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x - 1][j] == x + 1 && firststone[direct + 4][i][j] + stone[i - 1][j] == 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
							}
							if (direct == 1)
							{
								if (i >= x&&j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == x + 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i >= x - 1 && i <= 17 && j >= x - 1 && j <= 17)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x + 1][j - x + 1] == x + 1 && firststone[direct][i][j] + stone[i + 1][j + 1] == 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i >= 2 && i <= 16 && j >= 2 && j <= 16)
								{
									if (firststone[direct][i - 2][j - 2] == 3 && firststone[direct][i + 2][j + 2] == 3)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i <= 18 - x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == x + 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i >= 1 && i <= (18 - x) && j >= 1 && j <= (18 - x))
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x - 1][j + x - 1] == x + 1 && firststone[direct + 4][i][j] + stone[i - 1][j - 1] == 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
							}
							if (direct == 2)
							{
								if (j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i][j - x] == x + 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (j >= x - 1 && j <= 17)
								{
									if (firststone[direct][i][j] + firststone[direct][i][j - x + 1] == x + 1 && firststone[direct][i][j] + stone[i][j + 1] == 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == x + 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (j >= 2 && j <= 16)
								{
									if (firststone[direct][i][j - 2] == 3 && firststone[direct][i][j + 2] == 3)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (j >= 1 && j <= (18 - x))
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x - 1] == x + 1 && firststone[direct + 4][i][j] + stone[i][j - 1] == 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
							}
							if (direct == 3)
							{
								if (i <= 18 - x && j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == x + 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i >= 1 && i <= (18 - x) && j >= x - 1 && j <= 17)
								{
									if (firststone[direct][i][j] + firststone[direct][i + x - 1][j - x + 1] == x + 1 && firststone[direct][i][j] + stone[i - 1][j + 1] == 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i >= x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == x + 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i >= 2 && i <= 16 && j >= 2 && j <= 16)
								{
									if (firststone[direct][i-2][j + 2] == 3 && firststone[direct][i+2][j - 2] == 3)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
								if (i >= x - 1 && i <= 17 && j >= 1 && j <= (18 - x))
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x + 1][j + x - 1] == x + 1 && firststone[direct + 4][i][j] + stone[i + 1][j - 1] == 2)
									{
										stonex[i][j] += n4b;
										stonexb[i][j] += n4b;
									}
								}
							}
							firststone[direct][i][j] = -1;
							firststone[direct + 4][i][j] = -1;
							if (direct == 0)
							{
								if (i >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j] == -x - 2)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i >= x - 1 && i <= 17)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x + 1][j] == -x - 1 && firststone[direct][i][j] + stone[i + 1][j] == 1)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == -x - 2)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i >= 2 && i <= 16)
								{
									if (firststone[direct][i - 2][j] == -3 && firststone[direct][i + 2][j] == -3)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i >= 1 && i <= (18 - x))
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x - 1][j] == -x - 1 && firststone[direct + 4][i][j] + stone[i - 1][j] == 1)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
							}
							if (direct == 1)
							{
								if (i >= x&&j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == -x - 2)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i >= x - 1 && i <= 17 && j >= x - 1 && j <= 17)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x + 1][j - x + 1] == -x - 1 && firststone[direct][i][j] + stone[i + 1][j + 1] == 1)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i <= 18 - x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == -x - 2)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i >= 2 && i <= 16 && j >= 2 && j <= 16)
								{
									if (firststone[direct][i - 2][j - 2] == -3 && firststone[direct][i + 2][j + 2] == -3)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i >= 1 && i <= (18 - x) && j >= 1 && j <= (18 - x))
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x - 1][j + x - 1] == -x - 1 && firststone[direct + 4][i][j] + stone[i - 1][j - 1] == 1)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
							}
							if (direct == 2)
							{
								if (j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i][j - x] == -x - 2)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (j >= x - 1 && j <= 17)
								{
									if (firststone[direct][i][j] + firststone[direct][i][j - x + 1] == -x - 1 && firststone[direct][i][j] + stone[i][j + 1] == 1)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == -x - 2)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (j >= 2 && j <= 16)
								{
									if (firststone[direct][i][j - 2] == -3 && firststone[direct][i][j + 2] == -3)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (j >= 1 && j <= (18 - x))
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x - 1] == -x - 1 && firststone[direct + 4][i][j] + stone[i][j - 1] == 1)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
							}
							if (direct == 3)
							{
								if (i <= 18 - x && j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == -x - 2)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i >= 1 && i <= (18 - x) && j >= x - 1 && j <= 17)
								{
									if (firststone[direct][i][j] + firststone[direct][i + x - 1][j - x + 1] == -x - 1 && firststone[direct][i][j] + stone[i - 1][j + 1] == 1)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i >= x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == -x - 2)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i >= 2 && i <= 16 && j >= 2 && j <= 16)
								{
									if (firststone[direct][i - 2][j + 2] == -3 && firststone[direct][i + 2][j - 2] == -3)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
								if (i >= x - 1 && i <= 17 && j >= 1 && j <= (18 - x))
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x + 1][j + x - 1] == -x - 1 && firststone[direct + 4][i][j] + stone[i + 1][j - 1] == 1)
									{
										stonex[i][j] += n4w;
										stonexw[i][j] += n4w;
									}
								}
							}
							firststone[direct][i][j] = 0;
							firststone[direct + 4][i][j] = 0;
						}
					}
					if (x == 5)
					{
						for (int direct = 0; direct < 4; direct++)
						{
							firststone[direct][i][j] = 1;
							firststone[direct + 4][i][j] = 1;
							if (direct == 0)
							{
								if (i >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j] == x + 2)
									{
										stonex[i][j] += n5b;
										stonexb[i][j] += n5b;
									}
								}
								if (i <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == x + 2)
									{
										stonex[i][j] += n5b;
										stonexb[i][j] += n5b;
									}
								}
							}
							if (direct == 1)
							{
								if (i >= x&&j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == x + 2)
									{
										stonex[i][j] += n5b;
										stonexb[i][j] += n5b;
									}
								}
								if (i <= 18 - x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == x + 2)
									{
										stonex[i][j] += n5b;
										stonexb[i][j] += n5b;
									}
								}
							}
							if (direct == 2)
							{
								if (j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i][j - x] == x + 2)
									{
										stonex[i][j] += n5b;
										stonexb[i][j] += n5b;
									}
								}
								if (j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == x + 2)
									{
										stonex[i][j] += n5b;
										stonexb[i][j] += n5b;
									}
								}
							}
							if (direct == 3)
							{
								if (i <= 18 - x && j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == x + 2)
									{
										stonex[i][j] += n5b;
										stonexb[i][j] += n5b;
									}
								}
								if (i >= x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == x + 2)
									{
										stonex[i][j] += n5b;
										stonexb[i][j] += n5b;
									}
								}
							}
							firststone[direct][i][j] = -1;
							firststone[direct + 4][i][j] = -1;
							if (direct == 0)
							{
								if (i >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j] == -x - 2)
									{
										stonex[i][j] += n5w;
										stonexw[i][j] += n5w;
									}
								}
								if (i <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == -x - 2)
									{
										stonex[i][j] += n5w;
										stonexw[i][j] += n5w;
									}
								}
							}
							if (direct == 1)
							{
								if (i >= x&&j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == -x - 2)
									{
										stonex[i][j] += n5w;
										stonexw[i][j] += n5w;
									}
								}
								if (i <= 18 - x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == -x - 2)
									{
										stonex[i][j] += n5w;
										stonexw[i][j] += n5w;
									}
								}
							}
							if (direct == 2)
							{
								if (j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i][j - x] == -x - 2)
									{
										stonex[i][j] += n5w;
										stonexw[i][j] += n5w;
									}
								}
								if (j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == -x - 2)
									{
										stonex[i][j] += n5w;
										stonexw[i][j] += n5w;
									}
								}
							}
							if (direct == 3)
							{
								if (i <= 18 - x && j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == -x - 2)
									{
										stonex[i][j] += n5w;
										stonexw[i][j] += n5w;
									}
								}
								if (i >= x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == -x - 2)
									{
										stonex[i][j] += n5w;
										stonexw[i][j] += n5w;
									}
								}
							}
							firststone[direct][i][j] = 0;
							firststone[direct + 4][i][j] = 0;
						}
					}
					/*
					if (x == 6)
					{
						for (int direct = 0; direct < 4; direct++)
						{
							firststone[direct][i][j] = 1;
							firststone[direct+4][i][j] = 1;
							if (direct == 0)
							{
								if (i >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j] == x + 2)
									{
										stonex[i][j] += n6b;
										stonexb[i][j] += n6b;
									}
								}
								if (i <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == x + 2)
									{
										stonex[i][j] += n6b;
										stonexb[i][j] += n6b;
									}
								}
							}
							if (direct == 1)
							{
								if (i >= x&&j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == x + 2)
									{
										stonex[i][j] += n6b;
										stonexb[i][j] += n6b;
									}
								}
								if (i <= 18 - x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == x + 2)
									{
										stonex[i][j] += n6b;
										stonexb[i][j] += n6b;
									}
								}
							}
							if (direct == 2)
							{
								if (j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i][j - x] == x + 2)
									{
										stonex[i][j] += n6b;
										stonexb[i][j] += n6b;
									}
								}
								if (j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == x + 2)
									{
										stonex[i][j] += n6b;
										stonexb[i][j] += n6b;
									}
								}
							}
							if (direct == 3)
							{
								if (i <= 18 - x && j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == x + 2)
									{
										stonex[i][j] += n6b;
										stonexb[i][j] += n6b;
									}
								}
								if (i >= x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == x + 2)
									{
										stonex[i][j] += n6b;
										stonexb[i][j] += n6b;
									}
								}
							}
							firststone[direct][i][j] = -1;
							firststone[direct + 4][i][j] = -1;
							if (direct == 0)
							{
								if (i >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j] == -x - 2)
									{
										stonex[i][j] += n6w;
										stonexw[i][j] += n6w;
									}
								}
								if (i <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j] == -x - 2)
									{
										stonex[i][j] += n6w;
										stonexw[i][j] += n6w;
									}
								}
							}
							if (direct == 1)
							{
								if (i >= x&&j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i - x][j - x] == -x - 2)
									{
										stonex[i][j] += n6w;
										stonexw[i][j] += n6w;
									}
								}
								if (i <= 18 - x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i + x][j + x] == -x - 2)
									{
										stonex[i][j] += n6w;
										stonexw[i][j] += n6w;
									}
								}
							}
							if (direct == 2)
							{
								if (j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i][j - x] == -x - 2)
									{
										stonex[i][j] += n6w;
										stonexw[i][j] += n6w;
									}
								}
								if (j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i][j + x] == -x - 2)
									{
										stonex[i][j] += n6w;
										stonexw[i][j] += n6w;
									}
								}
							}
							if (direct == 3)
							{
								if (i <= 18 - x && j >= x)
								{
									if (firststone[direct][i][j] + firststone[direct][i + x][j - x] == -x - 2)
									{
										stonex[i][j] += n6w;
										stonexw[i][j] += n6w;
									}
								}
								if (i >= x&&j <= 18 - x)
								{
									if (firststone[direct + 4][i][j] + firststone[direct + 4][i - x][j + x] == -x - 2)
									{
										stonex[i][j] += n6w;
										stonexw[i][j] += n6w;
									}
								}
							}
							firststone[direct][i][j] = 0;
							firststone[direct + 4][i][j] = 0;
						}
					}*/
				}
			}
		}
	}
}
int chessboard::Evaluate(int *v1,int valstep)            //防守
{
	int val = 0;
	SeekLine(humcolor);                                                             //如果时间不够了可将二者合并以提高程序速度
	SeekLine(comcolor);
	val = 1 * sum[comcolor - 1][comcolor - 1] + 50 * sum[comcolor - 1][2] + 200 * sum[comcolor - 1][3] + 1000 * sum[comcolor-1][4]+10000*sum[comcolor-1][5] - (1 * sum[humcolor - 1][1] + 30 * sum[humcolor - 1][2] + 40 * sum[humcolor - 1][3] + 200 * sum[humcolor - 1][4] + 10000 * sum[humcolor - 1][5]);
	Set0();                                                                         //时刻注意更新
	*v1 = val;
	return val;
}
int chessboard::Evaluate1(int *v1,int valstep)      //攻击
{
	int val = 0;
	SeekLine(humcolor);                                                             //如果时间不够了可将二者合并以提高程序速度
	SeekLine(comcolor);
	val = -(1 * sum[comcolor - 1][1] + 50 * sum[comcolor - 1][2] + 200 * sum[comcolor - 1][3] + 1000 * sum[comcolor-1][4]+20000*sum[comcolor-1][5] - (1 * sum[humcolor - 1][1] + 30 * sum[humcolor - 1][2] + 40 * sum[humcolor - 1][3] + 200 * sum[humcolor - 1][4] + 6000 * sum[humcolor - 1][5]));
	Set0();                                                                         //时刻注意更新
	*v1 = val;
	return val;
}
void chessboard::Makenextmove(int *coord, int step,int Depth,int maxmin)
{
	coord[3] = step % 19;
	coord[2] = ((step - coord[3]) / 19) % 19;
	coord[1] = ((((step - coord[3]) / 19) - coord[2]) / 19) % 19;
	coord[0] = (((((step - coord[3]) / 19) - coord[2]) / 19) - coord[1]) / 19;
	if (maxmin % 2 == 0)
	{
		if (Depth % 2 == 0)
		{
			stone[coord[0]][coord[1]] = comcolor;
			stone[coord[2]][coord[3]] = comcolor;
		}

		else if (Depth % 2 == 1)
		{
			stone[coord[0]][coord[1]] = humcolor;
			stone[coord[2]][coord[3]] = humcolor;
		}
	}
	else if (maxmin%2==1)
	{
		if (Depth % 2 == 1)
		{
			stone[coord[0]][coord[1]] = comcolor;
			stone[coord[2]][coord[3]] = comcolor;
		}

		else if (Depth % 2 == 0)
		{
			stone[coord[0]][coord[1]] = humcolor;
			stone[coord[2]][coord[3]] = humcolor;
		}
	}
	
}
void chessboard::Maketextstep(int *coord, int step,int color)
{
	coord[3] = step % 19;
	coord[2] = ((step - coord[3]) / 19) % 19;
	coord[1] = ((((step - coord[3]) / 19) - coord[2]) / 19) % 19;
	coord[0] = (((((step - coord[3]) / 19) - coord[2]) / 19) - coord[1]) / 19;
	if (color == comcolor)
	{
		stone[coord[0]][coord[1]] = comcolor;
		stone[coord[2]][coord[3]] = comcolor;

	}
	else if (color == humcolor)
	{
		stone[coord[0]][coord[1]] = humcolor;
		stone[coord[2]][coord[3]] = humcolor;
	}
}
void chessboard::Maketextstepreal(int *coord)
{

		Ai_computer1(coord[0], coord[1]);
		STEP[N] = coord[0] * 19 + coord[1];
		N++;
		Ai_computer1(coord[2], coord[3]);
		STEP[N] = coord[2] * 19 + coord[3];
		N++;
}
void chessboard::UnMakenextmove(int *coord)
{
	stone[coord[0]][coord[1]] = 0;
	stone[coord[2]][coord[3]] = 0;
}

void chessboard::SeekMax1(int *step,int *valstep)                                          //寻找stonex的最大,并赋一个子的值
{
	int e = 0;
	int b = 0;
	int w = 0;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (stonex[i][j] >= e)
			{
				b = sum[0][1] + sum[0][2] + sum[0][3] + sum[0][4] + sum[0][5];
				w = sum[1][1] + sum[1][2] + sum[1][3] + sum[1][4] + sum[1][5];
				e = stonex[i][j];
				*step = i*19+j;
				*valstep = e;
			}
		}
	}
}
void chessboard::SeekMax2(int *step, int Step,int *valstep,int Valstep)
{
	int e = 0;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (stonex[i][j] >= e)
			{
				e = stonex[i][j];
				*step = ((Step * 19) + i) * 19 + j;
				*valstep = Valstep + e;
			}
		}
	}
}
void chessboard::SeekMaxFive(int *step,int *valstep)
{
	int b;
	int w;
	SeekLine(humcolor);
	b = sum[0][1] + sum[0][2] + sum[0][3] + sum[0][4] + sum[0][5];
	SeekLine(comcolor);
	w = sum[1][1] + sum[1][2] + sum[1][3] + sum[1][4] + sum[1][5];
	SetNull();
	for (int i =0; i < 5; i++)
	{
		SeekMax1(&step[i],&valstep[i]);                                                    //原来正常的step[i]值
		int p = (step[i] - (step[i]%19)) / 19;
		int q = step[i] % 19;
		stonex[p][q] = 0;
	}
	Set0();
}
void chessboard::SeekMax25(int *step1, int *step2, int Depth, int maxmin,int *valstep1, int *valstep2)
{
	SeekMaxFive(step1,valstep1);
	int n = 0;
	for (int i = 0; i < 5; i++)
	{
		int p = (step1[i] - (step1[i] % 19)) / 19;
		int q = step1[i] % 19;
		if (maxmin % 2 == 0)
		{
			if (Depth % 2 == 0)
			{
				stone[p][q] = comcolor;
			}
			else if (Depth % 2 == 1)
			{
				stone[p][q] = humcolor;
			}
		}
		else if (maxmin % 2 == 1)
		{
			if (Depth % 2 == 1)
			{
				stone[p][q] = comcolor;
			}

			else if (Depth % 2 == 0)
			{
				stone[p][q] = humcolor;
			}
		}
		int b;
		int w;
		SeekLine(humcolor);
		b = sum[0][1] + sum[0][2] + sum[0][3] + sum[0][4] + sum[0][5];
		SeekLine(comcolor);
		w = sum[1][1] + sum[1][2] + sum[1][3] + sum[1][4] + sum[1][5];
		SetNull();
		for (int j = 0; j < 5; j++)
		{
			SeekMax2(&step2[n],step1[i],&valstep2[n],valstep1[i]);
			int p = ((step2[n] - step2[n] % 19) / 19)%19;
			int q = step2[n] % 19;
			stonex[p][q] = 0;
			n++;
		}
		Set0();
		stone[p][q] = 0;
	}

}

int chessboard::Alphabeta(int v1Alpha, int v1Beta, int Depth, int maxmin,int valstep)
{

	int step1[5] = { -1, -1, -1, -1, -1 };
	int step2[25] =
	{ -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	};
	int valstep1[5] = { -1, -1, -1, -1, -1 };
	int valstep2[25] =
	{ -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	};
	int v1;
	int coord[4];
	int	v1best;
	int mvbest;

	SeekMax25(step1, step2, Depth, maxmin,valstep1,valstep2);
	v1best = -1000000;

	if (Depth == 0)
	{
			Evaluate(&v1,valstep);
		return v1;                             //到底是humcolor还是comcolor
	}
	else
	{
		for (int i = 0; i < 25; i++)
		{
			Makenextmove(coord, step2[i], Depth, maxmin);
            v1 = -Alphabeta(-v1Beta, -v1Alpha, Depth - 1, maxmin,valstep2[i]);
			UnMakenextmove(coord);
			if (v1 >= v1Beta)
			{
				return v1Beta;
			}
			if (v1 > v1Alpha)
			{
				mvbest = step2[i];
				v1Alpha = v1;
			}
		}
	}
	mvBesth = mvbest;                                                                  //记录人攻击及电脑防守最佳值
	return v1Alpha;
}
int chessboard::Alphabeta1(int v1Alpha, int v1Beta, int Depth, int maxmin, int valstep)
{

	int step1[5] = { -1, -1, -1, -1, -1 };
	int step2[25] =
	{ -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	};
	int valstep1[5] = { -1, -1, -1, -1, -1 };
	int valstep2[25] =
	{ -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1,
	};

	int v1;
	int coord[4];
	int	v1best;
	int mvbest;

	SeekMax25(step1, step2, Depth, maxmin, valstep1, valstep2);
	v1best = -1000000;

	if (Depth == 0)
	{
		Evaluate1(&v1,valstep);
		return v1;                             //到底是humcolor还是comcolor
	}
	else
	{
		for (int i = 0; i < 25; i++)
		{
			Makenextmove(coord, step2[i], Depth, maxmin);
			v1 = -Alphabeta1(-v1Beta, -v1Alpha, Depth - 1, maxmin, valstep2[i]);
			UnMakenextmove(coord);
			if (v1 >= v1Beta)
			{
				return v1Beta;
			}
			if (v1 > v1Alpha)
			{
				mvbest = step2[i];
				v1Alpha = v1;
			}
		}
	}
	mvBestc = mvbest;                                                           //记录电脑攻击最佳值
	return v1Alpha;
}
void chessboard::complex(int *coordh,int *coordc,int *c4, int *c5, int *h5,int *c6, int *h6)
{
	Alphabeta(-1000000, 1000000, 2, 2, 0);                                                        //获的人攻击及电脑防守最佳值
	Alphabeta1(-1000000, 1000000, 3, 3, 0);                                                     //获得电脑攻击最佳值

	Maketextstep(coordc, mvBestc, comcolor);
	SeekLine(humcolor);
	SeekLine(comcolor);
	*c6 = sum[comcolor - 1][5];
	*c5 = sum[comcolor - 1][4];
	*c4 = sum[comcolor - 1][3];
	Set0();
	UnMakenextmove(coordc);

	Maketextstep(coordh, mvBesth, humcolor);
	SeekLine(humcolor);
	SeekLine(comcolor);
	*h6 = sum[humcolor - 1][5];
	*h5 = sum[humcolor - 1][4];
	Set0();
	UnMakenextmove(coordh);
}
void chessboard::commove()
{

	one.SetSum1(humcolor);
	HWND wnd1 = GetHWnd();
	HWND wnd2 = GetHWnd();
	int b;
	int w;
	SeekLine(humcolor);
	b = sum[0][1] + sum[0][2] + sum[0][3] + sum[0][4] + sum[0][5];
	SeekLine(comcolor);
	w = sum[1][1] + sum[1][2] + sum[1][3] + sum[1][4] + sum[1][5];
	if (sum[humcolor - 1][5] > 0)                                                             // 注意sum和棋子颜色的对应，要减1；
	{
		MessageBox(wnd2, TEXT("你赢了！"), TEXT("结果"), MB_OK | MB_ICONWARNING);
		Set0();
		one.ResetSum1(humcolor);
	}
	else if (one.GetSum1(humcolor) == 1)
	{
		Ai_computer1(one.GetX() - 1, one.GetY() + 1);
		STEP[N] = (one.GetX() - 1) * 19 + one.GetY() + 1;
		N++;
		Ai_computer1(one.GetX() - 1, one.GetY());
		STEP[N] = (one.GetX() - 1) * 19 + one.GetY();
		N++;
		Set0();
		one.ResetSum1(humcolor);             //注意棋盘只要一改变，就要重新计算sum1，sum2.。。的数目
	}
	else
	{
//		int coords[4];                                                      //bf用于跳出两重循环		认输部分还存在bug
		if (grade == 3)
		{
			int c4, c5, c6,h5, h6;
			int coordh[4], coordc[4];
			Set0();
			complex(coordh, coordc, &c4, &c5,&h5,&c6, &h6);
			if (c6 > 0)                                                                   //白子能成连六，则走白子
			{
				Maketextstepreal(coordc);
			}
			else if(h6>0)                                                               //否则，黑子能成连六，走黑子
			{
				Maketextstepreal(coordh);
			}
			else if (c5 > 0)                                                           //白子走棋可成连五，说明白子现在有连四，白子可放心进攻
			{
				Maketextstepreal(coordc);
			}
			else if (h5 > 0)                                                           //否则白子无连四而黑子有连四，则百子需防守黑子
			{
				Maketextstepreal(coordh);
			}
			else if (c4 > 0)                                                           //若双方都无连四，则白子进攻，成连四
			{
				Maketextstepreal(coordc);
			}
			else                                                                       //若白子无法成连四，则守黑子
			{
				Maketextstepreal(coordh);
			}
		}
		else if (grade == 2)                                                              //会判断失误
		{
			int c4, c5, c6, h5, h6;
			int coordh[4], coordc[4];
			Set0();
			complex(coordh, coordc, &c4, &c5, &h5, &c6, &h6);
			if (c6 > 0)                                                                   //白子能成连六，则走白子
			{
				Maketextstepreal(coordc);
			}
			else if (h6>0)                                                               //否则，黑子能成连六，走黑子
			{
				Maketextstepreal(coordh);
			}
			else if (c4 > 0)                                                           //若双方都无连四，则白子进攻，成连四
			{
				Maketextstepreal(coordc);
			}
			else                                                                       //若白子无法成连四，则守黑子
			{
				Maketextstepreal(coordh);
			}
		}
		else if (grade == 1)                                                          //白子无法进攻，主动成连六
		{
			int c4, c5, c6, h5, h6;
			int coordh[4], coordc[4];
			Set0();
			complex(coordh, coordc, &c4, &c5, &h5, &c6, &h6);
			if (h6>0)                                                               //否则，黑子能成连六，走黑子
			{
				Maketextstepreal(coordh);
			}
			else if (c4 > 0)                                                           //若双方都无连四，则白子进攻，成连四
			{
				Maketextstepreal(coordc);
			}
			else                                                                       //若白子无法成连四，则守黑子
			{
				Maketextstepreal(coordh);
			}
		}
		b = sum[0][1] + sum[0][2] + sum[0][3] + sum[0][4] + sum[0][5];
		w = sum[1][1] + sum[1][2] + sum[1][3] + sum[1][4] + sum[1][5];
		SeekLine(humcolor);
		b = sum[0][1] + sum[0][2] + sum[0][3] + sum[0][4] + sum[0][5];
		SeekLine(comcolor);
		w = sum[1][1] + sum[1][2] + sum[1][3] + sum[1][4] + sum[1][5];
		if (sum[comcolor - 1][5] > 0)                                                             // 注意sum和棋子颜色的对应，要减1；
		{
			MessageBox(wnd1, TEXT("你输了！"), TEXT("结果"), MB_OK | MB_ICONWARNING);
			Set0();
			one.ResetSum1(humcolor);
		}
		Set0();
		one.ResetSum1(humcolor);
	}
}
void chessboard::imgboard()
{
	initgraph(1100, 960);
	setorigin(360, 80);//设置坐标原点为（360, 320）
	setbkcolor(LIGHTGRAY);// 设置背景色为浅灰色
	cleardevice();//用背景色清空屏幕
	setcolor(BLACK);// 设置边框绘图色为黑色
	setlinestyle(PS_SOLID, 3);//绘制实线，线宽为3
	//
	rectangle(-15, -15, 735, 735);// 画外矩形
	setfillcolor(BROWN);//设置填充颜色为黄色
	fillrectangle(-15, -15, 735, 735);//画填充矩形框

	setfillcolor(LIGHTBLUE);//设置填充颜色蓝色
	for (int i = 0; i < 5; i++)
	{
		rectangle(-270, -20+i*180, -90, 100+i*180);// 画小按钮
		fillrectangle(-270, -20 + i * 180, -90, 100 + i * 180);// 画填充小按钮                //(-270, -20, -90, 100)
	}																						//(-270, 160, -90, 280)
	TCHAR s1[] = _T("新棋局");														//(-270, 340, -90, 460)
	setlinecolor(WHITE);		// 设置文字颜色为白色 										//(-270, 520, -90, 640)
	setbkmode(TRANSPARENT);		// 设置文字背景为透明色									//(-270, 700, -90, 820)
	settextstyle(32, 0, _T("宋体"));
	outtextxy(-228, 24, s1);                                                                     //长加42，宽加44

	TCHAR s2[] = _T("悔棋");														//(-270, 340, -90, 460)
	outtextxy(-212, 204, s2);                                                                     //长加58，宽加44

	TCHAR s3[] = _T("认输");														//(-270, 340, -90, 460)
	outtextxy(-212, 384, s3);                                                                     //长加26，宽加44
	TCHAR s4[] = _T("存档");														//(-270, 340, -90, 460)
	outtextxy(-212, 564, s4);                                                                     //长加26，宽加44
	TCHAR s5[] = _T("复盘");														//(-270, 340, -90, 460)
	outtextxy(-212, 744, s5);                                                                     //长加26，宽加44

	setlinestyle(PS_SOLID, 2);//绘制实线，线宽为2
	setcolor(BLACK);//设置绘图色为黑色
	rectangle(0, 0, 720, 720);// 画内矩形
	for (int x = 0; x<720; x += 40) //画列线
	{
		line(x, 0, x, 720);
	}
	for (int y = 0; y<720; y += 40)//画行线
	{
		line(0, y, 720, y);
	}
	TCHAR snum0[] = _T("0");			
	TCHAR snum1[] = _T("1");
	TCHAR snum2[] = _T("2");
	TCHAR snum3[] = _T("3");
	TCHAR snum4[] = _T("4");
	TCHAR snum5[] = _T("5");
	TCHAR snum6[] = _T("6");
	TCHAR snum7[] = _T("7");
	TCHAR snum8[] = _T("8");
	TCHAR snum9[] = _T("9");
	TCHAR snum10[] = _T("10");
	TCHAR snum11[] = _T("11");
	TCHAR snum12[] = _T("12");
	TCHAR snum13[] = _T("13");
	TCHAR snum14[] = _T("14");
	TCHAR snum15[] = _T("15");
	TCHAR snum16[] = _T("16"); 
	TCHAR snum17[] = _T("17");
	TCHAR snum18[] = _T("18");

	setlinecolor(WHITE);		// 设置文字颜色为白色 										//(-270, 520, -90, 640)
	setbkmode(TRANSPARENT);		// 设置文字背景为透明色									//(-270, 700, -90, 820)
	settextstyle(32, 0, _T("楷体"));
	outtextxy(-9, -45, snum0);
	outtextxy(31, -45, snum1);
	outtextxy(71, -45, snum2);
	outtextxy(111, -45, snum3);
	outtextxy(151, -45, snum4);
	outtextxy(191, -45, snum5);
	outtextxy(231, -45, snum6);
	outtextxy(271, -45, snum7);
	outtextxy(311, -45, snum8);
	outtextxy(351, -45, snum9);
	outtextxy(382, -45, snum10);
	outtextxy(422, -45, snum11);
	outtextxy(462, -45, snum12);
	outtextxy(502, -45, snum13);
	outtextxy(542, -45, snum14);
	outtextxy(582, -45, snum15);
	outtextxy(622, -45, snum16);
	outtextxy(662, -45, snum17);
	outtextxy(702, -45, snum18);

	outtextxy(-35, -20, snum0);
	outtextxy(-35, 20, snum1);
	outtextxy(-35, 60, snum2);
	outtextxy(-35, 100, snum3);
	outtextxy(-35, 140, snum4);
	outtextxy(-35, 180, snum5);
	outtextxy(-35, 220, snum6);
	outtextxy(-35, 260, snum7);
	outtextxy(-35, 300, snum8);
	outtextxy(-35, 340, snum9);
	outtextxy(-45, 380, snum10);
	outtextxy(-45, 420, snum11);
	outtextxy(-45, 460, snum12);
	outtextxy(-45, 500, snum13);
	outtextxy(-45, 540, snum14);
	outtextxy(-45, 580, snum15);
	outtextxy(-45, 620, snum16);
	outtextxy(-45, 660, snum17);
	outtextxy(-45, 700, snum18);

	fl = 1;
	way = 1;
	humcolor = 1;
	comcolor = 2;
    fl = humcolor;
	grade =3;
	while (true)
	{
		if (humcolor == 2)
		{
			Ai_computer1(9, 9);
		}
		hummove();
		if (fl != -1 && way == 1 && fl != -2)
		{
			commove();
		}
		if (fl != -1 && way == 2 && fl != -2)
		{
			int color = humcolor;
			humcolor = comcolor;
			hummove();
			humcolor = color;
		}
	}
}
