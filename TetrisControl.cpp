//����˹������Ҫ�ĺ���
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
int g_BoxMarkRow = 0;//��ʼrow����λ��
int g_BoxMarkCol = 6;//��ʼcol����λ��
char g_szBox[][16] = {

	//�� �� �� ��
	{1,1,1,1,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//�� �� �� ��
	{1,1,1,1,
	 0,0,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//��
	//��
	//��
	//��
	{1,0,0,0,
	 1,0,0,0,
	 1,0,0,0,
	 1,0,0,0,
	},

	//��
	//��
	//��
	//��
	{1,0,0,0,
	 1,0,0,0,
	 1,0,0,0,
	 1,0,0,0,
	},

	//  ��
	//�� �� ��
	{0,1,0,0,
	 1,1,1,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//��
	//�� ��
	//��
	{1,0,0,0,
	 1,1,0,0,
	 1,0,0,0,
	 0,0,0,0,
	},

	//�� �� ��
	//  ��
	{1,1,1,0,
	 0,1,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},


	//  ��
	//�� ��
	//  ��
	{0,1,0,0,
	 1,1,0,0,
	 0,1,0,0,
	 0,0,0,0,
	},

	//��
	//�� �� ��
	{1,0,0,0,
	 1,1,1,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//�� ��
	//��  
	//��
	{1,1,0,0,
	 1,0,0,0,
	 1,0,0,0,
	 0,0,0,0,
	},

	//�� �� ��
	//    ��
	{1,1,1,0,
	 0,0,1,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//  �� 
	//  ��  
	//�� ��
	{0,1,0,0,
	 0,1,0,0,
	 1,1,0,0,
	 0,0,0,0,
	},

	//�� ��
	//  �� ��
	{1,1,0,0,
	 0,1,1,0,
	 0,0,0,0,
	 0,0,0,0,
	},
	//�� ��
	//  �� ��
	{1,1,0,0,
	 0,1,1,0,
	 0,0,0,0,
	 0,0,0,0,
	},

	//  ��
	//�� �� 
	//��
	{0,1,0,0,
	 1,1,0,0,
	 1,0,0,0,
	 0,0,0,0,
	},
	//  ��
	//�� �� 
	//��
	{0,1,0,0,
	 1,1,0,0,
	 1,0,0,0,
	 0,0,0,0,
	},

	//�� ��
	//�� ��
	{1,1,0,0,
	 1,1,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},
	//�� ��
	//�� ��
	{1,1,0,0,
	 1,1,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},
	//�� ��
	//�� ��
	{1,1,0,0,
	 1,1,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},
	//�� ��
	//�� ��
	{1,1,0,0,
	 1,1,0,0,
	 0,0,0,0,
	 0,0,0,0,
	},
};

//��ʼǽ
void InitWall() {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			if (j == 0 || j == COL - 1 || i == ROW - 1) {
				g_szTetris[i][j] = 1;
			}
		}
	}
}

//��ʼ������
void InitBox() {
	for (int i = 0; i < BOX_WIDTH; ++i) {
		for (int j = 0; j < BOX_WIDTH; ++j) {
			if (g_szBox[g_BoxIndex][i * BOX_WIDTH + j] == 1) {
				g_szTetris[g_BoxMarkRow + i][g_BoxMarkCol + j] = 2;//������д������飬2��Ϊ�˺�ǽ����
			}			
		}
	}
}

//��������
void CreateBox() {
	
	g_BoxType = rand() % 5;
	g_BoxShape = rand() % 4;
	g_BoxIndex = g_BoxType * 4 + g_BoxShape;
	g_BoxMarkRow = 0;//��ʼrow����λ��
	g_BoxMarkCol = 6;//��ʼcol����λ��
	InitBox();
}

//�������
void ClearBox() {
	for (int i = 0; i < BOX_WIDTH; ++i) {
		for (int j = 0; j < BOX_WIDTH; ++j) {
			if (g_szBox[g_BoxIndex][i * BOX_WIDTH + j] == 1) {
				g_szTetris[g_BoxMarkRow + i][g_BoxMarkCol + j] = 0;
			}
		}
	}
}

//�Ƿ���ƶ�����ת
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

//�̶����� 
void FixBox() {
	for (int i = 0; i < BOX_WIDTH; ++i) {
		for (int j = 0; j < BOX_WIDTH; ++j) {
			if (2 == g_szTetris[g_BoxMarkRow + i][g_BoxMarkCol + j]) {
				g_szTetris[g_BoxMarkRow + i][g_BoxMarkCol + j] = 3;//�̶����� 
			}
		}
	}
}

//��ת
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

//�����ƶ�
void MoveDown() {	
	if (CanBoxMoveOrSpin(g_BoxMarkRow+1, g_BoxMarkCol, g_BoxIndex)) {
		ClearBox();
		++g_BoxMarkRow;
		InitBox();
	}
	else {
		//�̶�����
		FixBox();
		//�Ƿ������
			//�ӷ�
				//�жϻ���
					//���ָߣ������ٶ���ӿ�
		//�����·���
		CreateBox();
		//��ʾ�·���
		ShowUI();
	}
}

//�����ƶ�
void MoveLeft() {
	if (CanBoxMoveOrSpin(g_BoxMarkRow, g_BoxMarkCol-1, g_BoxIndex)) {
		ClearBox();
		--g_BoxMarkCol;
		InitBox();
	}	
}

//�����ƶ�
void MoveRight() {
	if (CanBoxMoveOrSpin(g_BoxMarkRow, g_BoxMarkCol + 1, g_BoxIndex)) {
		ClearBox();
		++g_BoxMarkCol;
		InitBox();
	}	
}






//������
void ShowUI() {
	system("cls");
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			if (g_szTetris[i][j] == 1 || g_szTetris[i][j] == 2) {
				cout << "��";
			}
			else if (g_szTetris[i][j] == 3) {
				cout << "��";
			}
			else {
				cout << "  ";
			}
		}
		cout << endl;
	}
}

//���Ʒ���
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
			int ch = _getch();//��ͷҪ�����Σ���һ�κ���
			ch = _getch();//��72 ��75 ��77 ��80
			switch (ch) {
			case 72://��72
				MoveUp();
				ShowUI();
				break;
			case 75://��75
				MoveLeft();
				ShowUI();
				break;
			case 77://��77
				MoveRight();
				ShowUI();
				break;
			case 80://��80
				MoveDown();
				ShowUI();
				break;
			default:
				break;
			}			
		}
	}
}

//��ʼ��Ϸ
int StartGame() {
	srand((unsigned)time(NULL));
	//������
	InitWall();
	CreateBox();
	ShowUI();
	ControlBox();
	return 0;
}