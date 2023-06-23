#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main()
{
        int sock, connected, bytes_recieved , true = 1;
        char send_data [1024] , recv_data[1024];

        struct sockaddr_in server_addr,client_addr;
        int sin_size;

        sock = socket(AF_INET, SOCK_STREAM, 0);
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(9059);
        server_addr.sin_addr.s_addr = INADDR_ANY;
        bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
        listen(sock, 5);
        printf("\nTCPServer Waiting for client ");
        fflush(stdout);
       while(1)
        {

            sin_size = sizeof(struct sockaddr_in);

            connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

            printf("\n I got a connection from (%s , %d)",
                   inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

            while (1)
            {
              bytes_recieved = recv(connected,recv_data,1024,0);
              recv_data[bytes_recieved] = '\0';
              if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
              {
                close(connected);
                break;	
              }
	     int i=0,a=0;
	     char ope=' ';
	     float res=0;
    	     while(recv_data[i]!='\0'){
                 if (recv_data[i]=='+' || recv_data[i]=='-' || recv_data[i]=='*' || recv_data[i]=='/'){
                      ope=recv_data[i++];
                      res=a;
                      a=0;
                 }
                 else
                     a=a*10+(recv_data[i++]-'0');
             }
	     switch(ope){
       		 case '+':res=res+a;break;
        	 case '-':res=res-a;break;
        	 case '*':res=res*a;break;
       		 case '/':res=res/a;break;
   	      }
	     gcvt(res,3,recv_data); 
             
             printf("\n RECIEVED DATA = %s" , recv_data);
		       //sending data
                 send(connected, recv_data,strlen(recv_data), 0);
                fflush(stdout);
            }
        }

      close(sock);
      return 0;
}

