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
	m_hWnd = hWnd;//��ʼ�����ھ��
	m_hInstance = hInstance;//��ʼ��ʵ�����

	//������Ĳ�������
	/*********************************************************************/
	int i = 0;
	for (int j = 0; j < 52; j++)
		m_nCardsOrder[j] = j;
	srand((unsigned)time(NULL));
	random_shuffle(m_nCardsOrder, m_nCardsOrder + 52);

	//CreateWindow������ť
	/*******************************************************
	m_hCardButton = CreateWindow(L"BUTTON", NULL,
	WS_CHILD | WS_VISIBLE | BS_BITMAP | BS_PUSHBUTTON,
	50, 30, 80, 120, m_hWnd, (HMENU)1, m_hInstance, NULL);*/
}

void CardCtrl::GameInit()
{
	//52���Ƶİ�˳����س�ʼ��
	/*********************************************************************/
	Cards OrderCards[52];//����ԭʼ��������
	int count = 0;
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 13; i++)
		{
			OrderCards[count].m_nCardNum = i + 1;//�ƵĴ�С
			OrderCards[count].m_nCardColor = j + 1;//�ƵĻ�ɫ
			OrderCards[count].m_hCardBitmap = (HBITMAP)(LoadImage(m_hInstance,
				MAKEINTRESOURCE(IDB_BITMAP1 + j * 13 + i),
				IMAGE_BITMAP, 80, 120, LR_DEFAULTCOLOR));//�Ƶ�ͼƬ
			count++;
		}

	//52����������ش���˳��
	/*********************************************************************/
	for (int i = 0; i < 52; i++)
	{
		m_oNoOrderCards[i] = OrderCards[m_nCardsOrder[i]];
	}

	//������Ϸ��������
	/*********************************************************************/
	m_oDownCards.LoadAllCard(m_hInstance, m_oNoOrderCards);
	m_oFrameCards.LoadFrameCards(m_hInstance, m_oNoOrderCards);
	m_oButtonCards.LoadButtonCard(m_hInstance, m_oNoOrderCards);
}

//˫����滭��������
/*********************************************************************/
void CardCtrl::OnPaintWnd()
{
	HDC hDC = GetDC(m_hWnd);//ȡ�ô�����ĻDC
	HDC hMemDC = CreateCompatibleDC(hDC);//��ʼ���ڴ����DC

	//��Ϸ������ʼ��
	/*********************************************************************/
	//������Ϸ���汳��ͼ
	HBITMAP hBrackGround = (HBITMAP)LoadImage(m_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP58),
		IMAGE_BITMAP, 800, 600, LR_DEFAULTCOLOR);
	SelectObject(hMemDC, hBrackGround);//ѡ�񱳾�����λͼ

	//�����ư�ť�ڱ�����ͼƬ�ĳ�ʼ��
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

	//ʹ��˫���滭ͼ��ʾ������
	/*********************************************************************/
	m_oDownCards.ShowDownCard(hMemDC);//����7���ƶ�28���Ƶ���ʾ
	m_oFrameCards.ShowFrameCards(hMemDC);//
	m_oButtonCards.ShowButtonCard(hMemDC);

	ShowMouseCards(hMemDC);

	BitBlt(hDC, 0, 0, 800, 600, hMemDC, 0, 0, SRCCOPY);

	DeleteObject(hBrackGround);
	DeleteDC(hMemDC);
	DeleteDC(hDC);
}

//������ϰ�ť����
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

//��Ӧ���������µĲ���
/*********************************************************************/
void CardCtrl::OnMouseLDown(POINT pt)
{
	m_MouseLDown = pt;//��ȡ����������ʱ������

	//�������������ϰ�ť����
	OnLeftCardButtonClick();

	//���������»�ȡ���ϰ�ť�����ƶ�
	m_oButtonCards.MouseGetCard(m_MouseLDown, m_pMouseCardsHead,
		m_pMouseCardsEnd, m_nLocationFlag);

	//���������»�ȡ�����ĸ��ƿ����
	m_oFrameCards.MouseGetCard(m_MouseLDown, m_pMouseCardsHead,
		m_pMouseCardsEnd, m_nCountFrame, m_nLocationFlag);

	//���������»�ȡ����7���ƶ�֮һ����
	m_oDownCards.MouseGetCard(m_MouseLDown, m_pMouseCardsHead,
		m_pMouseCardsEnd, m_nLocationFlag, m_nCountDown);

	//�ػ�
	OnPaintWnd();
}

//��Ӧ�������ɿ��Ĳ���
/*********************************************************************/
void CardCtrl::OnMouseLUp(POINT pt)
{
	m_MouseUp = pt;//��ȡ�������ɿ�ʱ������

	//�������������������
	if (m_pMouseCardsHead != NULL)
	{
		//�жϸ����Ƿ��ܷŵ�����4���ƿ���
		m_oFrameCards.MouseCardPutDown(m_MouseUp, m_pMouseCardsHead,
			m_pMouseCardsEnd);

		//�жϸ����Ƿ��ܷŵ�����7���ƶ���
		m_oDownCards.MouseCardPutDown(m_MouseUp, m_pMouseCardsHead,
			m_pMouseCardsEnd);

		//�����Ƶ���Դ���ƷŻ�ԭ��
		switch (m_nLocationFlag)
		{
			//�������������7���ƶ�֮һ
			/************************************************************/
		case 1:
			//���ܷ�����ص�ԭ��
			m_oDownCards.MouseCardBack(m_nCountDown, m_pMouseCardsHead
				, m_pMouseCardsEnd);
			//����±�����ʾ�����Ƿ�����з��ƶ���
			m_oDownCards.SetEndCardVisual(m_nCountDown, m_hWnd);
			break;


			//������������4���ƶ�֮һ
			/************************************************************/
		case 2:
			//���ܷ�����ص�ԭ��
			m_oFrameCards.MouseCardBack(m_nCountFrame, m_pMouseCardsHead);
			break;


			//�������������ƶѰ�ť
			/************************************************************/
		case 3:
			//���ܷ�����ص�ԭ��
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
			MessageBox(m_hWnd, L"��ϲ��", L"��Ӯ�ˣ�", MB_OK);
		}
	}

	OnPaintWnd();
}

//��ȡ����ƶ�������
/*********************************************************************/
void CardCtrl::OnMouseMove(POINT pt)
{
	m_MouseMove = pt;

	if (m_pMouseCardsHead != NULL)
	{
		OnPaintWnd();
	}
}

//��ʾ������϶�����
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