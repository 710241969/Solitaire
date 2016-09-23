#pragma once

#ifndef CARDS_H_
#define CARDS_H_

#include<Windows.h>
#include<Windowsx.h>
#include"resource.h"

//����ֽ�ƽṹ��
struct Cards
{
	int m_nCardNum;
	int m_nCardColor;//1Ϊ���飬2Ϊ÷����3Ϊ���ģ�4Ϊ����
	HBITMAP m_hCardBitmap;
};

struct CardsList
{
	Cards m_Card;
	int m_nx;
	int m_ny;
	bool m_bFlag;//�Ƿ���ӱ�־��TRUEΪ���ӣ�FALSEΪ������
	CardsList* m_pNext;
	CardsList* m_pPre;
};


#endif