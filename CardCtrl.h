#include "DownCards.h"
#include "ButtonCards.h"
#include "FrameCards.h"
class CardCtrl
{
public:
	CardCtrl();
	~CardCtrl();
	void InitValue(const HWND& hWnd, const HINSTANCE& hInstance);//类数据初始化
	void GameInit();//游戏初始化
	void OnPaintWnd();//画面的生成
	void OnMouseLDown(POINT);//响应鼠标左键点下的操作
	void OnMouseLUp(POINT);//响应鼠标左键松开的操作
	void OnMouseMove(POINT);
	void DeleteCardsOb();
private:
	void OnLeftCardButtonClick();//点击左上按钮出牌
	void ShowMouseCards(HDC);

private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	int m_nCardsOrder[52];//创建无序牌用到的数组
	Cards m_oNoOrderCards[52];//创建无序牌组
	//HWND m_hCardButton;//左上按钮控件
	DownCards m_oDownCards;//初始界面牌的类
	FrameCards m_oFrameCards;//右上4个牌堆的类
	ButtonCards m_oButtonCards;//左上牌堆的类
	CardsList* m_pMouseCardsHead;
	CardsList* m_pMouseCardsEnd;
	POINT m_MouseLDown;//鼠标左键点下时的坐标
	POINT m_MouseUp;//鼠标左键松开时的坐标
	POINT m_MouseMove;
	int m_nLocationFlag;/*牌的来源位置标志，1为下面的7个牌堆之一，
						为右上4个牌框之一，3为右上出牌的牌堆，0为默认值*/
	int m_nCountDown;
	int m_nCountFrame;
};