#pragma once
#include <iostream>
#include <string>
#include <easyx.h>
#include <Windows.h>
#include "Sound.h"
#include "windows.h"						//窗口大小的宏定义
#include "Letter.h"
using namespace std;

extern IMAGE lstart;
extern IMAGE rstart;
extern void ImageTransparent(IMAGE* dstimg, int x, int y, IMAGE* srcimg);

//角色抽象类
class Role
{
public:
	//多态
	virtual void Judge(ExMessage& msg, Letter* letter,char* okLetter,int wordLength,int& current, string& downLetter) = 0;//角色的点击判断（或输入判断）
	virtual void Display(unsigned long long times) = 0;//显示角色图像
	virtual void Attack(unsigned long long times) = 0;//角色的攻击动画
	virtual void Injury(int value, unsigned long long times) = 0;//受到伤害
	virtual void Die() = 0;//死亡动画
	IMAGE img;//显示的图像
	int HP;//角色当前血量
	int maxHP;//角色最大血量
	int AD;//角色的攻击伤害
	int last_HP;//掉血之前的血量
};

