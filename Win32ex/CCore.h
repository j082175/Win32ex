#pragma once

//#include "define.h" �ʿ���� pch �ȿ� �ֱ⶧����
// 
//���� ����Լ�, ��ü���� ȣ�� ���� , �� this �� ���� �׸��� ��� ���� �Ұ���.

//���� ���� : �ٸ� ���Ͽ����� ���ٰ���
//���� ������ ���� ���� : �� ���Ͽ����� ���ٰ���
// �Լ� ���� ���� ���� : �� �Լ��� ���ؼ��� ���ٰ���
// Ŭ���� ���� ���� ���� : 

// ���� ��� ������ �ݵ�� ���� �ʱ�ȭ �ؾ���� ��ũ ������ �ȶ��!!!!! 


// ��ü�� ���� �Ҵ��ϴ� ����� �̱���
//class CCore2
//{
//private:
//	static CCore2* address;
//public:
//	static CCore2* getInstance();
//
//	static void release();
//
//
//private:
//	CCore2();
//	~CCore2();
//};


// DATA ������ ��ü�� �����ϴ� ����� �̱���
//class CCore
//{
//private:
//
//public:
//	static CCore* getInstance();
//
//private:
//	CCore();
//	~CCore();
//};





class CCore
{
private:
	HWND m_hWnd; // ���� ������ �ڵ�
	POINT m_ptResolution; // ���� ������ �ػ�
	HDC m_hDC; // ���� �����쿡 draw �� Device context
public:
	SINGLE(CCore);


public:
	int init(HWND _hWnd, POINT _ptResolution);

	void progress();

	HWND GetMainHwnd()
	{
		return m_hWnd;
	}

private:
	void update();
	void render();

//private:
//	CCore();
//	~CCore();
};