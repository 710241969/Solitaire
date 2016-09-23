#pragma once
#include "Cards.h"

//循环链表实现右上牌堆
/********************************************************/
class ButtonCards
{
public:
	ButtonCards();
	~ButtonCards();
	void LoadButtonCard(const HINSTANCE, Cards*);//加载下面的7个牌堆
	void ShowButtonCard(const HDC);
	void MouseGetCard(POINT, CardsList*&, CardsList*&, int&);
	void MouseCardBack(CardsList*);
	void DeleteCardsOb();

public:
	CardsList* m_pCardsHead;//左上牌堆第一张
	CardsList* m_pCardsEnd;//左上牌堆最后一张
	CardsList* m_pCardShow;//要显示的那一张牌
	CardsList* m_pToHead;
private:
	HBITMAP m_hCardBackBitmap;
	HBITMAP m_hCardBlankBitmap;
};

