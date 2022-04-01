#pragma once

//Time Manager
// 시간 동기화
class CTimeMgr
{
public:
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;
	LARGE_INTEGER m_llPrevCount;

	double m_dDT; // 프레임 사이의 시간값
	double m_dAcc;

	UINT m_iCallCount; // 초당 호출 횟수
	UINT m_iFPS;

	// FPS
	// 1 프레임당 시간 즉 delta time 
	// 컴퓨터당 초당 수행할 수 있는 Frame 이 제각기 다르므로 이걸 이용해 통일한다.



public:
	void init();
	void update();

	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

public:
	//GetTickCount() 초당 천번을 새는데 정확하지 않음.
	
	//CTimeMgr();
	//~CTimeMgr();
};

