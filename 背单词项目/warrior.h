#pragma once
#include "role.h"
#include "windows.h"						//窗口大小的宏定义


//战士类继承Role
class warrior : public Role
{
public:
	warrior();//构造函数 加载角色图像 角色最大生命值 角色伤害
	//多态
	void Judge(ExMessage& msg, Letter* letter, char* okLetter, int wordLength, int& current, string& downLetter);//角色的点击判断（或拖拽判断）
	void Display(unsigned long long times);//显示角色图像
	void Attack(unsigned long long times);//角色的攻击功能
	void Injury(int value, unsigned long long times);//角色受伤
	void Die();
	//战士贴图数量
	IMAGE attack[17];
	IMAGE die[7];
	IMAGE idle[4];
	IMAGE injury[3];

};