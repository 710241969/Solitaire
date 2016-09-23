#include "FrameCards.h"

FrameCards::FrameCards()
{
}

void FrameCards::LoadFrameCards(HINSTANCE hInstance, Cards* cards)
{
	m_hFrameBitmap = (HBITMAP)(LoadImage(hInstance,
		MAKEINTRESOURCE(IDB_BITMAP59),
		IMAGE_BITMAP, 80, 120, LR_DEFAULTCOLOR));

	for (int i = 0; i < 4; i++)
	{
		m_pCardsHead[i] = m_pCardsEnd[i] = NULL;
	}
}

void FrameCards::ShowFrameCards(HDC hDC)
{
	CardsList* temp;
	for (int i = 0; i < 4; i++)
	{
		temp = m_pCardsHead[i];
		if (temp == NULL)
		{
			HDC hMemDC = CreateCompatibleDC(hDC);
			SelectObject(hMemDC, m_hFrameBitmap);
			BitBlt(hDC, 350 + 110 * i, 30, 80, 120,
				hMemDC, 0, 0, SRCCOPY);
			DeleteDC(hMemDC);
		}
		else
		{
			while (temp != NULL)
			{
				HDC hMemDC = CreateCompatibleDC(hDC);
				SelectObject(hMemDC, temp->m_Card.m_hCardBitmap);
				BitBlt(hDC, 350 + 110 * i, 30, 80, 120,
					hMemDC, 0, 0, SRCCOPY);
				DeleteDC(hMemDC);
				temp = temp->m_pNext;
			}
		}
	}
}

void FrameCards::MouseGetCard(POINT pt, CardsList*& MouseCardsHead,
	CardsList*& MouseCardsEnd, int& CountFrame, int& LocationFlag)
{
	for (int i = 0; i < 4; i++)
	{
		if (pt.x>350 + 110 * i && pt.x < 430 + 110 * i &&
			pt.y > 30 && pt.y < 150)
		{
			LocationFlag = 2;
			CountFrame = i;
			CardsList* temp = m_pCardsEnd[i];
			if (m_pCardsEnd[i] != NULL)
			{
				MouseCardsEnd = MouseCardsHead = temp;
				if (m_pCardsHead[i] == m_pCardsEnd[i])
				{
					m_pCardsHead[i] = m_pCardsEnd[i] = NULL;
				}
				else
				{
					m_pCardsEnd[i] = m_pCardsEnd[i]->m_pPre;
					m_pCardsEnd[i]->m_pNext = NULL;
				}
				MouseCardsHead->m_pPre = MouseCardsHead->m_pNext = NULL;
				MouseCardsEnd->m_pPre = MouseCardsEnd->m_pNext = NULL;
			}
		}
	}
}

void FrameCards::MouseCardBack(int CountFrame, CardsList* MouseCardsHead)
{
	if (MouseCardsHead != NULL)
	{
		if (m_pCardsEnd[CountFrame] == NULL)
		{
			m_pCardsHead[CountFrame] =
				m_pCardsEnd[CountFrame] = MouseCardsHead;
		}
		else
		{
			MouseCardsHead->m_pPre = m_pCardsEnd[CountFrame];
			m_pCardsEnd[CountFrame]->m_pNext = MouseCardsHead;
			m_pCardsEnd[CountFrame] = MouseCardsHead;
		}
	}
}

void FrameCards::MouseCardPutDown(POINT pt, CardsList*& MouseCardsHead,
	CardsList*& MouseCardsEnd)
{
	if (MouseCardsHead != NULL)
	{
		if (MouseCardsHead == MouseCardsEnd)//鼠标中必须只有一张牌
		{
			if (pt.y > 30 && pt.y < 150)
			{
				for (int i = 0; i < 4; i++)
				{
					if (pt.x>350 + 110 * i && pt.x < 430 + 110 * i)
					{
						if (m_pCardsHead[i] == NULL)
						{
							if (MouseCardsHead->m_Card.m_nCardNum == 1)
							{
								MouseCardsHead->m_nx = 350 + 110 * i;
								MouseCardsHead->m_ny = 30;
								m_pCardsHead[i] = m_pCardsEnd[i]
									= MouseCardsHead;
								MouseCardsHead = MouseCardsEnd = NULL;
								break;
							}
						}
						else if (MouseCardsHead->m_Card.m_nCardNum ==
							m_pCardsEnd[i]->m_Card.m_nCardNum + 1 &&
							MouseCardsHead->m_Card.m_nCardColor ==
							m_pCardsEnd[i]->m_Card.m_nCardColor)
						{
							MouseCardsHead->m_nx = 350 + 110 * i;
							MouseCardsHead->m_ny = 30;
							MouseCardsHead->m_pPre = m_pCardsEnd[i];
							m_pCardsEnd[i]->m_pNext = MouseCardsHead;
							m_pCardsEnd[i] = MouseCardsHead;
							MouseCardsHead = MouseCardsEnd = NULL;
							break;
						}
					}
				}
			}
		}
	}
}

void FrameCards::DeleteCardsOb()
{
	DeleteObject(m_hFrameBitmap);
}

FrameCards::~FrameCards()
{
}
