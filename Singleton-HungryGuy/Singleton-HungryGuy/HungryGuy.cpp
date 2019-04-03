#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Singleton {
	public:
	static Singleton* GetInstance () {//获取实例；
		return &_sInstance;
	}
	private:
	Singleton () {}
	//防拷贝；
	Singleton (const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static Singleton _sInstance;
};

Singleton Singleton::_sInstance;//在程序入口之前就完成单例对象初始化；
int main () {
	return 0;
}