#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CObject g_obj;

// CCore2* CCore2::getInstance()
//{
//	if (address == nullptr)
//	{
//		address = new CCore2;
//	}
//
//	return address;
//
//}
//
// void CCore2::release()
//{
//	delete address;
//}
//
// CCore2::CCore2() {}
//
// CCore2::~CCore2() {}


// CCore* CCore::getInstance()
//{
//	static CCore core;
//
//	return &core;
//}
//
// CCore::CCore() {}
//
// CCore::~CCore() {}


// CCore2* CCore2::address = nullptr;

int CCore::init(HWND _hWnd, POINT _ptResolution)  //초기화가 성공했는지 실패했는지를 알기위해 반환형 int로
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;


	RECT rt{ 0,0,m_ptResolution.x,m_ptResolution.y }; // rectangle 을 본뜬 구조체 인자 4개  윈도우 창 크기


	//해상도에 맞게 윈도우 크기 조절

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // WS_OVERLAPPEDWINDOW : 자주 쓰는 설정값들을 모아놓은 세팅 3번째 인자로 메뉴창이 있으니 그것도 감안해서 true 로 인자 전달
	// 2번째 인자의 셋팅값과 3번째 인자의 메뉴 바 등등을 고려한 해상도를 고려해서 rt값을 그에맞게 수정해서 다시 수정함.

	// !!!! 그래서 첫번째 인자가 _Inout_ 이란 주석이 있는것이다. 값을 줌과 동시에 받아오는 기능도 하는 인자라는뜻!!!
	// 반대로 _In_ 요 주석이 있는 인자는 주는 기능만 하고 받는 기능은 없다는 것임을 알 수 있다.

	// 보통 리턴값이 클때 이러한 형태를 많이 취한다.


	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0); // 윈도우는 내부에 각각의 가로세로 픽셀을 곱한 비트맵을 가지게됨


	m_hDC = GetDC(m_hWnd); // dc


	//Manager 초기화
	CTimeMgr::getInstance()->init();
	CKeyMgr::getInstance()->init();
	

	g_obj.SetPos(Vec2(float(m_ptResolution.x / 2), float(m_ptResolution.y / 2)));
	g_obj.SetScale(Vec2(100, 100));


	return S_OK;
}



void CCore::progress()
{
	// 화면에 계속 그리는 부분
	// 
	// ----------- 렌더링이란 매 순간 순간마다 그림을 다시 처음부터 그리는건데 ---------
	//------------ 컴퓨터가 존나빨라서 우리는 이게 연속적인 것처럼 느낀다. ---------

	update();

	render();

	CTimeMgr::getInstance()->update();

}

// 옵젝의 변경점을 처리
void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 200.f * CTimeMgr::getInstance()->GetfDT();
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 200.f * CTimeMgr::getInstance()->GetfDT();
	}

	g_obj.SetPos(vPos);
}

// 변경된 옵젝을 그린다
// -- 
void CCore::render()
{

	//그리기

	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_hDC,
		(int)(vPos.x - vScale.x / 2.f),
		(int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f),
		(int)(vPos.y + vScale.y / 2.f)
	);
}

CCore::CCore()
	:m_hWnd(0),
	m_hDC(0),
	m_ptResolution{}
{}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
}
