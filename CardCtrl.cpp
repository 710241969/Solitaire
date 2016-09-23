#include <algorithm>
#include <time.h>
#include "CardCtrl.h"
using namespace std;

CardCtrl::CardCtrl()
{
	m_pMouseCardsHead = NULL;
	m_pMouseCardsEnd = NULL;
	m_nLocationFlag = 0;
}

void CardCtrl::InitValue(const HWND& hWnd, const HINSTANCE& hInstance)
{
	m_hWnd = hWnd;//初始化窗口句柄
	m_hInstance = hInstance;//初始化实例句柄

	//随机数的产生生成
	/*********************************************************************/
	int i = 0;
	for (int j = 0; j < 52; j++)
		m_nCardsOrder[j] = j;
	srand((unsigned)time(NULL));
	random_shuffle(m_nCardsOrder, m_nCardsOrder + 52);

	//CreateWindow创建按钮
	/*******************************************************
	m_hCardButton = CreateWindow(L"BUTTON", NULL,
	WS_CHILD | WS_VISIBLE | BS_BITMAP | BS_PUSHBUTTON,
	50, 30, 80, 120, m_hWnd, (HMENU)1, m_hInstance, NULL);*/
}

void CardCtrl::GameInit()
{
	//52张牌的按顺序加载初始化
	/*********************************************************************/
	Cards OrderCards[52];//创建原始有序牌组
	int count = 0;
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 13; i++)
		{
			OrderCards[count].m_nCardNum = i + 1;//牌的大小
			OrderCards[count].m_nCardColor = j + 1;//牌的花色
			OrderCards[count].m_hCardBitmap = (HBITMAP)(LoadImage(m_hInstance,
				MAKEINTRESOURCE(IDB_BITMAP1 + j * 13 + i),
				IMAGE_BITMAP, 80, 120, LR_DEFAULTCOLOR));//牌的图片
			count++;
		}

	//52张牌牌随机地打乱顺序
	/*********************************************************************/
	for (int i = 0; i < 52; i++)
	{
		m_oNoOrderCards[i] = OrderCards[m_nCardsOrder[i]];
	}

	//加载游戏的所有牌
	/*********************************************************************/
	m_oDownCards.LoadAllCard(m_hInstance, m_oNoOrderCards);
	m_oFrameCards.LoadFrameCards(m_hInstance, m_oNoOrderCards);
	m_oButtonCards.LoadButtonCard(m_hInstance, m_oNoOrderCards);
}

//双缓冲绘画整个界面
/*********************************************************************/
void CardCtrl::OnPaintWnd()
{
	HDC hDC = GetDC(m_hWnd);//取得窗口屏幕DC
	HDC hMemDC = CreateCompatibleDC(hDC);//初始化内存兼容DC

	//游戏背景初始化
	/*********************************************************************/
	//设置游戏界面背景图
	HBITMAP hBrackGround = (HBITMAP)LoadImage(m_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP58),
		IMAGE_BITMAP, 800, 600, LR_DEFAULTCOLOR);
	SelectObject(hMemDC, hBrackGround);//选择背景设置位图

	//左上牌按钮在背景中图片的初始化
	/********************************************************************
	if (m_oButtonCards.m_pCardShow == m_oButtonCards.m_pCardsEnd)
	{
	SelectObject(hMemDC, NULL);
	BitBlt(hDC, 50, 30, 80, 120, hMemDC, 0, 0, SRCCOPY);
	}
	else
	{
	//SendMessage(m_hCardButton, BM_SETIMAGE,
	//IMAGE_BITMAP, (LPARAM)hCardBackBitmap);
	SelectObject(hMemDC, hCardBackBitmap);
	BitBlt(hDC, 50, 30, 80, 120, hMemDC, 0, 0, SRCCOPY);
	}*/

	//使用双缓存画图显示所有牌
	/*********************************************************************/
	m_oDownCards.ShowDownCard(hMemDC);//下面7个牌堆28张牌的显示
	m_oFrameCards.ShowFrameCards(hMemDC);//
	m_oButtonCards.ShowButtonCard(hMemDC);

	ShowMouseCards(hMemDC);

	BitBlt(hDC, 0, 0, 800, 600, hMemDC, 0, 0, SRCCOPY);

	DeleteObject(hBrackGround);
	DeleteDC(hMemDC);
	DeleteDC(hDC);
}

//点击左上按钮出牌
/*********************************************************************/
void CardCtrl::OnLeftCardButtonClick()
{
	if (m_MouseLDown.x > 50 &&
		m_MouseLDown.x < 130 &&
		m_MouseLDown.y>30 &&
		m_MouseLDown.y < 150)
	{
		if (m_oButtonCards.m_pCardShow == NULL)
		{
			m_oButtonCards.m_pCardShow = m_oButtonCards.m_pCardsHead;
		}
		else
		{
			m_oButtonCards.m_pCardShow = m_oButtonCards.m_pCardShow->m_pNext;
			if (m_oButtonCards.m_pCardShow == m_oButtonCards.m_pToHead)
			{
				m_oButtonCards.m_pCardShow = NULL;
			}
		}
		OnPaintWnd();
	}
}

