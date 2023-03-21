#include "gamefunction.h"

extern vector<Word> words;
//全局变量
bool playBGM = true;				//表示是否播放BGM
bool playEffect = true;				//表示是否播放音效
int BGMVolume = 600;				//默认音量60%
int SEVolume = 600;				//默认音量60%
IMAGE start;
IMAGE lstart;
IMAGE rstart;

//sw:
//1 代表开始界面 
//2 代表职业选择界面
//3 代表游戏界面
//4 显示导入的单词的界面
//5 开发者名单界面
//6 游戏外设置界面
//7 单词概况界面
//8 结束界面
//9 游戏内设置
//10 退出游戏


int main()
{
	loadimage(&start, "./resource/bkImage/start.png",WindowWidth,WindowHeight);//载入游戏界面的图片	用于动画刷新
	loadimage(&lstart, "./resource/bkImage/lstart.png",WindowWidth,WindowHeight);//载入游戏界面的图片	用于动画刷新
	loadimage(&rstart, "./resource/bkImage/rstart.png",WindowWidth,WindowHeight);//载入游戏界面的图片	用于动画刷新
	initgraph(WindowWidth, WindowHeight/*, EX_SHOWCONSOLE*/);
	IMAGE img;
	loadimage(&img, "./resource/bkImage/Init.png", WindowWidth, WindowHeight);//载入游戏界面的图片	用于动画刷新
	putimage(0, 0, &img);
	//获取窗口句柄
	HWND hnd = GetHWnd();
	//设置窗口标题
	SetWindowText(hnd, "CrazyWords v0.4");
	setbkmode(TRANSPARENT);
	setbkcolor(WHITE);
	GameFunction gf;
	LoadMusic();	//载入音频

	//Button

	while (1)
	{
		switch (gf.sw)
		{
		case 1://开始界面
			gf.InitInterface();
			break;
		case 2://选择职业界面
			gf.RoleChoice();
			break;
		case 3://游戏界面
			gf.Start();
			break;
		case 4://导入的单词界面
			gf.WordList();
			break;
		case 5://开发者名单
			gf.DeveloperList();
			break;
		case 6://设置界面
			gf.SettingInterface();
			break;
		case 7://单词概况
			gf.WordSituation();
			break;
		case 8://结束界面
			gf.End();
			break;
		default://退出游戏
			CloseSound();
			exit(0);
			break;
		}
	}
	return 0;
}





//用于打开png透明照片(仅透明底)：使用方法: ImageTransparent(NULL, 220, 100, &picture[0]);//透明png
void ImageTransparent(IMAGE* dstimg, int x, int y, IMAGE* srcimg) //新版png
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}


