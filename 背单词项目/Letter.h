#pragma once


class Letter //打乱后单个字母的信息 包括图形化的位置信息
{
public:
	bool isClickable = false;//默认不能被点击 不能被点击的时候不显示
	bool isHover = false;	//鼠标是否悬浮在当前字母
	char ch = 0;//表示的字母
	int x1 = 0;//代表单个字母左上角的x位置信息
	int y1 = 0;//代表单个字母左上角的y位置信息
	int x2 = 0;//代表单个字母右下角的x位置信息
	int y2 = 0;//代表单个字母右下角的y位置信息

	//bool isClick(ExMessage& msg);

};