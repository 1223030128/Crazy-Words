#pragma once
#pragma once
#include "role.h"
#include "windows.h"						//���ڴ�С�ĺ궨��


//սʿ��̳�Role
class mage : public Role
{
public:
	mage();//���캯�� ���ؽ�ɫͼ�� ��ɫ�������ֵ ��ɫ�˺�
	//��̬
	void Judge(ExMessage& msg, Letter* letter, char* okLetter, int wordLength, int& current, string& downLetter);//��ɫ�ĵ���жϣ�����ק�жϣ�
	void Display(unsigned long long times);//��ʾ��ɫͼ��
	void Attack(unsigned long long times);//��ɫ�Ĺ�������
	void Injury(int value, unsigned long long times);//��ɫ����
	void Die();
	//������ͼ����
	IMAGE attack[9];
	IMAGE die[12];
	IMAGE idle[6];
	IMAGE injury[3];

};