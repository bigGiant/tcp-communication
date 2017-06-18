#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

class MyThread
{
private:
	pthread_t tid;
public:
	virtual void run() = 0;
	static void* task(void* arg)
	{
		static_cast<MyThread*>(arg)->run();
	}
	MyThread()
	{}
	void start()
	{
		pthread_create(&tid, NULL, task, this);
	}
};

class ChildThread:public MyThread
{
	void run()
	{
		while(1)
		{
			printf("hello!\n");
			sleep(1);
		}
	}
};

int main()
{
	ChildThread thread;
	thread.start();
	getchar();
	return 0;
}
