#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Singleton {
	public:
	static Singleton* GetInstance () {//��ȡʵ����
		if ( nullptr == _sInstance ) {//˫���:�������Ѿ����ˣ��Ͳ��ٽ��м���������(�������ģ��Ҳ��л��ɴ��У������½�)��˫�������Ч�ʣ������˷ѣ�
			m_mtx.lock ();//�ӻ�������t1��ȥ���������t2�͵õȵ�t1��������У���������ͬʱ��⵽�գ������������󣬾Ͳ��ǵ����ˣ��̲߳���ȫ��
			if ( _sInstance == nullptr ) {//��һ��ʹ�õ�ʱ��ų�ʼ��������
				_sInstance = new Singleton;
			}
			m_mtx.unlock ();//������
		}
		return _sInstance;
	}
	class CGarbo {//ʵ���ڲ���ʵ���������չ���
		public:
		~CGarbo () {
			if ( Singleton::_sInstance )
				delete Singleton::_sInstance;
		}
	};
	private:
	Singleton () {}
	//������������
	Singleton (const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static CGarbo Garbo;//����һ����̬��Ա������main�������ʱ��ϵͳ���ͷž�̬���������Զ������������������Ӷ��ͷŵ�������
	static Singleton* _sInstance;//��������ָ��
	static mutex m_mtx;//�ӻ�����
};

Singleton* Singleton::_sInstance = nullptr;
Singleton::CGarbo Singleton::Garbo;//��ʼ���������Զ���ȱʡ����
mutex Singleton::m_mtx;
void func (int n) {
	cout << Singleton::GetInstance () << endl;
}
int main () {
	thread t1 (func , 10);//��������߳�
	thread t2 (func , 10);
	t1.join ();//������t��һ��t1,t2,������t1,t2֮ǰ������
	t2.join ();
	cout << Singleton::GetInstance () << endl;
	cout << Singleton::GetInstance () << endl;
}