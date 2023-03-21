#pragma once
#include <iostream>
#include <string>
#include <easyx.h>
#include "Sound.h"
#include <Windows.h>
#include "windows.h"						//���ڴ�С�ĺ궨��

using namespace std;

extern IMAGE lstart;
extern IMAGE rstart;
extern void ImageTransparent(IMAGE* dstimg, int x, int y, IMAGE* srcimg);


class Monster
{
public:
	virtual void Display(unsigned long long times) = 0;//��ʾ����
	virtual void Attack(unsigned long long times) = 0;//���﹥���Ĺ���
	virtual void Injury(int value, unsigned long long times) = 0;//�ܵ��˺�
	virtual void Die() = 0;//��������

	IMAGE img;//��ʾ��ͼ��
	int HP;//���ﵱǰѪ��
	int AD;//����Ĺ����˺�
	int maxHP;//�������Ѫ��
	int last_HP;//��Ѫ֮ǰ��Ѫ��
};