#pragma once

//Time Manager
// �ð� ����ȭ
class CTimeMgr
{
public:
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;
	LARGE_INTEGER m_llPrevCount;

	double m_dDT; // ������ ������ �ð���
	double m_dAcc;

	UINT m_iCallCount; // �ʴ� ȣ�� Ƚ��
	UINT m_iFPS;

	// FPS
	// 1 �����Ӵ� �ð� �� delta time 
	// ��ǻ�ʹ� �ʴ� ������ �� �ִ� Frame �� ������ �ٸ��Ƿ� �̰� �̿��� �����Ѵ�.



public:
	void init();
	void update();

	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

public:
	//GetTickCount() �ʴ� õ���� ���µ� ��Ȯ���� ����.
	
	//CTimeMgr();
	//~CTimeMgr();
};

