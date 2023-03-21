#include "mage.h"

mage::mage()
{
	this->AD = 15;					//Ĭ�Ϲ�����
	this->maxHP = 50;				//��ʼ���Ѫ��
	this->HP = this->maxHP;			//��ǰѪ��	
	this->last_HP = this->maxHP;	//��Ѫǰ��Ѫ��

	string png = ".png";
	//���ؽ�ɫͼƬ
	string path1 = "./resource/role/mage/attack";
	string path2 = "./resource/role/mage/die";
	string path3 = "./resource/role/mage/idle";
	string path4 = "./resource/role/mage/injury";

	for (int i = 1; i <= 9; i++)
	{
		string temp = path1;
		string num = to_string(i);
		path1.append(num);
		path1.append(png);
		loadimage(&this->attack[i - 1], path1.c_str(), 2.26 * HeightPiece * 10, HeightPiece * 10);//452/200 = 2.26
		path1 = temp;
	}
	for (int i = 1; i <= 12; i++)
	{
		string temp = path2;
		string num = to_string(i);
		path2.append(num);
		path2.append(png);
		loadimage(&this->die[i - 1], path2.c_str(), 0.667 * HeightPiece * 10, HeightPiece * 10);
		path2 = temp;
	}
	for (int i = 1; i <= 6; i++)
	{
		string temp = path3;
		string num = to_string(i);
		path3.append(num);
		path3.append(png);
		loadimage(&this->idle[i - 1], path3.c_str(), 0.667 * HeightPiece * 10, HeightPiece*10); //32/48 = 0.667 
		path3 = temp;
	}
	for (int i = 1; i <= 3; i++)
	{
		string temp = path4;
		string num = to_string(i);
		path4.append(num);
		path4.append(png);
		loadimage(&this->injury[i - 1], path4.c_str(), 0.667 * HeightPiece * 10, HeightPiece * 10);
		path4 = temp;
	}
}

/*	void mage::Judge() 
	���ռ�������
*/
void mage::Judge(ExMessage& msg, Letter* letter, char* okLetter, int wordLength, int& current,string& downLetter)
{
	char c = 0;
	switch (msg.message)
	{
	case WM_KEYDOWN:
		if (msg.vkcode >= 65 && msg.vkcode <= 90)//�������ĸ����
		{
			cout << msg.vkcode << endl;
			if (letter[current].ch <= 90) //���ƴд����ĸ�Ǵ�д��ĸ
			{
				okLetter[current] = msg.vkcode;//���д��ĸ��okLetter��
				cout << (int)letter[current].ch << endl;
				cout << "�洢��д��ĸ" << okLetter[current] << endl;


				if (downLetter.size() <= 25) //���һ������ʾ��ô�����ĸ
				{
					downLetter.push_back(msg.vkcode);
				}
				else
				{
					downLetter.erase(0, 1);//ɾ����һ���ַ�
					downLetter.push_back(msg.vkcode);
				}
			}
			else
			{
				okLetter[current] = msg.vkcode + 32;//תΪСд��ĸȻ��洢��okLetter��
				cout << "�洢Сд��ĸ" << okLetter[current] << endl;

				if (downLetter.size() <= 25) //���һ������ʾ��ô�����ĸ
				{
					downLetter.push_back(msg.vkcode+32);
				}
				else
				{
					downLetter.erase(0, 1);//ɾ����һ���ַ�
					downLetter.push_back(msg.vkcode+32);
				}

			}
			current++;

		}
	}

}

/*	void mage::Display()
	1.��ʾ��ͼ��ָ��λ��
*/
void mage::Display(unsigned long long times)
{

	int a = (times / 200) % 6;//200ms һ��
	img = idle[a];
	ImageTransparent(NULL, WidthPiece*5, HeightPiece * 11, &img);
}

/*	void mage::Attack()
	1.ʵ�ֹ�����Ч
	2.ʵ�ֹ�������
*/
void mage::Attack(unsigned long long times)
{
	double dis = WidthPiece * 10 / 20;
	if (HP != maxHP)//���Ѫ����Ϊ��Ѫ
	{
		srand((unsigned)time(nullptr));			//���������
		this->last_HP = HP;	//��ѪǰѪ��
		AD = 20 + rand()%((maxHP - HP))/2;
		HP += rand() % ((maxHP - HP) / 2);//����ظ�  (0 ~ ��Ѫ��)/2 ��Ѫ��
		//last_HP = HP;
	}
	else
	{
		AD = 15;
	}
	////�ߵ������м�
	//for (size_t i = 0; i < 20; i++)
	//{
	//	ImageTransparent(NULL, 0, 0, &lstart);
	//	ImageTransparent(NULL, WidthPiece * 5 + dis * (i + 1), HeightPiece * 11, &idle[i % 2]);
	//	Sleep(20);
	//}
	//���Ź�������
	for (size_t i = 0; i < 9; i++)
	{
		IMAGE img = attack[i];

		if (i == 5)//��������
			Sound(MageAttack);
		ImageTransparent(NULL, 0, 0, &lstart);
		ImageTransparent(NULL, WidthPiece * 5 - 18, HeightPiece * 11, &img);
		Sleep(200);
	}
	img = idle[0];
	ImageTransparent(NULL, 0, 0, &lstart);
	ImageTransparent(NULL, WidthPiece * 5, HeightPiece * 11, &img);

	//�����߻�ȥ...
	//for (size_t i = 20; i > 0; i--)
	//{
	//	ImageTransparent(NULL, 0, 0, &lstart);
	//	ImageTransparent(NULL, WidthPiece * 5 + dis * (i + 1), HeightPiece * 11, &idle[i % 2]);
	//	Sleep(20);
	//}
}

/*	void Injury(int value) ��Ѫ����
	������:	����ԣ
	1.��ҵ�valueֵ��Ѫ��
	2.��֤���Ѫ����СֵΪ0

	��չ:
	3.ʵ�����˶�������Ч
*/
void mage::Injury(int value, unsigned long long times)
{
	srand((unsigned)time(nullptr));			//���������
	value += rand() % 5;  //�ܵ��˺�������� 0~4��
	this->last_HP = HP;
	this->HP -= value;
	if (HP < 0)
		this->HP = 0;

	for (size_t i = 0; i < 3; i++)
	{
		if (i == 0)
			Sound(InjuryEffect);
		IMAGE img = injury[i];
		ImageTransparent(NULL, 0, 0, &lstart);
		ImageTransparent(NULL, WidthPiece * 5, HeightPiece * 11, &img);
		Sleep(200);
	}
	if (HP == 0)
		Die();
}

void mage::Die()
{
	for (size_t i = 0; i < 12; i++)
	{
		IMAGE img = die[i];
		ImageTransparent(NULL, 0, 0, &lstart);
		ImageTransparent(NULL, WidthPiece * 5, HeightPiece * 11, &img);
		Sleep(200);
	}
}