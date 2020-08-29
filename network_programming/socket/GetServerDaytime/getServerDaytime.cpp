#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    assert(argc == 2);
    const char *host = argv[1];

    /* 获取目标主机地址信息 */
    struct hostent *hostInfo = gethostbyname(host);
    assert(hostInfo);

    /* 获取daytime服务信息 */
    struct servent *servInfo = getservbyname("daytime", "tcp");
    assert(servInfo);
    printf("daytime port is %d\n", ntohs(servInfo->s_port));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = servInfo->s_port;
    address.sin_addr = *(struct in_addr *)*hostInfo->h_addr_list;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int result = connect(sockfd, (struct sockaddr *)&address, sizeof(address));

    char buffer[128];
    result = read(sockfd, buffer, sizeof(buffer));
    assert(result > 0);
    buffer[result] = '\0';
    printf("the day time is : %s\n", buffer);
    close(sockfd);
    return 0;
}