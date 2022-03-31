#pragma once

//#include "define.h" 필요없음 pch 안에 있기때문에
// 
//정적 멤버함수, 객체없이 호출 가능 , 즉 this 가 없다 그말은 멤버 접근 불가능.

//전역 변수 : 다른 파일에서도 접근가능
//파일 범위의 정적 변수 : 그 파일에서만 접근가능
// 함수 내의 정적 변수 : 그 함수를 통해서만 접근가능
// 클래스 내의 정적 변수 : 

// 정적 멤버 변수는 반드시 따로 초기화 해야줘야 링크 에러가 안뜬다!!!!! 


// 객체를 동적 할당하는 방식의 싱글톤
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


// DATA 영역에 객체를 저장하는 방식의 싱글톤
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
	HWND m_hWnd; // 메인 윈도우 핸들
	POINT m_ptResolution; // 메인 윈도우 해상도
	HDC m_hDC; // 메인 윈도우에 draw 할 Device context
public:
	SINGLE(CCore);


public:
	int init(HWND _hWnd, POINT _ptResolution);

	void progress();

private:
	void update();
	void render();

private:
	CCore();
	~CCore();
};