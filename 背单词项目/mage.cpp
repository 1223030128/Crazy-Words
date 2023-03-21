#include "mage.h"

mage::mage()
{
	this->AD = 15;					//默认攻击力
	this->maxHP = 50;				//初始最大血量
	this->HP = this->maxHP;			//当前血量	
	this->last_HP = this->maxHP;	//扣血前的血量

	string png = ".png";
	//加载角色图片
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
	接收键盘输入
*/
void mage::Judge(ExMessage& msg, Letter* letter, char* okLetter, int wordLength, int& current,string& downLetter)
{
	char c = 0;
	switch (msg.message)
	{
	case WM_KEYDOWN:
		if (msg.vkcode >= 65 && msg.vkcode <= 90)//如果是字母输入
		{
			cout << msg.vkcode << endl;
			if (letter[current].ch <= 90) //如果拼写的字母是大写字母
			{
				okLetter[current] = msg.vkcode;//存大写字母到okLetter中
				cout << (int)letter[current].ch << endl;
				cout << "存储大写字母" << okLetter[current] << endl;


				if (downLetter.size() <= 25) //最多一次性显示这么多个字母
				{
					downLetter.push_back(msg.vkcode);
				}
				else
				{
					downLetter.erase(0, 1);//删除第一个字符
					downLetter.push_back(msg.vkcode);
				}
			}
			else
			{
				okLetter[current] = msg.vkcode + 32;//转为小写字母然后存储到okLetter中
				cout << "存储小写字母" << okLetter[current] << endl;

				if (downLetter.size() <= 25) //最多一次性显示这么多个字母
				{
					downLetter.push_back(msg.vkcode+32);
				}
				else
				{
					downLetter.erase(0, 1);//删除第一个字符
					downLetter.push_back(msg.vkcode+32);
				}

			}
			current++;

		}
	}

}

/*	void mage::Display()
	1.显示贴图到指定位置
*/
void mage::Display(unsigned long long times)
{

	int a = (times / 200) % 6;//200ms 一次
	img = idle[a];
	ImageTransparent(NULL, WidthPiece*5, HeightPiece * 11, &img);
}

/*	void mage::Attack()
	1.实现攻击音效
	2.实现攻击动画
*/
void mage::Attack(unsigned long long times)
{
	double dis = WidthPiece * 10 / 20;
	if (HP != maxHP)//如果血量不为满血
	{
		srand((unsigned)time(nullptr));			//随机数种子
		this->last_HP = HP;	//回血前血量
		AD = 20 + rand()%((maxHP - HP))/2;
		HP += rand() % ((maxHP - HP) / 2);//随机回复  (0 ~ 掉血量)/2 的血量
		//last_HP = HP;
	}
	else
	{
		AD = 15;
	}
	////走到画面中间
	//for (size_t i = 0; i < 20; i++)
	//{
	//	ImageTransparent(NULL, 0, 0, &lstart);
	//	ImageTransparent(NULL, WidthPiece * 5 + dis * (i + 1), HeightPiece * 11, &idle[i % 2]);
	//	Sleep(20);
	//}
	//播放攻击动画
	for (size_t i = 0; i < 9; i++)
	{
		IMAGE img = attack[i];

		if (i == 5)//发出声音
			Sound(MageAttack);
		ImageTransparent(NULL, 0, 0, &lstart);
		ImageTransparent(NULL, WidthPiece * 5 - 18, HeightPiece * 11, &img);
		Sleep(200);
	}
	img = idle[0];
	ImageTransparent(NULL, 0, 0, &lstart);
	ImageTransparent(NULL, WidthPiece * 5, HeightPiece * 11, &img);

	//倒着走回去...
	//for (size_t i = 20; i > 0; i--)
	//{
	//	ImageTransparent(NULL, 0, 0, &lstart);
	//	ImageTransparent(NULL, WidthPiece * 5 + dis * (i + 1), HeightPiece * 11, &idle[i % 2]);
	//	Sleep(20);
	//}
}

/*	void Injury(int value) 扣血函数
	负责人:	田奕裕
	1.玩家掉value值的血量
	2.保证玩家血量最小值为0

	拓展:
	3.实现受伤动画和音效
*/
void mage::Injury(int value, unsigned long long times)
{
	srand((unsigned)time(nullptr));			//随机数种子
	value += rand() % 5;  //受到伤害随机增加 0~4点
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