#pragma once
#include "windows.h"						//���ڴ�С�ĺ궨��
#include "Monster.h"
#include <string>

//��ħ��̳�Monster
class Demon : public Monster
{
public:
	Demon();//���캯�� ����ͼ�� �������ֵ �˺���Ϣ
	//��̬
	void Display(unsigned long long times);//��ʾ����
	void Attack(unsigned long long times);//���﹥���Ĺ���
	void Injury(int value, unsigned long long times);//����
	void Die();
	//������ͼ����
	IMAGE attack[18];
	IMAGE die[15];
	IMAGE idle[11];
	IMAGE injury[8];
};