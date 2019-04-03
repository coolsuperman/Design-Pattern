#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Singleton {
	public:
	static Singleton* GetInstance () {//��ȡʵ����
		return &_sInstance;
	}
	private:
	Singleton () {}
	//��������
	Singleton (const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static Singleton _sInstance;
};

Singleton Singleton::_sInstance;//�ڳ������֮ǰ����ɵ��������ʼ����
int main () {
	return 0;
}