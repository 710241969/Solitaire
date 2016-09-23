#pragma once
#include "Cards.h"

//ѭ������ʵ�������ƶ�
/********************************************************/
class ButtonCards
{
public:
	ButtonCards();
	~ButtonCards();
	void LoadButtonCard(const HINSTANCE, Cards*);//���������7���ƶ�
	void ShowButtonCard(const HDC);
	void MouseGetCard(POINT, CardsList*&, CardsList*&, int&);
	void MouseCardBack(CardsList*);
	void DeleteCardsOb();

public:
	CardsList* m_pCardsHead;//�����ƶѵ�һ��
	CardsList* m_pCardsEnd;//�����ƶ����һ��
	CardsList* m_pCardShow;//Ҫ��ʾ����һ����
	CardsList* m_pToHead;
private:
	HBITMAP m_hCardBackBitmap;
	HBITMAP m_hCardBlankBitmap;
};