//载入音频
void LoadMusic()
{
	string vo = to_string(BGMVolume);	//获取当前音量
	string file;
	

	mciSendString("open ./reSources/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章 .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章 .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/button_back .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/button_click .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/injury .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/warrior_attack .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/Hover .wav", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/mage_attack .mp3", NULL, 0, NULL);

	//file = "setaudio ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3 volume to ";
	//file.append(vo);//连接字符串
	//mciSendString(file.c_str(), NULL, 0, NULL);	//设置音量
	//mciSendString("play ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3 repeat", 0, 0, 0);		//开始菜单bgm

	//file = "setaudio ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3 volume to ";
	//file.append(vo);//连接字符串
	//mciSendString(file.c_str(), NULL, 0, NULL); //设置音量
	//mciSendString("play ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3 repeat", 0, 0, 0);

	Sound(InitInterfaceBGMPlay);
	Sound(GameStartBGM);
	mciSendString("pause ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3", 0, 0, 0);
	mciSendString("pause ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3", 0, 0, 0);
	
}
//实现音频播放 停止等功能
/*	void Sound(int sign)	通过接收的值实现各种功能 (具体功能见Sound.h文件)
	负责人:		梁雨菲
	1.当接收值为ShutBGM(-2)时 使playBGM = false;
	2.当接收值为ShutSoundEffect(-3)时 使playEffect = false;
	3.当playBGM为true时 允许执行1-3对应的功能
	4.当playEffect为true时 允许执行4-7对应的功能
*/
void Sound(int sign)
{
	/*
#define Stop -1							//停止当前播放

//BGM播放
#define InitInterfaceBGMPlay 1			//播放开始界面的BGM
#define GameStartBGM 2					//游戏开始时的BGM 用于职业选择界面和游戏界面
#define EndBGM 3						//游戏结束界面的BGM （可以没有）

//游戏音效
#define ButtonHoverSound 4				//鼠标悬浮到按钮上时播放的音效
#define ButtonPressSound 5				//按下按钮时的音效
#define AttackEffect 6					//攻击音效
#define ClickEffect 7					//点击字母音效 (可以没有)
#define InjuryEffect 8					//受伤音效
#define ButtonBackPressSound 9			//返回按钮音效
	*/
	string vo = to_string(BGMVolume);	//获取当前BGM音量
	string vo1 = to_string(SEVolume);	//获取当前SE音量
	string file;
	// to后面一定要有空格，不然会报错
	//file = "setaudio ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3 volume to ";
	//file = "setaudio ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3 volume to ";
	//file.append(vo);//连接字符串
	//mciSendString(file.c_str(), NULL, 0, NULL);

//	file[0] = "setaudio ./resource/music/SE/button_back.mp3 volume to ";
//	file[1] = "setaudio ./resource/music/SE/button_click.mp3 volume to ";
//	file[2] = "setaudio ./resource/music/SE/injury.mp3 volume to ";
//	file[3] = "setaudio ./resource/music/SE/warrior_attack.mp3 volume to ";

	if (sign == Stop)
		SoundStop();
	//if (sign == StopH)
	//	mciSendString("stop ./resource/music/SE/Hover.wav", NULL, 0, NULL);
	if (sign == Pause)
	{
		mciSendString("pause ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3", 0, 0, 0);
		mciSendString("pause ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3", 0, 0, 0);
	}
	if (sign == Play)
	{
		mciSendString("resume ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3", 0, 0, 0);
		mciSendString("resume ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3", 0, 0, 0);
	}

	if (playBGM)//每次播放前都先设置音量
	{
		switch (sign)
		{
		case InitInterfaceBGMPlay:
			// to后面一定要有空格，不然会报错
			file = "setaudio ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3 volume to ";
			file.append(vo);//连接字符串
			mciSendString("play ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3 repeat", 0, 0, 0);//开始菜单bgm
			mciSendString(file.c_str(), NULL, 0, NULL);	//设置音量
			break;

		case GameStartBGM:	//游戏开始bgm
			file = "setaudio ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3 volume to ";
			file.append(vo);//连接字符串
			mciSendString("play ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3 repeat", 0, 0, 0);	
			mciSendString(file.c_str(), NULL, 0, NULL); //设置音量
			break;
		}
	}
	if (playEffect)//每次播放前先设置音量
	{
		switch (sign)
		{
		case ButtonPressSound:	//普通按钮按下音效
			file = "setaudio ./resource/music/SE/button_click.mp3 volume to ";
			file.append(vo1);//连接字符串
			mciSendString("play ./resource/music/SE/button_click.mp3", 0, 0, 0);
			mciSendString(file.c_str(), NULL, 0, NULL);	//设置音量
			break;

		case ButtonBackPressSound:	//返回按钮按下音效
			file = "setaudio ./resource/music/SE/button_back.mp3 volume to ";
			file.append(vo1);//连接字符串
			mciSendString("play ./resource/music/SE/button_back.mp3", 0, 0, 0);
			mciSendString(file.c_str(), NULL, 0, NULL);	//设置音量
			break;

		case InjuryEffect:	//受到攻击音效
			file = "setaudio ./resource/music/SE/injury.mp3 volume to ";
			file.append(vo1);//连接字符串
			mciSendString("play ./resource/music/SE/injury.mp3", 0, 0, 0);
			mciSendString(file.c_str(), NULL, 0, NULL);	//设置音量
			break;

		case WarriorAttack:	//战士攻击音效
			file = "setaudio ./resource/music/SE/warrior_attack.mp3 volume to ";
			file.append(vo1);//连接字符串
			mciSendString("play ./resource/music/SE/warrior_attack.mp3", 0, 0, 0);
			mciSendString(file.c_str(), NULL, 0, NULL);	//设置音量
			break;

		case ButtonHoverSound:	//悬浮音效
			file = "setaudio ./resource/music/SE/Hover.wav volume to ";
			file.append(vo1);//连接字符串
			mciSendString("play ./resource/music/SE/Hover.wav", NULL, 0, NULL);
			mciSendString(file.c_str(), NULL, 0, NULL);	//设置音量
			break;

		case MageAttack:
			file = "setaudio ./resource/music/SE/mage_attack.mp3 volume to ";
			file.append(vo1);//连接字符串
			mciSendString("play ./resource/music/SE/mage_attack.mp3", NULL, 0, NULL);
			mciSendString(file.c_str(), NULL, 0, NULL);	//设置音量
			break;
		}
	}
}
void SoundStop()
{
	mciSendString("stop ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/button_back.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/button_click.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/injury.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/warrior_attack.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/Hover.wav", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/mage_attack.mp3", NULL, 0, NULL);
}
void CloseSound()
{
	mciSendString("close ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3", NULL, 0, NULL);
	mciSendString("close ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3", NULL, 0, NULL);
	mciSendString("close ./resource/music/SE/button_back.mp3", NULL, 0, NULL);
	mciSendString("close ./resource/music/SE/button_click.mp3", NULL, 0, NULL);
	mciSendString("close ./resource/music/SE/injury.mp3", NULL, 0, NULL);
	mciSendString("close ./resource/music/SE/warrior_attack.mp3", NULL, 0, NULL);
	mciSendString("close ./resource/music/SE/Hover.wav", NULL, 0, NULL);
	mciSendString("close ./resource/music/SE/mage_attack.mp3", NULL, 0, NULL);
}
void BGMUP()
{
	//char a[100];
	//mciSendString("status ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3 volume", a, 100, 0);

	//int volume = 0;		//用来存储音量大小
	//volume = atoi(a); //转化语句
	BGMVolume += 100;
	if (BGMVolume > 1000)//最大为1000
		BGMVolume = 1000;
	cout << "当前BGM音量：" << BGMVolume << endl;
	string vo = to_string(BGMVolume);
	string file[2];

	// to后面一定要有空格，不然会报错
	file[0] = "setaudio ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3 volume to ";
	file[1] = "setaudio ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3 volume to ";

	file[0].append(vo);//连接字符串
	file[1].append(vo);//连接字符串

	//其中a是字符串，如果想把a转换为数字，可以调用atoi函数
	//int b = atoi(a);//通过atoi函数进行字符数字串转换到int类型

	for (size_t i = 0; i < 2; i++)
	{
		mciSendString(file[i].c_str() , NULL, 0, NULL);
	}

}
void BGMDOWN()
{
	BGMVolume -= 100;
	if (BGMVolume < 0)//最小为0
		BGMVolume = 0;
	cout << "当前BGM音量：" << BGMVolume << endl;

	string vo = to_string(BGMVolume);
	string file[2];

	// to后面一定要有空格，不然会报错
	file[0] = "setaudio ./resource/music/BGM/开始菜单_莫扎特_钢琴曲k448_第二乐章.mp3 volume to ";
	file[1] = "setaudio ./resource/music/BGM/战斗_莫扎特_钢琴曲k448_第一乐章.mp3 volume to ";

	file[0].append(vo);//连接字符串
	file[1].append(vo);//连接字符串

	//其中a是字符串，如果想把a转换为数字，可以调用atoi函数
	//int b = atoi(a);//通过atoi函数进行字符数字串转换到int类型

	for (size_t i = 0; i < 2; i++)
	{
		mciSendString(file[i].c_str(), NULL, 0, NULL);
	}

}
void SEUP()
{
	SEVolume += 100;
	if (SEVolume > 1000)//最大为1000
		SEVolume = 1000;
	cout << "当前BGM音量：" << SEVolume << endl;
//	char res[260];
//	mciSendString("status ./resource/music/SE/button_back.mp3 volume", res, 260, 0);
//
//	int volume = 0;		//用来存储音量大小
//	volume = atoi(res); //转化语句
//	volume += 100;
//	if (volume > 1000)
//		volume = 1000;
//	cout << "当前SE音量：" << volume << endl;
//	string vo = to_string(volume);
//	string file[4];
//
//	// to后面一定要有空格，不然会报错
//	file[0] = "setaudio ./resource/music/SE/button_back.mp3 volume to ";
//	file[1] = "setaudio ./resource/music/SE/button_click.mp3 volume to ";
//	file[2] = "setaudio ./resource/music/SE/injury.mp3 volume to ";
//	file[3] = "setaudio ./resource/music/SE/warrior_attack.mp3 volume to ";
//
//
//	file[0].append(vo);//连接字符串
//	file[1].append(vo);//连接字符串
//	file[2].append(vo);//连接字符串
//	file[3].append(vo);//连接字符串
//
//	for (size_t i = 0; i < 4; i++)
//	{
//		mciSendString(file[i].c_str(), NULL, 0, NULL);
//	}
//
}
void SEDOWN()
{
	SEVolume -= 100;
	if (SEVolume < 0)//最小为0
		SEVolume = 0;
	cout << "当前BGM音量：" << SEVolume << endl;
//	char res[260];
//	mciSendString("status ./resource/music/SE/button_back.mp3 volume", res, 260, 0);
//
//	int volume = 0;		//用来存储音量大小
//	volume = atoi(res); //转化语句
//	volume -= 100;
//	if(volume < 0)
//		volume = 0;
//	cout << "当前SE音量：" << volume << endl;
//	string vo = to_string(volume);
//	string file[4];
//
//	// to后面一定要有空格，不然会报错
//	file[0] = "setaudio ./resource/music/SE/button_back.mp3 volume to ";
//	file[1] = "setaudio ./resource/music/SE/button_click.mp3 volume to ";
//	file[2] = "setaudio ./resource/music/SE/injury.mp3 volume to ";
//	file[3] = "setaudio ./resource/music/SE/warrior_attack.mp3 volume to ";
//
//	file[0].append(vo);//连接字符串
//	file[1].append(vo);//连接字符串
//	file[2].append(vo);//连接字符串
//	file[3].append(vo);//连接字符串
//
//	for (size_t i = 0; i < 4; i++)
//	{
//		mciSendString(file[i].c_str(), NULL, 0, NULL);
//	}
//
}