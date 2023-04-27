#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능
class CCore
{
public:
	CCore* GetInstance()
	{

		return nullptr;
	}

private:
	CCore();
	~CCore();
};

