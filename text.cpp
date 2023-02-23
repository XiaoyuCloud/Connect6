#include"chessboard.h"
int main()





{
	onestone one(18, 18, 4, 4);                                              //注意资源图片一定要实时转移！！！
	chessboard easy(one);
	cout << firststone[0][9][9] << endl;
	easy.imgboard();
	_getch();
	closegraph();
	return 0;
}