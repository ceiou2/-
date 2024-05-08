#include<iostream>
#include<time.h>//随机数种子
#include"conio.h" //用于_getch()无回显移动
using namespace std;

struct ken//链表构建队列储存视野
{
	int x;
	int y;
	ken* next;
};

void show_game(char arr[][25], ken* front)
{
	int map[50][25];
	if (front == NULL)
	{
		cout << "头指针为空，游戏出错！" << endl;
		return;
	}
	while (front != NULL)//队列中元素坐标为原点，+-2共5x5个坐标（可能边界）标注
	{
		for (int i = -2; i < 3; i++)
		{
			if (!((((front->x) + i) > -1) && ((front->x) + i) < 50))
			{
				continue;
			}
			for (int j = -2; j < 3; j++)
			{
				if (!((((front->y) + j) > -1) && ((front->y) + j) < 25))
				{
					continue;
				}
				map[(front->x) + i][(front->y) + j] = 1;
			}
		}

		front = front->next;
	}
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (map[j][i] == 1)
			{
				cout << arr[j][i];
			}
			else
			{
				cout << "E";
			}
		}
		cout << endl;
	}

}

void dig_map(char arr[][25], int dx, int dy, int step, bool& ed, int& ans, int map_ans[][25])//step实参实时记录当前路程 x y为坐标 ed为是否存在出口 0无 1有  ans为答案长度与难度
{

	while (1)
	{
		//记录南北东西四个方向的可挖掘性 0不 1可 t[0~3]为S N E W
		bool t[4] = { 0,0,0,0 };

		//检测挖掘可行方向
		if (((dy < 23)
			//判断落点四周除去来时方向外，所有方向不能存在空路，否则形成回路。（下3行代码
			&& (arr[dx][dy + 2] == '#')
			&& (arr[dx + 1][dy + 1] == '#')
			&& (arr[dx - 1][dy + 1] == '#')
			&& (arr[dx][dy + 1] == '#')
			&& (dx < 49) && (dx > 0))//排除边界情况
			|| ((ed == 0) && (step > 90) && (dy == 23)))
		{
			t[0] = 1;
		}
		if (((dy > 1)
			&& (arr[dx][dy - 2] == '#')
			&& (arr[dx - 1][dy - 1] == '#')
			&& (arr[dx + 1][dy - 1] == '#')
			&& (arr[dx][dy - 1] == '#')
			&& (dx < 49) && (dx > 0))
			|| ((ed == 0) && (step > 90) && (dy == 1)))
		{
			t[1] = 1;
		}
		if (((dx < 48)
			&& (arr[dx + 2][dy] == '#')
			&& (arr[dx + 1][dy + 1] == '#')
			&& (arr[dx + 1][dy - 1] == '#')
			&& (arr[dx + 1][dy] == '#')
			&& (arr[dx + 1][dy] == '#')
			&& (dy < 49) && (dy > 0))
			|| ((ed == 0) && (step > 90) && (dx == 48)))
		{
			t[2] = 1;
		}
		if (((dx > 1)
			&& (arr[dx - 2][dy] == '#')
			&& (arr[dx - 1][dy + 1] == '#')
			&& (arr[dx - 1][dy - 1] == '#')
			&& (arr[dx - 1][dy] == '#')
			&& (dy < 24) && (dy > 0))
			|| ((ed == 0) && (step > 90) && (dx == 1)))
		{
			t[3] = 1;
		}


		int tn = 0;//可行方向的数量
		for (int i = 0; i < 4; i++)
		{
			if (t[i] == 1)
			{
				tn++;
			}
		}

		if (tn == 0)
		{
			return;//无可挖掘，回退或挖掘结束
		}


		//在可行项中随机抽取挖掘方向

		int num = rand() % tn;


		int to = 0;//预设挖掘方向
		while (t[to] == 0)
		{
			to++;
		}
		for (int i = 0; i < num; i++)//确定挖掘方向为t[to]
		{
			to++;
			to = to % 4;
			if (t[to] == 0)
			{
				i--;
			}
		}

		//挖
		if (to == 0) //代表挖掘S
		{
			arr[dx][dy + 1] = ' ';
			if (ed == 0)//第一答案通路记录答案，此时存在可能回溯而记录的多余项
			{
				map_ans[dx][dy + 1] = 1;
			}
			if (dy + 1 == 24)
			{
				ed = 1;
				ans = step + 1;
			}
			else
			{
				dig_map(arr, dx, dy + 1, step + 1, ed, ans, map_ans);
				if (ed == 0)//去多余项
				{
					map_ans[dx][dy + 1] = 0;
				}
			}
		}

		if (to == 1) //代表挖掘N
		{
			arr[dx][dy - 1] = ' ';
			if (ed == 0)
			{
				map_ans[dx][dy - 1] = 1;
			}
			if (dy - 1 == 0)
			{
				ed = 1;
				ans = step + 1;
			}
			else
			{
				dig_map(arr, dx, dy - 1, step + 1, ed, ans, map_ans);
				if (ed == 0)
				{
					map_ans[dx][dy - 1] = 0;
				}
			}
		}
		if (to == 2) //代表挖掘E
		{
			arr[dx + 1][dy] = ' ';
			if (ed == 0)
			{
				map_ans[dx + 1][dy] = 1;
			}
			if (dx + 1 == 49)
			{
				ed = 1;
				ans = step + 1;
			}
			else
			{
				dig_map(arr, dx + 1, dy, step + 1, ed, ans, map_ans);
				if (ed == 0)
				{
					map_ans[dx + 1][dy] = 0;
				}
			}
		}
		if (to == 3) //代表挖掘W
		{
			arr[dx - 1][dy] = ' ';
			if (ed == 0)
			{
				map_ans[dx - 1][dy] = 1;
			}
			if (dx - 1 == 0)
			{
				ed = 1;
				ans = step + 1;
			}
			else
			{
				dig_map(arr, dx - 1, dy, step + 1, ed, ans, map_ans);
				if (ed == 0)
				{
					map_ans[dx - 1][dy] = 0;
				}
			}
		}

	}
}

