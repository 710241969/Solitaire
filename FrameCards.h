#pragma once
#include "Cards.h"
class FrameCards
{
public:
	FrameCards();
	~FrameCards();
	void LoadFrameCards(const HINSTANCE, Cards*);//���������7���ƶ�
	void ShowFrameCards(const HDC);
	void MouseGetCard(POINT, CardsList*&, CardsList*&, int&, int&);
	void MouseCardBack(int, CardsList*);
	void MouseCardPutDown(POINT, CardsList*&, CardsList*&);
	void DeleteCardsOb();

public:
	CardsList* m_pCardsHead[4];//����4���ƿ��ƶ�
	CardsList* m_pCardsEnd[4];
	HBITMAP m_hFrameBitmap;
};

