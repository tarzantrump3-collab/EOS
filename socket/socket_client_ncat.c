#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define SERVER_PORT 2204
#define SERVER_IP "192.168.83.248"

void main(){
	struct sockaddr_in server_addr;
	int client_fd ,ret;
	char buffer[512] = {0};

	client_fd = socket(AF_INET,SOCK_STREAM,0);
	if (client_fd == -1){
		perror("socket create err: ");
		return;
	}
	printf("client_fd : %d created \n" , client_fd);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	ret = inet_pton(AF_INET, SERVER_IP, (void *) &server_addr.sin_addr);

	if(1 != ret ){
		perror("inet_pton err:");
		close(client_fd);
		return;
	}

	printf(":server IP configured in struct sockaddr_in \n");
	ret = connect(client_fd, (const struct sockaddr*) &server_addr,sizeof(struct sockaddr));

	if (-1 == ret ){
		perror("connect to server err:");
		close(client_fd);
		return;
	}

	printf("connect to server success... sending in 2 second\n");
	
	ret = send(client_fd, (const void *) "HELLO FROM CLIENT PC 04",17,0);
	
	if ( 0 >= ret ){
                perror("con closed or err:");
		close(client_fd);
                return;
        }

	printf("client_fd %d, send : %d bytes\n",client_fd,ret);


	ret = recv(client_fd, (void *)buffer, sizeof(buffer), 0);
	
	if( 0  >= ret){
		perror("con closed or err:");
                close(client_fd);
		return;
	}	

	printf("client_fd :%d , recv: %d bytes\n",client_fd,ret);
	printf(":recevived: %s \n", buffer);
	close(client_fd);



}



