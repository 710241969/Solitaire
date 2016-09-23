#include "DownCards.h"

DownCards::DownCards()
{
}

void DownCards::LoadAllCard(HINSTANCE hInstance, Cards* cards)
{
	for (int i = 0; i < 7; i++)
	{
		m_pCardsHead[i] = m_pCardsEnd[i] = NULL;
	}
	//位图设置
	/*********************************************************************/
	//牌背面图位图设置
	m_hCardBackBitmap = (HBITMAP)LoadImage(hInstance,
		MAKEINTRESOURCE(IDB_BITMAP53),
		IMAGE_BITMAP, 80, 120, LR_DEFAULTCOLOR);
	//空牌堆位图
	m_hCardBlankBitmap = (HBITMAP)LoadImage(hInstance,
		MAKEINTRESOURCE(IDB_BITMAP60),
		IMAGE_BITMAP, 80, 120, LR_DEFAULTCOLOR);

	/*********************************************************************/
	int n = 0;
	for (int i = 0; i < 7; i++)
	{
		if (i < 7)
		{
			for (int j = 0; j <= i; j++)
			{
				CardsList* temp = new CardsList;
				temp->m_Card = cards[n++];
				temp->m_bFlag = FALSE;
				temp->m_nx = 20 + 110 * i;
				temp->m_ny = 200 + 20 * j;
				temp->m_pNext = temp->m_pPre = NULL;
				if (m_pCardsHead[i] == NULL)
				{
					m_pCardsHead[i] = temp;
				}
				else
				{
					m_pCardsEnd[i]->m_pNext = temp;
					temp->m_pPre = m_pCardsEnd[i];
				}
				m_pCardsEnd[i] = temp;
			}
			m_pCardsEnd[i]->m_bFlag = TRUE;
		}
	}
}

void DownCards::ShowDownCard(HDC hDC)
{
	CardsList* temp;

	for (int i = 0; i < 7; i++)
	{
		temp = m_pCardsHead[i];
		if (temp == NULL)
		{
			HDC hMemDC = CreateCompatibleDC(hDC);
			SelectObject(hMemDC, m_hCardBlankBitmap);
			BitBlt(hDC, 20 + 110 * i, 200, 80, 120,
				hMemDC, 0, 0, SRCCOPY);
			DeleteDC(hMemDC);
		}
		else
		{
			while (temp != NULL)
			{
				HDC hMemDC = CreateCompatibleDC(hDC);
				if (temp->m_bFlag == TRUE)
				{
					SelectObject(hMemDC, temp->m_Card.m_hCardBitmap);
				}
				else
				{
					SelectObject(hMemDC, m_hCardBackBitmap);
				}
				BitBlt(hDC, temp->m_nx, temp->m_ny, 80, 120,
					hMemDC, 0, 0, SRCCOPY);
				temp = temp->m_pNext;
				DeleteDC(hMemDC);
			}
		}
	}
}

void DownCards::GetVisualCardList()
{
	for (int i = 0; i < 7; i++)
	{
		m_hVisualCardListHead[i] = m_hVisualCardListEnd[i] = NULL;
	}

	CardsList* temp;
	for (int i = 0; i < 7; i++)
	{
		//
		temp = m_pCardsHead[i];
		if (temp != NULL)
		{
			while (temp->m_bFlag != TRUE)
			{
				temp = temp->m_pNext;
			}
			m_hVisualCardListHead[i] = temp;
			while (temp->m_pNext != NULL)
			{
				temp = temp->m_pNext;
			}
			m_hVisualCardListEnd[i] = temp;
		}
		else
		{
			m_hVisualCardListHead[i] = m_hVisualCardListEnd[i] = NULL;
		}

	}
}

void DownCards::MouseGetCard(POINT pt, CardsList*& MouseCardsHead,
	CardsList*& MouseCardsEnd, int& LocationFlag, int& CountDown)
{

	GetVisualCardList();
	CardsList* temp;
	for (int i = 0; i < 7; i++)
	{
		temp = m_hVisualCardListHead[i];
		while (temp != NULL)
		{
			//如果取牌堆中间的牌
			if (temp != m_hVisualCardListEnd[i])
			{
				if (pt.x > temp->m_nx && pt.x < temp->m_nx + 80 &&
					pt.y > temp->m_ny && pt.y < temp->m_ny + 20)
				{
					LocationFlag = 1;
					CountDown = i;
					MouseCardsHead = temp;
					MouseCardsEnd = m_hVisualCardListEnd[i];
					if (temp == m_pCardsHead[i])
					{
						m_pCardsHead[i] = m_pCardsEnd[i] = NULL;
					}
					else
					{
						m_pCardsEnd[i] = temp->m_pPre;
						m_pCardsEnd[i]->m_pNext = NULL;
					}
					MouseCardsHead->m_pPre = NULL;
					break;
				}
			}
			//如果点击的该牌为最底下的牌
			else
			{
				if (pt.x > temp->m_nx && pt.x < temp->m_nx + 80 &&
					pt.y > temp->m_ny && pt.y < temp->m_ny + 120)
				{
					LocationFlag = 1;
					CountDown = i;
					MouseCardsHead = MouseCardsEnd = temp;
					if (temp == m_pCardsHead[i])
					{
						m_pCardsHead[i] = m_pCardsEnd[i] = NULL;
					}
					else
					{
						m_pCardsEnd[i] = m_pCardsEnd[i]->m_pPre;
						m_pCardsEnd[i]->m_pNext = NULL;
						MouseCardsHead->m_pNext = MouseCardsHead->m_pPre = NULL;
					}
					MouseCardsHead->m_pPre = NULL;
					break;
				}
			}
			temp = temp->m_pNext;
		}
	}
}

