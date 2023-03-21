#pragma once
#include <iostream>							
#include <string>
#include <vector>							//stl容器
#include <ctime>							//用来获取随机数 实现计时器
#include <easyx.h>							//简易图形库
#include <fstream>							//读取文件
#include <mmsystem.h>
#include <conio.h>
#include "Sound.h"							//存储各种声音相关的宏定义
#include "Letter.h"							//存储单个字母信息的类
#include "role.h"							//角色抽象类
#include "Monster.h"						//怪物抽象类
#include "warrior.h"						//战士类
#include "mage.h"							//射手类
#include "Demon.h"							//恶魔类
#include "windows.h"						//窗口大小的宏定义
#include <Windows.h>
#pragma comment(lib,"MSIMG32.LIB")			//用于显示透明图片
//#pragma comment(lib,"winmm.lib")			//用于媒体播放

using namespace std;

extern IMAGE start;
extern IMAGE lstart;
extern IMAGE rstart;

class Word //存储单词数据
{
public:
	//构造函数
	Word(string word, string mean,int num);

	string word;
	string mean;
	int errorNum;
};

//按钮类 实现按钮功能
class Button
{
public:
	//按钮构造函数
	Button(int x, int y, int w, int h, LPCTSTR str,int textSize);
	Button(int x, int y, int w, int h, LPCTSTR str, COLORREF fillColor, COLORREF lineColor, COLORREF textColor, int textSize);

	//按钮点击判断
	bool isClick(ExMessage& msg);
	bool isClick(ExMessage& msg, COLORREF hoverColor);

	//用于实现左上角的返回按钮 按不同的sw值返回不同的界面 (删除此功能)
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
/*↓函数——————————————————————————————————————————————————————————————————————————————————*/

/*↓view——————————————————————————————————————————————————————————————————————————————————————*/
	void InitInterface();			//开始界面的绘制和逻辑的实现(包括按钮动画和音效)  点击按钮改变sw的值 sw = 1
	void DeveloperList();			//开发者名单界面 sw = 5
	void WordList();				//显示已导入的单词 sw = 4
	void WordFrom(int x, int y, int W, int H, LPCTSTR str, int i);	//改变矩形圆润度
	void RoleChoice();				//职业选择界面 sw = 2
	void SettingInterface();		//设置界面 sw = 6
	void SettingINGame();			//游戏内设置界面 
	void Start();					//开始游戏 用已有函数实现游戏逻辑 sw = 3
	void WordSituation();			//单词拼写的情况界面 sw=7
	void GameInterface();			//游戏底层界面  不会发生改变 sw = 3
	void DisplayWord();				//用于显示字母和当前在拼写的单词的函数 当前拼写单词的下标为wordCurrent
	void DisplayLetter(Letter& letter);	//用于显示单个字母
	void Lifebar(int& role_life, int& monster_life);//显示血条
	void LifebarDraw(int x, int y, int W, int H, float per, LPCTSTR str);	//绘制血条
	//血条显示 使用变量role.HP role.maxHP  monster.HP monster.maxHP去实现血条显示
	void WordFrom(int x, int y, int W, int H, LPCTSTR str);//用于制作单词表格
	void DisplayOk(int& x, int& y, int& W, int& H,bool isCorrect);
	void DisplayDown(string down, bool b);	//显示前三个按下的字母
	//显示已拼好的英文
	//void DisplayRight(int& x, int& y, int& W, int& H,bool isCorrect);//显示已拼好的英文
	void DisplayMean(int& x, int& y, int& W, int& H);//用于显示当前拼写单词的中文

	//void DisplayOk(int& x, int& y, int& W, int& H);//显示已拼好的英文
	//void GameInterfaceOperation(ExMessage& msg);	//游戏界面的操作


/*↓server——————————————————————————————————————————————————————————————————————————————————————*/

	GameFunction();						//构造函数 用来做一次初始化
	void loadRecord();					//从文件流中读取数据载入vector容器中
	void Init();
	//初始化读取数据
	void End();							//结束界面 sw = 8
	void InitMonster();					//初始化怪物
	void RandomRead();					//随机选择一个单词读取信息存到wordLength和letter中 并且用随机数确定字母的位置
	bool isSame(Letter& currentletterpos, Letter* letter,int length); //判断是否字母重叠 用于打乱函数
	void SaveErrorNum();
	string UtfToGbk(string strValue);	//防止string类型乱码 将UTF-8转为GBK

	~GameFunction();					//析构函数 用来释放开辟的空间

/*↑函数——————————————————————————————————————————————————————————————————————*/


/*↓变量——————————————————————————————————————————————————————————————————————*/
	//Word* word;						//代表导入的单词
	Role* role;							//代表选择的角色
	Monster* monster;					//代表怪物
	//ExMessage msg;					//创建ExMessage对象
	string downLetter;					//用来表示按下的字母
	Letter letter[30];					//用来存储单词字母 允许的最大单词长度为30
	char okLetter[31] = { 0 };			//代表已经拼好的字母
	bool isRead = true;					//表示是否要读入单词
	bool isGame = false;				//表示是否在游戏内
	bool isWin = false;					//表示是否胜利
	int* xWords;						//存储不出现的单词
	int errorwordNum = 0;				//表示拼写错误的单词的数量					
	int errorAllnum = 0;				//表示错误的总次数					
	int wordNum = 0;					//表示导入的单词数量
	int errorNum = 3;					//允许错误的次数
	int SpellingTimes = 0;				//表示拼写的次数
	int wordLength = 0;					//表示当前单词的长度
	int current = 0;					//用于表示当前判断的单词的字母的下标
	int wordCurrent = 0;				//用来表示当前显示单词的下标
	int roleNum = 0;					//用来表示选择的职业		1:战士   2:射手		
	int sw = 1;							//表示界面 1为开始界面

/*↑变量——————————————————————————————————————————————————————————————————————*/
};



//全局函数

//service
//void Sound(int sign);					//声音函数 其他函数可以调用声音函数 靠不同的sign值来输出声音(已包含在Sound.h头文件中)