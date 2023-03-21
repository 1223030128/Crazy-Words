#pragma once
#include "windows.h"						//窗口大小的宏定义
#include "Monster.h"
#include <string>

//恶魔类继承Monster
class Demon : public Monster
{
public:
	Demon();//构造函数 加载图像 最大生命值 伤害信息
	//多态
	void Display(unsigned long long times);//显示怪物
	void Attack(unsigned long long times);//怪物攻击的功能
	void Injury(int value, unsigned long long times);//受伤
	void Die();
	//怪物贴图数量
	IMAGE attack[18];
	IMAGE die[15];
	IMAGE idle[11];
	IMAGE injury[8];
};