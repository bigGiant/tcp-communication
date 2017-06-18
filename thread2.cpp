#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

class MyThread
{
private:
	pthread_t tid;
public:
	static virtual void* task(void* arg) = 0;
	MyThread()
	{}
	void start()
	{
		pthread_create(&tid, NULL, task, NULL);
	}
};

class ChildThread::public MyThread
{
public:
	void* task(void* arg)
	{
		while(1)
		{
			printf("hello!\n");
			sleep(1);
		}
		return NULL;
	}
};

int main()
{
	ChildThread thread;
	thread.start();
	getchar();
	return 0;
}
