#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()

{

        int sock, bytes_recieved;
        char send_data[1024],recv_data[1024];
        struct sockaddr_in server_addr;
       sock = socket(AF_INET, SOCK_STREAM, 0);
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(9059);
        server_addr.sin_addr.s_addr =htonl(INADDR_ANY);       
        bzero(&(server_addr.sin_zero),8);
        connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr));
	send(sock,"12",sizeof(int), 0);
	bytes_recieved=recv(sock,recv_data,1024,0);
	printf("\nRecieved data = %s " , recv_data);
	close(sock);//close(connected);
	return 0;
}
