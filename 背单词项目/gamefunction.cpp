#include "gamefunction.h"

extern void ImageTransparent(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
vector<Word> words;


/*��������������������������������������������������������������������������������View������������������������������������������������������������������������������������������������*/


/*	void InitInterface() ���˵�
	������:		�꺣��
	1.��������: ��С WindowWidth * WindowHeight
	2.���ϱ�����ͼ
	3.����Init()���� ���г�ʼ��
	4.���ư�ť
		��ʼ��Ϸ sw = 2
		�����б� sw = 4
		��Ϸ���� sw = 6
		�������� sw = 5
		�˳���Ϸ sw = 9
	5.ʵ�ְ�ť����
		�����Ӧ����ı�sw��ֵ
		�������Ч��(�������ڰ�ť��ʱ�ı䰴ť��ɫ)
	6.��չ
		���������Ч(����Sound()����)
		�������Ч(����Sound()����)
*/
void GameFunction::InitInterface()
{
	//��ͼ����
	IMAGE img;
	//Sound(InitInterfaceBGMPlay);
	//����ͼƬ  ��easyx��ʹ���ַ���
	//loadimage(&img, "images/bk.png", getwidth(), getheight());
	loadimage(&img, "./resource/bkImage/Init.png", WindowWidth, WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	//����ͼƬ
	putimage(0, 0, &img);
	int width = WidthPiece * 5.3,
		height = HeightPiece * 3.2,
		dis = HeightPiece * 3.7;
	//��ʼ����ȡ����
	Init();
	//Button btn0(WindowWidth / 2 - 20, WindowHeight - 500, 150, 75, str1, 50);
	BeginBatchDraw();
	Button btn1((WindowWidth - width)/2, (WindowHeight - height)/2.5 + dis * 1, width, height, "��ʼ��Ϸ", 40);
	Button btn2((WindowWidth - width)/2, (WindowHeight - height)/2.5 + dis * 2, width, height, "�����б�", 40);
	Button btn3((WindowWidth - width)/2, (WindowHeight - height)/2.5 + dis * 3, width, height, "��Ϸ����", 40);
	Button btn4((WindowWidth - width)/2, (WindowHeight - height)/2.5 + dis * 4, width, height, "��������", 40);
	Button btn5((WindowWidth - width)/2, (WindowHeight - height)/2.5 + dis * 5, width, height, "�˳���Ϸ", 40);
	//����ѭ�������ý�����һ�ξ�ʧЧ
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
				sw = -1;	//�˳���Ϸ
			}
		}
	FlushBatchDraw();
	}
}

/*	void DeveloperList() ��������������
	������:		����ԣ
	1.��ʾ��ͼ
	2.����GoBack()������ʵ�����ϽǷ��ذ�ť
*/
void GameFunction::DeveloperList()
{
	BeginBatchDraw();
	cleardevice();
	IMAGE img;
	loadimage(&img, "./resource/bkImage/DpList.png", WindowWidth, WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	putimage(0, 0, &img);
	int back_width = 3.3 * WidthPiece,
		back_height = 2.5 * HeightPiece;
	Button b(WidthPiece, HeightPiece, back_width, back_height, "�� ��", 30);
	ExMessage ms;
	while (true)
	{
		if (peekmessage(&ms, EX_MOUSE))
		{
			if (b.isClick(ms))
			{
				Sound(ButtonPressSound);
				sw = 1;//�л���������
				return;
			}
			FlushBatchDraw();
		}
	}
}

/*	void WordList() �����б���� ��ʾ����ɹ��ĵ���
	������:		Ī���
	1.���뱳����ͼ(�����)
	2.���÷��غ���ʵ�����ϽǷ��ذ�ť
	3.����Word*ָ��ĵ�����Ӣ������ ��������Ӣ��������ʾ��������
	4.ʵ�ַ�ҳ��ť ��һҳ ��һҳ  �Լ�ʵ�ַ�ҳ����
	5.�����б��·� ��ʾ��ǰҳ����ҳ�� ������20ҳ���� Ŀǰ�ڵ�3ҳ ����ʾ 3/20
*/
void GameFunction::WordList()
{
	BeginBatchDraw();
	cleardevice();

	IMAGE img;
	loadimage(&img, "./resource/bkImage/other.png", WindowWidth, WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	putimage(0, 0, &img);

	int onePage = 14;
	int LnowWord = 0;
	int LshowWord = onePage;
	int RnowWord = 0;
	int RshowWord = onePage;
	int totalPage = (wordNum + ((LshowWord + RshowWord) - 1)) / (LshowWord + RshowWord);	//��ҳ�� ����ȡ��
	int curPage = 1;	//��ǰҳ��
	
	char page[12] = { 0 };//���֧�� 10000/10000

	//λ�� ����
	int width = WidthPiece * 3,
		height = HeightPiece * 2.5,
		back_width = 3.3 * WidthPiece,
		back_height = 2.5 * HeightPiece;

	Button last((WindowWidth - width) / 6, (WindowHeight - height) / 5, width, height, "��һҳ", RGB(164, 173, 179), BLACK, WHITE, 30);
	Button next((WindowWidth - width) / 6, WindowHeight - ((WindowHeight - height) / 5) - height, width, height, "��һҳ", RGB(164, 173, 179), BLACK, WHITE, 30);
	Button back(WidthPiece, HeightPiece, back_width, back_height, "�� ��", 30);
	ExMessage ms;

	//char arr[] = "�����б�";
	int a = WidthPiece + (back_width - textwidth("��")) / 2;
	settextcolor(BLACK);
	settextstyle(65, 0, "΢���ź�");
	outtextxy(a, HeightPiece * 6, "��");
	outtextxy(a, HeightPiece * 13, "��");
	outtextxy(a, HeightPiece * 21, "��");
	outtextxy(a, HeightPiece * 29, "��");

	settextcolor(WHITE);
	_stprintf_s(page, "%d / %d", curPage, totalPage);
	cout << page << endl;
	settextstyle(45, 0, "΢���ź�");
	WordFrom(WidthPiece * 22.2, HeightPiece * 33.5, WidthPiece * 3, HeightPiece * 2, page, 20);

	while (true) 
	{
		//�����ӡ
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
		//�ұ���ӡ
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
			if (next.isClick(ms))//��ҳ
			{
				Sound(ButtonPressSound);
				//������ʾ�ĵ���С�ڵ������� ����������
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
					settextstyle(45, 0, "΢���ź�");
					WordFrom(WidthPiece * 22.2, HeightPiece * 33.5, WidthPiece*3, HeightPiece*2, page, 20);
				}
			}
			else if (last.isClick(ms))
			{
				Sound(ButtonPressSound);
				//�����ڵ�һҳ����Լ���
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
					settextstyle(45, 0, "΢���ź�");
					WordFrom(WidthPiece * 22.2, HeightPiece * 33.5, WidthPiece * 3, HeightPiece * 2, page, 20);
					//outtextxy(WidthPiece * 22.2, HeightPiece * 33.2, page);
				}
			}
			else if (back.isClick(ms))
			{
				Sound(ButtonPressSound);
				sw = 1;//�л���������
				return;
			}
		}
		FlushBatchDraw();
	}
}

