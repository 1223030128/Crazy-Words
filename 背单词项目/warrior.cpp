#include "warrior.h"


/*	warrior()战士构造函数
	1.初始化角色数值  攻击力 角色最大生命值 当前生命值等
	2.加载角色图像
*/
warrior::warrior()
{
	this->AD = 10;					//默认攻击力
	this->maxHP = 80;				//初始最大血量
	this->HP = this->maxHP;			//当前血量	
	this->last_HP = this->maxHP;	//扣血前的血量

	string png = ".png";
	//加载角色图片
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

/*	void warrior::Judge() 用于接收战士的点击操作
	1.根据传入的msg 单词长度 和对于的letter坐标 接收鼠标点击操作 
	2.判断是否点击到字母  若点击到则使将该字母存储到okLetter中
	3.使被点击字母无法被点击(isClick = false)
	4.执行完点击之后current值+1
*/
void warrior::Judge(ExMessage& msg, Letter* letter, char* okLetter, int wordLength, int& current, string& downLetter)
{
	for (size_t i = 0; i < wordLength; i++)
	{
		if (letter[i].isClickable)
		{
			switch (msg.message)
			{
				//左键点击
			case WM_LBUTTONDOWN:
				if (msg.x >= letter[i].x1 && msg.y >= letter[i].y1 && msg.x <= letter[i].x2 && msg.y <= letter[i].y2)
				{
					letter[i].isClickable = false;//使其不能被点击
					okLetter[current] = letter[i].ch;//将点击的字母存到okLetter中
					current++;
					return;				//找到一个就不继续判断后面的了
				}
				break;
				//鼠标移动
			case WM_MOUSEMOVE:
				if (msg.x >= letter[i].x1 && msg.y >= letter[i].y1 && msg.x <= letter[i].x2 && msg.y <= letter[i].y2)
				{
					letter[i].isHover = true;
					//找到一个之后直接把之后的全设成false
					for (size_t j = i + 1; j < wordLength; j++)
					{
						if (letter[j].isClickable)
							letter[j].isHover = false;
					}
					return;				//找到一个就不继续判断后面的了
				}
				else//表示鼠标不在当前悬浮按钮上
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
	//		letter[i].isClickable = false;//使其不能被点击
	//		okLetter[current] = letter[i].ch;//将点击的字母存到okLetter中
	//		current++;
	//		return;				//找到一个就不继续判断后面的了
	//	}
	//}

}

/*	void warrior::Display()
	1.显示战士贴图到指定位置
*/
void warrior::Display(unsigned long long times)
{

	int a = (times / 250) % 4;//250ms 一次
	img = idle[a];
	ImageTransparent(NULL, WidthPiece*3, HeightPiece*10.2, &img);
}

/*	void warrior::Attack()
	1.实现攻击音效
	2.实现攻击动画
*/
void warrior::Attack(unsigned long long times)
{

	//低血量攻击奖励	血量<=40时 攻击会使血量随机增加(3~8) 并且伤害随机增加 3~5点
	if (HP <= 40)
	{
		srand((unsigned)time(nullptr));			//随机数种子
		last_HP = HP;							//记录当前HP
		HP += ((rand()% 6)+5);					//随机增加 5~10点血

		AD = 13 + rand()%3;
	}
	else
	{
		AD = 10;
	}
	double dis = WidthPiece * 10 / 20;
	//走到画面中间
	for (size_t i = 0; i < 20; i++)
	{
		ImageTransparent(NULL, 0, 0 , &lstart);
		ImageTransparent(NULL, WidthPiece * 3 + dis*(i + 1), HeightPiece * 10.2, &idle[i % 4]);
		Sleep(15);
	}

	//播放攻击动画
	for (size_t i = 0; i < 17; i++)
	{
		IMAGE img = attack[i];
		if (i == 3|| i==8|| i == 13)//挥发出声音
			Sound(WarriorAttack);
		ImageTransparent(NULL, 0, 0, &lstart);
		ImageTransparent(NULL, WidthPiece * 3 + dis *20, HeightPiece * 10.2, &img);
		Sleep(80);
	}

	//倒着走回去...
	for (size_t i = 20; i > 0; i--)
	{
		ImageTransparent(NULL, 0, 0, &lstart);
		ImageTransparent(NULL, WidthPiece * 3 + dis * (i + 1), HeightPiece * 10.2, &idle[i % 4]);
		Sleep(15);
	}
}

/*	void Injury(int value) 扣血函数
	负责人:	田奕裕
	1.玩家掉value值的血量
	2.保证玩家血量最小值为0

	拓展:
	3.实现受伤动画和音效
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