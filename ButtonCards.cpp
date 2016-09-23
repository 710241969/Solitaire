#include "ButtonCards.h"

ButtonCards::ButtonCards()
{
}

void ButtonCards::LoadButtonCard(HINSTANCE hInstance, Cards* cards)
{
	m_pCardsHead = m_pCardsEnd = NULL;
	int n = 28;
	for (int i = 0; i < 24; i++)
	{
		CardsList* temp = new CardsList;
		temp->m_Card = cards[n++];
		temp->m_bFlag = TRUE;
		temp->m_nx = 150;
		temp->m_ny = 30;
		temp->m_pNext = temp->m_pPre = NULL;
		if (m_pCardsHead == NULL)
		{
			m_pCardsHead = temp;
		}
		else
		{
			m_pCardsEnd->m_pNext = temp;
			temp->m_pPre = m_pCardsEnd;
		}
		m_pCardsEnd = temp;
	}

	m_pToHead = new CardsList;
	m_pToHead->m_pPre = NULL;
	m_pToHead->m_pNext = m_pCardsHead;
	m_pCardsEnd->m_pNext = m_pToHead;
	m_pCardShow = NULL;

	//ÉèÖÃ¿¨ÅÆ±³ÃæÍ¼
	m_hCardBackBitmap = (HBITMAP)LoadImage(hInstance,
		MAKEINTRESOURCE(IDB_BITMAP53),
		IMAGE_BITMAP, 80, 120, LR_DEFAULTCOLOR);
	m_hCardBlankBitmap = (HBITMAP)LoadImage(hInstance,
		MAKEINTRESOURCE(IDB_BITMAP60),
		IMAGE_BITMAP, 80, 120, LR_DEFAULTCOLOR);
}

void ButtonCards::ShowButtonCard(HDC hDC)
{
	if (m_pCardShow != NULL && m_pCardShow != m_pToHead)
	{
		CardsList* temp = new CardsList;
		temp = m_pCardsHead;
		while (temp != m_pCardShow->m_pNext)
		{
			HDC hMemDC = CreateCompatibleDC(hDC);
			SelectObject(hMemDC, temp->m_Card.m_hCardBitmap);
			BitBlt(hDC, temp->m_nx, temp->m_ny, 80, 120,
				hMemDC, 0, 0, SRCCOPY);
			DeleteDC(hMemDC);
			temp = temp->m_pNext;
		}
	}

	HDC hMemDC = CreateCompatibleDC(hDC);
	if (m_pCardShow == m_pCardsEnd)
	{
		SelectObject(hMemDC, m_hCardBlankBitmap);
		BitBlt(hDC, 50, 30, 80, 120, hMemDC, 0, 0, SRCCOPY);
	}
	else
	{
		SelectObject(hMemDC, m_hCardBackBitmap);
		BitBlt(hDC, 50, 30, 80, 120, hMemDC, 0, 0, SRCCOPY);
	}
	DeleteDC(hMemDC);

	if (m_pCardsHead == NULL)
	{
		HDC hMemDC = CreateCompatibleDC(hDC);
		SelectObject(hMemDC, m_hCardBlankBitmap);
		BitBlt(hDC, 50, 30, 80, 120, hMemDC, 0, 0, SRCCOPY);
		DeleteDC(hMemDC);
	}
}

void ButtonCards::MouseGetCard(POINT pt, CardsList*& MouseCardsHead,
	CardsList*& MouseCardsEnd, int& LocationFlag)
{
	if (pt.x > 150 && pt.x < 230 && pt.y > 30 && pt.y < 150 &&
		m_pCardShow != NULL)
	{
		CardsList* temp = m_pCardShow;
		LocationFlag = 3;
		if (m_pCardShow == m_pCardsHead)
		{
			m_pCardShow = NULL;
			m_pCardsHead = m_pCardsHead->m_pNext;
			m_pCardsHead->m_pPre = NULL;
			m_pToHead->m_pNext = m_pCardsHead;
		}
		else
		{

			if (m_pCardShow == m_pCardsEnd)
			{
				m_pCardsEnd = m_pCardShow->m_pPre;
				m_pCardsEnd->m_pNext = m_pToHead;
				m_pCardShow = m_pCardsEnd;
			}
			else
			{
				m_pCardShow->m_pNext->m_pPre = m_pCardShow->m_pPre;
				m_pCardShow->m_pPre->m_pNext = m_pCardShow->m_pNext;
				m_pCardShow = m_pCardShow->m_pPre;
			}
		}
		temp->m_pNext = NULL;
		temp->m_pPre = NULL;

		MouseCardsEnd = MouseCardsHead = temp;
	}
}

void ButtonCards::MouseCardBack(CardsList* MouseCardsHead)
{
	if (MouseCardsHead != NULL)
	{
		if (m_pCardShow == NULL)
		{
			MouseCardsHead->m_pNext = m_pCardsHead;
			m_pCardsHead->m_pPre = MouseCardsHead;
			m_pCardsHead = MouseCardsHead;
			m_pToHead->m_pNext = m_pCardsHead;
			m_pCardShow = m_pCardsHead;
		}
		else
		{
			MouseCardsHead->m_pNext = m_pCardShow->m_pNext;
			MouseCardsHead->m_pPre = m_pCardShow;
			if (m_pCardShow == m_pCardsEnd)
			{
				m_pCardsEnd = MouseCardsHead;
			}

			m_pCardShow->m_pNext->m_pPre = MouseCardsHead;
			m_pCardShow->m_pNext = MouseCardsHead;
			m_pCardShow = MouseCardsHead;
		}
	}
}

void ButtonCards::DeleteCardsOb()
{
	DeleteObject(m_hCardBackBitmap);
	DeleteObject(m_hCardBlankBitmap);
}

ButtonCards::~ButtonCards()
{
	delete m_pToHead;
}
