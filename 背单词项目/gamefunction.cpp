#include "gamefunction.h"

extern void ImageTransparent(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
vector<Word> words;


/*↓———————————————————————————————————————View———————————————————————————————————————————————↓*/


/*	void InitInterface() 主菜单
	负责人:		申海洋
	1.创建界面: 大小 WindowWidth * WindowHeight
	2.贴上背景贴图
	3.调用Init()函数 进行初始化
	4.绘制按钮
		开始游戏 sw = 2
		单词列表 sw = 4
		游戏设置 sw = 6
		开发名单 sw = 5
		退出游戏 sw = 9
	5.实现按钮功能
		点击对应坐标改变sw的值
		鼠标悬浮效果(当鼠标放在按钮上时改变按钮颜色)
	6.拓展
		鼠标悬浮音效(调用Sound()函数)
		鼠标点击音效(调用Sound()函数)
*/
void GameFunction::InitInterface()
{
	//贴图操作
	IMAGE img;
	//Sound(InitInterfaceBGMPlay);
	//加载图片  在easyx中使用字符串
	//loadimage(&img, "images/bk.png", getwidth(), getheight());
	loadimage(&img, "./resource/bkImage/Init.png", WindowWidth, WindowHeight);//载入游戏界面的图片	用于动画刷新
	//绘制图片
	putimage(0, 0, &img);
	int width = WidthPiece * 5.3,
		height = HeightPiece * 3.2,
		dis = HeightPiece * 3.7;
	//初始化读取数据
	Init();
	//Button btn0(WindowWidth / 2 - 20, WindowHeight - 500, 150, 75, str1, 50);
	BeginBatchDraw();
	Button btn1((WindowWidth - width)/2, (WindowHeight - height)/2.5 + dis * 1, width, height, "开始游戏", 40);
	Button btn2((WindowWidth - width)/2, (WindowHeight - height)/2.5 + dis * 2, width, height, "单词列表", 40);
	Button btn3((WindowWidth - width)/2, (WindowHeight - height)/2.5 + dis * 3, width, height, "游戏设置", 40);
	Button btn4((WindowWidth - width)/2, (WindowHeight - height)/2.5 + dis * 4, width, height, "开发名单", 40);
	Button btn5((WindowWidth - width)/2, (WindowHeight - height)/2.5 + dis * 5, width, height, "退出游戏", 40);
	//进入循环，不让界面点击一次就失效
	ExMessage m;
	while (sw == 1) {
		if (peekmessage(&m, EX_MOUSE)) {
			if (btn1.isClick(m))
			{
				sw = 2;
				Sound(ButtonPressSound);
			}
			else  if (btn2.isClick(m))
			{
				sw = 4;
				Sound(ButtonPressSound);
			}
			else  if (btn3.isClick(m))
			{
				sw = 6;
				Sound(ButtonPressSound);
			}
			else  if (btn4.isClick(m))
			{
				sw = 5;
				Sound(ButtonPressSound);
			}
			else  if (btn5.isClick(m))
			{
				Sound(ButtonPressSound);
				sw = -1;	//退出游戏
			}
		}
	FlushBatchDraw();
	}
}

/*	void DeveloperList() 开发者名单界面
	负责人:		田奕裕
	1.显示贴图
	2.调用GoBack()函数来实现左上角返回按钮
*/
void GameFunction::DeveloperList()
{
	BeginBatchDraw();
	cleardevice();
	IMAGE img;
	loadimage(&img, "./resource/bkImage/DpList.png", WindowWidth, WindowHeight);//载入游戏界面的图片	用于动画刷新
	putimage(0, 0, &img);
	int back_width = 3.3 * WidthPiece,
		back_height = 2.5 * HeightPiece;
	Button b(WidthPiece, HeightPiece, back_width, back_height, "返 回", 30);
	ExMessage ms;
	while (true)
	{
		if (peekmessage(&ms, EX_MOUSE))
		{
			if (b.isClick(ms))
			{
				Sound(ButtonPressSound);
				sw = 1;//切换到主界面
				return;
			}
			FlushBatchDraw();
		}
	}
}

/*	void WordList() 单词列表界面 显示导入成功的单词
	负责人:		莫玄昊
	1.导入背景贴图(带表格)
	2.调用返回函数实现左上角返回按钮
	3.利用Word*指针的单词中英文数据 将单词中英文依次显示到界面上
	4.实现翻页按钮 上一页 下一页  以及实现翻页功能
	5.单词列表下方 显示当前页和总页数 例如有20页单词 目前在第3页 则显示 3/20
*/
void GameFunction::WordList()
{
	BeginBatchDraw();
	cleardevice();

	IMAGE img;
	loadimage(&img, "./resource/bkImage/other.png", WindowWidth, WindowHeight);//载入游戏界面的图片	用于动画刷新
	putimage(0, 0, &img);

	int onePage = 14;
	int LnowWord = 0;
	int LshowWord = onePage;
	int RnowWord = 0;
	int RshowWord = onePage;
	int totalPage = (wordNum + ((LshowWord + RshowWord) - 1)) / (LshowWord + RshowWord);	//总页数 向上取整
	int curPage = 1;	//当前页数
	
	char page[12] = { 0 };//最大支持 10000/10000

	//位置 长宽
	int width = WidthPiece * 3,
		height = HeightPiece * 2.5,
		back_width = 3.3 * WidthPiece,
		back_height = 2.5 * HeightPiece;

	Button last((WindowWidth - width) / 6, (WindowHeight - height) / 5, width, height, "上一页", RGB(164, 173, 179), BLACK, WHITE, 30);
	Button next((WindowWidth - width) / 6, WindowHeight - ((WindowHeight - height) / 5) - height, width, height, "下一页", RGB(164, 173, 179), BLACK, WHITE, 30);
	Button back(WidthPiece, HeightPiece, back_width, back_height, "返 回", 30);
	ExMessage ms;

	//char arr[] = "单词列表";
	int a = WidthPiece + (back_width - textwidth("字")) / 2;
	settextcolor(BLACK);
	settextstyle(65, 0, "微软雅黑");
	outtextxy(a, HeightPiece * 6, "单");
	outtextxy(a, HeightPiece * 13, "词");
	outtextxy(a, HeightPiece * 21, "列");
	outtextxy(a, HeightPiece * 29, "表");

	settextcolor(WHITE);
	_stprintf_s(page, "%d / %d", curPage, totalPage);
	cout << page << endl;
	settextstyle(45, 0, "微软雅黑");
	WordFrom(WidthPiece * 22.2, HeightPiece * 33.5, WidthPiece * 3, HeightPiece * 2, page, 20);

	while (true) 
	{
		//左表格打印
		if (LnowWord != LshowWord)
		{
			for (int i = 0; LnowWord < LshowWord; LnowWord++,i += HeightPiece * 2 + 4)
			{
				if (LnowWord < wordNum)
				{
					WordFrom(WidthPiece * 12, HeightPiece * 2 + i, WidthPiece*4.5, HeightPiece*2,words[LnowWord].word.c_str());
					WordFrom(WidthPiece * 16.5 + 4, HeightPiece * 2 + i, WidthPiece*6.5, HeightPiece*2,words[LnowWord].mean.c_str());
				}
				else
				{
					WordFrom(WidthPiece * 12, HeightPiece * 2 + i, WidthPiece * 4.5, HeightPiece * 2 ,"");
					WordFrom(WidthPiece * 16.5 + 4, HeightPiece * 2 + i, WidthPiece * 6.5, HeightPiece * 2,"");
				}
			}
		}
		//右表格打印
		if (RnowWord != RshowWord)
		{
			for (int i = 0; RnowWord < RshowWord; RnowWord++,i += HeightPiece * 2 + 4)
			{
				if ((RnowWord + LnowWord) < wordNum)
				{
					WordFrom(WidthPiece * 24, HeightPiece * 2 + i, WidthPiece * 4.5, HeightPiece * 2, words[RnowWord + LnowWord].word.c_str());
					WordFrom(WidthPiece * 28.5 + 4, HeightPiece * 2 + i, WidthPiece * 6.5, HeightPiece * 2, words[RnowWord + LnowWord].mean.c_str());
				}
				else
				{
					WordFrom(WidthPiece * 24, HeightPiece * 2 + i, WidthPiece * 4.5, HeightPiece * 2, "");
					WordFrom(WidthPiece * 28.5 + 4, HeightPiece * 2 + i, WidthPiece * 6.5, HeightPiece * 2, "");
				}
			}
		}
		if (peekmessage(&ms, EX_MOUSE)) {
			if (next.isClick(ms))//翻页
			{
				Sound(ButtonPressSound);
				//若已显示的单词小于单词总数 则允许增加
				if (curPage < totalPage)
				{
					curPage++;
					LnowWord = (curPage - 1) * 2 * onePage;
					RnowWord = 0;
					LshowWord = LnowWord + onePage;
					//RshowWord = LshowWord;

					settextcolor(WHITE);
					_stprintf_s(page, "%d / %d", curPage, totalPage);
					cout << page << endl;
					settextstyle(45, 0, "微软雅黑");
					WordFrom(WidthPiece * 22.2, HeightPiece * 33.5, WidthPiece*3, HeightPiece*2, page, 20);
				}
			}
			else if (last.isClick(ms))
			{
				Sound(ButtonPressSound);
				//若不在第一页则可以减少
				if (curPage != 1)
				{
					curPage--;
					LnowWord = (curPage - 1) * 2 * onePage;
					RnowWord = 0;
					LshowWord = LnowWord + onePage;
					//RshowWord = LshowWord;

					settextcolor(WHITE);
					_stprintf_s(page, "%d / %d", curPage, totalPage);
					cout << page << endl;
					settextstyle(45, 0, "微软雅黑");
					WordFrom(WidthPiece * 22.2, HeightPiece * 33.5, WidthPiece * 3, HeightPiece * 2, page, 20);
					//outtextxy(WidthPiece * 22.2, HeightPiece * 33.2, page);
				}
			}
			else if (back.isClick(ms))
			{
				Sound(ButtonPressSound);
				sw = 1;//切换到主界面
				return;
			}
		}
		FlushBatchDraw();
	}
}

//用于绘制单词表格
void GameFunction::WordFrom(int x,int y,int W,int H,LPCTSTR str)
{
	setfillcolor(RGB(206, 206, 206));
	setlinecolor(WHITE);
	fillroundrect(x, y, x + W, y + H, 0, 0);
	int textSize = 30;	//代表字体大小
	while (true)	//字体大小匹配
	{
		settextstyle(textSize, 0, "微软雅黑");
		if (textwidth(str) >= W - 6 || textheight(str) >= H - 8)
			textSize -= 2;
		else
			break;
	}
	//居中对齐
	int text_x = (W - textwidth(str)) / 2 + x;
	int text_y = (H - textheight(str)) / 2 + y;
	settextcolor(BLACK);
	outtextxy(text_x, text_y, str);
}
void GameFunction::WordFrom(int x, int y, int W, int H, LPCTSTR str, int i)
{
	setfillcolor(RGB(222, 222, 222));
	setlinecolor(RGB(222, 222, 222));
	if (!i)
	{
		setfillcolor(RGB(206, 127, 89));
		setlinecolor(RED);
	}
	fillroundrect(x, y, x + W, y + H, i, i);
	int textSize = 30;	//代表字体大小
	while (true)	//字体大小匹配
	{
		settextstyle(textSize, 0, "微软雅黑");
		if (textwidth(str) >= W - 6 || textheight(str) >= H - 8)
			textSize -= 2;
		else
			break;
	}
	//居中对齐
	int text_x = (W - textwidth(str)) / 2 + x;
	int text_y = (H - textheight(str)) / 2 + y;
	settextcolor(BLACK);
	outtextxy(text_x, text_y, str);
}

/*	void DeveloperList() 职业选择界面
	负责人:	芦正琦
	1.职业界面背景贴图
	2.调用GoBack()函数实现 左上角返回按钮(点击返回主菜单)
	3.实现职业选择按钮 以及按钮悬浮变色效果 以及点击音效(调用Sound()函数)
	4.实现职业选择按钮的点击 点击不同的按钮创建不同的role对象 并且使sw=3进入游戏界面

	拓展:
	4.单击职业选择按钮时显示该职业的具体信息 双击时选择职业
*/
void GameFunction::RoleChoice()
{
	cleardevice();
	IMAGE img;
	IMAGE img1;
	IMAGE img2;
	bool refresh = true;
	int roleN = 1;//1代表战士界面
	loadimage(&img, "./resource/bkImage/RoleChoice.png", WindowWidth, WindowHeight);//载入游戏界面的图片	用于动画刷新
	loadimage(&img1, "./resource/bkImage/RoleChoice1.png", WindowWidth, WindowHeight);//载入游戏界面的图片	用于动画刷新
	loadimage(&img2, "./resource/bkImage/RoleChoice2.png", WindowWidth, WindowHeight);//载入游戏界面的图片	用于动画刷新
	putimage(0, 0, &img);//底层背景  只输出一次
	Init();
	int width = WidthPiece * 5,
		height = HeightPiece * 3,
		dis = HeightPiece * 6.5,
		back_width = 3.3 * WidthPiece,
		back_height = 2.5 * HeightPiece;
	Button b1(WidthPiece + height/2, WindowHeight / 2, height, height, "<--", 30);
	Button b2(WindowWidth - (WidthPiece + height / 2) - height, WindowHeight / 2, height, height, "-->", 30);
	Button ok((WindowWidth - width) / 2, HeightPiece * 31.5, width, height, "选择", 40);
	Button b(WidthPiece, HeightPiece, back_width, back_height, "返 回", 30);
	settextstyle(55, 0, "楷体");
	settextcolor(BLACK);
	//outtextxy((WindowWidth - width) / 2 - 100, ((WindowHeight - height) / 4 + dis) + (height - textheight("AD:10  HP:50  Click！")) / 2, "AD:10  HP:50  Click！");
	ExMessage m;
	while (true)
	{
		if (refresh)
		{
			switch (roleN)
			{
			case 1: //战士
				ImageTransparent(NULL, 0, 0, &img1);
				break;
			case 2: //法师
				ImageTransparent(NULL, 0, 0, &img2);
				break;
			}
		}
		if (peekmessage(&m, EX_MOUSE))
		{
			BeginBatchDraw();
			if (b1.isClick(m))//左
			{
				Sound(ButtonPressSound);
				roleN -= 1;
				if (roleN <= 0)
					roleN = 1;
				refresh = true;
			}
			else if (b2.isClick(m))//右
			{
				Sound(ButtonPressSound);
				roleN += 1;
				if (roleN >= 2)
					roleN = 2;
				refresh = true;
			}
			else if (b.isClick(m))//返回
			{
				Sound(ButtonPressSound);
				sw = 1;
				return;
			}
			else if (ok.isClick(m))
			{
				Sound(ButtonPressSound);
				switch (roleN)
				{
				case 1: //选择战士
					role = new warrior;
					roleNum = 1;
					sw = 3;
					return;
				case 2: //选择法师
					role = new mage;
					roleNum = 2;
					sw = 3;
					return;
				}
			}
			FlushBatchDraw();
		}
	}
}

/*	void SettingInterface() 游戏外设置界面
	负责人:		张家宁
	1.设置界面贴图
	2.调用GoBack()函数实现左上角返回按钮
	3.实现游戏外的设置界面 实现悬浮按钮变色 点击功能 以及点击音效 
		音效开关		调用Sound函数
		BGM开关		调用Sound函数
		拼写概况		sw = 7
*/
void GameFunction::SettingInterface()
{
	BeginBatchDraw();
	cleardevice();
	IMAGE img;
	loadimage(&img, "./resource/bkImage/Setting.png", WindowWidth, WindowHeight);//载入游戏界面的图片	用于动画刷新
	putimage(0, 0, &img);

	int width = WidthPiece*6,
		height = HeightPiece*4, 
		dis = HeightPiece*7.5, 
		back_width = 3.3*WidthPiece, 
		back_height = 2.5*HeightPiece;

	Button b1((WindowWidth - width) / 2, (WindowHeight - height) / 3.5, width, height, "音效开关", 40);
	Button SEdown((WindowWidth - width) / 2 + width + 10, (WindowHeight - height) / 3.5 +10, height-20, height-20, "-", 50);
	Button SEup((WindowWidth - width) / 2 - height + 10, (WindowHeight - height) / 3.5 + 10, height-20, height-20, "+", 50);

	Button b2((WindowWidth - width) / 2, (WindowHeight - height) / 3.5 + dis * 1, width, height, "BGM开关", 40);
	Button BGMdown((WindowWidth - width) / 2 + width + 10, (WindowHeight - height) / 3.5 + dis * 1 + 10, height-20, height - 20, "-", 50);
	Button BGMup((WindowWidth - width) / 2 - height + 10, (WindowHeight - height) / 3.5 + dis * 1 + 10, height - 20, height - 20, "+", 50);
	Button b3((WindowWidth - width) / 2, (WindowHeight - height) / 3.5 + dis * 2, width, height, "拼写概况", 40);

	Button b(WidthPiece, HeightPiece, back_width, back_height, "返 回", 30);
	ExMessage ms;
	while (true) {
		if (peekmessage(&ms,EX_MOUSE)) {
			if (b1.isClick(ms))
			{
				if (playEffect)
				{
					Sound(ButtonPressSound);
					cout << "音效关" << endl;
					playEffect = false;
				}
				else
				{
					playEffect = true;
					Sound(ButtonPressSound);
					cout << "音效开" << endl;
				}
					
			}
			else if (b2.isClick(ms))
			{
				if (playBGM)
				{
					Sound(ButtonPressSound);
					Sound(Pause);
					cout << "BGM关" << endl;
					playBGM = false;
				}
				else
				{
					Sound(ButtonPressSound);
					cout << "BGM开" << endl;
					playBGM = true;
					mciSendString("resume ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3", 0, 0, 0);
				}
			}
			else if (b3.isClick(ms))
			{
				Sound(ButtonPressSound);
				WordSituation();
				putimage(0, 0, &img);
			}
			else if (b.isClick(ms))
			{
				Sound(ButtonPressSound);
				sw = 1;//切换到主界面
				return;
			}
			else if (BGMdown.isClick(ms))
			{
				Sound(ButtonPressSound);
				BGMDOWN();
			}
			else if (BGMup.isClick(ms))
			{
				Sound(ButtonPressSound);
				BGMUP();
			}			
			else if (SEdown.isClick(ms))
			{
				Sound(ButtonPressSound);
				SEDOWN();
			}
			else if (SEup.isClick(ms))
			{
				Sound(ButtonPressSound);
				SEUP();
			}
		}
		FlushBatchDraw();
	}
}

/*	void SettingINGame() 游戏内设置界面
	1.实现游戏内的设置界面
		调用GoBack()实现左上角返回 	回到游戏
		返回主菜单	sw = 1
		音效开关		调用Sound函数
		BGM开关		调用Sound函数
		拼写概况		sw = 7
	2.实现悬浮按钮变色 点击功能 以及点击音效(调用Sound函数)
*/
void GameFunction::SettingINGame()
{
	BeginBatchDraw();
	cleardevice();
	IMAGE img;
	loadimage(&img, "./resource/bkImage/Setting.png", WindowWidth, WindowHeight);//载入游戏界面的图片	用于动画刷新
	//绘制图片
	putimage(0, 0, &img);

	int width = WidthPiece * 6,
		height = HeightPiece * 4,
		dis = HeightPiece * 6.5,
		back_width = 3.3 * WidthPiece,
		back_height = 2.5 * HeightPiece;
	Button reInit((WindowWidth - width) / 2, (WindowHeight - height) / 4, width, height, "返回主菜单", 40);
	Button b1((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 1, width, height, "音效开关", 40);
	Button SEdown((WindowWidth - width) / 2 + width + 10, (WindowHeight - height) / 4 + dis + 10, height - 20, height - 20, "-", 50);
	Button SEup((WindowWidth - width) / 2 - height + 10, (WindowHeight - height) / 4 + dis + 10, height - 20, height - 20, "+", 50);

	Button b2((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 2, width, height, "BGM开关", 40);
	Button BGMdown((WindowWidth - width) / 2 + width + 10, (WindowHeight - height) / 4 + dis * 2 + 10, height - 20, height - 20, "-", 50);
	Button BGMup((WindowWidth - width) / 2 - height + 10, (WindowHeight - height) / 4 + dis * 2 + 10, height - 20, height - 20, "+", 50);
	Button b3((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 3, width, height, "拼写概况", 40);
	Button b(WidthPiece, HeightPiece, back_width, back_height, "返 回", 30);
	ExMessage ms;
	while (true) {
		if (peekmessage(&ms, EX_MOUSE)) {
			if (b1.isClick(ms))
			{
				if (playEffect)
				{
					Sound(ButtonPressSound);
					cout << "音效关" << endl;
					playEffect = false;
				}
				else
				{
					playEffect = true;
					Sound(ButtonPressSound);
					cout << "音效开" << endl;
				}

			}
			else if (b2.isClick(ms))
			{
				if (playBGM)
				{
					Sound(ButtonPressSound);
					Sound(Pause);
					cout << "BGM关" << endl;
					playBGM = false;
				}
				else
				{
					cout << "BGM开" << endl;
					mciSendString("resume ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3", 0, 0, 0);
					playBGM = true;
					Sound(ButtonPressSound);
				}
			}
			else if (b3.isClick(ms))
			{
				Sound(ButtonPressSound);
				sw = 3;
				WordSituation();//切换到单词概况界面
				putimage(0, 0, &img);
			}
			else if (b.isClick(ms))	//返回
			{
				Sound(ButtonPressSound);
				sw = 9;
				return;
			}
			else if (reInit.isClick(ms))
			{
				Sound(ButtonPressSound);
				sw = 1;//返回主菜单
				return;
			}
			else if (BGMdown.isClick(ms))
			{
				Sound(ButtonPressSound);
				BGMDOWN();
			}
			else if (BGMup.isClick(ms))
			{
				Sound(ButtonPressSound);
				BGMUP();
			}
			else if (SEdown.isClick(ms))
			{
				Sound(ButtonPressSound);
				SEDOWN();
			}
			else if (SEup.isClick(ms))
			{
				Sound(ButtonPressSound);
				SEUP();
			}
		}
		FlushBatchDraw();
	}
}

/*	void Start() 游戏逻辑实现
	负责人:		田奕裕
	后续拓展：
	添加动画功能
*/
void GameFunction::Start()
{
	InitMonster();					//初始化怪物(若有选关或者难度可以根据选关和难度新建不同的怪物对象)
	cleardevice();					//清屏
	GameInterface();				//游戏底层界面的显示(这里是不发生改变的界面)
	Init();							//初始化数值
	isRead = true;					//将各数值初始化
	isGame = true;
	this->current = 0;
	memset(this->okLetter, 0, sizeof(okLetter));
	downLetter = "";				//初始化字符串
	int i = 0;						//用于计数
	bool inSet = false;				//表示是否进入过设置界面
	unsigned long long times = 0;	//用来实现动画间隔 (计时器)	//times中存储的是毫秒
	clock_t begin = 0, end = 0;		//实现计时功能
	ExMessage ms;

	//创建设置按钮对象
	Button set(WidthPiece, HeightPiece, 3.3 * WidthPiece, 2.5 * HeightPiece, "设 置", 30);	

	while (1)
	{
		if (roleNum == 2)			//若为射手职业 清除键盘输入缓冲
			flushmessage();
		RandomRead();				//若isRead为真则 随机读入一个单词 并且当前单词打乱并使isRead为假  否则仅打乱
		while(errorNum)				//若错误次数不为0		玩家回合内
		{
			BeginBatchDraw();		//双缓冲防频闪
			begin = clock();		//此处开始计算时间
			ImageTransparent(NULL,0, 0, &start);
			role->Display(times);		//显示玩家
			monster->Display(times);	//显示怪物
			if (sw == 9)//从设置界面返回
			{
				cleardevice();
				sw = 3;
			}
			else if (sw == 1)
			{
				delete role;
				delete monster;
				return;
			}
			if (inSet)
			{
				GameInterface();//游戏底层界面的显示(这里是不发生改变的界面)
				inSet = false;
			}
			//GameInterface();			//游戏底层界面的显示(这里是不发生改变的界面)
			DisplayWord();			//显示读入的单词 包括打乱的字母
			Lifebar(role->last_HP,monster->last_HP);//显示血条
			//若鼠标 或者键盘有操作
			if (peekmessage(&ms, EX_MOUSE | EX_KEY))
			{
				//接收界面的操作（设置） 玩家点击 若玩家有点击操作 则current值会增加
				if (ms.message)
				{
					if (set.isClick(ms))
					{
						Sound(ButtonPressSound);
						SettingINGame();//显示游戏内设置界面
						inSet = true;
					}
					else
					{
						role->Judge(ms, letter, okLetter, wordLength, current, downLetter);
					}
				}
			}
			FlushBatchDraw();
			EndBatchDraw();
			//若current不为0 并且上一个存进去的字母与正确字母不匹配 则为拼写错误
			if (current && okLetter[current-1] != words[wordCurrent].word[current - 1])
			{
				if (roleNum == 2)
				{
					//显示已经按下的字母
					DisplayDown(downLetter, false);
				}

				downLetter.clear();//清空字符串
				words[wordCurrent].errorNum++;//此单词的错误次数+1

				SaveErrorNum();//每次输入错误就保存一次

				cout << words[wordCurrent].word << endl;
				errorAllnum++;				//总错误次数+1
				SpellingTimes++;


				//将各数值初始化 并且结束循环
				this->current = 0;
				memset(this->okLetter, 0, sizeof(okLetter));
				//可错误次数减少1
				errorNum--;
				if (errorNum == 1)//若连续错两次 则显示正确拼写
				{
					int	x = WindowWidth * 3 / 8 + 4,
						y = HeightPiece * 5 + 4,
						W = WindowWidth * 5 / 8 - 4 - x,
						H = HeightPiece * 9 - 4 - y,
						y_m = HeightPiece / 2 + 4;
					DisplayOk(x, y_m, W, H, true);
				}
				break;
			}
			//EndBatchDraw();
			//若拼写完成						
			if (current == (wordLength-5))
			{
				if (roleNum == 2)
				{
					//显示已经按下的字母
					DisplayDown(downLetter, true);
				}

				int	x = WindowWidth * 3 / 8 + 4,
					y = HeightPiece * 5 + 4,
					W = WindowWidth * 5 / 8 - 4 - x,
					H = HeightPiece * 9 - 4 - y,
					y_m = HeightPiece / 2 + 4;
				DisplayOk(x, y_m, W, H, true);

				SpellingTimes++;			//拼写单词数量+1
				this->role->Attack(times);//玩家攻击音效（可以先忽略）
				errorNum = 3;//错误次数恢复
				this->monster->Injury(this->role->AD, times);//怪物减少血量 减少的值为角色的AD
				memset(this->okLetter, 0, sizeof(okLetter));
				this->isRead = true;
				this->current = 0;
				Lifebar(role->last_HP, monster->last_HP);//血条刷新
				//若怪物血量归零 则胜利				
				cout << "怪物血量:" << this->monster->HP << endl;
				cout << "玩家血量:" << this->role->HP << endl;
				if (this->monster->HP == 0)
				{
					isWin = true;//表示胜利
					//monster->Die();
					if (role)
					{
						delete role;
						role = NULL;
					}
					if (!monster)
					{
						delete monster;
						monster = NULL;
					}
					this->End();
					return;//此次游戏结束
				}
				break;
			}
			end = clock();		//此处停止本次计时
			times += double(end - begin) / CLOCKS_PER_SEC * 1000;	//存下毫秒数

			if (times >= 100000) //每100秒重置一次计数器
				times = 0;

		//FlushBatchDraw();
		}
		BeginBatchDraw();		//双缓冲防频闪
		if (errorNum == 0)//如果连续错误三次
		{
			int	x = WindowWidth * 3 / 8 + 4,
				y = HeightPiece * 5 + 4,
				W = WindowWidth * 5 / 8 - 4 - x,
				H = HeightPiece * 9 - 4 - y,
				y_m = HeightPiece / 2 + 4;
			DisplayOk(x, y_m, W, H, true);
			errorNum = 3;//重置次数
			isRead = true;//重新随机单词
		}
		//FlushBatchDraw();
		//循环外部：
		EndBatchDraw();
		this->monster->Attack(times);//怪物攻击音效（可以先忽略）
		this->role->Injury(this->monster->AD, times);//角色减少血量
		Lifebar(role->last_HP, monster->last_HP);//血条刷新
		//若角色血量归零 则失败
		cout << "怪物血量:" << this->monster->HP << endl;
		cout << "玩家血量:" << this->role->HP << endl;
		if(roleNum == 2)
			downLetter.clear();		//清空字符串的内容

		if (this->role->HP == 0)
		{
			isWin = false;//表示失败
			//role->Die();
			delete role;
			delete monster;
			role = NULL;
			monster = NULL;
			this->End();
			return;//此次游戏结束
		}
	}
}

/*	void WordSituation() 单词概况界面
	负责人:		周凯凯
	1.显示贴图背景 以及绘画界面
	2.调用GoBack()函数实现左上角返回按钮
	3.利用Word指针的数据 使列表位置显示拼写错误的单词 按照错误次数降序排序
	4.制作翻页按钮 上一页 下一页 并实现翻页逻辑
	5.利用已有数据实现 拼写次数 错误次数 正确率的数据显示
	6.实现翻页按钮中间的页面显示 如有20页 当前在第3页 则显示 3/20
*/
void GameFunction::WordSituation()
{
	BeginBatchDraw();
	cleardevice();
	IMAGE img;
	loadimage(&img, "./resource/bkImage/other.png", WindowWidth, WindowHeight);//载入游戏界面的图片	用于动画刷新
	putimage(0, 0, &img);

	errorwordNum = 0;
	//errorAllnum = 0;
	//计算错误过的单词的数量
	for (size_t i = 0; i < (words.size()); i++)
	{
		if (words[i].errorNum)
		{
			errorwordNum++;
			//errorAllnum += words[i].errorNum;
		}
	}
	int onePage = 14;
	int LnowWord = 0;
	int LshowWord = onePage;
	int totalPage = (errorwordNum + (LshowWord - 1)) / LshowWord;	//总页数 向上取整
	if (totalPage == 0)
		totalPage = 1;
	int curPage = 1;	//当前页数

	char page[12] = { 0 };//最大支持 10000/10000

	//位置 长宽
	int width = WidthPiece * 3,
		height = HeightPiece * 2.5,
		back_width = 3.3 * WidthPiece,
		back_height = 2.5 * HeightPiece;

	Button last(WidthPiece * 22.5, HeightPiece * 33, width, height, "上一页", RGB(164, 173, 179),BLACK, WHITE, 30);
	Button next(WidthPiece * 32, HeightPiece * 33, width, height, "下一页", RGB(164, 173, 179), BLACK, WHITE, 30);
	Button back(WidthPiece, HeightPiece, back_width, back_height, "返 回", 30);
	ExMessage ms;

	int a = WidthPiece + (back_width - textwidth("字")) / 2;
	settextcolor(BLACK);
	settextstyle(65, 0, "微软雅黑");
	outtextxy(a, HeightPiece * 6, "单");
	outtextxy(a, HeightPiece * 13, "词");
	outtextxy(a, HeightPiece * 21, "概");
	outtextxy(a, HeightPiece * 29, "况");

	settextcolor(WHITE);
	_stprintf_s(page, "%d / %d", curPage, totalPage);
	cout << page << endl;
	settextstyle(45, 0, "微软雅黑");
	WordFrom(WidthPiece * 27.3, HeightPiece * 33.5, WidthPiece * 3, HeightPiece * 2, page, 20);
	//先把错误过的单词的下标和错误次数存储起来
	int* errindex = NULL;
	int* errnum = NULL;
	

	setfillcolor(RGB(230,230,230));
	fillroundrect(WidthPiece*7, HeightPiece*2, WidthPiece * 18, HeightPiece*32.5, 10, 10);

	settextstyle(50, 0, "微软雅黑");
	outtextxy((WidthPiece * 11 - textwidth("拼写次数:"))/2 + WidthPiece * 7, HeightPiece * 5,"拼写次数:");
	string text = to_string(SpellingTimes);
	outtextxy((WidthPiece * 11 - textwidth(text.c_str()))/2 + WidthPiece * 7, HeightPiece * 8,text.c_str());

	outtextxy((WidthPiece * 11 - textwidth("错误次数:"))/2 + WidthPiece * 7, HeightPiece * 14,"错误次数:");
	text = to_string(errorAllnum);
	outtextxy((WidthPiece * 11 - textwidth(text.c_str()))/2 + WidthPiece * 7, HeightPiece * 17,text.c_str());

	outtextxy((WidthPiece * 11 - textwidth("正确率:"))/2 + WidthPiece * 7, HeightPiece * 23,"正确率:");
	if (errorAllnum == 0 || SpellingTimes == 0)//若错误次数或拼写次数为0 则显示100%正确率
		text = to_string(100);
	else
	{
		int p = ((SpellingTimes - errorAllnum) / (float)SpellingTimes) * 100;
		text = to_string(p);
	}
	text.push_back('%');
	outtextxy((WidthPiece * 11 - textwidth(text.c_str()))/2 + WidthPiece * 7, HeightPiece * 26,text.c_str());


	
	if (errorwordNum != 0)
	{
		errindex = new int[errorwordNum];
		errnum = new int[errorwordNum];
		memset(errindex, 0, sizeof(int) * errorwordNum);
		memset(errnum, 0, sizeof(int) * errorwordNum);

		for (size_t i = 0,j = 0; i < words.size(); i++)
		{
			if (words[i].errorNum != 0)
			{
				errindex[j] = i;
				errnum[j] = words[i].errorNum;
				j++;
			}
		}
		//冒泡排序
		for (size_t i = 0; i < errorwordNum - 1; i++)
		{
			for (size_t j = 0; j < errorwordNum - i - 1; j++)
			{
				if (errnum[j] < errnum[j + 1])
				{
					int temp = errnum[j];
					errnum[j] = errnum[j + 1];
					errnum[j + 1] = temp;

					temp = errindex[j];
					errindex[j] = errindex[j + 1];
					errindex[j + 1] = temp;
				}
			}
		}

		for (size_t i = 0; i < errorwordNum; i++)
		{
			cout << "数量:" << errnum[i];
			cout << "\t下标:" << errindex[i] << endl;
		}

		delete[] errnum;
	}
	while (true)
	{
		//表格打印
		if (LnowWord != LshowWord)
		{
			for (int i = 0; LnowWord < LshowWord; LnowWord++, i += HeightPiece * 2 + 4)
			{
				if (LnowWord < errorwordNum)
				{
					string temp = to_string(words[errindex[LnowWord]].errorNum);
					WordFrom(WidthPiece * 22, HeightPiece * 2 + i, WidthPiece * 4.5, HeightPiece * 2, words[errindex[LnowWord]].word.c_str());
					WordFrom(WidthPiece * 26.5 + 4, HeightPiece * 2 + i, WidthPiece * 6.5, HeightPiece * 2, words[errindex[LnowWord]].mean.c_str());
					WordFrom(WidthPiece * 33 + 8, HeightPiece * 2 + i, HeightPiece * 3, HeightPiece * 2, temp.c_str());
				}
				else
				{
					WordFrom(WidthPiece * 22, HeightPiece * 2 + i, WidthPiece * 4.5, HeightPiece * 2, "");
					WordFrom(WidthPiece * 26.5 + 4, HeightPiece * 2 + i, WidthPiece * 6.5, HeightPiece * 2, "");
					WordFrom(WidthPiece * 33 + 8, HeightPiece * 2 + i, HeightPiece * 3, HeightPiece * 2, "");
				}
			}
		}
		if (peekmessage(&ms, EX_MOUSE)) {
			if (next.isClick(ms))//翻页
			{
				Sound(ButtonPressSound);
				//若已显示的单词小于单词总数 则允许增加
				if (curPage < totalPage)
				{
					curPage++;
					LshowWord += onePage;

					settextcolor(WHITE);
					_stprintf_s(page, "%d / %d", curPage, totalPage);
					cout << page << endl;
					settextstyle(45, 0, "微软雅黑");
					WordFrom(WidthPiece * 27.3, HeightPiece * 33.5, WidthPiece * 3, HeightPiece * 2, page, 20);
				}
			}
			else if (last.isClick(ms))
			{
				Sound(ButtonPressSound);
				//若不在第一页则可以减少
				if (curPage != 1)
				{
					curPage--;
					LnowWord -= 2 * onePage;
					LshowWord -= onePage;

					settextcolor(WHITE);
					_stprintf_s(page, "%d / %d", curPage, totalPage);
					cout << page << endl;
					settextstyle(45, 0, "微软雅黑");
					WordFrom(WidthPiece * 27.3, HeightPiece * 33.5, WidthPiece * 3, HeightPiece * 2, page, 20);
				}
			}
			else if (back.isClick(ms))
			{
				Sound(ButtonPressSound);
				if(sw != 3)
					sw = 1;//切换到主界面
				if(errindex!=NULL)
					delete[] errindex;
				return;
			}
		}
		FlushBatchDraw();
	}
	
	
}

/*	void GameInterface() 游戏显示界面的实现
	负责人:		李铭康
	1.游戏底层贴图
	2.游戏界面绘制 (详见原型图)
*/
void GameFunction::GameInterface()
{
	cleardevice(); //清屏

	IMAGE img; //定义一个变量
	loadimage(&img, "./resource/bkImage/GameInterface.png", WindowWidth, WindowHeight); //相对路径：./表示当前文件夹下，../表示当前文件夹的上一级目录
	putimage(0, 0, &img);	 //绘制图像


	setlinecolor(RGB(213, 221, 224));		//画线
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE | PS_JOIN_ROUND, 6);
	line(3, HeightPiece * 7, WindowWidth * 3 / 8, HeightPiece * 7);
	line(WindowWidth * 5 / 8 + 6, HeightPiece * 7, WindowWidth, HeightPiece * 7);
	setlinecolor(RGB(29, 110, 157));
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE | PS_JOIN_ROUND, 2);
	line(0, HeightPiece * 7 - 2, WindowWidth * 3 / 8, HeightPiece * 7 - 2);
	line(0, HeightPiece * 7 + 2, WindowWidth * 3 / 8, HeightPiece * 7 + 2);
	setlinecolor(RGB(43, 60, 70));
	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE | PS_JOIN_ROUND, 2);
	line(WindowWidth * 5 / 8, HeightPiece * 7 - 2, WindowWidth, HeightPiece * 7 - 2);
	line(WindowWidth * 5 / 8, HeightPiece * 7 + 2, WindowWidth, HeightPiece * 7 + 2);


	setfillcolor(WHITE);		//画显示已输入字母的矩形框
	setlinestyle(PS_ENDCAP_FLAT, 6);
	setlinecolor(RGB(127, 255, 170));
	fillroundrect(WindowWidth * 3 / 8, HeightPiece * 1 / 2, WindowWidth * 5 / 8, HeightPiece * 9 / 2, 10, 10);
	setlinecolor(RGB(0, 100, 0));	//画外框
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
	roundrect(WindowWidth * 3 / 8 - 2, HeightPiece * 1 / 2 - 2, WindowWidth * 5 / 8 + 2, HeightPiece * 9 / 2 + 2, 8, 8);
	setlinecolor(RGB(60, 179, 113));	//画内框
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
	roundrect(WindowWidth * 3 / 8 + 4, HeightPiece * 1 / 2 + 4, WindowWidth * 5 / 8 - 4, HeightPiece * 9 / 2 - 4, 8, 8);

	setfillcolor(WHITE);		//画显示中文的矩形框
	setlinecolor(RGB(230, 230, 250));
	setlinestyle(PS_ENDCAP_FLAT, 6);
	fillroundrect(WindowWidth * 3 / 8, HeightPiece * 5, WindowWidth * 5 / 8, HeightPiece * 9, 10, 10);
	setlinecolor(RGB(75, 0, 130));	//画外框
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
	roundrect(WindowWidth * 3 / 8 - 2, HeightPiece * 5 - 2, WindowWidth * 5 / 8 + 2, HeightPiece * 9 + 2, 8, 8);
	setlinecolor(RGB(147, 112, 219));	//画内框
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
	roundrect(WindowWidth * 3 / 8 + 4, HeightPiece * 5 + 4, WindowWidth * 5 / 8 - 4, HeightPiece * 9 - 4, 8, 8);

	setlinecolor(RGB(156, 144, 144));	//画显示打乱后的字母的矩形框
	setlinestyle(PS_SOLID | PS_JOIN_ROUND | PS_ENDCAP_ROUND, 5);
	fillroundrect(4, HeightPiece * 23 + 4, WindowWidth - 4, WindowHeight - 4, 8, 8);
	setlinecolor(RGB(156, 144, 144));
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
	roundrect(1, HeightPiece * 23 + 1, WindowWidth - 1, WindowHeight - 1, 8, 8);		//外框
	setlinecolor(RGB(255, 215, 0));
	roundrect(7, HeightPiece * 23 + 7, WindowWidth - 7, WindowHeight - 7, 8, 8);		//内框
}

/*	void GameInterfaceOperation()	游戏界面操作功能
	1.调用goback()函数实现左上角返回按钮
	2.接收鼠标点击(拖动)操作
		调用角色Judge()
*/
//void GameFunction::GameInterfaceOperation(ExMessage& ms)
//{
//
//}

/*	void DisplayWord() 显示单词
	负责人:		田奕裕
	1.根据letter的坐标数据将letter中的字母依次显示出来(若isClickable==false则不显示)
	2.根据okLetter中已有的内容将其显示在上方字母显示区
	3.显示中文
*/
void GameFunction::DisplayWord()
{
	int	x = WindowWidth * 3 / 8 + 4,
		y = HeightPiece * 5 + 4,
		W = WindowWidth * 5 / 8 - 4 - x,
		H = HeightPiece * 9 - 4 - y,
		y_m = HeightPiece / 2 + 4;
	//W_m = W - 20,
	//x_m = WindowWidth / 2 - W_m / 2;

	DisplayMean(x,y,W,H);			//显示中文
	//fillroundrect(10, 480, , y + H, 15, 15);
	//cout << wordLength << endl;
	if (roleNum == 1)			//若选择战士职业  则显示已打乱的单词 否则不显示
	{
		setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
		setlinecolor(RGB(255, 215, 0));
		setfillcolor(WHITE);
		fillroundrect(7, HeightPiece * 23 + 7, WindowWidth - 7, WindowHeight - 7, 8, 8);		//内框
		for (size_t i = 0; i < wordLength; i++)
			DisplayLetter(letter[i]);	//打印字母
	}
	else if (roleNum == 2 && downLetter!="")
	{
		//显示已经按下的字母
		DisplayDown(downLetter,true);
	}
	//显示已拼好的英文
	DisplayOk(x, y_m, W, H,false);

}
//显示中文含义
void GameFunction::DisplayMean(int& x,int& y,int& W,int& H)
{
	setfillcolor(WHITE);
	setlinecolor(RGB(147, 112, 219));	//画内框
	//根据界面的大小绘制的显示框
	fillroundrect(x, y, x + W, y + H, 8, 8);
	int textSize = 100;	//代表字体大小
	//将string转为char*
	LPCTSTR mean = words[wordCurrent].mean.c_str();
	//居中对齐
	while (true)
	{
		settextstyle(textSize, 0, "微软雅黑");
		if (textwidth(mean) >= W - 6 || textheight(mean) >= H - 8)
			textSize -= 2;
		else
			break;
	}
	int text_x = (W - textwidth(mean)) / 2 + x;
	int text_y = (H - textheight(mean)) / 2 + y;
	settextcolor(BLACK);
	outtextxy(text_x, text_y, mean);
}

//显示单个字母
void GameFunction::DisplayLetter(Letter& letter)
{
	if (letter.isClickable)
	{
		setlinestyle(PS_SOLID, 3);
		setlinecolor(BLACK);
		if (letter.isHover)	//若鼠标悬浮
		{
			setfillcolor(RGB(120, 120, 120));
		}
		else
		{
			setfillcolor(WHITE);
		}
		fillroundrect(letter.x1, letter.y1, letter.x2, letter.y2, 20, 20);
		settextstyle(35, 0, "微软雅黑");
		settextcolor(BLACK);
		int a = letter.x1 + ((letter.x2 - letter.x1) - textwidth(letter.ch)) / 2;
		int b = letter.y1 + ((letter.y2 - letter.y1) - textheight(letter.ch)) / 2;
		outtextxy(a, b, letter.ch);
	}
	setlinestyle(PS_SOLID, 1);
}

//显示已拼好的英文
void GameFunction::DisplayOk(int& x, int& y, int& W, int& H,bool isComplete)
{
	setlinecolor(RGB(60, 179, 113));	//内框颜色
	setfillcolor(WHITE);
	fillroundrect(x, y, x + W, y + H, 8, 8);
	//words[wordCurrent]
	setlinecolor(WHITE);
	fillroundrect(x, y, x + W, y + H, 15, 15);
	int textSize = 100;	//代表字体大小
	//将string转为char*
	LPCTSTR word;
	if (isComplete)
	{
		word = words[wordCurrent].word.c_str();
	}
	else
	{
		word = okLetter;
	}
	//居中对齐
	while (true)
	{
		settextstyle(textSize, 0, "微软雅黑");
		if (textwidth(word) >= W - 4 || textheight(word) >= H - 8)
			textSize -= 2;
		else
			break;
	}
	int text_x = (W - textwidth(word)) / 2 + x;
	int text_y = (H - textheight(word)) / 2 + y;
	settextcolor(RGB(79, 154, 69));
	outtextxy(text_x, text_y, word);
}

void GameFunction::DisplayDown(string down,bool b)
{
	//画框
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
	setlinecolor(RGB(255, 215, 0));
	setfillcolor(WHITE);
	fillroundrect(7, HeightPiece * 23 + 7, WindowWidth - 7, WindowHeight - 7, 8, 8);		//内框

	
	//宽度 WindowWidth-14
	//高度 HeightPiece*13 -14
	int dis = 10;//每个方块的距离
	int n = down.size();//表示当前有多少个字符要显示

	int w = (HeightPiece * 13  - 14) / 3;//内框的1/3高度
	int h = w;

	int x = ((WindowWidth - 14) - (n * w + (n - 1) * dis)) / 2 + 7;
	int y = (HeightPiece * 23 + 7) + (HeightPiece * 13 - 14 - h)/2;

	//打印出来
	for (size_t i = 0; i < n - 1; i++)
	{
		//setfillcolor(RGB(230,230,230));
		//WordFrom(100,100, 50, 50, down.substr(i, 1).c_str());		//字母框
		WordFrom(x+i*(w+dis), y, w, h, down.substr(i, 1).c_str());		//字母框

	}
	if (b)
	{
		WordFrom(x + (n-1) * (w + dis), y, w, h, down.substr((n-1), 1).c_str());		//字母框
	}
	else
	{
		//输入错误则打印成红色
		WordFrom(x + (n - 1) * (w + dis), y, w, h, down.substr((n - 1), 1).c_str(),0);		//字母框
	}
}

/*	void button()输入按钮左上角位置、宽、高、按钮名称，打印按钮并将文字居中
	void isClick()判断按钮是否被点击 以及悬浮效果
	负责人:		田奕裕 
*/
Button::Button(int x, int y, int w, int h, LPCTSTR str, int textSize)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->str = str;
	this->textSize = textSize;
	this->fillColor = RGB(238, 248, 254);//默认爱丽丝蓝
	this->lineColor = BLACK;//默认描边黑色
	this->textColor = BLACK;//默认文字黑色

	setfillcolor(fillColor);
	setlinecolor(lineColor);
	fillroundrect(x, y, x + w, y + h, 30, 30);
	settextstyle(textSize, 0, "微软雅黑");
	settextcolor(textColor);
	int a = x + (w - textwidth(str)) / 2;
	int b = y + (h - textheight(str)) / 2;
	outtextxy(a, b, str);
}
Button::Button(int x, int y, int w, int h, LPCTSTR str, COLORREF fillColor, COLORREF lineColor, COLORREF textColor, int textSize)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->str = str;
	this->textSize = textSize;
	this->fillColor = fillColor;
	this->lineColor = lineColor;
	this->textColor = textColor;

	setfillcolor(fillColor);
	setlinecolor(lineColor);
	fillroundrect(x, y, x + w, y + h, 30, 30);
	settextstyle(textSize, 0, "微软雅黑");
	settextcolor(textColor);
	int a = x + (w - textwidth(str)) / 2;
	int b = y + (h - textheight(str)) / 2;
	outtextxy(a, b, str);
}
bool Button::isClick(ExMessage& msg)
{
	if (!this->isHover)
	{
		//绘制按钮 默认淡蓝色
		setfillcolor(fillColor);
		setlinecolor(lineColor);
		fillroundrect(x, y, x + w, y + h, 30, 30);
		settextstyle(textSize, 0, "微软雅黑");
		settextcolor(textColor);
		int a = x + (w - textwidth(str)) / 2;
		int b = y + (h - textheight(str)) / 2;
		outtextxy(a, b, str);
	}
	else
	{
		//悬浮时的颜色 默认蓝色
		setfillcolor(RGB(136, 206, 250));
		setlinecolor(lineColor);
		fillroundrect(x, y, x + w, y + h, 30, 30);
		settextstyle(textSize, 0, "微软雅黑");
		settextcolor(textColor);
		int a = x + (w - textwidth(str)) / 2;
		int b = y + (h - textheight(str)) / 2;
		outtextxy(a, b, str);
	}

	switch (msg.message)
	{
	//左键点击
	case WM_LBUTTONDOWN:
		if (msg.x >= x && msg.y >= y && msg.x <= x + w && msg.y <= y + h)
			return true;
		break;
	//鼠标移动
	case WM_MOUSEMOVE:
		if (msg.x >= x && msg.y >= y && msg.x <= x + w && msg.y <= y + h)
		{
			this->isHover = true;//代表鼠标悬浮在按钮上
		}
		else
			this->isHover = false;//表示鼠标没有悬停在按钮上
		break;
	}
	return false;
}
bool Button::isClick(ExMessage& msg, COLORREF hoverColor)
{
	if (!this->isHover)
	{
		//绘制按钮 
		setfillcolor(fillColor);
		setlinecolor(lineColor);
		fillroundrect(x, y, x + w, y + h, 30, 30);
		settextstyle(textSize, 0,"微软雅黑");
		settextcolor(textColor);
		int a = x + (w - textwidth(str)) / 2;
		int b = y + (h - textheight(str)) / 2;
		outtextxy(a, b, str);
	}
	else
	{
		//悬浮时的颜色 
		setfillcolor(hoverColor);
		setlinecolor(lineColor);
		fillroundrect(x, y, x + w, y + h, 30, 30);
		settextstyle(textSize, 0, "微软雅黑");
		settextcolor(textColor);
		int a = x + (w - textwidth(str)) / 2;
		int b = y + (h - textheight(str)) / 2;
		outtextxy(a, b, str);
	}

	switch (msg.message)
	{
		//左键点击
	case WM_LBUTTONDOWN:
		if (msg.x >= x && msg.y >= y && msg.x <= x + w && msg.y <= y + h)
			return true;
		break;
		//鼠标移动
	case WM_MOUSEMOVE:
		if (msg.x >= x && msg.y >= y && msg.x <= x + w && msg.y <= y + h)
		{
			this->isHover = true;//代表鼠标悬浮在按钮上
		}
		else
			this->isHover = false;//表示鼠标没有悬停在按钮上
		break;
	}
	return false;
}


