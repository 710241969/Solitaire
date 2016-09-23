#include"Cards.h"

class DownCards
{
public:
	DownCards();
	~DownCards();
	void LoadAllCard(const HINSTANCE, Cards*);//���������7���ƶ�
	void ShowDownCard(const HDC);
	void MouseGetCard(POINT, CardsList*&, CardsList*&, int&, int&);
	void MouseCardBack(int, CardsList*,CardsList*);
	void MouseCardPutDown(POINT, CardsList*&, CardsList*&);
	void SetEndCardVisual(int, HWND);//ʹ�Ʒ���������Ĳ���
	void DeleteCardsOb();

private:
	void GetVisualCardList();

public:
	CardsList* m_pCardsHead[7];//����7���ƶѵ�ͷ
	CardsList* m_pCardsEnd[7];
private:
	HBITMAP m_hCardBackBitmap;//�Ʊ���ͼλͼ
	HBITMAP m_hCardBlankBitmap;//���ƶ�λͼ
	CardsList* m_hVisualCardListHead[7];
	CardsList* m_hVisualCardListEnd[7];
};