void show_map(char arr[][25])//打印地图  arr[x列][y行]
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			cout << arr[j][i];
		}
		cout << endl;
	}
}

void show_ans(char arr[][25], int map_ans[][25])
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 50; j++)
		{

			if (map_ans[j][i] == 1)
			{
				cout << 'A';
			}
			else
			{
				cout << arr[j][i];
			}
		}
		cout << endl;
	}
}

int map_create(char arr[][25], int map_ans[][25])
{
	int ans = -1;//迷宫答案长度，难度系数，函数返回值
	for (int i = 0; i < 50; i++)//地图初始化，#为围墙
	{
		for (int j = 0; j < 25; j++)
		{
			arr[i][j] = '#';
			map_ans[i][j] = 0;
		}
	}

	arr[0][1] = ' ';//入口设置 ps出口随机挖




	//DFS挖迷宫
	int dx = 0;//挖机参数
	int dy = 1;

	ans = 0;

	bool ed = 0;//初始没有入口
	int step = 0;

	dig_map(arr, dx, dy, step, ed, ans, map_ans);//采用递归实现DFS挖掘迷宫地图。

	//show_map(arr);

	return ans;
}

bool play(char arr[][25], int map_ans[][25])//游戏操作部分，返回是否通过本关，1通过，0不通过
{
	int x = 0;
	int y = 1;//当前坐标初始化；
	char c;//记录操作  wasd分别上左下右移动

	ken* front = NULL;//队列以及初始化 rear队尾入队 front队头出队
	ken* rear = NULL;
	front = new ken;
	rear = front;
	rear->next = NULL;
	rear->x = 0;
	rear->y = 1;
	int que_num = 1;


	while (1)
	{

		system("cls");
		arr[x][y] = 'P';
		show_game(arr, front);
		cout << "请输出移动方向， w上 a左 s下 d右:" << endl;
		cout << "（或者输入‘t’以打开选项目录）" << endl;
		c = _getch();
		if (c == 'w')
		{
			if ((y == 0) || (arr[x][y - 1] == '#'))
			{
				continue;
			}
			else
			{
				arr[x][y] = ' ';
				y--;



				if (y == 0)
				{
					break;
				}
			}
		}
		else if (c == 'a')
		{
			if ((x == 0) || (arr[x - 1][y] == '#'))
			{
				continue;
			}
			else
			{
				arr[x][y] = ' ';
				x--;
				if ((x == 0) && (y != 1))
				{
					break;
				}
			}
		}
		else if (c == 's')
		{
			if ((y == 24) || (arr[x][y + 1] == '#'))
			{
				continue;
			}
			else
			{
				arr[x][y] = ' ';
				y++;
				if (y == 24)
				{
					break;
				}
			}
		}
		else if (c == 'd')
		{
			if ((x == 49) || (arr[x + 1][y] == '#'))
			{
				continue;
			}
			else
			{
				arr[x][y] = ' ';
				x++;
				if (x == 49)
				{
					break;
				}
			}
		}
		//入队列并检查队列是否满溢，溢出则出队列
		if (c == 'w' || c == 'a' || c == 's' || c == 'd')
		{
			rear->next = new ken;//入队计数
			rear = rear->next;
			rear->x = x;
			rear->y = y;
			rear->next = NULL;
			que_num++;
		}

		if (que_num > 20)//超过则出队
		{
			ken* temp = front;
			front = front->next;
			delete temp;
			temp = NULL;
			que_num--;
		}

		else if (c == 't')
		{
			while (1)
			{
				system("cls");
				cout << "选项：" << endl;
				cout << "输入n以退出关卡并返回主界面" << endl;
				cout << "输入m以获取当前关卡地图(无迷雾)" << endl;
				cout << "输入a以获取当前关卡答案" << endl;
				cout << "输入r以返回关卡继续游戏" << endl;
				cout << "输入s以跳过本关" << endl;
				char t;
				t = _getch();
				if (t == 'n')
				{
					system("cls");
					cout << "请确认是否退出关卡并返回主菜单" << endl;
					cout << "按下y键以确认退出" << endl;
					cout << "按下其他任意键以返回选项菜单" << endl;
					char o;
					o = _getch();
					if (o == 'y')
					{
						//释放new
						while (front != NULL)
						{
							ken* temp = front;
							front = front->next;
							delete temp;
							temp = NULL;
							que_num--;
						}

						return 0;
					}

				}
				if (t == 'm')
				{
					system("cls");
					show_map(arr);
					cout << "按下Enter键返回选项菜单" << endl;

					while (char s = cin.get())
					{
						if (s == '\n')
						{
							system("cls");
							break;
						}
					}
				}
				if (t == 'a')
				{
					system("cls");
					show_ans(arr, map_ans);
					cout << "按下Enter键返回选项菜单" << endl;

					while (char s = cin.get())
					{
						if (s == '\n')
						{
							system("cls");
							break;
						}
					}
				}
				if (t == 'r')
				{
					break;
				}
				if (t == 's')
				{
					return 1;
				}
			}
		}

	}
	while (front != NULL)//释放new
	{
		ken* temp = front;
		front = front->next;
		delete temp;
		temp = NULL;
		que_num--;
	}

	return 1;
}