/*	void Lifebar() 血条显示
	负责人:		张家宁
	1.根据role指针和monster指针中的血量数据来绘制血条
	2.血条上显示当前血量和最大血量 如(10/20)
*/
void GameFunction::Lifebar(int& role_life, int& monster_life)
{
	int bar_x = WidthPiece * 3.4, 
		bar_y = HeightPiece * 6.3,
		bar_width = WidthPiece * 7,
		bar_height = HeightPiece * 1.6;
	char str1[20] = { 0 }, str2[20] = { 0 };

	_stprintf_s(str1, "%d / %d", this->role->last_HP, this->role->maxHP);
	_stprintf_s(str2, "%d / %d", this->monster->last_HP, this->monster->maxHP);

	//玩家血条
	LifebarDraw(bar_x, bar_y, bar_width, bar_height, (float)role->last_HP/ role->maxHP,str1);
	LifebarDraw(WindowWidth - bar_x - bar_width, bar_y, bar_width, bar_height, (float)monster->last_HP/ monster->maxHP,str2);

	while ((role->HP != role->last_HP) || (monster->HP != monster->last_HP))
	{
		BeginBatchDraw();
		if (role->HP < role->last_HP)
		{
			this->role->last_HP--;
		}
		else if (role->HP > role->last_HP)
		{
			this->role->last_HP++;
		}
		if (monster->HP < monster->last_HP)
		{
			this->monster->last_HP--;
		}
		else if (monster->HP > monster->last_HP)
		{
			this->monster->last_HP++;
			
		}
		//显示两个血条
		_stprintf_s(str1, "%d / %d", this->role->last_HP, this->role->maxHP);
		LifebarDraw(bar_x, bar_y, bar_width, bar_height, (float)role->last_HP / role->maxHP, str1);
		_stprintf_s(str2, "%d / %d", this->monster->last_HP, this->monster->maxHP);
		LifebarDraw(WindowWidth - bar_x - bar_width, bar_y, bar_width, bar_height, ((float)monster->last_HP / monster->maxHP), str2);

		FlushBatchDraw();
		//等待50毫秒
		Sleep(50);
		
	}
	EndBatchDraw();
}
//血条矩形绘制
void GameFunction::LifebarDraw(int x,int y,int w,int h,float per, LPCTSTR str)
{
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	settextcolor(BLACK);
	settextstyle(20, 0, "微软雅黑");
	setlinestyle(PS_SOLID, 1);
	fillrectangle(x, y, x + w, y + h);//代表血条后面的白框
	setlinecolor(RGB(255, 68, 0));
	setfillcolor(RGB(255, 68, 0));
	fillrectangle(x+3, y+3, x + w*per - 3, (y + h)-3);//代表血条(红)

	int textSize = 30;	//代表字体大小
	//居中对齐
	while (true)
	{
		settextstyle(textSize, 0, "微软雅黑");
		if (textwidth(str) >= w - 5 || textheight(str) >= h - 4)
			textSize -= 2;
		else
			break;
	}
	int text_x = (w - textwidth(str)) / 2 + x;
	int text_y = (h - textheight(str)) / 2 + y;
	settextcolor(BLACK);
	outtextxy(text_x, text_y, str);
}


