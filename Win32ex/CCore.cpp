#include "pch.h"
#include "CCore.h"

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


	  RECT rt{0,0,m_ptResolution.x,m_ptResolution.y}; // rectangle 을 본뜬 구조체 인자 4개  윈도우 창 크기


	  //해상도에 맞게 윈도우 크기 조절

	  AdjustWindowRect(&rt,WS_OVERLAPPEDWINDOW,true); // WS_OVERLAPPEDWINDOW : 자주 쓰는 설정값들을 모아놓은 세팅 3번째 인자로 메뉴창이 있으니 그것도 감안해서 true 로 인자 전달
	  // 2번째 인자의 셋팅값과 3번째 인자의 메뉴 바 등등을 고려한 해상도를 고려해서 rt값을 그에맞게 수정해서 다시 수정함.

	  // !!!! 그래서 첫번째 인자가 _Inout_ 이란 주석이 있는것이다. 값을 줌과 동시에 받아오는 기능도 하는 인자라는뜻!!!
	  // 반대로 _In_ 요 주석이 있는 인자는 주는 기능만 하고 받는 기능은 없다는 것임을 알 수 있다.

	  // 보통 리턴값이 클때 이러한 형태를 많이 취한다.


	  SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);


	  m_hDC = GetDC(m_hWnd); // dc

	  return S_OK;
  }

  void CCore::progress()
  {

  }

   CCore::CCore()
   :m_hWnd(0),
	   m_hDC(0),
	   m_ptResolution{}
   {}

   CCore::~CCore() {}
