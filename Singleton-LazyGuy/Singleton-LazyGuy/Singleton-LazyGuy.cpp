#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Singleton {
	public:
	static Singleton* GetInstance () {//获取实例；
		if ( nullptr == _sInstance ) {//双检查:当对象已经有了，就不再进行枷锁解锁了(会有消耗，且并行会变成串行，性能下降)，双检查会提高效率，减少浪费；
			m_mtx.lock ();//加互斥锁，t1进去后会上锁，t2就得等到t1解锁后才行；不加若是同时检测到空，创建两个对象，就不是单例了，线程不安全；
			if ( _sInstance == nullptr ) {//第一次使用的时候才初始化创建；
				_sInstance = new Singleton;
			}
			m_mtx.unlock ();//解锁；
		}
		return _sInstance;
	}
	class CGarbo {//实现内部类实现垃圾回收功能
		public:
		~CGarbo () {
			if ( Singleton::_sInstance )
				delete Singleton::_sInstance;
		}
	};
	private:
	Singleton () {}
	//单例防拷贝；
	Singleton (const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static CGarbo Garbo;//定义一个静态成员变量，main程序结束时，系统会释放静态变量，会自动调用它的析构函数从而释放单例对象；
	static Singleton* _sInstance;//单例对象指针
	static mutex m_mtx;//加互斥锁
};

Singleton* Singleton::_sInstance = nullptr;
Singleton::CGarbo Singleton::Garbo;//初始化类对象会自动调缺省构造
mutex Singleton::m_mtx;
void func (int n) {
	cout << Singleton::GetInstance () << endl;
}
int main () {
	thread t1 (func , 10);//创建多个线程
	thread t2 (func , 10);
	t1.join ();//本程序t等一下t1,t2,不可在t1,t2之前结束；
	t2.join ();
	cout << Singleton::GetInstance () << endl;
	cout << Singleton::GetInstance () << endl;
}