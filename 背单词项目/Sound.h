#pragma once
extern void Sound(int sign);
extern void LoadMusic();				//���ػ��õ���BGM�ļ�����Ч�ļ�
extern void SoundStop();				//��ͣ����
extern void CloseSound();				//�رմ򿪵���Ƶ	
extern bool playBGM;					//��ʾ�Ƿ񲥷�BGM
extern bool playEffect;					//��ʾ�Ƿ񲥷���Ч
extern void SEUP();
extern void SEDOWN();
extern void BGMDOWN();
extern void BGMUP();

//���ܣ�
#define Stop -1							//ֹͣ��ǰ����
#define StopH -2						//ֹͣ�˴�������Ч
//#define ShutBGM -2					//�رձ�������
//#define ShutSoundEffect -3			//�ر���Ч

//BGM����
#define InitInterfaceBGMPlay 1			//���ſ�ʼ�����BGM
#define GameStartBGM 2					//��Ϸ��ʼʱ��BGM ����ְҵѡ��������Ϸ����
#define EndBGM 3						//��Ϸ���������BGM ������û�У�

//��Ϸ��Ч
#define ButtonHoverSound 4				//�����������ť��ʱ���ŵ���Ч
#define ButtonPressSound 5				//���°�ťʱ����Ч
#define WarriorAttack 6					//սʿ������Ч
#define ClickEffect 7					//�����ĸ��Ч (����û��)
#define InjuryEffect 8					//������Ч
#define ButtonBackPressSound 9			//���ذ�ť��Ч
#define Pause 10						//��ͣBGM
#define Play 11							//���¿�ʼ����
#define MageAttack 12

