#pragma once
#include <iostream>
#include <string>
#include <easyx.h>
#include <Windows.h>
#include "Sound.h"
#include "windows.h"						//���ڴ�С�ĺ궨��
#include "Letter.h"
using namespace std;

extern IMAGE lstart;
extern IMAGE rstart;
extern void ImageTransparent(IMAGE* dstimg, int x, int y, IMAGE* srcimg);

//��ɫ������
class Role
{
public:
	//��̬
	virtual void Judge(ExMessage& msg, Letter* letter,char* okLetter,int wordLength,int& current, string& downLetter) = 0;//��ɫ�ĵ���жϣ��������жϣ�
	virtual void Display(unsigned long long times) = 0;//��ʾ��ɫͼ��
	virtual void Attack(unsigned long long times) = 0;//��ɫ�Ĺ�������
	virtual void Injury(int value, unsigned long long times) = 0;//�ܵ��˺�
	virtual void Die() = 0;//��������
	IMAGE img;//��ʾ��ͼ��
	int HP;//��ɫ��ǰѪ��
	int maxHP;//��ɫ���Ѫ��
	int AD;//��ɫ�Ĺ����˺�
	int last_HP;//��Ѫ֮ǰ��Ѫ��
};

