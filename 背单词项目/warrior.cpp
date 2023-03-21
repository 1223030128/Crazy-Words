#include "warrior.h"


/*	warrior()սʿ���캯��
	1.��ʼ����ɫ��ֵ  ������ ��ɫ�������ֵ ��ǰ����ֵ��
	2.���ؽ�ɫͼ��
*/
warrior::warrior()
{
	this->AD = 10;					//Ĭ�Ϲ�����
	this->maxHP = 80;				//��ʼ���Ѫ��
	this->HP = this->maxHP;			//��ǰѪ��	
	this->last_HP = this->maxHP;	//��Ѫǰ��Ѫ��

	string png = ".png";
	//���ؽ�ɫͼƬ
	string path1 = "./resource/role/warrior/attack";
	string path2 = "./resource/role/warrior/die";
	string path3 = "./resource/role/warrior/idle";
	string path4 = "./resource/role/warrior/injury";
	
	for (int i = 1; i <= 17; i++)
	{
		string temp = path1;
		string num = to_string(i);
		path1.append(num);
		path1.append(png);
		loadimage(&this->attack[i-1], path1.c_str(), 9.25 * HeightPiece * 1.3513, 9.25* HeightPiece); //250/185 = 1.3513
		path1 = temp;
	}
	for (int i = 1; i <= 7; i++)
	{
		string temp = path2;
		string num = to_string(i);
		path2.append(num);
		path2.append(png);
		loadimage(&this->die[i - 1], path2.c_str(), 9.25 * HeightPiece * 1.3513, 9.25 * HeightPiece);
		path2 = temp;
	}
	for (int i = 1; i <= 4; i++)
	{
		string temp = path3;
		string num = to_string(i);
		path3.append(num);
		path3.append(png);
		loadimage(&this->idle[i - 1], path3.c_str(), 9.25 * HeightPiece * 1.3513, 9.25 * HeightPiece);
		path3 = temp;
	}
	for (int i = 1; i <= 3; i++)
	{
		string temp = path4;
		string num = to_string(i);
		path4.append(num);
		path4.append(png);
		loadimage(&this->injury[i - 1], path4.c_str(), 9.25 * HeightPiece * 1.3513, 9.25 * HeightPiece);
		path4 = temp;
	}
}

/*	void warrior::Judge() ���ڽ���սʿ�ĵ������
	1.���ݴ����msg ���ʳ��� �Ͷ��ڵ�letter���� ������������� 
	2.�ж��Ƿ�������ĸ  ���������ʹ������ĸ�洢��okLetter��
	3.ʹ�������ĸ�޷������(isClick = false)
	4.ִ������֮��currentֵ+1
*/
void warrior::Judge(ExMessage& msg, Letter* letter, char* okLetter, int wordLength, int& current, string& downLetter)
{
	for (size_t i = 0; i < wordLength; i++)
	{
		if (letter[i].isClickable)
		{
			switch (msg.message)
			{
				//������
			case WM_LBUTTONDOWN:
				if (msg.x >= letter[i].x1 && msg.y >= letter[i].y1 && msg.x <= letter[i].x2 && msg.y <= letter[i].y2)
				{
					letter[i].isClickable = false;//ʹ�䲻�ܱ����
					okLetter[current] = letter[i].ch;//���������ĸ�浽okLetter��
					current++;
					return;				//�ҵ�һ���Ͳ������жϺ������
				}
				break;
				//����ƶ�
			case WM_MOUSEMOVE:
				if (msg.x >= letter[i].x1 && msg.y >= letter[i].y1 && msg.x <= letter[i].x2 && msg.y <= letter[i].y2)
				{
					letter[i].isHover = true;
					//�ҵ�һ��֮��ֱ�Ӱ�֮���ȫ���false
					for (size_t j = i + 1; j < wordLength; j++)
					{
						if (letter[j].isClickable)
							letter[j].isHover = false;
					}
					return;				//�ҵ�һ���Ͳ������жϺ������
				}
				else//��ʾ��겻�ڵ�ǰ������ť��
					letter[i].isHover = false;
				break;
			}
		}
	}
	//for (size_t i = 0; i < wordLength; i++)
	//{
	//	if (!letter[i].isClickable) continue;
	//	if (letter[i].isClick(msg))
	//	{
	//		letter[i].isClickable = false;//ʹ�䲻�ܱ����
	//		okLetter[current] = letter[i].ch;//���������ĸ�浽okLetter��
	//		current++;
	//		return;				//�ҵ�һ���Ͳ������жϺ������
	//	}
	//}

}

/*	void warrior::Display()
	1.��ʾսʿ��ͼ��ָ��λ��
*/
void warrior::Display(unsigned long long times)
{

	int a = (times / 250) % 4;//250ms һ��
	img = idle[a];
	ImageTransparent(NULL, WidthPiece*3, HeightPiece*10.2, &img);
}

/*	void warrior::Attack()
	1.ʵ�ֹ�����Ч
	2.ʵ�ֹ�������
*/
void warrior::Attack(unsigned long long times)
{

	//��Ѫ����������	Ѫ��<=40ʱ ������ʹѪ���������(3~8) �����˺�������� 3~5��
	if (HP <= 40)
	{
		srand((unsigned)time(nullptr));			//���������
		last_HP = HP;							//��¼��ǰHP
		HP += ((rand()% 6)+5);					//������� 5~10��Ѫ

		AD = 13 + rand()%3;
	}
	else
	{
		AD = 10;
	}
	double dis = WidthPiece * 10 / 20;
	//�ߵ������м�
	for (size_t i = 0; i < 20; i++)
	{
		ImageTransparent(NULL, 0, 0 , &lstart);
		ImageTransparent(NULL, WidthPiece * 3 + dis*(i + 1), HeightPiece * 10.2, &idle[i % 4]);
		Sleep(15);
	}

	//���Ź�������
	for (size_t i = 0; i < 17; i++)
	{
		IMAGE img = attack[i];
		if (i == 3|| i==8|| i == 13)//�ӷ�������
			Sound(WarriorAttack);
		ImageTransparent(NULL, 0, 0, &lstart);
		ImageTransparent(NULL, WidthPiece * 3 + dis *20, HeightPiece * 10.2, &img);
		Sleep(80);
	}

	//�����߻�ȥ...
	for (size_t i = 20; i > 0; i--)
	{
		ImageTransparent(NULL, 0, 0, &lstart);
		ImageTransparent(NULL, WidthPiece * 3 + dis * (i + 1), HeightPiece * 10.2, &idle[i % 4]);
		Sleep(15);
	}
}

/*	void Injury(int value) ��Ѫ����
	������:	����ԣ
	1.��ҵ�valueֵ��Ѫ��
	2.��֤���Ѫ����СֵΪ0

	��չ:
	3.ʵ�����˶�������Ч
*/
void warrior::Injury(int value, unsigned long long times)
{
	this->last_HP = HP;
	this->HP -= value;
	if (HP < 0)
		this->HP = 0;

	for (size_t i = 0; i < 3; i++)
	{
		if(i == 0)
			Sound(InjuryEffect);
		IMAGE img = injury[i];
		ImageTransparent(NULL, 0, 0, &lstart);
		ImageTransparent(NULL, WidthPiece * 3, HeightPiece * 10.2, &img);
		Sleep(100);
	}
	if (HP == 0)
		Die();
}

void warrior::Die()
{
	for (size_t i = 0; i < 7; i++)
	{
		IMAGE img = die[i];
		ImageTransparent(NULL, 0, 0, &lstart);
		ImageTransparent(NULL, WidthPiece * 3, HeightPiece * 10.2, &img);
		Sleep(200);
	}
}