#include "pch.h"
#include "CCore.h"
#include "CObject.h"

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


	  g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	  g_obj.m_ptScale = POINT{ 100,100 };


	  return S_OK;
  }

 

  void CCore::progress()
  {
	  // ȭ�鿡 ��� �׸��� �κ�
	  // 
	  // ----------- �������̶� �� ���� �������� �׸��� �ٽ� ó������ �׸��°ǵ� ---------
	  //------------ ��ǻ�Ͱ� �������� �츮�� �̰� �������� ��ó�� ������. ---------

	  update();

	  render();

  }

  // ������ �������� ó��
  void CCore::update()
  {
	  if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	  {
		  g_obj.m_ptPos.x -= 1;
	  }

	  if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	  {
		  g_obj.m_ptPos.x += 1;
	  }
  }

  // ����� ������ �׸���
  void CCore::render()
  {
	  Rectangle(m_hDC,
		  g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2,
		  g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2,
		  g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2,
		  g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2
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
