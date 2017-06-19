#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

void* task(void* arg)
{
	int accfd = *(int*)arg;
	while(1)
	{
		char buf[128];
		int rlen = recv(accfd, buf, sizeof(buf), 0);
		if(rlen < 0)
		{
			printf("message receive error!\n");
			return NULL;
		}
		else if(rlen > 0)
			printf("receive message from client: %s\n", buf);
		if(strcmp(buf, "bye"))
			pthread_exit(NULL);
	}
	return NULL;
}

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//char ip[] = "123.206.214.192";
	if(sockfd < 0)
	{
		printf("creat socket error!\n");
		return -1;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = htonl(ip);
	//addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(9999);
	
	int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
	if(ret < 0)
	{
		printf("bind error!\n");
		return -1;
	}
	
	listen(sockfd, 100);

	int accfd;
	while(1)
	{
		struct sockaddr_in clientAddr;
		pthread_t tid;
		socklen_t len = sizeof(clientAddr);
		accfd = accept(sockfd, (struct sockaddr*)&clientAddr, &len);
		if(accfd < 0)
		{
			printf("accept error!\n");
			return -1;
		}
		ret = pthread_create(&tid, NULL, task, &accfd);
		if(ret < 0)
		{
			printf("create pthreat wrong!\n");
		}

	}
	close(accfd);
	close(sockfd);
	return 0;
}
