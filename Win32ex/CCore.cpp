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

  int CCore::init(HWND _hWnd, POINT _ptResolution)  //�ʱ�ȭ�� �����ߴ��� �����ߴ����� �˱����� ��ȯ�� int��
  {
	  m_hWnd = _hWnd;
	  m_ptResolution = _ptResolution;


	  RECT rt{0,0,m_ptResolution.x,m_ptResolution.y}; // rectangle �� ���� ����ü ���� 4��  ������ â ũ��


	  //�ػ󵵿� �°� ������ ũ�� ����

	  AdjustWindowRect(&rt,WS_OVERLAPPEDWINDOW,true); // WS_OVERLAPPEDWINDOW : ���� ���� ���������� ��Ƴ��� ���� 3��° ���ڷ� �޴�â�� ������ �װ͵� �����ؼ� true �� ���� ����
	  // 2��° ������ ���ð��� 3��° ������ �޴� �� ����� ����� �ػ󵵸� ����ؼ� rt���� �׿��°� �����ؼ� �ٽ� ������.

	  // !!!! �׷��� ù��° ���ڰ� _Inout_ �̶� �ּ��� �ִ°��̴�. ���� �ܰ� ���ÿ� �޾ƿ��� ��ɵ� �ϴ� ���ڶ�¶�!!!
	  // �ݴ�� _In_ �� �ּ��� �ִ� ���ڴ� �ִ� ��ɸ� �ϰ� �޴� ����� ���ٴ� ������ �� �� �ִ�.

	  // ���� ���ϰ��� Ŭ�� �̷��� ���¸� ���� ���Ѵ�.


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
