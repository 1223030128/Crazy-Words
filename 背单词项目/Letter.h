#pragma once


class Letter //���Һ󵥸���ĸ����Ϣ ����ͼ�λ���λ����Ϣ
{
public:
	bool isClickable = false;//Ĭ�ϲ��ܱ���� ���ܱ������ʱ����ʾ
	bool isHover = false;	//����Ƿ������ڵ�ǰ��ĸ
	char ch = 0;//��ʾ����ĸ
	int x1 = 0;//��������ĸ���Ͻǵ�xλ����Ϣ
	int y1 = 0;//��������ĸ���Ͻǵ�yλ����Ϣ
	int x2 = 0;//��������ĸ���½ǵ�xλ����Ϣ
	int y2 = 0;//��������ĸ���½ǵ�yλ����Ϣ

	//bool isClick(ExMessage& msg);

};