#pragma once
extern void Sound(int sign);
extern void LoadMusic();				//加载会用到的BGM文件和音效文件
extern void SoundStop();				//暂停音乐
extern void CloseSound();				//关闭打开的音频	
extern bool playBGM;					//表示是否播放BGM
extern bool playEffect;					//表示是否播放音效
extern void SEUP();
extern void SEDOWN();
extern void BGMDOWN();
extern void BGMUP();

//功能：
#define Stop -1							//停止当前播放
#define StopH -2						//停止此次悬浮音效
//#define ShutBGM -2					//关闭背景音乐
//#define ShutSoundEffect -3			//关闭音效

//BGM播放
#define InitInterfaceBGMPlay 1			//播放开始界面的BGM
#define GameStartBGM 2					//游戏开始时的BGM 用于职业选择界面和游戏界面
#define EndBGM 3						//游戏结束界面的BGM （可以没有）

//游戏音效
#define ButtonHoverSound 4				//鼠标悬浮到按钮上时播放的音效
#define ButtonPressSound 5				//按下按钮时的音效
#define WarriorAttack 6					//战士攻击音效
#define ClickEffect 7					//点击字母音效 (可以没有)
#define InjuryEffect 8					//受伤音效
#define ButtonBackPressSound 9			//返回按钮音效
#define Pause 10						//暂停BGM
#define Play 11							//重新开始播放
#define MageAttack 12