void game()
{
	//地图创建
	char map0[50][25];//地图大小50x25，二维数组存放
	char map1[50][25];
	char map2[50][25];
	char map3[50][25];
	char map4[50][25];

	int map0_ans[50][25];//存放答案路径，1为路 0为非路
	int map1_ans[50][25];
	int map2_ans[50][25];
	int map3_ans[50][25];
	int map4_ans[50][25];


	srand(time(0));//设置随机数种子。

	int m[5][2];// m[0存放地图号码][1地图难度系数——答案长度]

	m[0][1] = map_create(map0, map0_ans);//地图生成以及难度系数导入

	//show_ans(map0, map0_ans);
	m[1][1] = map_create(map1, map1_ans);
	m[2][1] = map_create(map2, map2_ans);
	m[3][1] = map_create(map3, map3_ans);
	m[4][1] = map_create(map4, map4_ans);

	m[0][0] = 0;//地图号码初始化
	m[1][0] = 1;
	m[2][0] = 2;
	m[3][0] = 3;
	m[4][0] = 4;


	//地图选择

	for (int i = 0; i < 5; i++)//地图按照难度系数排序，创造5关卡难度递增  排序后m[k][0]=x,x为第k大难度的地图号码
	{
		for (int j = 0; j < 5 - i - 1; j++)
		{
			if (m[j][1] > m[j + 1][1])
			{
				int temp = m[j][0];
				m[j][0] = m[j + 1][0];
				m[j + 1][0] = temp;//m地图号码从m[0-4][0]低到高排序

				temp = m[j][1];
				m[j][1] = m[j + 1][1];
				m[j + 1][1] = temp;//地图难度同步交换
			}
		}
	}

	int map_now;//当前游戏地图
	int map_level;//当前难度



	bool ju;//判断是否通过当前关卡，为1通过，为0不通过，游戏结束。
	for (int i = 0; i < 5; i++)
	{
		map_now = m[i][0];//根据难度选择当前地图  i为难度 map_now为地图编号

		map_level = i;
		if (map_now == 0)
		{
			ju = play(map0, map0_ans);
			if (ju == 1)
			{
				system("cls");

				cout << "恭喜完成本关！按下Enter键开始下一关" << endl;

				while (char s = cin.get())
				{
					if (s == '\n')
					{
						system("cls");
						break;
					}
				}
			}
		}
		else if (map_now == 1)
		{
			ju = play(map1, map1_ans);
			if (ju == 1)
			{
				system("cls");

				cout << "恭喜完成本关！按下Enter键开始下一关" << endl;
				while (char s = cin.get())
				{
					if (s == '\n')
					{
						system("cls");
						break;
					}
				}
			}
		}
		else if (map_now == 2)
		{
			ju = play(map2, map2_ans);
			if (ju == 1)
			{
				system("cls");

				cout << "恭喜完成本关！按下Enter键开始下一关" << endl;
				while (char s = cin.get())
				{
					if (s == '\n')
					{
						system("cls");
						break;
					}
				}
			}
		}
		else if (map_now == 3)
		{
			ju = play(map3, map3_ans);
			if (ju == 1)
			{
				system("cls");

				cout << "恭喜完成本关！按下Enter键开始下一关" << endl;
				while (char s = cin.get())
				{
					if (s == '\n')
					{
						system("cls");
						break;
					}
				}
			}

		}
		else if (map_now == 4)
		{
			ju = play(map4, map4_ans);
		}

		if (ju == 0)
		{
			system("cls");
			cout << "游戏结束！您的得分是" << map_level << "分！" << endl;
			cout << "请按下Enter键以继续......" << endl;
			while (char s = cin.get())
			{
				if (s == '\n')
				{
					system("cls");
					break;
				}
			}
			return;
		}

	}

	system("cls");
	cout << "恭喜通关！" << endl;
	cout << "请按Enter键以继续" << endl;

	while (char s = cin.get())
	{
		if (s == '\n')
		{
			system("cls");
			break;
		}
	}
	return;
}

int main()
{
	while (1)
	{
		cout << "迷宫小游戏" << endl;
		cout << "规则:" << endl;
		cout << "一轮游戏共分为五关，分别对应难度1~5" << endl;
		cout << "字母P代表角色，'#'是墙无法越过，'E'是迷雾，迷雾中的地形不显示" << endl;
		cout << "玩家P通过按下‘w’‘a ’‘s’‘d’键移动" << endl;
		cout << "玩家P可在关卡中通过按下‘t’键打开游戏选项菜单" << endl;
		cout << "玩家可在游戏选项菜单中查看当前关卡地图答案以及退出关卡" << endl;
		cout << "" << endl;//规则补充——————————
		cout << "按下Enter键开始游戏！" << endl;
		cout << "输入‘k’退出游戏程序" << endl;

		while (char s = cin.get())//不断检测输入，若为enter则开始游戏
		{
			if (s == '\n')
			{
				system("cls");
				break;
			}
			if (s == 'k')
			{
				return 0;
			}
		}
		//游戏开始
		game();
	}
}