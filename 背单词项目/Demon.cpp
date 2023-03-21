#include "Demon.h"

/*	Demon()恶魔构造函数
	1.初始化数值  攻击力 怪物最大生命值 当前生命值等
	2.加载图像
*/
Demon::Demon()
{
	this->AD = 4;					//默认攻击力
	this->maxHP = 160;				//初始最大血量
	this->HP = this->maxHP;			//初始血量
	this->last_HP = this->maxHP;
	//加载怪物图片
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
	1.显示怪物贴图到指定位置
	2.实现站立动画
*/
void Demon::Display(unsigned long long times)
{
	int a = (times / 100) % 11;//500ms 一次
	img = idle[a];
	ImageTransparent(NULL, WidthPiece * 26.3, HeightPiece * 10.2, &img);
}

/*	void Demon::Attack()
	1.实现攻击音效
	2.实现攻击动画
*/
void Demon::Attack(unsigned long long times)
{
	//低血量攻击奖励	低血量攻击伤害随机增加2-10点
	//低血量有概率回血 +10
	if (HP <= 20)
	{
		srand((unsigned)time(nullptr));			//随机数种子
		AD = 6 + rand() % 10;
		if (AD >= 12)
		{//大概1/2概率血量+5
			HP += 5;
			//last_HP = HP;
		}
	}
	else if(HP <= 60)
	{
		srand((unsigned)time(nullptr));			//随机数种子
		AD = 6 + rand() % 4; //随机增加2 - 4点
		if (AD == 10)
		{//1/4概率血量+5
			HP += 5;
			//last_HP = HP;
		}
	}
	else
	{
		AD = 4;
	}
	double dis = WidthPiece * 10 / 20;
	//走到中间
	for (size_t i = 0; i < 20; i++)
	{
		ImageTransparent(NULL, 0, 0, &rstart);
		ImageTransparent(NULL, WidthPiece * 26.3 - dis * (i + 1), HeightPiece * 10.2, &idle[i % 11]);
		Sleep(15);
	}
	//播放攻击动画
	for (size_t i = 0; i < 18; i++)
	{
		IMAGE img = attack[i];
		ImageTransparent(NULL, 0, 0, &rstart);
		ImageTransparent(NULL, WidthPiece * 24 - dis*20, HeightPiece * 9.4, &img);
		if (i == 7)//挥斧头时发出声音
		{
			Sound(WarriorAttack);
		}
		Sleep(100);
	}
	//倒着走回去
	for (size_t i = 20; i > 0; i--)
	{
		ImageTransparent(NULL, 0, 0, &rstart);
		ImageTransparent(NULL, WidthPiece * 26.3 - dis * (i + 1), HeightPiece * 10.2, &idle[i % 11]);
		Sleep(15);
	}
}

/*	void Injury(int value) 扣血函数
	1.怪物掉value值的血量
	2.保证血量最小值为0

	拓展:
	3.实现怪物受伤动画和音效
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