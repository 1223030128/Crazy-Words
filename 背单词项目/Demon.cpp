#include "Demon.h"

/*	Demon()��ħ���캯��
	1.��ʼ����ֵ  ������ �����������ֵ ��ǰ����ֵ��
	2.����ͼ��
*/
Demon::Demon()
{
	this->AD = 4;					//Ĭ�Ϲ�����
	this->maxHP = 160;				//��ʼ���Ѫ��
	this->HP = this->maxHP;			//��ʼѪ��
	this->last_HP = this->maxHP;
	//���ع���ͼƬ
	string path1 = "./resource/monster/demon/attack";
	string path2 = "./resource/monster/demon/die";
	string path3 = "./resource/monster/demon/idle";
	string path4 = "./resource/monster/demon/injury";

	string png = ".png";

	for (int i = 1; i <= 18; i++)
	{
		string temp = path1;
		string num = to_string(i); 
		path1.append(num);
		path1.append(png);
		loadimage(&this->attack[i - 1], path1.c_str(), 9.8*HeightPiece*1.162, 9.8*HeightPiece); //43/37=1.162
		path1 = temp;
	}
	for (int i = 1; i <= 15; i++)
	{
		string temp = path2;
		string num = to_string(i);
		path2.append(num);
		path2.append(png);
		loadimage(&this->die[i - 1], path2.c_str(), 9.05 * HeightPiece*1.03125, 9.05 * HeightPiece); //33/32=1.03125
		path2 = temp;
	}
	for (int i = 1; i <= 11; i++)
	{
		string temp = path3;
		string num = to_string(i);
		path3.append(num);
		path3.append(png);
		loadimage(&this->idle[i - 1], path3.c_str(), 9.05 * HeightPiece * 0.75, 9.05 * HeightPiece);	//24*32   24/32 = 0.75
		path3 = temp;
	}
	for (int i = 1; i <= 8; i++)
	{
		string temp = path4;
		string num = to_string(i);
		path4.append(num);
		path4.append(png);
		loadimage(&this->injury[i - 1], path4.c_str(), 9.05 * HeightPiece*0.9375, 9.05 * HeightPiece); //30/32 = 0.9375
		path4 = temp;
	}
}


/*	void Demon::Display() 
	1.��ʾ������ͼ��ָ��λ��
	2.ʵ��վ������
*/
void Demon::Display(unsigned long long times)
{
	int a = (times / 100) % 11;//500ms һ��
	img = idle[a];
	ImageTransparent(NULL, WidthPiece * 26.3, HeightPiece * 10.2, &img);
}

/*	void Demon::Attack()
	1.ʵ�ֹ�����Ч
	2.ʵ�ֹ�������
*/
void Demon::Attack(unsigned long long times)
{
	//��Ѫ����������	��Ѫ�������˺��������2-10��
	//��Ѫ���и��ʻ�Ѫ +10
	if (HP <= 20)
	{
		srand((unsigned)time(nullptr));			//���������
		AD = 6 + rand() % 10;
		if (AD >= 12)
		{//���1/2����Ѫ��+5
			HP += 5;
			//last_HP = HP;
		}
	}
	else if(HP <= 60)
	{
		srand((unsigned)time(nullptr));			//���������
		AD = 6 + rand() % 4; //�������2 - 4��
		if (AD == 10)
		{//1/4����Ѫ��+5
			HP += 5;
			//last_HP = HP;
		}
	}
	else
	{
		AD = 4;
	}
	double dis = WidthPiece * 10 / 20;
	//�ߵ��м�
	for (size_t i = 0; i < 20; i++)
	{
		ImageTransparent(NULL, 0, 0, &rstart);
		ImageTransparent(NULL, WidthPiece * 26.3 - dis * (i + 1), HeightPiece * 10.2, &idle[i % 11]);
		Sleep(15);
	}
	//���Ź�������
	for (size_t i = 0; i < 18; i++)
	{
		IMAGE img = attack[i];
		ImageTransparent(NULL, 0, 0, &rstart);
		ImageTransparent(NULL, WidthPiece * 24 - dis*20, HeightPiece * 9.4, &img);
		if (i == 7)//�Ӹ�ͷʱ��������
		{
			Sound(WarriorAttack);
		}
		Sleep(100);
	}
	//�����߻�ȥ
	for (size_t i = 20; i > 0; i--)
	{
		ImageTransparent(NULL, 0, 0, &rstart);
		ImageTransparent(NULL, WidthPiece * 26.3 - dis * (i + 1), HeightPiece * 10.2, &idle[i % 11]);
		Sleep(15);
	}
}

/*	void Injury(int value) ��Ѫ����
	1.�����valueֵ��Ѫ��
	2.��֤Ѫ����СֵΪ0

	��չ:
	3.ʵ�ֹ������˶�������Ч
*/
void Demon::Injury(int value, unsigned long long times)
{
	this->last_HP = HP;
	this->HP -= value;
	if (HP < 0)
		this->HP = 0;

	for (size_t i = 0; i < 8; i++)
	{
		if (i == 0)
			Sound(InjuryEffect);
		IMAGE img = injury[i];
		ImageTransparent(NULL, 0, 0, &rstart);
		ImageTransparent(NULL, WidthPiece * 26.3, HeightPiece * 10.2, &img);
		Sleep(50);
	}
	if (HP == 0)
		Die();
}

void Demon::Die()
{
	for (size_t i = 0; i < 15; i++)
	{
		IMAGE img = die[i];
		ImageTransparent(NULL, 0, 0, &rstart);
		ImageTransparent(NULL, WidthPiece * 26.3, HeightPiece * 10.2, &img);
		Sleep(200);
	}
}