//响应鼠标左键点下的操作
/*********************************************************************/
void CardCtrl::OnMouseLDown(POINT pt)
{
	m_MouseLDown = pt;//获取鼠标左键点下时的坐标

	//鼠标左键点下左上按钮出牌
	OnLeftCardButtonClick();

	//鼠标左键点下获取左上按钮出的牌堆
	m_oButtonCards.MouseGetCard(m_MouseLDown, m_pMouseCardsHead,
		m_pMouseCardsEnd, m_nLocationFlag);

	//鼠标左键点下获取右上四个牌框的牌
	m_oFrameCards.MouseGetCard(m_MouseLDown, m_pMouseCardsHead,
		m_pMouseCardsEnd, m_nCountFrame, m_nLocationFlag);

	//鼠标左键点下获取下面7个牌堆之一的牌
	m_oDownCards.MouseGetCard(m_MouseLDown, m_pMouseCardsHead,
		m_pMouseCardsEnd, m_nLocationFlag, m_nCountDown);

	//重画
	OnPaintWnd();
}

//响应鼠标左键松开的操作
/*********************************************************************/
void CardCtrl::OnMouseLUp(POINT pt)
{
	m_MouseUp = pt;//获取鼠标左键松开时的坐标

	//假如鼠标牌链表中有牌
	if (m_pMouseCardsHead != NULL)
	{
		//判断该牌是否能放到右上4个牌框中
		m_oFrameCards.MouseCardPutDown(m_MouseUp, m_pMouseCardsHead,
			m_pMouseCardsEnd);

		//判断该牌是否能放到下面7个牌堆中
		m_oDownCards.MouseCardPutDown(m_MouseUp, m_pMouseCardsHead,
			m_pMouseCardsEnd);

		//根据牌的来源将牌放回原处
		switch (m_nLocationFlag)
		{
			//此牌来自下面的7个牌堆之一
			/************************************************************/
		case 1:
			//不能放下则回到原处
			m_oDownCards.MouseCardBack(m_nCountDown, m_pMouseCardsHead
				, m_pMouseCardsEnd);
			//最底下背面显示的牌是否可以有翻牌动作
			m_oDownCards.SetEndCardVisual(m_nCountDown, m_hWnd);
			break;


			//此牌来自右上4个牌堆之一
			/************************************************************/
		case 2:
			//不能放下则回到原处
			m_oFrameCards.MouseCardBack(m_nCountFrame, m_pMouseCardsHead);
			break;


			//此牌来自左上牌堆按钮
			/************************************************************/
		case 3:
			//不能放下则回到原处
			m_oButtonCards.MouseCardBack(m_pMouseCardsHead);
			break;


		default:
			break;
		}
	}

	m_pMouseCardsHead = m_pMouseCardsEnd = NULL;

	if (m_oButtonCards.m_pCardsHead == NULL)
	{
		int WinFlag = 0;
		for (int i = 0; i < 7; i++)
		{
			if (m_oDownCards.m_pCardsHead[i] == NULL)
			{
				WinFlag++;
			}
		}
		if (WinFlag == 7)
		{
			MessageBox(m_hWnd, L"恭喜！", L"你赢了！", MB_OK);
		}
	}

	OnPaintWnd();
}

//获取鼠标移动的坐标
/*********************************************************************/
void CardCtrl::OnMouseMove(POINT pt)
{
	m_MouseMove = pt;

	if (m_pMouseCardsHead != NULL)
	{
		OnPaintWnd();
	}
}

//显示鼠标上拖动的牌
/*********************************************************************/
void CardCtrl::ShowMouseCards(HDC hDC)
{
	int nPosX = m_MouseMove.x - m_MouseLDown.x;
	int nPosY = m_MouseMove.y - m_MouseLDown.y;

	CardsList* temp = m_pMouseCardsHead;

	while (temp != NULL)
	{
		HDC hMemDc = CreateCompatibleDC(hDC);
		SelectObject(hMemDc, temp->m_Card.m_hCardBitmap);
		BitBlt(hDC, temp->m_nx + nPosX, temp->m_ny + nPosY,
			80, 120, hMemDc, 0, 0, SRCCOPY);
		DeleteDC(hMemDc);
		temp = temp->m_pNext;
	}
}

void CardCtrl::DeleteCardsOb()
{
	for (int i = 0; i < 52; i++)
	{
		DeleteObject(m_oNoOrderCards[i].m_hCardBitmap);
	}
	m_oDownCards.DeleteCardsOb();
	m_oFrameCards.DeleteCardsOb();
	m_oButtonCards.DeleteCardsOb();
}

CardCtrl::~CardCtrl()
{
	delete m_pMouseCardsHead;
	delete m_pMouseCardsEnd;
}