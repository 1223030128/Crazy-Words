#pragma once
#pragma once
#include "role.h"
#include "windows.h"						//窗口大小的宏定义


//战士类继承Role
class mage : public Role
{
public:
	mage();//构造函数 加载角色图像 角色最大生命值 角色伤害
	//多态
	void Judge(ExMessage& msg, Letter* letter, char* okLetter, int wordLength, int& current, string& downLetter);//角色的点击判断（或拖拽判断）
	void Display(unsigned long long times);//显示角色图像
	void Attack(unsigned long long times);//角色的攻击功能
	void Injury(int value, unsigned long long times);//角色受伤
	void Die();
	//射手贴图数量
	IMAGE attack[9];
	IMAGE die[12];
	IMAGE idle[6];
	IMAGE injury[3];

};