void DownCards::MouseCardBack(int CountDown, CardsList* MouseCardsHead
	, CardsList* MouseCardsEnd)
{
	if (MouseCardsHead != NULL)
	{
		if (m_pCardsHead[CountDown] == NULL)
		{
			m_pCardsHead[CountDown] = MouseCardsHead;
			m_pCardsEnd[CountDown] = MouseCardsEnd;
		}
		else
		{
			m_pCardsEnd[CountDown]->m_pNext = MouseCardsHead;
			MouseCardsHead->m_pPre = m_pCardsEnd[CountDown];
			m_pCardsEnd[CountDown] = MouseCardsEnd;
		}
	}
}

void DownCards::MouseCardPutDown(POINT pt, CardsList*& MouseCardsHead,
	CardsList*& MouseCardsEnd)
{
	if (MouseCardsHead != NULL)
	{
		for (int i = 0; i < 7; i++)
		{
			//如果牌堆最下面一张不为空
			if (m_pCardsEnd[i] != NULL)
			{
				if (pt.x > m_pCardsEnd[i]->m_nx &&
					pt.x < m_pCardsEnd[i]->m_nx + 80 &&
					pt.y > m_pCardsEnd[i]->m_ny &&
					pt.y < m_pCardsEnd[i]->m_ny + 120)
				{
					if (m_pCardsEnd[i]->m_bFlag == TRUE)
					{
						if ((MouseCardsHead->m_Card.m_nCardColor + 1) % 2
							== (m_pCardsEnd[i]->m_Card.m_nCardColor) % 2
							&& MouseCardsHead->m_Card.m_nCardNum ==
							m_pCardsEnd[i]->m_Card.m_nCardNum - 1)
						{
							CardsList* temp = MouseCardsHead;
							int count = 1;
							while (temp != NULL)
							{
								temp->m_nx = 20 + 110 * i;
								temp->m_ny =
									m_pCardsEnd[i]->m_ny + 20 * count;
								count++;
								temp = temp->m_pNext;
							}
							MouseCardsHead->m_pPre = m_pCardsEnd[i];
							m_pCardsEnd[i]->m_pNext = MouseCardsHead;
							m_pCardsEnd[i] = MouseCardsEnd;
							MouseCardsHead = MouseCardsEnd = NULL;
							break;
						}
					}
				}
			}
			//如果牌堆为空，只能放入头牌数字为K的牌链表
			else
			{
				if (pt.x > 20 + 110 * i && pt.x < 100 + 110 * i &&
					pt.y > 200 && pt.y < 320)
				{
					if (MouseCardsHead->m_Card.m_nCardNum == 13)
					{
						CardsList* temp = MouseCardsHead;
						int count = 0;
						while (temp != NULL)
						{
							temp->m_nx = 20 + 110 * i;
							temp->m_ny = 200 + 20 * count;
							count++;
							temp = temp->m_pNext;
						}
						m_pCardsHead[i] = MouseCardsHead;
						m_pCardsEnd[i] = MouseCardsEnd;
						MouseCardsHead = MouseCardsEnd = NULL;
						break;
					}
				}
			}
		}
	}
}

void DownCards::SetEndCardVisual(int CountDown, HWND hwnd)
{
	CardsList* temp = m_pCardsEnd[CountDown];
	if (temp != NULL)
	{
		if (m_pCardsEnd[CountDown]->m_bFlag == FALSE)
		{
			m_pCardsEnd[CountDown]->m_bFlag = TRUE;
		}
	}
}

void DownCards::DeleteCardsOb()
{
	DeleteObject(m_hCardBackBitmap);
	DeleteObject(m_hCardBlankBitmap);
	for (int i = 0; i < 7; i++)
	{
		m_hVisualCardListHead[i] = m_hVisualCardListEnd[i] = NULL;
	}
}

DownCards::~DownCards()
{

}