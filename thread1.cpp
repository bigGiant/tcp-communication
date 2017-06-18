#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

class MyThread
{
private:
	pthread_t tid;
	static void* task(void* arg)		//no static wrong!
	{
		while(1)
		{
			printf("hello!\n");
			sleep(1);
		}
		return NULL;
	}
public:
	MyThread()
	{
	}
	void start()
	{
		pthread_create(&tid, NULL,task, NULL);
	}
};

int main()
{
	MyThread thread;
	thread.start();
	getchar();
	return 0;
}
