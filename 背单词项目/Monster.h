#pragma once
#include <iostream>
#include <string>
#include <easyx.h>
#include "Sound.h"
#include <Windows.h>
#include "windows.h"						//窗口大小的宏定义

using namespace std;

extern IMAGE lstart;
extern IMAGE rstart;
extern void ImageTransparent(IMAGE* dstimg, int x, int y, IMAGE* srcimg);


class Monster
{
public:
	virtual void Display(unsigned long long times) = 0;//显示怪物
	virtual void Attack(unsigned long long times) = 0;//怪物攻击的功能
	virtual void Injury(int value, unsigned long long times) = 0;//受到伤害
	virtual void Die() = 0;//死亡动画

	IMAGE img;//显示的图像
	int HP;//怪物当前血量
	int AD;//怪物的攻击伤害
	int maxHP;//怪物最大血量
	int last_HP;//掉血之前的血量
};