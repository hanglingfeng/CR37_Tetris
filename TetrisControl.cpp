//俄罗斯方块主要的函数
#include <iostream>
using namespace::std;
#include <time.h>
#include <conio.h>
void ShowUI();

#define ROW 16
#define COL 16
#define BOX_WIDTH 4
char g_szTetris[ROW][COL] = {};

int g_BoxType = 0;
int g_BoxShape = 0;
int g_BoxIndex = 0;
int g_BoxMarkRow = 0;//初始row出现位置
int g_BoxMarkCol = 6;//初始col出现位置
char g_szBox[][16] = {

	//■ ■ ■ ■
	{1,1,1,1,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//■ ■ ■ ■
	{1,1,1,1,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//■
	//■
	//■
	//■
	{1,0,0,0,
	 1,0,0,0,
	 1,0,0,0,
	 1,0,0,0,
	},

	//■
	//■
	//■
	//■
	{1,0,0,0,
	 1,0,0,0,
	 1,0,0,0,
	 1,0,0,0,
	},

	//  ■
	//■ ■ ■
	{0,1,0,0,
	 1,1,1,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//■
	//■ ■
	//■
	{1,0,0,0,
	 1,1,0,0,
	 1,0,0,0,
	 0,0,0,0,
	},

	//■ ■ ■
	//  ■
	{1,1,1,0,
	 0,1,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},


	//  ■
	//■ ■
	//  ■
	{0,1,0,0,
	 1,1,0,0,
	 0,1,0,0,
	 0,0,0,0,
	},

	//■
	//■ ■ ■
	{1,0,0,0,
	 1,1,1,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//■ ■
	//■  
	//■
	{1,1,0,0,
	 1,0,0,0,
	 1,0,0,0,
	 0,0,0,0,
	},

	//■ ■ ■
	//    ■
	{1,1,1,0,
	 0,0,1,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//  ■ 
	//  ■  
	//■ ■
	{0,1,0,0,
	 0,1,0,0,
	 1,1,0,0,
	 0,0,0,0,
	},

	//■ ■
	//  ■ ■
	{1,1,0,0,
	 0,1,1,0,
	 0,0,0,0,
	 0,0,0,0,
	},
	//■ ■
	//  ■ ■
	{1,1,0,0,
	 0,1,1,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//  ■
	//■ ■ 
	//■
	{0,1,0,0,
	 1,1,0,0,
	 1,0,0,0,
	 0,0,0,0,
	},
	//  ■
	//■ ■ 
	//■
	{0,1,0,0,
	 1,1,0,0,
	 1,0,0,0,
	 0,0,0,0,
	},

	//■ ■
	//■ ■
	{1,1,0,0,
	 1,1,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},
	//■ ■
	//■ ■
	{1,1,0,0,
	 1,1,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},
	//■ ■
	//■ ■
	{1,1,0,0,
	 1,1,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},
	//■ ■
	//■ ■
	{1,1,0,0,
	 1,1,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},
};

//初始墙
void InitWall() {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			if (j == 0 || j == COL - 1 || i == ROW - 1) {
				g_szTetris[i][j] = 1;
			}
		}
	}
}

//初始化方块
void InitBox() {
	for (int i = 0; i < BOX_WIDTH; ++i) {
		for (int j = 0; j < BOX_WIDTH; ++j) {
			if (g_szBox[g_BoxIndex][i * BOX_WIDTH + j] == 1) {
				g_szTetris[g_BoxMarkRow + i][g_BoxMarkCol + j] = 2;//将方块写入大数组，2是为了和墙区分
			}			
		}
	}
}

//创建方块
void CreateBox() {
	
	g_BoxType = rand() % 5;
	g_BoxShape = rand() % 4;
	g_BoxIndex = g_BoxType * 4 + g_BoxShape;
	g_BoxMarkRow = 0;//初始row出现位置
	g_BoxMarkCol = 6;//初始col出现位置
	InitBox();
}

//清除方块
void ClearBox() {
	for (int i = 0; i < BOX_WIDTH; ++i) {
		for (int j = 0; j < BOX_WIDTH; ++j) {
			if (g_szBox[g_BoxIndex][i * BOX_WIDTH + j] == 1) {
				g_szTetris[g_BoxMarkRow + i][g_BoxMarkCol + j] = 0;
			}
		}
	}
}

//是否可移动或旋转
bool CanBoxMoveOrSpin(int boxMarkRow, int boxMarkCol, int boxIndex) {
	for (int i = 0; i < BOX_WIDTH; ++i) {
		for (int j = 0; j < BOX_WIDTH; ++j) {
			if (1 == g_szTetris[boxMarkRow + i][boxMarkCol + j] &&	1 == g_szBox[i][j + boxIndex] ||
				3 == g_szTetris[boxMarkRow + i][boxMarkCol + j] && 1 == g_szBox[i][j + boxIndex]) {
				return false;
			}
		}
	}
	return true;
}

//固定方块 
void FixBox() {
	for (int i = 0; i < BOX_WIDTH; ++i) {
		for (int j = 0; j < BOX_WIDTH; ++j) {
			if (2 == g_szTetris[g_BoxMarkRow + i][g_BoxMarkCol + j]) {
				g_szTetris[g_BoxMarkRow + i][g_BoxMarkCol + j] = 3;//固定方块 
			}
		}
	}
}

//旋转
void MoveUp() {
	int boxShape = (g_BoxShape + 1) % 4;
	int boxIndex = g_BoxType * 4 + g_BoxShape;
	if (CanBoxMoveOrSpin(g_BoxMarkRow, g_BoxMarkCol, boxIndex)) {
		ClearBox();
		g_BoxShape = boxShape;
		g_BoxIndex = boxIndex;
		InitBox();
	}
}

//向下移动
void MoveDown() {	
	if (CanBoxMoveOrSpin(g_BoxMarkRow+1, g_BoxMarkCol, g_BoxIndex)) {
		ClearBox();
		++g_BoxMarkRow;
		InitBox();
	}
	else {
		//固定方块
		FixBox();
		//是否可消行
			//加分
				//判断积分
					//积分高，下落速度则加快
		//产生新方块
		CreateBox();
		//显示新房快
		ShowUI();
	}
}

//向左移动
void MoveLeft() {
	if (CanBoxMoveOrSpin(g_BoxMarkRow, g_BoxMarkCol-1, g_BoxIndex)) {
		ClearBox();
		--g_BoxMarkCol;
		InitBox();
	}	
}

//向右移动
void MoveRight() {
	if (CanBoxMoveOrSpin(g_BoxMarkRow, g_BoxMarkCol + 1, g_BoxIndex)) {
		ClearBox();
		++g_BoxMarkCol;
		InitBox();
	}	
}






//画界面
void ShowUI() {
	system("cls");
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			if (g_szTetris[i][j] == 1 || g_szTetris[i][j] == 2) {
				cout << "■";
			}
			else if (g_szTetris[i][j] == 3) {
				cout << "□";
			}
			else {
				cout << "  ";
			}
		}
		cout << endl;
	}
}

//控制方块
void ControlBox() {
	clock_t lastTime = clock();

	while (true) {
		clock_t currentTime = clock();
		if (currentTime - lastTime > 1000) {
			lastTime = currentTime;
			MoveDown();
			ShowUI();
		}
		if (_kbhit()) {
			int ch = _getch();//箭头要按两次，第一次忽略
			ch = _getch();//上72 左75 右77 下80
			switch (ch) {
			case 72://上72
				MoveUp();
				ShowUI();
				break;
			case 75://左75
				MoveLeft();
				ShowUI();
				break;
			case 77://右77
				MoveRight();
				ShowUI();
				break;
			case 80://下80
				MoveDown();
				ShowUI();
				break;
			default:
				break;
			}			
		}
	}
}

//开始游戏
int StartGame() {
	srand((unsigned)time(NULL));
	//画界面
	InitWall();
	CreateBox();
	ShowUI();
	ControlBox();
	return 0;
}