#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("creat socket error!\n");
		return -1;
	}
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("123.206.214.192");
	addr.sin_port = htons(9999);

	int ret = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret < 0)
	{
		printf("connect server error!\n");
	}
	while(1)
	{
		char buf[128] = {0};
		printf("input: ");
		scanf("%s", buf);
		ret = send(sockfd, buf, sizeof(buf), 0);
		if(ret < 0)
		{
			printf("message send error!\n");
			return -1;
		}
	}
	close(sockfd);
	return 0;
}
