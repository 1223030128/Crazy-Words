#pragma once
#include "role.h"
#include "windows.h"						//���ڴ�С�ĺ궨��


//սʿ��̳�Role
class warrior : public Role
{
public:
	warrior();//���캯�� ���ؽ�ɫͼ�� ��ɫ�������ֵ ��ɫ�˺�
	//��̬
	void Judge(ExMessage& msg, Letter* letter, char* okLetter, int wordLength, int& current, string& downLetter);//��ɫ�ĵ���жϣ�����ק�жϣ�
	void Display(unsigned long long times);//��ʾ��ɫͼ��
	void Attack(unsigned long long times);//��ɫ�Ĺ�������
	void Injury(int value, unsigned long long times);//��ɫ����
	void Die();
	//սʿ��ͼ����
	IMAGE attack[17];
	IMAGE die[7];
	IMAGE idle[4];
	IMAGE injury[3];

};