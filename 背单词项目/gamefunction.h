#pragma once
#include <iostream>							
#include <string>
#include <vector>							//stl����
#include <ctime>							//������ȡ����� ʵ�ּ�ʱ��
#include <easyx.h>							//����ͼ�ο�
#include <fstream>							//��ȡ�ļ�
#include <mmsystem.h>
#include <conio.h>
#include "Sound.h"							//�洢����������صĺ궨��
#include "Letter.h"							//�洢������ĸ��Ϣ����
#include "role.h"							//��ɫ������
#include "Monster.h"						//���������
#include "warrior.h"						//սʿ��
#include "mage.h"							//������
#include "Demon.h"							//��ħ��
#include "windows.h"						//���ڴ�С�ĺ궨��
#include <Windows.h>
#pragma comment(lib,"MSIMG32.LIB")			//������ʾ͸��ͼƬ
//#pragma comment(lib,"winmm.lib")			//����ý�岥��

using namespace std;

extern IMAGE start;
extern IMAGE lstart;
extern IMAGE rstart;

class Word //�洢��������
{
public:
	//���캯��
	Word(string word, string mean,int num);

	string word;
	string mean;
	int errorNum;
};

//��ť�� ʵ�ְ�ť����
class Button
{
public:
	//��ť���캯��
	Button(int x, int y, int w, int h, LPCTSTR str,int textSize);
	Button(int x, int y, int w, int h, LPCTSTR str, COLORREF fillColor, COLORREF lineColor, COLORREF textColor, int textSize);

	//��ť����ж�
	bool isClick(ExMessage& msg);
	bool isClick(ExMessage& msg, COLORREF hoverColor);

	//����ʵ�����Ͻǵķ��ذ�ť ����ͬ��swֵ���ز�ͬ�Ľ��� (ɾ���˹���)
	//void GoBack(ExMessage& msg);
	//void GoBack(ExMessage& msg, COLORREF hoverColor);
	int x;
	int y;
	int w;
	int h;
	int textSize;
	COLORREF fillColor;
	COLORREF lineColor;
	COLORREF textColor;
	LPCTSTR str;
	bool isHover = false;
};

class GameFunction
{
public:
/*��������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

/*��view����������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/
	void InitInterface();			//��ʼ����Ļ��ƺ��߼���ʵ��(������ť��������Ч)  �����ť�ı�sw��ֵ sw = 1
	void DeveloperList();			//�������������� sw = 5
	void WordList();				//��ʾ�ѵ���ĵ��� sw = 4
	void WordFrom(int x, int y, int W, int H, LPCTSTR str, int i);	//�ı����Բ���
	void RoleChoice();				//ְҵѡ����� sw = 2
	void SettingInterface();		//���ý��� sw = 6
	void SettingINGame();			//��Ϸ�����ý��� 
	void Start();					//��ʼ��Ϸ �����к���ʵ����Ϸ�߼� sw = 3
	void WordSituation();			//����ƴд��������� sw=7
	void GameInterface();			//��Ϸ�ײ����  ���ᷢ���ı� sw = 3
	void DisplayWord();				//������ʾ��ĸ�͵�ǰ��ƴд�ĵ��ʵĺ��� ��ǰƴд���ʵ��±�ΪwordCurrent
	void DisplayLetter(Letter& letter);	//������ʾ������ĸ
	void Lifebar(int& role_life, int& monster_life);//��ʾѪ��
	void LifebarDraw(int x, int y, int W, int H, float per, LPCTSTR str);	//����Ѫ��
	//Ѫ����ʾ ʹ�ñ���role.HP role.maxHP  monster.HP monster.maxHPȥʵ��Ѫ����ʾ
	void WordFrom(int x, int y, int W, int H, LPCTSTR str);//�����������ʱ��
	void DisplayOk(int& x, int& y, int& W, int& H,bool isCorrect);
	void DisplayDown(string down, bool b);	//��ʾǰ�������µ���ĸ
	//��ʾ��ƴ�õ�Ӣ��
	//void DisplayRight(int& x, int& y, int& W, int& H,bool isCorrect);//��ʾ��ƴ�õ�Ӣ��
	void DisplayMean(int& x, int& y, int& W, int& H);//������ʾ��ǰƴд���ʵ�����

	//void DisplayOk(int& x, int& y, int& W, int& H);//��ʾ��ƴ�õ�Ӣ��
	//void GameInterfaceOperation(ExMessage& msg);	//��Ϸ����Ĳ���


/*��server����������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	GameFunction();						//���캯�� ������һ�γ�ʼ��
	void loadRecord();					//���ļ����ж�ȡ��������vector������
	void Init();
	//��ʼ����ȡ����
	void End();							//�������� sw = 8
	void InitMonster();					//��ʼ������
	void RandomRead();					//���ѡ��һ�����ʶ�ȡ��Ϣ�浽wordLength��letter�� �����������ȷ����ĸ��λ��
	bool isSame(Letter& currentletterpos, Letter* letter,int length); //�ж��Ƿ���ĸ�ص� ���ڴ��Һ���
	void SaveErrorNum();
	string UtfToGbk(string strValue);	//��ֹstring�������� ��UTF-8תΪGBK

	~GameFunction();					//�������� �����ͷſ��ٵĿռ�

/*��������������������������������������������������������������������������������������������������������������������������������������������������*/


/*��������������������������������������������������������������������������������������������������������������������������������������������������*/
	//Word* word;						//������ĵ���
	Role* role;							//����ѡ��Ľ�ɫ
	Monster* monster;					//�������
	//ExMessage msg;					//����ExMessage����
	string downLetter;					//������ʾ���µ���ĸ
	Letter letter[30];					//�����洢������ĸ �������󵥴ʳ���Ϊ30
	char okLetter[31] = { 0 };			//�����Ѿ�ƴ�õ���ĸ
	bool isRead = true;					//��ʾ�Ƿ�Ҫ���뵥��
	bool isGame = false;				//��ʾ�Ƿ�����Ϸ��
	bool isWin = false;					//��ʾ�Ƿ�ʤ��
	int* xWords;						//�洢�����ֵĵ���
	int errorwordNum = 0;				//��ʾƴд����ĵ��ʵ�����					
	int errorAllnum = 0;				//��ʾ������ܴ���					
	int wordNum = 0;					//��ʾ����ĵ�������
	int errorNum = 3;					//�������Ĵ���
	int SpellingTimes = 0;				//��ʾƴд�Ĵ���
	int wordLength = 0;					//��ʾ��ǰ���ʵĳ���
	int current = 0;					//���ڱ�ʾ��ǰ�жϵĵ��ʵ���ĸ���±�
	int wordCurrent = 0;				//������ʾ��ǰ��ʾ���ʵ��±�
	int roleNum = 0;					//������ʾѡ���ְҵ		1:սʿ   2:����		
	int sw = 1;							//��ʾ���� 1Ϊ��ʼ����

/*��������������������������������������������������������������������������������������������������������������������������������������������������*/
};



//ȫ�ֺ���

//service
//void Sound(int sign);					//�������� �����������Ե����������� ����ͬ��signֵ���������(�Ѱ�����Sound.hͷ�ļ���)