#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BIND_PORT 	5000

void main() {
	int list_fd, ret, opt, con_fd;
	struct sockaddr_in bind_addr;

	list_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(list_fd == -1) {
		perror("sock create err:");
		return;
	}
	printf("Server sock: %d	fd\n", list_fd);
	
	opt = 1;
	ret = setsockopt(list_fd,SOL_SOCKET, SO_REUSEADDR, 
			(const void *) &opt, sizeof(opt));
	if(ret == -1) {
		perror("setsock opt REUSEADDR");
		close(list_fd);
		return;
	}
	printf("REUSEADDR opt set\n");

	bind_addr.sin_family = AF_INET;
	bind_addr.sin_port = htons(BIND_PORT);
	bind_addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(list_fd, (const struct sockaddr *) &bind_addr,
		       	sizeof(struct sockaddr));
	if(ret == -1) {
		perror("sock bind err:");
		close(list_fd);
		return;
	}
	printf("list_fd: %d bind success\n", list_fd);

	ret = listen(list_fd, 0);
	if(ret == -1) {
		perror("listen err:");
		close(list_fd);
		return;
	}
	printf("list_fd: %d listen success\n", list_fd);
	
	printf("server will wait now for incoming connection !!!\n");
	con_fd = accept(list_fd, NULL, NULL);
	if(con_fd == -1) {
		perror("accept err:");
		close(list_fd);
		return;
	}
	printf("accept success, con_fd: %d\n", con_fd);
	
	char buff[512] = {0};
	ret = recv(con_fd, (void *)buff, sizeof(buff), 0);
	if(ret <= 0) {
		perror("con closed or err:");
		close(list_fd);
		close(con_fd);
		return;
	}
	printf("con_fd: %d, recv: %d bytes\n", con_fd, ret);
	printf("RECEIVED: %s\n", buff);
	ret = send(con_fd, (const void *) "Hello from Server", 17, 0);
	if(ret <= 0) {
		perror("con closed or err:");
		close(list_fd);
		close(con_fd);
		return;
	}
	printf("con_fd: %d, send: %d bytes\n", con_fd, ret);
	close(list_fd);
	close(con_fd);
	return;
}
