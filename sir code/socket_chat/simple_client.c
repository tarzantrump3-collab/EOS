#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT		5000
#define SERVER_IP		"127.0.0.1"
void main() {
	struct sockaddr_in server_addr;
	int client_fd, ret;
	char buff[512] = {0};

	client_fd = socket(AF_INET, SOCK_STREAM , 0);
	if(client_fd == -1) {
		perror("socket create err:");
		return;
	}
	printf("client_fd: %d created\n", client_fd);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	ret = inet_pton(AF_INET, SERVER_IP, (void *) &server_addr.sin_addr);
	if(ret != 1) {
		perror("inet pton err:");
		close(client_fd);
		return;
	}
	printf("serverIP configured in struct sockaddr_in\n");
	ret = connect(client_fd, (const struct sockaddr *) &server_addr,
			sizeof(struct sockaddr));
	if(ret == -1) {
		perror("connect to server err:");
		close(client_fd);
		return;
	}
	printf("connect to server success... sending in 2 seconds\n");
	ret = send(client_fd, (const void *) "Hello from Client", 17, 0);
       	if(ret <= 0) {
		perror("con closed or err:");
		close(client_fd);
		return;
	}
	printf("client_fd: %d, send: %d bytes\n", client_fd, ret);

	ret = recv(client_fd, (void *) buff, sizeof(buff), 0);
	if(ret <= 0) {
		perror("con closed or err:");
		close(client_fd);
		return;
	}

	printf("client_fd: %d, recv: %d bytes\n", client_fd, ret);
	printf("RECEIVED: %s\n", buff);
	close(client_fd);
	return;
}