//���ڻ��Ƶ��ʱ��
void GameFunction::WordFrom(int x,int y,int W,int H,LPCTSTR str)
{
	setfillcolor(RGB(206, 206, 206));
	setlinecolor(WHITE);
	fillroundrect(x, y, x + W, y + H, 0, 0);
	int textSize = 30;	//���������С
	while (true)	//�����Сƥ��
	{
		settextstyle(textSize, 0, "΢���ź�");
		if (textwidth(str) >= W - 6 || textheight(str) >= H - 8)
			textSize -= 2;
		else
			break;
	}
	//���ж���
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
	int textSize = 30;	//���������С
	while (true)	//�����Сƥ��
	{
		settextstyle(textSize, 0, "΢���ź�");
		if (textwidth(str) >= W - 6 || textheight(str) >= H - 8)
			textSize -= 2;
		else
			break;
	}
	//���ж���
	int text_x = (W - textwidth(str)) / 2 + x;
	int text_y = (H - textheight(str)) / 2 + y;
	settextcolor(BLACK);
	outtextxy(text_x, text_y, str);
}

/*	void DeveloperList() ְҵѡ�����
	������:	«����
	1.ְҵ���汳����ͼ
	2.����GoBack()����ʵ�� ���ϽǷ��ذ�ť(����������˵�)
	3.ʵ��ְҵѡ��ť �Լ���ť������ɫЧ�� �Լ������Ч(����Sound()����)
	4.ʵ��ְҵѡ��ť�ĵ�� �����ͬ�İ�ť������ͬ��role���� ����ʹsw=3������Ϸ����

	��չ:
	4.����ְҵѡ��ťʱ��ʾ��ְҵ�ľ�����Ϣ ˫��ʱѡ��ְҵ
*/
void GameFunction::RoleChoice()
{
	cleardevice();
	IMAGE img;
	IMAGE img1;
	IMAGE img2;
	bool refresh = true;
	int roleN = 1;//1����սʿ����
	loadimage(&img, "./resource/bkImage/RoleChoice.png", WindowWidth, WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	loadimage(&img1, "./resource/bkImage/RoleChoice1.png", WindowWidth, WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	loadimage(&img2, "./resource/bkImage/RoleChoice2.png", WindowWidth, WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	putimage(0, 0, &img);//�ײ㱳��  ֻ���һ��
	Init();
	int width = WidthPiece * 5,
		height = HeightPiece * 3,
		dis = HeightPiece * 6.5,
		back_width = 3.3 * WidthPiece,
		back_height = 2.5 * HeightPiece;
	Button b1(WidthPiece + height/2, WindowHeight / 2, height, height, "<--", 30);
	Button b2(WindowWidth - (WidthPiece + height / 2) - height, WindowHeight / 2, height, height, "-->", 30);
	Button ok((WindowWidth - width) / 2, HeightPiece * 31.5, width, height, "ѡ��", 40);
	Button b(WidthPiece, HeightPiece, back_width, back_height, "�� ��", 30);
	settextstyle(55, 0, "����");
	settextcolor(BLACK);
	//outtextxy((WindowWidth - width) / 2 - 100, ((WindowHeight - height) / 4 + dis) + (height - textheight("AD:10  HP:50  Click��")) / 2, "AD:10  HP:50  Click��");
	ExMessage m;
	while (true)
	{
		if (refresh)
		{
			switch (roleN)
			{
			case 1: //սʿ
				ImageTransparent(NULL, 0, 0, &img1);
				break;
			case 2: //��ʦ
				ImageTransparent(NULL, 0, 0, &img2);
				break;
			}
		}
		if (peekmessage(&m, EX_MOUSE))
		{
			BeginBatchDraw();
			if (b1.isClick(m))//��
			{
				Sound(ButtonPressSound);
				roleN -= 1;
				if (roleN <= 0)
					roleN = 1;
				refresh = true;
			}
			else if (b2.isClick(m))//��
			{
				Sound(ButtonPressSound);
				roleN += 1;
				if (roleN >= 2)
					roleN = 2;
				refresh = true;
			}
			else if (b.isClick(m))//����
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
				case 1: //ѡ��սʿ
					role = new warrior;
					roleNum = 1;
					sw = 3;
					return;
				case 2: //ѡ��ʦ
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

/*	void SettingInterface() ��Ϸ�����ý���
	������:		�ż���
	1.���ý�����ͼ
	2.����GoBack()����ʵ�����ϽǷ��ذ�ť
	3.ʵ����Ϸ������ý��� ʵ��������ť��ɫ ������� �Լ������Ч 
		��Ч����		����Sound����
		BGM����		����Sound����
		ƴд�ſ�		sw = 7
*/
void GameFunction::SettingInterface()
{
	BeginBatchDraw();
	cleardevice();
	IMAGE img;
	loadimage(&img, "./resource/bkImage/Setting.png", WindowWidth, WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	putimage(0, 0, &img);

	int width = WidthPiece*6,
		height = HeightPiece*4, 
		dis = HeightPiece*7.5, 
		back_width = 3.3*WidthPiece, 
		back_height = 2.5*HeightPiece;

	Button b1((WindowWidth - width) / 2, (WindowHeight - height) / 3.5, width, height, "��Ч����", 40);
	Button SEdown((WindowWidth - width) / 2 + width + 10, (WindowHeight - height) / 3.5 +10, height-20, height-20, "-", 50);
	Button SEup((WindowWidth - width) / 2 - height + 10, (WindowHeight - height) / 3.5 + 10, height-20, height-20, "+", 50);

	Button b2((WindowWidth - width) / 2, (WindowHeight - height) / 3.5 + dis * 1, width, height, "BGM����", 40);
	Button BGMdown((WindowWidth - width) / 2 + width + 10, (WindowHeight - height) / 3.5 + dis * 1 + 10, height-20, height - 20, "-", 50);
	Button BGMup((WindowWidth - width) / 2 - height + 10, (WindowHeight - height) / 3.5 + dis * 1 + 10, height - 20, height - 20, "+", 50);
	Button b3((WindowWidth - width) / 2, (WindowHeight - height) / 3.5 + dis * 2, width, height, "ƴд�ſ�", 40);

	Button b(WidthPiece, HeightPiece, back_width, back_height, "�� ��", 30);
	ExMessage ms;
	while (true) {
		if (peekmessage(&ms,EX_MOUSE)) {
			if (b1.isClick(ms))
			{
				if (playEffect)
				{
					Sound(ButtonPressSound);
					cout << "��Ч��" << endl;
					playEffect = false;
				}
				else
				{
					playEffect = true;
					Sound(ButtonPressSound);
					cout << "��Ч��" << endl;
				}
					
			}
			else if (b2.isClick(ms))
			{
				if (playBGM)
				{
					Sound(ButtonPressSound);
					Sound(Pause);
					cout << "BGM��" << endl;
					playBGM = false;
				}
				else
				{
					Sound(ButtonPressSound);
					cout << "BGM��" << endl;
					playBGM = true;
					mciSendString("resume ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3", 0, 0, 0);
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
				sw = 1;//�л���������
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

/*	void SettingINGame() ��Ϸ�����ý���
	1.ʵ����Ϸ�ڵ����ý���
		����GoBack()ʵ�����ϽǷ��� 	�ص���Ϸ
		�������˵�	sw = 1
		��Ч����		����Sound����
		BGM����		����Sound����
		ƴд�ſ�		sw = 7
	2.ʵ��������ť��ɫ ������� �Լ������Ч(����Sound����)
*/
void GameFunction::SettingINGame()
{
	BeginBatchDraw();
	cleardevice();
	IMAGE img;
	loadimage(&img, "./resource/bkImage/Setting.png", WindowWidth, WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	//����ͼƬ
	putimage(0, 0, &img);

	int width = WidthPiece * 6,
		height = HeightPiece * 4,
		dis = HeightPiece * 6.5,
		back_width = 3.3 * WidthPiece,
		back_height = 2.5 * HeightPiece;
	Button reInit((WindowWidth - width) / 2, (WindowHeight - height) / 4, width, height, "�������˵�", 40);
	Button b1((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 1, width, height, "��Ч����", 40);
	Button SEdown((WindowWidth - width) / 2 + width + 10, (WindowHeight - height) / 4 + dis + 10, height - 20, height - 20, "-", 50);
	Button SEup((WindowWidth - width) / 2 - height + 10, (WindowHeight - height) / 4 + dis + 10, height - 20, height - 20, "+", 50);

	Button b2((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 2, width, height, "BGM����", 40);
	Button BGMdown((WindowWidth - width) / 2 + width + 10, (WindowHeight - height) / 4 + dis * 2 + 10, height - 20, height - 20, "-", 50);
	Button BGMup((WindowWidth - width) / 2 - height + 10, (WindowHeight - height) / 4 + dis * 2 + 10, height - 20, height - 20, "+", 50);
	Button b3((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 3, width, height, "ƴд�ſ�", 40);
	Button b(WidthPiece, HeightPiece, back_width, back_height, "�� ��", 30);
	ExMessage ms;
	while (true) {
		if (peekmessage(&ms, EX_MOUSE)) {
			if (b1.isClick(ms))
			{
				if (playEffect)
				{
					Sound(ButtonPressSound);
					cout << "��Ч��" << endl;
					playEffect = false;
				}
				else
				{
					playEffect = true;
					Sound(ButtonPressSound);
					cout << "��Ч��" << endl;
				}

			}
			else if (b2.isClick(ms))
			{
				if (playBGM)
				{
					Sound(ButtonPressSound);
					Sound(Pause);
					cout << "BGM��" << endl;
					playBGM = false;
				}
				else
				{
					cout << "BGM��" << endl;
					mciSendString("resume ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3", 0, 0, 0);
					playBGM = true;
					Sound(ButtonPressSound);
				}
			}
			else if (b3.isClick(ms))
			{
				Sound(ButtonPressSound);
				sw = 3;
				WordSituation();//�л������ʸſ�����
				putimage(0, 0, &img);
			}
			else if (b.isClick(ms))	//����
			{
				Sound(ButtonPressSound);
				sw = 9;
				return;
			}
			else if (reInit.isClick(ms))
			{
				Sound(ButtonPressSound);
				sw = 1;//�������˵�
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

/*	void Start() ��Ϸ�߼�ʵ��
	������:		����ԣ
	������չ��
	��Ӷ�������
*/
void GameFunction::Start()
{
	InitMonster();					//��ʼ������(����ѡ�ػ����Ѷȿ��Ը���ѡ�غ��Ѷ��½���ͬ�Ĺ������)
	cleardevice();					//����
	GameInterface();				//��Ϸ�ײ�������ʾ(�����ǲ������ı�Ľ���)
	Init();							//��ʼ����ֵ
	isRead = true;					//������ֵ��ʼ��
	isGame = true;
	this->current = 0;
	memset(this->okLetter, 0, sizeof(okLetter));
	downLetter = "";				//��ʼ���ַ���
	int i = 0;						//���ڼ���
	bool inSet = false;				//��ʾ�Ƿ��������ý���
	unsigned long long times = 0;	//����ʵ�ֶ������ (��ʱ��)	//times�д洢���Ǻ���
	clock_t begin = 0, end = 0;		//ʵ�ּ�ʱ����
	ExMessage ms;

	//�������ð�ť����
	Button set(WidthPiece, HeightPiece, 3.3 * WidthPiece, 2.5 * HeightPiece, "�� ��", 30);	

	while (1)
	{
		if (roleNum == 2)			//��Ϊ����ְҵ ����������뻺��
			flushmessage();
		RandomRead();				//��isReadΪ���� �������һ������ ���ҵ�ǰ���ʴ��Ҳ�ʹisReadΪ��  ���������
		while(errorNum)				//�����������Ϊ0		��һغ���
		{
			BeginBatchDraw();		//˫�����Ƶ��
			begin = clock();		//�˴���ʼ����ʱ��
			ImageTransparent(NULL,0, 0, &start);
			role->Display(times);		//��ʾ���
			monster->Display(times);	//��ʾ����
			if (sw == 9)//�����ý��淵��
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
				GameInterface();//��Ϸ�ײ�������ʾ(�����ǲ������ı�Ľ���)
				inSet = false;
			}
			//GameInterface();			//��Ϸ�ײ�������ʾ(�����ǲ������ı�Ľ���)
			DisplayWord();			//��ʾ����ĵ��� �������ҵ���ĸ
			Lifebar(role->last_HP,monster->last_HP);//��ʾѪ��
			//����� ���߼����в���
			if (peekmessage(&ms, EX_MOUSE | EX_KEY))
			{
				//���ս���Ĳ��������ã� ��ҵ�� ������е������ ��currentֵ������
				if (ms.message)
				{
					if (set.isClick(ms))
					{
						Sound(ButtonPressSound);
						SettingINGame();//��ʾ��Ϸ�����ý���
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
			//��current��Ϊ0 ������һ�����ȥ����ĸ����ȷ��ĸ��ƥ�� ��Ϊƴд����
			if (current && okLetter[current-1] != words[wordCurrent].word[current - 1])
			{
				if (roleNum == 2)
				{
					//��ʾ�Ѿ����µ���ĸ
					DisplayDown(downLetter, false);
				}

				downLetter.clear();//����ַ���
				words[wordCurrent].errorNum++;//�˵��ʵĴ������+1

				SaveErrorNum();//ÿ���������ͱ���һ��

				cout << words[wordCurrent].word << endl;
				errorAllnum++;				//�ܴ������+1
				SpellingTimes++;


				//������ֵ��ʼ�� ���ҽ���ѭ��
				this->current = 0;
				memset(this->okLetter, 0, sizeof(okLetter));
				//�ɴ����������1
				errorNum--;
				if (errorNum == 1)//������������ ����ʾ��ȷƴд
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
			//��ƴд���						
			if (current == (wordLength-5))
			{
				if (roleNum == 2)
				{
					//��ʾ�Ѿ����µ���ĸ
					DisplayDown(downLetter, true);
				}

				int	x = WindowWidth * 3 / 8 + 4,
					y = HeightPiece * 5 + 4,
					W = WindowWidth * 5 / 8 - 4 - x,
					H = HeightPiece * 9 - 4 - y,
					y_m = HeightPiece / 2 + 4;
				DisplayOk(x, y_m, W, H, true);

				SpellingTimes++;			//ƴд��������+1
				this->role->Attack(times);//��ҹ�����Ч�������Ⱥ��ԣ�
				errorNum = 3;//��������ָ�
				this->monster->Injury(this->role->AD, times);//�������Ѫ�� ���ٵ�ֵΪ��ɫ��AD
				memset(this->okLetter, 0, sizeof(okLetter));
				this->isRead = true;
				this->current = 0;
				Lifebar(role->last_HP, monster->last_HP);//Ѫ��ˢ��
				//������Ѫ������ ��ʤ��				
				cout << "����Ѫ��:" << this->monster->HP << endl;
				cout << "���Ѫ��:" << this->role->HP << endl;
				if (this->monster->HP == 0)
				{
					isWin = true;//��ʾʤ��
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
					return;//�˴���Ϸ����
				}
				break;
			}
			end = clock();		//�˴�ֹͣ���μ�ʱ
			times += double(end - begin) / CLOCKS_PER_SEC * 1000;	//���º�����

			if (times >= 100000) //ÿ100������һ�μ�����
				times = 0;

		//FlushBatchDraw();
		}
		BeginBatchDraw();		//˫�����Ƶ��
		if (errorNum == 0)//���������������
		{
			int	x = WindowWidth * 3 / 8 + 4,
				y = HeightPiece * 5 + 4,
				W = WindowWidth * 5 / 8 - 4 - x,
				H = HeightPiece * 9 - 4 - y,
				y_m = HeightPiece / 2 + 4;
			DisplayOk(x, y_m, W, H, true);
			errorNum = 3;//���ô���
			isRead = true;//�����������
		}
		//FlushBatchDraw();
		//ѭ���ⲿ��
		EndBatchDraw();
		this->monster->Attack(times);//���﹥����Ч�������Ⱥ��ԣ�
		this->role->Injury(this->monster->AD, times);//��ɫ����Ѫ��
		Lifebar(role->last_HP, monster->last_HP);//Ѫ��ˢ��
		//����ɫѪ������ ��ʧ��
		cout << "����Ѫ��:" << this->monster->HP << endl;
		cout << "���Ѫ��:" << this->role->HP << endl;
		if(roleNum == 2)
			downLetter.clear();		//����ַ���������

		if (this->role->HP == 0)
		{
			isWin = false;//��ʾʧ��
			//role->Die();
			delete role;
			delete monster;
			role = NULL;
			monster = NULL;
			this->End();
			return;//�˴���Ϸ����
		}
	}
}

/*	void WordSituation() ���ʸſ�����
	������:		�ܿ���
	1.��ʾ��ͼ���� �Լ��滭����
	2.����GoBack()����ʵ�����ϽǷ��ذ�ť
	3.����Wordָ������� ʹ�б�λ����ʾƴд����ĵ��� ���մ��������������
	4.������ҳ��ť ��һҳ ��һҳ ��ʵ�ַ�ҳ�߼�
	5.������������ʵ�� ƴд���� ������� ��ȷ�ʵ�������ʾ
	6.ʵ�ַ�ҳ��ť�м��ҳ����ʾ ����20ҳ ��ǰ�ڵ�3ҳ ����ʾ 3/20
*/
void GameFunction::WordSituation()
{
	BeginBatchDraw();
	cleardevice();
	IMAGE img;
	loadimage(&img, "./resource/bkImage/other.png", WindowWidth, WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	putimage(0, 0, &img);

	errorwordNum = 0;
	//errorAllnum = 0;
	//���������ĵ��ʵ�����
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
	int totalPage = (errorwordNum + (LshowWord - 1)) / LshowWord;	//��ҳ�� ����ȡ��
	if (totalPage == 0)
		totalPage = 1;
	int curPage = 1;	//��ǰҳ��

	char page[12] = { 0 };//���֧�� 10000/10000

	//λ�� ����
	int width = WidthPiece * 3,
		height = HeightPiece * 2.5,
		back_width = 3.3 * WidthPiece,
		back_height = 2.5 * HeightPiece;

	Button last(WidthPiece * 22.5, HeightPiece * 33, width, height, "��һҳ", RGB(164, 173, 179),BLACK, WHITE, 30);
	Button next(WidthPiece * 32, HeightPiece * 33, width, height, "��һҳ", RGB(164, 173, 179), BLACK, WHITE, 30);
	Button back(WidthPiece, HeightPiece, back_width, back_height, "�� ��", 30);
	ExMessage ms;

	int a = WidthPiece + (back_width - textwidth("��")) / 2;
	settextcolor(BLACK);
	settextstyle(65, 0, "΢���ź�");
	outtextxy(a, HeightPiece * 6, "��");
	outtextxy(a, HeightPiece * 13, "��");
	outtextxy(a, HeightPiece * 21, "��");
	outtextxy(a, HeightPiece * 29, "��");

	settextcolor(WHITE);
	_stprintf_s(page, "%d / %d", curPage, totalPage);
	cout << page << endl;
	settextstyle(45, 0, "΢���ź�");
	WordFrom(WidthPiece * 27.3, HeightPiece * 33.5, WidthPiece * 3, HeightPiece * 2, page, 20);
	//�ȰѴ�����ĵ��ʵ��±�ʹ�������洢����
	int* errindex = NULL;
	int* errnum = NULL;
	

	setfillcolor(RGB(230,230,230));
	fillroundrect(WidthPiece*7, HeightPiece*2, WidthPiece * 18, HeightPiece*32.5, 10, 10);

	settextstyle(50, 0, "΢���ź�");
	outtextxy((WidthPiece * 11 - textwidth("ƴд����:"))/2 + WidthPiece * 7, HeightPiece * 5,"ƴд����:");
	string text = to_string(SpellingTimes);
	outtextxy((WidthPiece * 11 - textwidth(text.c_str()))/2 + WidthPiece * 7, HeightPiece * 8,text.c_str());

	outtextxy((WidthPiece * 11 - textwidth("�������:"))/2 + WidthPiece * 7, HeightPiece * 14,"�������:");
	text = to_string(errorAllnum);
	outtextxy((WidthPiece * 11 - textwidth(text.c_str()))/2 + WidthPiece * 7, HeightPiece * 17,text.c_str());

	outtextxy((WidthPiece * 11 - textwidth("��ȷ��:"))/2 + WidthPiece * 7, HeightPiece * 23,"��ȷ��:");
	if (errorAllnum == 0 || SpellingTimes == 0)//�����������ƴд����Ϊ0 ����ʾ100%��ȷ��
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
		//ð������
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
			cout << "����:" << errnum[i];
			cout << "\t�±�:" << errindex[i] << endl;
		}

		delete[] errnum;
	}
	while (true)
	{
		//����ӡ
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
			if (next.isClick(ms))//��ҳ
			{
				Sound(ButtonPressSound);
				//������ʾ�ĵ���С�ڵ������� ����������
				if (curPage < totalPage)
				{
					curPage++;
					LshowWord += onePage;

					settextcolor(WHITE);
					_stprintf_s(page, "%d / %d", curPage, totalPage);
					cout << page << endl;
					settextstyle(45, 0, "΢���ź�");
					WordFrom(WidthPiece * 27.3, HeightPiece * 33.5, WidthPiece * 3, HeightPiece * 2, page, 20);
				}
			}
			else if (last.isClick(ms))
			{
				Sound(ButtonPressSound);
				//�����ڵ�һҳ����Լ���
				if (curPage != 1)
				{
					curPage--;
					LnowWord -= 2 * onePage;
					LshowWord -= onePage;

					settextcolor(WHITE);
					_stprintf_s(page, "%d / %d", curPage, totalPage);
					cout << page << endl;
					settextstyle(45, 0, "΢���ź�");
					WordFrom(WidthPiece * 27.3, HeightPiece * 33.5, WidthPiece * 3, HeightPiece * 2, page, 20);
				}
			}
			else if (back.isClick(ms))
			{
				Sound(ButtonPressSound);
				if(sw != 3)
					sw = 1;//�л���������
				if(errindex!=NULL)
					delete[] errindex;
				return;
			}
		}
		FlushBatchDraw();
	}
	
	
}

/*	void GameInterface() ��Ϸ��ʾ�����ʵ��
	������:		������
	1.��Ϸ�ײ���ͼ
	2.��Ϸ������� (���ԭ��ͼ)
*/
void GameFunction::GameInterface()
{
	cleardevice(); //����

	IMAGE img; //����һ������
	loadimage(&img, "./resource/bkImage/GameInterface.png", WindowWidth, WindowHeight); //���·����./��ʾ��ǰ�ļ����£�../��ʾ��ǰ�ļ��е���һ��Ŀ¼
	putimage(0, 0, &img);	 //����ͼ��


	setlinecolor(RGB(213, 221, 224));		//����
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


	setfillcolor(WHITE);		//����ʾ��������ĸ�ľ��ο�
	setlinestyle(PS_ENDCAP_FLAT, 6);
	setlinecolor(RGB(127, 255, 170));
	fillroundrect(WindowWidth * 3 / 8, HeightPiece * 1 / 2, WindowWidth * 5 / 8, HeightPiece * 9 / 2, 10, 10);
	setlinecolor(RGB(0, 100, 0));	//�����
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
	roundrect(WindowWidth * 3 / 8 - 2, HeightPiece * 1 / 2 - 2, WindowWidth * 5 / 8 + 2, HeightPiece * 9 / 2 + 2, 8, 8);
	setlinecolor(RGB(60, 179, 113));	//���ڿ�
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
	roundrect(WindowWidth * 3 / 8 + 4, HeightPiece * 1 / 2 + 4, WindowWidth * 5 / 8 - 4, HeightPiece * 9 / 2 - 4, 8, 8);

	setfillcolor(WHITE);		//����ʾ���ĵľ��ο�
	setlinecolor(RGB(230, 230, 250));
	setlinestyle(PS_ENDCAP_FLAT, 6);
	fillroundrect(WindowWidth * 3 / 8, HeightPiece * 5, WindowWidth * 5 / 8, HeightPiece * 9, 10, 10);
	setlinecolor(RGB(75, 0, 130));	//�����
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
	roundrect(WindowWidth * 3 / 8 - 2, HeightPiece * 5 - 2, WindowWidth * 5 / 8 + 2, HeightPiece * 9 + 2, 8, 8);
	setlinecolor(RGB(147, 112, 219));	//���ڿ�
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 2);
	roundrect(WindowWidth * 3 / 8 + 4, HeightPiece * 5 + 4, WindowWidth * 5 / 8 - 4, HeightPiece * 9 - 4, 8, 8);

	setlinecolor(RGB(156, 144, 144));	//����ʾ���Һ����ĸ�ľ��ο�
	setlinestyle(PS_SOLID | PS_JOIN_ROUND | PS_ENDCAP_ROUND, 5);
	fillroundrect(4, HeightPiece * 23 + 4, WindowWidth - 4, WindowHeight - 4, 8, 8);
	setlinecolor(RGB(156, 144, 144));
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
	roundrect(1, HeightPiece * 23 + 1, WindowWidth - 1, WindowHeight - 1, 8, 8);		//���
	setlinecolor(RGB(255, 215, 0));
	roundrect(7, HeightPiece * 23 + 7, WindowWidth - 7, WindowHeight - 7, 8, 8);		//�ڿ�
}

/*	void GameInterfaceOperation()	��Ϸ�����������
	1.����goback()����ʵ�����ϽǷ��ذ�ť
	2.���������(�϶�)����
		���ý�ɫJudge()
*/
//void GameFunction::GameInterfaceOperation(ExMessage& ms)
//{
//
//}

/*	void DisplayWord() ��ʾ����
	������:		����ԣ
	1.����letter���������ݽ�letter�е���ĸ������ʾ����(��isClickable==false����ʾ)
	2.����okLetter�����е����ݽ�����ʾ���Ϸ���ĸ��ʾ��
	3.��ʾ����
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

	DisplayMean(x,y,W,H);			//��ʾ����
	//fillroundrect(10, 480, , y + H, 15, 15);
	//cout << wordLength << endl;
	if (roleNum == 1)			//��ѡ��սʿְҵ  ����ʾ�Ѵ��ҵĵ��� ������ʾ
	{
		setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
		setlinecolor(RGB(255, 215, 0));
		setfillcolor(WHITE);
		fillroundrect(7, HeightPiece * 23 + 7, WindowWidth - 7, WindowHeight - 7, 8, 8);		//�ڿ�
		for (size_t i = 0; i < wordLength; i++)
			DisplayLetter(letter[i]);	//��ӡ��ĸ
	}
	else if (roleNum == 2 && downLetter!="")
	{
		//��ʾ�Ѿ����µ���ĸ
		DisplayDown(downLetter,true);
	}
	//��ʾ��ƴ�õ�Ӣ��
	DisplayOk(x, y_m, W, H,false);

}
//��ʾ���ĺ���
void GameFunction::DisplayMean(int& x,int& y,int& W,int& H)
{
	setfillcolor(WHITE);
	setlinecolor(RGB(147, 112, 219));	//���ڿ�
	//���ݽ���Ĵ�С���Ƶ���ʾ��
	fillroundrect(x, y, x + W, y + H, 8, 8);
	int textSize = 100;	//���������С
	//��stringתΪchar*
	LPCTSTR mean = words[wordCurrent].mean.c_str();
	//���ж���
	while (true)
	{
		settextstyle(textSize, 0, "΢���ź�");
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

//��ʾ������ĸ
void GameFunction::DisplayLetter(Letter& letter)
{
	if (letter.isClickable)
	{
		setlinestyle(PS_SOLID, 3);
		setlinecolor(BLACK);
		if (letter.isHover)	//���������
		{
			setfillcolor(RGB(120, 120, 120));
		}
		else
		{
			setfillcolor(WHITE);
		}
		fillroundrect(letter.x1, letter.y1, letter.x2, letter.y2, 20, 20);
		settextstyle(35, 0, "΢���ź�");
		settextcolor(BLACK);
		int a = letter.x1 + ((letter.x2 - letter.x1) - textwidth(letter.ch)) / 2;
		int b = letter.y1 + ((letter.y2 - letter.y1) - textheight(letter.ch)) / 2;
		outtextxy(a, b, letter.ch);
	}
	setlinestyle(PS_SOLID, 1);
}

//��ʾ��ƴ�õ�Ӣ��
void GameFunction::DisplayOk(int& x, int& y, int& W, int& H,bool isComplete)
{
	setlinecolor(RGB(60, 179, 113));	//�ڿ���ɫ
	setfillcolor(WHITE);
	fillroundrect(x, y, x + W, y + H, 8, 8);
	//words[wordCurrent]
	setlinecolor(WHITE);
	fillroundrect(x, y, x + W, y + H, 15, 15);
	int textSize = 100;	//���������С
	//��stringתΪchar*
	LPCTSTR word;
	if (isComplete)
	{
		word = words[wordCurrent].word.c_str();
	}
	else
	{
		word = okLetter;
	}
	//���ж���
	while (true)
	{
		settextstyle(textSize, 0, "΢���ź�");
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
	//����
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
	setlinecolor(RGB(255, 215, 0));
	setfillcolor(WHITE);
	fillroundrect(7, HeightPiece * 23 + 7, WindowWidth - 7, WindowHeight - 7, 8, 8);		//�ڿ�

	
	//��� WindowWidth-14
	//�߶� HeightPiece*13 -14
	int dis = 10;//ÿ������ľ���
	int n = down.size();//��ʾ��ǰ�ж��ٸ��ַ�Ҫ��ʾ

	int w = (HeightPiece * 13  - 14) / 3;//�ڿ��1/3�߶�
	int h = w;

	int x = ((WindowWidth - 14) - (n * w + (n - 1) * dis)) / 2 + 7;
	int y = (HeightPiece * 23 + 7) + (HeightPiece * 13 - 14 - h)/2;

	//��ӡ����
	for (size_t i = 0; i < n - 1; i++)
	{
		//setfillcolor(RGB(230,230,230));
		//WordFrom(100,100, 50, 50, down.substr(i, 1).c_str());		//��ĸ��
		WordFrom(x+i*(w+dis), y, w, h, down.substr(i, 1).c_str());		//��ĸ��

	}
	if (b)
	{
		WordFrom(x + (n-1) * (w + dis), y, w, h, down.substr((n-1), 1).c_str());		//��ĸ��
	}
	else
	{
		//����������ӡ�ɺ�ɫ
		WordFrom(x + (n - 1) * (w + dis), y, w, h, down.substr((n - 1), 1).c_str(),0);		//��ĸ��
	}
}

/*	void button()���밴ť���Ͻ�λ�á����ߡ���ť���ƣ���ӡ��ť�������־���
	void isClick()�жϰ�ť�Ƿ񱻵�� �Լ�����Ч��
	������:		����ԣ 
*/
Button::Button(int x, int y, int w, int h, LPCTSTR str, int textSize)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->str = str;
	this->textSize = textSize;
	this->fillColor = RGB(238, 248, 254);//Ĭ�ϰ���˿��
	this->lineColor = BLACK;//Ĭ����ߺ�ɫ
	this->textColor = BLACK;//Ĭ�����ֺ�ɫ

	setfillcolor(fillColor);
	setlinecolor(lineColor);
	fillroundrect(x, y, x + w, y + h, 30, 30);
	settextstyle(textSize, 0, "΢���ź�");
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
	settextstyle(textSize, 0, "΢���ź�");
	settextcolor(textColor);
	int a = x + (w - textwidth(str)) / 2;
	int b = y + (h - textheight(str)) / 2;
	outtextxy(a, b, str);
}
bool Button::isClick(ExMessage& msg)
{
	if (!this->isHover)
	{
		//���ư�ť Ĭ�ϵ���ɫ
		setfillcolor(fillColor);
		setlinecolor(lineColor);
		fillroundrect(x, y, x + w, y + h, 30, 30);
		settextstyle(textSize, 0, "΢���ź�");
		settextcolor(textColor);
		int a = x + (w - textwidth(str)) / 2;
		int b = y + (h - textheight(str)) / 2;
		outtextxy(a, b, str);
	}
	else
	{
		//����ʱ����ɫ Ĭ����ɫ
		setfillcolor(RGB(136, 206, 250));
		setlinecolor(lineColor);
		fillroundrect(x, y, x + w, y + h, 30, 30);
		settextstyle(textSize, 0, "΢���ź�");
		settextcolor(textColor);
		int a = x + (w - textwidth(str)) / 2;
		int b = y + (h - textheight(str)) / 2;
		outtextxy(a, b, str);
	}

	switch (msg.message)
	{
	//������
	case WM_LBUTTONDOWN:
		if (msg.x >= x && msg.y >= y && msg.x <= x + w && msg.y <= y + h)
			return true;
		break;
	//����ƶ�
	case WM_MOUSEMOVE:
		if (msg.x >= x && msg.y >= y && msg.x <= x + w && msg.y <= y + h)
		{
			this->isHover = true;//������������ڰ�ť��
		}
		else
			this->isHover = false;//��ʾ���û����ͣ�ڰ�ť��
		break;
	}
	return false;
}
bool Button::isClick(ExMessage& msg, COLORREF hoverColor)
{
	if (!this->isHover)
	{
		//���ư�ť 
		setfillcolor(fillColor);
		setlinecolor(lineColor);
		fillroundrect(x, y, x + w, y + h, 30, 30);
		settextstyle(textSize, 0,"΢���ź�");
		settextcolor(textColor);
		int a = x + (w - textwidth(str)) / 2;
		int b = y + (h - textheight(str)) / 2;
		outtextxy(a, b, str);
	}
	else
	{
		//����ʱ����ɫ 
		setfillcolor(hoverColor);
		setlinecolor(lineColor);
		fillroundrect(x, y, x + w, y + h, 30, 30);
		settextstyle(textSize, 0, "΢���ź�");
		settextcolor(textColor);
		int a = x + (w - textwidth(str)) / 2;
		int b = y + (h - textheight(str)) / 2;
		outtextxy(a, b, str);
	}

	switch (msg.message)
	{
		//������
	case WM_LBUTTONDOWN:
		if (msg.x >= x && msg.y >= y && msg.x <= x + w && msg.y <= y + h)
			return true;
		break;
		//����ƶ�
	case WM_MOUSEMOVE:
		if (msg.x >= x && msg.y >= y && msg.x <= x + w && msg.y <= y + h)
		{
			this->isHover = true;//������������ڰ�ť��
		}
		else
			this->isHover = false;//��ʾ���û����ͣ�ڰ�ť��
		break;
	}
	return false;
}


/*	void Lifebar() Ѫ����ʾ
	������:		�ż���
	1.����roleָ���monsterָ���е�Ѫ������������Ѫ��
	2.Ѫ������ʾ��ǰѪ�������Ѫ�� ��(10/20)
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

	//���Ѫ��
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
		//��ʾ����Ѫ��
		_stprintf_s(str1, "%d / %d", this->role->last_HP, this->role->maxHP);
		LifebarDraw(bar_x, bar_y, bar_width, bar_height, (float)role->last_HP / role->maxHP, str1);
		_stprintf_s(str2, "%d / %d", this->monster->last_HP, this->monster->maxHP);
		LifebarDraw(WindowWidth - bar_x - bar_width, bar_y, bar_width, bar_height, ((float)monster->last_HP / monster->maxHP), str2);

		FlushBatchDraw();
		//�ȴ�50����
		Sleep(50);
		
	}
	EndBatchDraw();
}
//Ѫ�����λ���
void GameFunction::LifebarDraw(int x,int y,int w,int h,float per, LPCTSTR str)
{
	setfillcolor(WHITE);
	setlinecolor(BLACK);
	settextcolor(BLACK);
	settextstyle(20, 0, "΢���ź�");
	setlinestyle(PS_SOLID, 1);
	fillrectangle(x, y, x + w, y + h);//����Ѫ������İ׿�
	setlinecolor(RGB(255, 68, 0));
	setfillcolor(RGB(255, 68, 0));
	fillrectangle(x+3, y+3, x + w*per - 3, (y + h)-3);//����Ѫ��(��)

	int textSize = 30;	//���������С
	//���ж���
	while (true)
	{
		settextstyle(textSize, 0, "΢���ź�");
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


/*	void End()  ��Ϸ��������

	1.����isWin��ֵ ��ʾʤ����ʧ����ͼ
	2.ʵ�ְ�ť ʵ��������ť��ɫ ������� �Լ������Ч
		ƴд�ſ�		����ƴд�ſ����溯��
		���¿�ʼ		sw = 2
		�������˵�	sw = 1
*/
void GameFunction::End()
{
	BeginBatchDraw();
	cleardevice();
	isGame = true;
	IMAGE img;
	loadimage(&img, "./resource/bkImage/End.png", WindowWidth, WindowHeight);//������Ϸ�����ͼƬ	���ڶ���ˢ��
	//����ͼƬ
	putimage(0, 0, &img);

	int width = WidthPiece * 6,
		height = HeightPiece * 4,
		dis = HeightPiece * 6;
	if (isWin)
	{
		char arr[] = "WIN";
		settextcolor(GREEN);
		settextstyle(100, 0, "΢���ź�");
		outtextxy((WindowWidth - textwidth(arr)) / 2, (WindowHeight - textheight(arr)) / 4 - 6, arr);
	}
	else
	{
		char arr[] = "LOSE";
		settextcolor(RED);
		settextstyle(100, 0, "΢���ź�");
		outtextxy((WindowWidth - textwidth(arr)) / 2, (WindowHeight - textheight(arr)) / 4 - 6, arr);
	}
	Button b1((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 1, width, height, "ƴд�ſ�", 40);
	Button b2((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 2, width, height, "���¿�ʼ", 40);
	Button b3((WindowWidth - width) / 2, (WindowHeight - height) / 4 + dis * 3, width, height, "�������˵�", 40);
	ExMessage ms;
	while (true) {
		if (peekmessage(&ms)) {
			if (b1.isClick(ms)) {//���ʸſ�
				Sound(ButtonPressSound);
				WordSituation();
				//����ͼƬ
				putimage(0, 0, &img);
			}
			else if (b2.isClick(ms)) {//���¿�ʼ �ص�ְҵѡ�����
				sw = 2;
				Sound(ButtonPressSound);
				return;
			}
			else if (b3.isClick(ms)) {//�������˵�
				//mciSendString("Stop ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3 to start", 0, 0, 0);//�ӿ�ͷ��ʼ����
				sw = 1;
				Sound(ButtonPressSound);
				return;
			}
		}
		FlushBatchDraw();
	}
}

/*��������������������������������������������������������������������������������Service������������������������������������������������������������������������������������������������*/

/*	GameFunction() ֻ����һ��
	������:		���˰�
	1.ȷ��TxT�ı�����ĵ������� ������Ӧ������Word��������
	2.����TxT�ı�����ĵ��ʺ�������˼ ���ֱ�洢��Word�������� һ��Ԫ�ش洢һ�����ʺ�һ������
	3.��wordNum��ֵΪ��Ӧֵ
*/
GameFunction::GameFunction()
{
	loadRecord();
	this->wordNum = words.size();
	//[];
}

/*	void loadRecord()	��ȡ�ļ��ڵĵ���
	������:		���˰�
*/
void GameFunction::loadRecord()
{
	ifstream ifs("./Data/Words.txt", ios::in);

	if (!ifs.is_open())
	{
		cout << "���ʱ�����" << endl;
		ifs.close();
		exit(0);
		return;
	}
	char ch;
	int num = 0;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "���ʱ�Ϊ��" << endl;
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
			ifs.putback(ch);//������������ ��Ż�ȥ
			ifs >> num;//���ҽ���ֵ�浽num��
		}
		else
		{
			ifs.putback(ch);//����������ĸ  ��Ż�ȥ ������ȡ��һ��
			num = 0;
		}
		//wordC = UtfToGbk(wordC);
		Word tempword(wordE, wordC,num);
		words.push_back(tempword);
	}
	ifs.close();	//�ر��ļ�
}


/*	void Init() ��ʼ����
	������:		����ԣ
	1.errorNum = 3;(���ÿɴ������)
	2.isRead = true;(�����´�������ʶ�ȡ)
	3.��sw��ֵͬ���Ų�ͬ�ı�������
	4.current = 0;(��ʼ����ǰ�жϵ���ĸ�±�)
	5.wordCurrent = 0;(��ǰ����)
*/
void GameFunction::Init()
{
	switch (sw)//��sw��ֵͬ���Ų�ͬ�ı������� ����ִ�в�ͬ�Ĵ���
	{
	case 1://��ʼ�˵�����
		if (!isGame && playBGM)
		{
			mciSendString("pause ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3", 0, 0, 0);
			mciSendString("resume ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3", 0, 0, 0);
		}
		else if (playBGM)//���Ǵӽ������� ������Ϸ�������˳����� �Ǿ����²��ſ�ʼ�˵�BGM
		{
			mciSendString("stop ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3", 0, 0, 0);
			mciSendString("stop ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3", 0, 0, 0);
			Sound(InitInterfaceBGMPlay);//���²��ſ�ʼ����BGM
		}
		isGame = false;
		break;
	case 2://ְҵѡ�����
		if (playBGM)
		{
			mciSendString("pause ./resource/music/BGM/��ʼ�˵�_Ī����_������k448_�ڶ�����.mp3", 0, 0, 0);
			//mciSendString("resume ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3", 0, 0, 0);
			mciSendString("stop ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3", 0, 0, 0);
			Sound(GameStartBGM);//����ְҵѡ�����BGM
			//mciSendString("seek ./resource/music/BGM/ս��_Ī����_������k448_��һ����.mp3 to 0", 0, 0, 0);//�ӿ�ͷ��ʼ����
		}
		break;
	case 3://��Ϸ����
		errorNum = 3;		//(���ÿɴ������)
		isGame = true;		//��ʾ��������Ϸ��
		isRead = true;		//(�����´�������ʶ�ȡ)
		current = 0;		//(��ʼ����ǰ�жϵ���ĸ�±�)
		wordCurrent = 0;	//(���õ�ǰ����)
		wordLength = 0;		//���õ��ʳ���
		break;
	case 8://��������
		//Sound(Stop);
		//Sound(EndBGM);
	default:
		break;
	}
}




//����ɾ��......
/*	int GoBack()   ��Ϊ�ڸ������浥��ʵ�ַ��ذ�ť
	1.�������ϽǷ��ذ�ť
	2.���ô����msg ʵ�ֵ�� ���� �������ť��
		��sw = 2		ʹ sw = 1	ְҵѡ�����ķ���
		��sw = 4		ʹ sw = 1	�����б����ķ���
		��sw = 6		ʹ sw = 1	��Ϸ�����õķ���
		��sw = 5		ʹ sw = 1	��������������ķ���
		��sw = 7	 || isGame = true	ʹ sw = 3	��Ϸ�����в鿴���ʸſ�
	3.����Ч�� �����Ч
*///����ɾ��......




/*	void InitMonster() ��ʼ������(д��������������������ѡ�ع��� �������������������ͬ�Ĺ������)
	(��ǰֻ��һ�ֹ�����)
	1.����Demon�� ��this->monsterָ�����
*/
void GameFunction::InitMonster()
{
	this->monster = new Demon;
}

/*	void Sound(int sign)	ͨ�����յ�ֵʵ�ָ��ֹ��� (���幦�ܼ�Sound.h�ļ�)
	������:		�����
	1.������ֵΪShutBGM(-2)ʱ ʹplayBGM = false; 
	2.������ֵΪShutSoundEffect(-3)ʱ ʹplayEffect = false; 
	3.��playBGMΪtrueʱ ����ִ��1-3��Ӧ�Ĺ���
	4.��playEffectΪtrueʱ ����ִ��4-7��Ӧ�Ĺ���
*/


/*	void RandomRead() �����ȡ���� //���ѡ��һ�����ʶ�ȡ��Ϣ�浽wordLength��letter�� �����������ȷ����ĸ��λ��
	������:	���˰�	
	1.��rand()��ȡ��Χ�ڵ������ ��words�����ѡ��һ�����ʽ��ж�ȡ
	2.����ȡ�ĵ��ʵ���ĸ���ȴ洢��wordLength�� 
	  Ȼ�����ν���ĸ�洢��letter������ 
	  ���ҽ��д洢��ĸ��letter���Ϊ�ɵ�� (isClickable = true)
	3.�������������rand()Ϊ������ĸȷ������ ȷ����������Ϣ�洢��letter�� (Ҫ��֤�䲻�ص�)
*/
void GameFunction::RandomRead()
{
	srand((unsigned)time(nullptr));			//���������
	int W = 50;
	int H = 50;
	int Height = HeightPiece * 13 - 2*H;
	int Width = WindowWidth - 4*W;

	//setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
	//setlinecolor(RGB(255, 215, 0));
	//roundrect(7, HeightPiece * 25 + 7, WindowWidth - 7, WindowHeight - 7, 8, 8);		//�ڿ�


	if (this->isRead)						//������Ҫ��ȡ�µĵ����������
	{
		int temp = -1;
		temp = rand() % words.size();
		while (temp == this->wordCurrent)
		{
			temp = rand() % words.size();
		}
		this->wordCurrent = temp;//���һ���±����(��������һ�����ʲ���ͬ)
		cout << "RandomRead():���������" << endl;
		this->isRead = false;
	}
	string sE(words[this->wordCurrent].word);
	
	//��Ϊսʿְҵ ��洢����ҵ���
	wordLength = sE.length() + 5;			//�洢���ʳ��� +5����������ĸ

	if (roleNum == 2)	//��Ϊ����ְҵ ����Ҫ���ҵ��� �洢����
	{
		for (int i = 0; i < sE.length(); ++i)
		{
			letter[i].ch = sE[i];
		}
		return;
	}

	
	cout << "�����±�:" << this->wordCurrent << endl;

	for (int i = 0; i < wordLength-5; ++i) {
		letter[i].ch = sE[i];
		letter[i].isClickable = true;
		letter[i].isHover = false;

		do {
			cout << "�����..." << endl;
			letter[i].x1 = (rand() % Width) + 2*W;
			letter[i].x2 = letter[i].x1 + W;
			letter[i].y1 = WindowHeight - (rand() % Height) - 1.5*H;
			letter[i].y2 = letter[i].y1 + H;

		} while (isSame(letter[i],letter,i + 1));
		//v.push_back(letter[i]);
	}
	cout << "RandomRead():��ĸ�Ѵ���" << endl;

	//�������ӻ��ҳ̶�
	for (int i = wordLength - 5; i < wordLength; ++i) {
		letter[i].ch = 97+(rand()%26);//�����ĸ
		letter[i].isClickable = true;
		letter[i].isHover = false;

		do {
			cout << "�����..." << endl;
			letter[i].x1 = (rand() % Width) + 2 * W;
			letter[i].x2 = letter[i].x1 + W;
			letter[i].y1 = WindowHeight - (rand() % Height) - 1.5 * H;
			letter[i].y2 = letter[i].y1 + H;

		} while (isSame(letter[i], letter, i + 1));
		//v.push_back(letter[i]);
	}
	cout << "RandomRead():��ĸ�ѻ���" << endl;
}

/*	bool isSame() �ж���ĸ�Ƿ��ص�
	������:		���˰�
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
			continue;//��ÿ����ĸ�����ص�
	}
	return false;
}

void GameFunction::SaveErrorNum()
{
	ofstream ofs("./Data/Words.txt", ios::out);//��������ʽ���ļ�
	//д������
	for (size_t i = 0; i < words.size(); i++)
	{
		ofs << words[i].word << ' ' << words[i].mean << ' ' << words[i].errorNum << endl;
	}
}



//������ֹstring��ȡ�������� ��utf-8תΪgbk��ʽ	
//����:CSDN
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


/*	~GameFunction() ��������
	���п��ٿռ� �����ڴ˴��ͷ�
*/
GameFunction::~GameFunction()
{
	if(role != NULL)
		delete role;
	if(monster != NULL)
		delete monster;
}

//Word�Ĺ��캯��
Word::Word(string word, string mean,int num)
{
	this->word = word;
	this->mean = mean;
	errorNum = num;//ƴ��Ĵ���
}



//bool Letter::isClick(ExMessage& msg)
//{
//	BeginBatchDraw();
//	if (this->isClickable)
//	{
//		setlinestyle(PS_SOLID, 3);
//		setlinecolor(BLACK);
//		if (this->isHover)	//���������
//			setfillcolor(RGB(120, 120, 120));
//		else
//			setfillcolor(WHITE);
//		fillroundrect(this->x1, this->y1, this->x2, this->y2, 20, 20);
//		settextstyle(35, 0, "΢���ź�");
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
//		//������
//	case WM_LBUTTONDOWN:
//		if (msg.x >= x1 && msg.y >= y1 && msg.x <= x2 && msg.y <= y2)
//			return true;
//		break;
//		//����ƶ�
//	case WM_MOUSEMOVE:
//		if (msg.x >= x1 && msg.y >= y1 && msg.x <= x2 && msg.y <= y2)
//			this->isHover = true;//������������ڰ�ť��
//		else
//			this->isHover = false;//��ʾ���û����ͣ�ڰ�ť��
//		break;
//	}
//
//	return false;
//}