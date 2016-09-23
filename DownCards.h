#include"Cards.h"

class DownCards
{
public:
	DownCards();
	~DownCards();
	void LoadAllCard(const HINSTANCE, Cards*);//加载下面的7个牌堆
	void ShowDownCard(const HDC);
	void MouseGetCard(POINT, CardsList*&, CardsList*&, int&, int&);
	void MouseCardBack(int, CardsList*,CardsList*);
	void MouseCardPutDown(POINT, CardsList*&, CardsList*&);
	void SetEndCardVisual(int, HWND);//使牌翻过来正面的操作
	void DeleteCardsOb();

private:
	void GetVisualCardList();

public:
	CardsList* m_pCardsHead[7];//下面7个牌堆的头
	CardsList* m_pCardsEnd[7];
private:
	HBITMAP m_hCardBackBitmap;//牌背面图位图
	HBITMAP m_hCardBlankBitmap;//空牌堆位图
	CardsList* m_hVisualCardListHead[7];
	CardsList* m_hVisualCardListEnd[7];
};