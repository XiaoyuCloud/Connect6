#include"chessboard.h"
int main()





{
	onestone one(18, 18, 4, 4);                                              //ע����ԴͼƬһ��Ҫʵʱת�ƣ�����
	chessboard easy(one);
	cout << firststone[0][9][9] << endl;
	easy.imgboard();
	_getch();
	closegraph();
	return 0;
}