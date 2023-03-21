#include "gamefunction.h"

extern vector<Word> words;
//ȫ�ֱ���
bool playBGM = true;				//��ʾ�Ƿ񲥷�BGM
bool playEffect = true;				//��ʾ�Ƿ񲥷���Ч
int BGMVolume = 600;				//Ĭ������60%
int SEVolume = 600;				//Ĭ������60%
IMAGE start;
IMAGE lstart;
IMAGE rstart;

//sw:
//1 ����ʼ���� 
//2 ����ְҵѡ�����
//3 ������Ϸ����
//4 ��ʾ����ĵ��ʵĽ���
//5 ��������������
//6 ��Ϸ�����ý���
//7 ���ʸſ�����
//8 ��������
//9 ��Ϸ������
//10 �˳���Ϸ


int main()
{
	loadimage(&start, "./resource/bkImage/start.png",WindowWidth,WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	loadimage(&lstart, "./resource/bkImage/lstart.png",WindowWidth,WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	loadimage(&rstart, "./resource/bkImage/rstart.png",WindowWidth,WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	initgraph(WindowWidth, WindowHeight/*, EX_SHOWCONSOLE*/);
	IMAGE img;
	loadimage(&img, "./resource/bkImage/Init.png", WindowWidth, WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	putimage(0, 0, &img);
	//��ȡ���ھ��
	HWND hnd = GetHWnd();
	//���ô��ڱ���
	SetWindowText(hnd, "CrazyWords v0.4");
	setbkmode(TRANSPARENT);
	setbkcolor(WHITE);
	GameFunction gf;
	LoadMusic();	//������Ƶ

	//Button

	while (1)
	{
		switch (gf.sw)
		{
		case 1://��ʼ����
			gf.InitInterface();
			break;
		case 2://ѡ��ְҵ����
			gf.RoleChoice();
			break;
		case 3://��Ϸ����
			gf.Start();
			break;
		case 4://����ĵ��ʽ���
			gf.WordList();
			break;
		case 5://����������
			gf.DeveloperList();
			break;
		case 6://���ý���
			gf.SettingInterface();
			break;
		case 7://���ʸſ�
			gf.WordSituation();
			break;
		case 8://��������
			gf.End();
			break;
		default://�˳���Ϸ
			CloseSound();
			exit(0);
			break;
		}
	}
	return 0;
}





//���ڴ�png͸����Ƭ(��͸����)��ʹ�÷���: ImageTransparent(NULL, 220, 100, &picture[0]);//͸��png
void ImageTransparent(IMAGE* dstimg, int x, int y, IMAGE* srcimg) //�°�png
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}


//������Ƶ
void LoadMusic()
{
	string vo = to_string(BGMVolume);	//��ȡ��ǰ����
	string file;
	

	mciSendString("open ./reSources/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ����� .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/BGM/ս��_Ī����_������k448_��һ���� .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/button_back .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/button_click .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/injury .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/warrior_attack .mp3", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/Hover .wav", NULL, 0, NULL);
	mciSendString("open ./reSources/music/SE/mage_attack .mp3", NULL, 0, NULL);

	//file = "setaudio ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3 volume to ";
	//file.append(vo);//�����ַ���
	//mciSendString(file.c_str(), NULL, 0, NULL);	//��������
	//mciSendString("play ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3 repeat", 0, 0, 0);		//��ʼ�˵�bgm

	//file = "setaudio ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3 volume to ";
	//file.append(vo);//�����ַ���
	//mciSendString(file.c_str(), NULL, 0, NULL); //��������
	//mciSendString("play ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3 repeat", 0, 0, 0);

	Sound(InitInterfaceBGMPlay);
	Sound(GameStartBGM);
	mciSendString("pause ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3", 0, 0, 0);
	mciSendString("pause ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3", 0, 0, 0);
	
}
//ʵ����Ƶ���� ֹͣ�ȹ���
/*	void Sound(int sign)	ͨ�����յ�ֵʵ�ָ��ֹ��� (���幦�ܼ�Sound.h�ļ�)
	������:		�����
	1.������ֵΪShutBGM(-2)ʱ ʹplayBGM = false;
	2.������ֵΪShutSoundEffect(-3)ʱ ʹplayEffect = false;
	3.��playBGMΪtrueʱ ����ִ��1-3��Ӧ�Ĺ���
	4.��playEffectΪtrueʱ ����ִ��4-7��Ӧ�Ĺ���
*/
void Sound(int sign)
{
	/*
#define Stop -1							//ֹͣ��ǰ����

//BGM����
#define InitInterfaceBGMPlay 1			//���ſ�ʼ�����BGM
#define GameStartBGM 2					//��Ϸ��ʼʱ��BGM ����ְҵѡ��������Ϸ����
#define EndBGM 3						//��Ϸ���������BGM ������û�У�

//��Ϸ��Ч
#define ButtonHoverSound 4				//�����������ť��ʱ���ŵ���Ч
#define ButtonPressSound 5				//���°�ťʱ����Ч
#define AttackEffect 6					//������Ч
#define ClickEffect 7					//�����ĸ��Ч (����û��)
#define InjuryEffect 8					//������Ч
#define ButtonBackPressSound 9			//���ذ�ť��Ч
	*/
	string vo = to_string(BGMVolume);	//��ȡ��ǰBGM����
	string vo1 = to_string(SEVolume);	//��ȡ��ǰSE����
	string file;
	// to����һ��Ҫ�пո񣬲�Ȼ�ᱨ��
	//file = "setaudio ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3 volume to ";
	//file = "setaudio ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3 volume to ";
	//file.append(vo);//�����ַ���
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
		mciSendString("pause ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3", 0, 0, 0);
		mciSendString("pause ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3", 0, 0, 0);
	}
	if (sign == Play)
	{
		mciSendString("resume ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3", 0, 0, 0);
		mciSendString("resume ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3", 0, 0, 0);
	}

	if (playBGM)//ÿ�β���ǰ������������
	{
		switch (sign)
		{
		case InitInterfaceBGMPlay:
			// to����һ��Ҫ�пո񣬲�Ȼ�ᱨ��
			file = "setaudio ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3 volume to ";
			file.append(vo);//�����ַ���
			mciSendString("play ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3 repeat", 0, 0, 0);//��ʼ�˵�bgm
			mciSendString(file.c_str(), NULL, 0, NULL);	//��������
			break;

		case GameStartBGM:	//��Ϸ��ʼbgm
			file = "setaudio ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3 volume to ";
			file.append(vo);//�����ַ���
			mciSendString("play ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3 repeat", 0, 0, 0);	
			mciSendString(file.c_str(), NULL, 0, NULL); //��������
			break;
		}
	}
	if (playEffect)//ÿ�β���ǰ����������
	{
		switch (sign)
		{
		case ButtonPressSound:	//��ͨ��ť������Ч
			file = "setaudio ./resource/music/SE/button_click.mp3 volume to ";
			file.append(vo1);//�����ַ���
			mciSendString("play ./resource/music/SE/button_click.mp3", 0, 0, 0);
			mciSendString(file.c_str(), NULL, 0, NULL);	//��������
			break;

		case ButtonBackPressSound:	//���ذ�ť������Ч
			file = "setaudio ./resource/music/SE/button_back.mp3 volume to ";
			file.append(vo1);//�����ַ���
			mciSendString("play ./resource/music/SE/button_back.mp3", 0, 0, 0);
			mciSendString(file.c_str(), NULL, 0, NULL);	//��������
			break;

		case InjuryEffect:	//�ܵ�������Ч
			file = "setaudio ./resource/music/SE/injury.mp3 volume to ";
			file.append(vo1);//�����ַ���
			mciSendString("play ./resource/music/SE/injury.mp3", 0, 0, 0);
			mciSendString(file.c_str(), NULL, 0, NULL);	//��������
			break;

		case WarriorAttack:	//սʿ������Ч
			file = "setaudio ./resource/music/SE/warrior_attack.mp3 volume to ";
			file.append(vo1);//�����ַ���
			mciSendString("play ./resource/music/SE/warrior_attack.mp3", 0, 0, 0);
			mciSendString(file.c_str(), NULL, 0, NULL);	//��������
			break;

		case ButtonHoverSound:	//������Ч
			file = "setaudio ./resource/music/SE/Hover.wav volume to ";
			file.append(vo1);//�����ַ���
			mciSendString("play ./resource/music/SE/Hover.wav", NULL, 0, NULL);
			mciSendString(file.c_str(), NULL, 0, NULL);	//��������
			break;

		case MageAttack:
			file = "setaudio ./resource/music/SE/mage_attack.mp3 volume to ";
			file.append(vo1);//�����ַ���
			mciSendString("play ./resource/music/SE/mage_attack.mp3", NULL, 0, NULL);
			mciSendString(file.c_str(), NULL, 0, NULL);	//��������
			break;
		}
	}
}
void SoundStop()
{
	mciSendString("stop ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/button_back.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/button_click.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/injury.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/warrior_attack.mp3", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/Hover.wav", NULL, 0, NULL);
	mciSendString("stop ./resource/music/SE/mage_attack.mp3", NULL, 0, NULL);
}
void CloseSound()
{
	mciSendString("close ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3", NULL, 0, NULL);
	mciSendString("close ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3", NULL, 0, NULL);
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
	//mciSendString("status ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3 volume", a, 100, 0);

	//int volume = 0;		//�����洢������С
	//volume = atoi(a); //ת�����
	BGMVolume += 100;
	if (BGMVolume > 1000)//���Ϊ1000
		BGMVolume = 1000;
	cout << "��ǰBGM������" << BGMVolume << endl;
	string vo = to_string(BGMVolume);
	string file[2];

	// to����һ��Ҫ�пո񣬲�Ȼ�ᱨ��
	file[0] = "setaudio ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3 volume to ";
	file[1] = "setaudio ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3 volume to ";

	file[0].append(vo);//�����ַ���
	file[1].append(vo);//�����ַ���

	//����a���ַ�����������aת��Ϊ���֣����Ե���atoi����
	//int b = atoi(a);//ͨ��atoi���������ַ����ִ�ת����int����

	for (size_t i = 0; i < 2; i++)
	{
		mciSendString(file[i].c_str() , NULL, 0, NULL);
	}

}
void BGMDOWN()
{
	BGMVolume -= 100;
	if (BGMVolume < 0)//��СΪ0
		BGMVolume = 0;
	cout << "��ǰBGM������" << BGMVolume << endl;

	string vo = to_string(BGMVolume);
	string file[2];

	// to����һ��Ҫ�пո񣬲�Ȼ�ᱨ��
	file[0] = "setaudio ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3 volume to ";
	file[1] = "setaudio ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3 volume to ";

	file[0].append(vo);//�����ַ���
	file[1].append(vo);//�����ַ���

	//����a���ַ�����������aת��Ϊ���֣����Ե���atoi����
	//int b = atoi(a);//ͨ��atoi���������ַ����ִ�ת����int����

	for (size_t i = 0; i < 2; i++)
	{
		mciSendString(file[i].c_str(), NULL, 0, NULL);
	}

}
void SEUP()
{
	SEVolume += 100;
	if (SEVolume > 1000)//���Ϊ1000
		SEVolume = 1000;
	cout << "��ǰBGM������" << SEVolume << endl;
//	char res[260];
//	mciSendString("status ./resource/music/SE/button_back.mp3 volume", res, 260, 0);
//
//	int volume = 0;		//�����洢������С
//	volume = atoi(res); //ת�����
//	volume += 100;
//	if (volume > 1000)
//		volume = 1000;
//	cout << "��ǰSE������" << volume << endl;
//	string vo = to_string(volume);
//	string file[4];
//
//	// to����һ��Ҫ�пո񣬲�Ȼ�ᱨ��
//	file[0] = "setaudio ./resource/music/SE/button_back.mp3 volume to ";
//	file[1] = "setaudio ./resource/music/SE/button_click.mp3 volume to ";
//	file[2] = "setaudio ./resource/music/SE/injury.mp3 volume to ";
//	file[3] = "setaudio ./resource/music/SE/warrior_attack.mp3 volume to ";
//
//
//	file[0].append(vo);//�����ַ���
//	file[1].append(vo);//�����ַ���
//	file[2].append(vo);//�����ַ���
//	file[3].append(vo);//�����ַ���
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
	if (SEVolume < 0)//��СΪ0
		SEVolume = 0;
	cout << "��ǰBGM������" << SEVolume << endl;
//	char res[260];
//	mciSendString("status ./resource/music/SE/button_back.mp3 volume", res, 260, 0);
//
//	int volume = 0;		//�����洢������С
//	volume = atoi(res); //ת�����
//	volume -= 100;
//	if(volume < 0)
//		volume = 0;
//	cout << "��ǰSE������" << volume << endl;
//	string vo = to_string(volume);
//	string file[4];
//
//	// to����һ��Ҫ�пո񣬲�Ȼ�ᱨ��
//	file[0] = "setaudio ./resource/music/SE/button_back.mp3 volume to ";
//	file[1] = "setaudio ./resource/music/SE/button_click.mp3 volume to ";
//	file[2] = "setaudio ./resource/music/SE/injury.mp3 volume to ";
//	file[3] = "setaudio ./resource/music/SE/warrior_attack.mp3 volume to ";
//
//	file[0].append(vo);//�����ַ���
//	file[1].append(vo);//�����ַ���
//	file[2].append(vo);//�����ַ���
//	file[3].append(vo);//�����ַ���
//
//	for (size_t i = 0; i < 4; i++)
//	{
//		mciSendString(file[i].c_str(), NULL, 0, NULL);
//	}
//
}