/*	void End()  游戏结束界面

	1.利用isWin的值 显示胜利或失败贴图
	2.实现按钮 实现悬浮按钮变色 点击功能 以及点击音效
		拼写概况		调用拼写概况界面函数
		重新开始		sw = 2
		返回主菜单	sw = 1
*/
void GameFunction::End()
{
	BeginBatchDraw();
	cleardevice();
	isGame = true;
	IMAGE img;
	loadimage(&img, "./resource/bkImage/End.png", WindowWidth, WindowHeight);//载入游戏界面的图片	用于动画刷新
	//绘制图片
	putimage(0, 0, &img);

	int width = WidthPiece * 6,
		height = HeightPiece * 4,
		dis = HeightPiece * 6;
	if (isWin)
	{
		char arr[] = "WIN";
		settextcolor(GREEN);
		settextstyle(100, 0, "微软雅黑");
		outtextxy((WindowWidth - textwidth(arr)) / 2, (WindowHeight - textheight(arr)) / 4 - 6, arr);
	}
	else
	{
		char arr[] = "LOSE";
		settextcolor(RED);
		settextstyle(100, 0, "微软雅黑");
		outtextxy((WindowWidth - textwidth(arr)) / 2, (WindowHeight - textheight(arr)) / 4 - 6, arr);
	}
	Button b1((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 1, width, height, "拼写概况", 40);
	Button b2((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 2, width, height, "重新开始", 40);
	Button b3((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 3, width, height, "返回主菜单", 40);
	ExMessage ms;
	while (true) {
		if (peekmessage(&ms)) {
			if (b1.isClick(ms)) {//单词概况
				Sound(ButtonPressSound);
				WordSituation();
				//绘制图片
				putimage(0, 0, &img);
			}
			else if (b2.isClick(ms)) {//重新开始 回到职业选择界面
				sw = 2;
				Sound(ButtonPressSound);
				return;
			}
			else if (b3.isClick(ms)) {//返回主菜单
				//mciSendString("Stop ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3 to start", 0, 0, 0);//从开头开始播放
				sw = 1;
				Sound(ButtonPressSound);
				return;
			}
		}
		FlushBatchDraw();
	}
}

/*↓———————————————————————————————————————Service———————————————————————————————————————————————↓*/

/*	GameFunction() 只运行一次
	负责人:		许兴邦
	1.确定TxT文本里面的单词数量 开辟相应数量的Word类型数组
	2.接收TxT文本里面的单词和中文意思 并分别存储到Word数组里面 一个元素存储一个单词和一个含义
	3.将wordNum赋值为相应值
*/
GameFunction::GameFunction()
{
	loadRecord();
	this->wordNum = words.size();
	//[];
}

/*	void loadRecord()	读取文件内的单词
	负责人:		许兴邦
*/
void GameFunction::loadRecord()
{
	ifstream ifs("./Data/Words.txt", ios::in);

	if (!ifs.is_open())
	{
		cout << "单词表不存在" << endl;
		ifs.close();
		exit(0);
		return;
	}
	char ch;
	int num = 0;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "单词表为空" << endl;
		ifs.close();
		//exit(0);
		return;
	}

	ifs.putback(ch);
	string wordE;
	string wordC;
	while (ifs >> wordE)
	{
		ifs >> wordC;
		ifs >> ch;
		if (ch >= '0' && ch <= '9')
		{
			ifs.putback(ch);//读到的是数字 则放回去
			ifs >> num;//并且将数值存到num中
		}
		else
		{
			ifs.putback(ch);//读到的是字母  则放回去 继续读取下一行
			num = 0;
		}
		//wordC = UtfToGbk(wordC);
		Word tempword(wordE, wordC,num);
		words.push_back(tempword);
	}
	ifs.close();	//关闭文件
}


/*	void Init() 初始化：
	负责人:		田奕裕
	1.errorNum = 3;(重置可错误次数)
	2.isRead = true;(允许下次随机单词读取)
	3.按sw不同值播放不同的背景音乐
	4.current = 0;(初始化当前判断的字母下标)
	5.wordCurrent = 0;(当前单词)
*/
void GameFunction::Init()
{
	switch (sw)//按sw不同值播放不同的背景音乐 并且执行不同的代码
	{
	case 1://开始菜单界面
		if (!isGame && playBGM)
		{
			mciSendString("pause ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3", 0, 0, 0);
			mciSendString("resume ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3", 0, 0, 0);
		}
		else if (playBGM)//若是从结束界面 或者游戏过程中退出来的 那就重新播放开始菜单BGM
		{
			mciSendString("stop ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3", 0, 0, 0);
			mciSendString("stop ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3", 0, 0, 0);
			Sound(InitInterfaceBGMPlay);//重新播放开始界面BGM
		}
		isGame = false;
		break;
	case 2://职业选择界面
		if (playBGM)
		{
			mciSendString("pause ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3", 0, 0, 0);
			//mciSendString("resume ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3", 0, 0, 0);
			mciSendString("stop ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3", 0, 0, 0);
			Sound(GameStartBGM);//播放职业选择界面BGM
			//mciSendString("seek ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3 to 0", 0, 0, 0);//从开头开始播放
		}
		break;
	case 3://游戏界面
		errorNum = 3;		//(重置可错误次数)
		isGame = true;		//表示现在在游戏内
		isRead = true;		//(允许下次随机单词读取)
		current = 0;		//(初始化当前判断的字母下标)
		wordCurrent = 0;	//(重置当前单词)
		wordLength = 0;		//重置单词长度
		break;
	case 8://结束界面
		//Sound(Stop);
		//Sound(EndBGM);
	default:
		break;
	}
}




//功能删除......
/*	int GoBack()   改为在各个界面单独实现返回按钮
	1.绘制左上角返回按钮
	2.利用传入的msg 实现点击 功能 若点击按钮则：
		当sw = 2		使 sw = 1	职业选择界面的返回
		当sw = 4		使 sw = 1	单词列表界面的返回
		当sw = 6		使 sw = 1	游戏外设置的返回
		当sw = 5		使 sw = 1	开发者名单界面的返回
		当sw = 7	 || isGame = true	使 sw = 3	游戏过程中查看单词概况
	3.悬浮效果 点击音效
*///功能删除......




/*	void InitMonster() 初始化怪物(写这个函数的是想着如果有选关功能 可以用这个函数创建不同的怪物对象)
	(当前只有一种怪物类)
	1.创建Demon类 用this->monster指向该类
*/
void GameFunction::InitMonster()
{
	this->monster = new Demon;
}

/*	void Sound(int sign)	通过接收的值实现各种功能 (具体功能见Sound.h文件)
	负责人:		梁雨菲
	1.当接收值为ShutBGM(-2)时 使playBGM = false; 
	2.当接收值为ShutSoundEffect(-3)时 使playEffect = false; 
	3.当playBGM为true时 允许执行1-3对应的功能
	4.当playEffect为true时 允许执行4-7对应的功能
*/


/*	void RandomRead() 随机读取单词 //随机选择一个单词读取信息存到wordLength和letter中 并且用随机数确定字母的位置
	负责人:	许兴邦	
	1.用rand()获取范围内的随机数 在words中随机选择一个单词进行读取
	2.将读取的单词的字母长度存储到wordLength中 
	  然后依次将字母存储到letter数组中 
	  并且将有存储字母的letter类改为可点击 (isClickable = true)
	3.利用随机数函数rand()为各个字母确定坐标 确定的坐标信息存储到letter中 (要保证其不重叠)
*/
void GameFunction::RandomRead()
{
	srand((unsigned)time(nullptr));			//随机数种子
	int W = 50;
	int H = 50;
	int Height = HeightPiece * 13 - 2*H;
	int Width = WindowWidth - 4*W;

	//setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
	//setlinecolor(RGB(255, 215, 0));
	//roundrect(7, HeightPiece * 25 + 7, WindowWidth - 7, WindowHeight - 7, 8, 8);		//内框


	if (this->isRead)						//若不需要读取新的单词则仅打乱
	{
		int temp = -1;
		temp = rand() % words.size();
		while (temp == this->wordCurrent)
		{
			temp = rand() % words.size();
		}
		this->wordCurrent = temp;//随机一个下标出来(并且与上一个单词不相同)
		cout << "RandomRead():已随机单词" << endl;
		this->isRead = false;
	}
	string sE(words[this->wordCurrent].word);
	
	//若为战士职业 则存储后打乱单词
	wordLength = sE.length() + 5;			//存储单词长度 +5个混淆的字母

	if (roleNum == 2)	//若为射手职业 则不需要打乱单词 存储即可
	{
		for (int i = 0; i < sE.length(); ++i)
		{
			letter[i].ch = sE[i];
		}
		return;
	}

	
	cout << "单词下标:" << this->wordCurrent << endl;

	for (int i = 0; i < wordLength-5; ++i) {
		letter[i].ch = sE[i];
		letter[i].isClickable = true;
		letter[i].isHover = false;

		do {
			cout << "随机中..." << endl;
			letter[i].x1 = (rand() % Width) + 2*W;
			letter[i].x2 = letter[i].x1 + W;
			letter[i].y1 = WindowHeight - (rand() % Height) - 1.5*H;
			letter[i].y2 = letter[i].y1 + H;

		} while (isSame(letter[i],letter,i + 1));
		//v.push_back(letter[i]);
	}
	cout << "RandomRead():字母已打乱" << endl;

	//用于增加混乱程度
	for (int i = wordLength - 5; i < wordLength; ++i) {
		letter[i].ch = 97+(rand()%26);//随机字母
		letter[i].isClickable = true;
		letter[i].isHover = false;

		do {
			cout << "随机中..." << endl;
			letter[i].x1 = (rand() % Width) + 2 * W;
			letter[i].x2 = letter[i].x1 + W;
			letter[i].y1 = WindowHeight - (rand() % Height) - 1.5 * H;
			letter[i].y2 = letter[i].y1 + H;

		} while (isSame(letter[i], letter, i + 1));
		//v.push_back(letter[i]);
	}
	cout << "RandomRead():字母已混淆" << endl;
}

/*	bool isSame() 判断字母是否重叠
	负责人:		许兴邦
*/
bool GameFunction::isSame(Letter& currentletterpos, Letter* letter, int length)
{
	for (int i = 0; i < length-1; i++)
	{
		if (((currentletterpos.x1 > letter[i].x1 - 2 && currentletterpos.x1 < letter[i].x2 + 2)
			&& (currentletterpos.y1 > letter[i].y1 - 2 && currentletterpos.y1 < letter[i].y2 + 2))
			||
			((currentletterpos.x2 > letter[i].x1 - 2 && currentletterpos.x2 < letter[i].x2 + 2)
			&& (currentletterpos.y2 > letter[i].y1 - 2 && currentletterpos.y2 < letter[i].y2 + 2))
			||
			((currentletterpos.x1 > letter[i].x1 - 2 && currentletterpos.x1 < letter[i].x2 + 2)
			&& (currentletterpos.y2 > letter[i].y1 - 2 && currentletterpos.y2 < letter[i].y2 + 2))
			||
			((currentletterpos.x2 > letter[i].x1 - 2 && currentletterpos.x2 < letter[i].x2 + 2)
			&& (currentletterpos.y1 > letter[i].y1 - 2 && currentletterpos.y1 < letter[i].y2 + 2)))
		{
			return true;
		}
		else
			continue;//与每个字母都不重叠
	}
	return false;
}

void GameFunction::SaveErrorNum()
{
	ofstream ofs("./Data/Words.txt", ios::out);//以输入形式打开文件
	//写入数据
	for (size_t i = 0; i < words.size(); i++)
	{
		ofs << words[i].word << ' ' << words[i].mean << ' ' << words[i].errorNum << endl;
	}
}



//用来防止string读取中文乱码 将utf-8转为gbk格式	
//来自:CSDN
//string GameFunction::UtfToGbk(string strValue)
//{
//	int len = MultiByteToWideChar(CP_UTF8, 0, strValue.c_str(), -1, NULL, 0);
//	wchar_t* wstr = new wchar_t[len + 1];
//	memset(wstr, 0, len + 1);
//	MultiByteToWideChar(CP_UTF8, 0, strValue.c_str(), -1, wstr, len);
//	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
//	char* str = new char[len + 1];
//	memset(str, 0, len + 1);
//	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
//	if (wstr) delete[] wstr;
//	return string(str);
//}


/*	~GameFunction() 析构函数
	若有开辟空间 可以在此处释放
*/
GameFunction::~GameFunction()
{
	if(role != NULL)
		delete role;
	if(monster != NULL)
		delete monster;
}

//Word的构造函数
Word::Word(string word, string mean,int num)
{
	this->word = word;
	this->mean = mean;
	errorNum = num;//拼错的次数
}



//bool Letter::isClick(ExMessage& msg)
//{
//	BeginBatchDraw();
//	if (this->isClickable)
//	{
//		setlinestyle(PS_SOLID, 3);
//		setlinecolor(BLACK);
//		if (this->isHover)	//若鼠标悬浮
//			setfillcolor(RGB(120, 120, 120));
//		else
//			setfillcolor(WHITE);
//		fillroundrect(this->x1, this->y1, this->x2, this->y2, 20, 20);
//		settextstyle(35, 0, "微软雅黑");
//		settextcolor(BLACK);
//		int a = this->x1 + ((this->x2 - this->x1) - textwidth(this->ch)) / 2;
//		int b = this->y1 + ((this->y2 - this->y1) - textheight(this->ch)) / 2;
//		outtextxy(a, b, this->ch);
//	}
//	setlinestyle(PS_SOLID, 1);
//	FlushBatchDraw();
//
//	switch (msg.message)
//	{
//		//左键点击
//	case WM_LBUTTONDOWN:
//		if (msg.x >= x1 && msg.y >= y1 && msg.x <= x2 && msg.y <= y2)
//			return true;
//		break;
//		//鼠标移动
//	case WM_MOUSEMOVE:
//		if (msg.x >= x1 && msg.y >= y1 && msg.x <= x2 && msg.y <= y2)
//			this->isHover = true;//代表鼠标悬浮在按钮上
//		else
//			this->isHover = false;//表示鼠标没有悬停在按钮上
//		break;
//	}
//
//	return false;
//}