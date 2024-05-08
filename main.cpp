#include<iostream>
#include<time.h>//���������
#include"conio.h" //����_getch()�޻����ƶ�
using namespace std;

struct ken//���������д�����Ұ
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
		cout << "ͷָ��Ϊ�գ���Ϸ����" << endl;
		return;
	}
	while (front != NULL)//������Ԫ������Ϊԭ�㣬+-2��5x5�����꣨���ܱ߽磩��ע
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

void dig_map(char arr[][25], int dx, int dy, int step, bool& ed, int& ans, int map_ans[][25])//stepʵ��ʵʱ��¼��ǰ·�� x yΪ���� edΪ�Ƿ���ڳ��� 0�� 1��  ansΪ�𰸳������Ѷ�
{

	while (1)
	{
		//��¼�ϱ������ĸ�����Ŀ��ھ��� 0�� 1�� t[0~3]ΪS N E W
		bool t[4] = { 0,0,0,0 };

		//����ھ���з���
		if (((dy < 23)
			//�ж�������ܳ�ȥ��ʱ�����⣬���з����ܴ��ڿ�·�������γɻ�·������3�д���
			&& (arr[dx][dy + 2] == '#')
			&& (arr[dx + 1][dy + 1] == '#')
			&& (arr[dx - 1][dy + 1] == '#')
			&& (arr[dx][dy + 1] == '#')
			&& (dx < 49) && (dx > 0))//�ų��߽����
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


		int tn = 0;//���з��������
		for (int i = 0; i < 4; i++)
		{
			if (t[i] == 1)
			{
				tn++;
			}
		}

		if (tn == 0)
		{
			return;//�޿��ھ򣬻��˻��ھ����
		}


		//�ڿ������������ȡ�ھ���

		int num = rand() % tn;


		int to = 0;//Ԥ���ھ���
		while (t[to] == 0)
		{
			to++;
		}
		for (int i = 0; i < num; i++)//ȷ���ھ���Ϊt[to]
		{
			to++;
			to = to % 4;
			if (t[to] == 0)
			{
				i--;
			}
		}

		//��
		if (to == 0) //�����ھ�S
		{
			arr[dx][dy + 1] = ' ';
			if (ed == 0)//��һ��ͨ·��¼�𰸣���ʱ���ڿ��ܻ��ݶ���¼�Ķ�����
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
				if (ed == 0)//ȥ������
				{
					map_ans[dx][dy + 1] = 0;
				}
			}
		}

		if (to == 1) //�����ھ�N
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
		if (to == 2) //�����ھ�E
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
		if (to == 3) //�����ھ�W
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

void show_map(char arr[][25])//��ӡ��ͼ  arr[x��][y��]
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
	int ans = -1;//�Թ��𰸳��ȣ��Ѷ�ϵ������������ֵ
	for (int i = 0; i < 50; i++)//��ͼ��ʼ����#ΪΧǽ
	{
		for (int j = 0; j < 25; j++)
		{
			arr[i][j] = '#';
			map_ans[i][j] = 0;
		}
	}

	arr[0][1] = ' ';//������� ps���������




	//DFS���Թ�
	int dx = 0;//�ڻ�����
	int dy = 1;

	ans = 0;

	bool ed = 0;//��ʼû�����
	int step = 0;

	dig_map(arr, dx, dy, step, ed, ans, map_ans);//���õݹ�ʵ��DFS�ھ��Թ���ͼ��

	//show_map(arr);

	return ans;
}

bool play(char arr[][25], int map_ans[][25])//��Ϸ�������֣������Ƿ�ͨ�����أ�1ͨ����0��ͨ��
{
	int x = 0;
	int y = 1;//��ǰ�����ʼ����
	char c;//��¼����  wasd�ֱ����������ƶ�

	ken* front = NULL;//�����Լ���ʼ�� rear��β��� front��ͷ����
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
		cout << "������ƶ����� w�� a�� s�� d��:" << endl;
		cout << "���������롮t���Դ�ѡ��Ŀ¼��" << endl;
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
		//����в��������Ƿ����磬����������
		if (c == 'w' || c == 'a' || c == 's' || c == 'd')
		{
			rear->next = new ken;//��Ӽ���
			rear = rear->next;
			rear->x = x;
			rear->y = y;
			rear->next = NULL;
			que_num++;
		}

		if (que_num > 20)//���������
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
				cout << "ѡ�" << endl;
				cout << "����n���˳��ؿ�������������" << endl;
				cout << "����m�Ի�ȡ��ǰ�ؿ���ͼ(������)" << endl;
				cout << "����a�Ի�ȡ��ǰ�ؿ���" << endl;
				cout << "����r�Է��عؿ�������Ϸ" << endl;
				cout << "����s����������" << endl;
				char t;
				t = _getch();
				if (t == 'n')
				{
					system("cls");
					cout << "��ȷ���Ƿ��˳��ؿ����������˵�" << endl;
					cout << "����y����ȷ���˳�" << endl;
					cout << "��������������Է���ѡ��˵�" << endl;
					char o;
					o = _getch();
					if (o == 'y')
					{
						//�ͷ�new
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
					cout << "����Enter������ѡ��˵�" << endl;

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
					cout << "����Enter������ѡ��˵�" << endl;

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
	while (front != NULL)//�ͷ�new
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
	//��ͼ����
	char map0[50][25];//��ͼ��С50x25����ά������
	char map1[50][25];
	char map2[50][25];
	char map3[50][25];
	char map4[50][25];

	int map0_ans[50][25];//��Ŵ�·����1Ϊ· 0Ϊ��·
	int map1_ans[50][25];
	int map2_ans[50][25];
	int map3_ans[50][25];
	int map4_ans[50][25];


	srand(time(0));//������������ӡ�

	int m[5][2];// m[0��ŵ�ͼ����][1��ͼ�Ѷ�ϵ�������𰸳���]

	m[0][1] = map_create(map0, map0_ans);//��ͼ�����Լ��Ѷ�ϵ������

	//show_ans(map0, map0_ans);
	m[1][1] = map_create(map1, map1_ans);
	m[2][1] = map_create(map2, map2_ans);
	m[3][1] = map_create(map3, map3_ans);
	m[4][1] = map_create(map4, map4_ans);

	m[0][0] = 0;//��ͼ�����ʼ��
	m[1][0] = 1;
	m[2][0] = 2;
	m[3][0] = 3;
	m[4][0] = 4;


	//��ͼѡ��

	for (int i = 0; i < 5; i++)//��ͼ�����Ѷ�ϵ�����򣬴���5�ؿ��Ѷȵ���  �����m[k][0]=x,xΪ��k���Ѷȵĵ�ͼ����
	{
		for (int j = 0; j < 5 - i - 1; j++)
		{
			if (m[j][1] > m[j + 1][1])
			{
				int temp = m[j][0];
				m[j][0] = m[j + 1][0];
				m[j + 1][0] = temp;//m��ͼ�����m[0-4][0]�͵�������

				temp = m[j][1];
				m[j][1] = m[j + 1][1];
				m[j + 1][1] = temp;//��ͼ�Ѷ�ͬ������
			}
		}
	}

	int map_now;//��ǰ��Ϸ��ͼ
	int map_level;//��ǰ�Ѷ�



	bool ju;//�ж��Ƿ�ͨ����ǰ�ؿ���Ϊ1ͨ����Ϊ0��ͨ������Ϸ������
	for (int i = 0; i < 5; i++)
	{
		map_now = m[i][0];//�����Ѷ�ѡ��ǰ��ͼ  iΪ�Ѷ� map_nowΪ��ͼ���

		map_level = i;
		if (map_now == 0)
		{
			ju = play(map0, map0_ans);
			if (ju == 1)
			{
				system("cls");

				cout << "��ϲ��ɱ��أ�����Enter����ʼ��һ��" << endl;

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

				cout << "��ϲ��ɱ��أ�����Enter����ʼ��һ��" << endl;
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

				cout << "��ϲ��ɱ��أ�����Enter����ʼ��һ��" << endl;
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

				cout << "��ϲ��ɱ��أ�����Enter����ʼ��һ��" << endl;
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
			cout << "��Ϸ���������ĵ÷���" << map_level << "�֣�" << endl;
			cout << "�밴��Enter���Լ���......" << endl;
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
	cout << "��ϲͨ�أ�" << endl;
	cout << "�밴Enter���Լ���" << endl;

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
		cout << "�Թ�С��Ϸ" << endl;
		cout << "����:" << endl;
		cout << "һ����Ϸ����Ϊ��أ��ֱ��Ӧ�Ѷ�1~5" << endl;
		cout << "��ĸP�����ɫ��'#'��ǽ�޷�Խ����'E'�����������еĵ��β���ʾ" << endl;
		cout << "���Pͨ�����¡�w����a ����s����d�����ƶ�" << endl;
		cout << "���P���ڹؿ���ͨ�����¡�t��������Ϸѡ��˵�" << endl;
		cout << "��ҿ�����Ϸѡ��˵��в鿴��ǰ�ؿ���ͼ���Լ��˳��ؿ�" << endl;
		cout << "" << endl;//���򲹳䡪������������������
		cout << "����Enter����ʼ��Ϸ��" << endl;
		cout << "���롮k���˳���Ϸ����" << endl;

		while (char s = cin.get())//���ϼ�����룬��Ϊenter��ʼ��Ϸ
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
		//��Ϸ��ʼ
		game();
	}
}