#include "DownCards.h"
#include "ButtonCards.h"
#include "FrameCards.h"
class CardCtrl
{
public:
	CardCtrl();
	~CardCtrl();
	void InitValue(const HWND& hWnd, const HINSTANCE& hInstance);//�����ݳ�ʼ��
	void GameInit();//��Ϸ��ʼ��
	void OnPaintWnd();//���������
	void OnMouseLDown(POINT);//��Ӧ���������µĲ���
	void OnMouseLUp(POINT);//��Ӧ�������ɿ��Ĳ���
	void OnMouseMove(POINT);
	void DeleteCardsOb();
private:
	void OnLeftCardButtonClick();//������ϰ�ť����
	void ShowMouseCards(HDC);

private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	int m_nCardsOrder[52];//�����������õ�������
	Cards m_oNoOrderCards[52];//������������
	//HWND m_hCardButton;//���ϰ�ť�ؼ�
	DownCards m_oDownCards;//��ʼ�����Ƶ���
	FrameCards m_oFrameCards;//����4���ƶѵ���
	ButtonCards m_oButtonCards;//�����ƶѵ���
	CardsList* m_pMouseCardsHead;
	CardsList* m_pMouseCardsEnd;
	POINT m_MouseLDown;//����������ʱ������
	POINT m_MouseUp;//�������ɿ�ʱ������
	POINT m_MouseMove;
	int m_nLocationFlag;/*�Ƶ���Դλ�ñ�־��1Ϊ�����7���ƶ�֮һ��
						Ϊ����4���ƿ�֮һ��3Ϊ���ϳ��Ƶ��ƶѣ�0ΪĬ��ֵ*/
	int m_nCountDown;
	int m_nCountFrame;
};