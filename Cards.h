#pragma once

#ifndef CARDS_H_
#define CARDS_H_

#include<Windows.h>
#include<Windowsx.h>
#include"resource.h"

//定义纸牌结构体
struct Cards
{
	int m_nCardNum;
	int m_nCardColor;//1为方块，2为梅花，3为红心，4为黑桃
	HBITMAP m_hCardBitmap;
};

struct CardsList
{
	Cards m_Card;
	int m_nx;
	int m_ny;
	bool m_bFlag;//是否可视标志，TRUE为可视，FALSE为不可视
	CardsList* m_pNext;
	CardsList* m_pPre;
};


#endif