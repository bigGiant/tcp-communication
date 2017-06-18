//At this program, we can know that all of them in one pid,
//main and that task(just creat) are not in one tid.


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_t tid;
void* task(void* arg)
{
	//printf("hello!\n");
	printf("New process: pid: %d, tid: %u.\n", getpid(), (unsigned int)pthread_self());
	printf("New process: pid: %d, tid: %u.\n", getpid(), (unsigned int)tid);
	return NULL;
}

int main()
{
	//pthread_t tid;
	int ret = pthread_create(&tid, NULL, task, NULL);
	if(ret < 0)
	{
		printf("failed to creat thread!\n");
		return -1;
	}
	else if(ret == 0)
		printf("create thread successfully!\n");
	printf("TID in pthread_creat function: %u.\n", (unsigned int)tid);
	printf("main process: pid: %d, tid: %u\n", getpid(), (unsigned int)pthread_self()); //build will cause format '%u' excepts argument of type 'unsigned int' wrong without (unsigned int).
	sleep(5);
	return 0;
}
