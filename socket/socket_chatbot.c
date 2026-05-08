#include <stdio.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define SERVER_PORT 2204
#define BUF_SIZE 512
#define SERVER_IP "192.168.83.248"

char buffer[512] = {0};
int client_fd ,ret;


void *thread_recv(void *arg){
	char recv_buf[BUF_SIZE];
    	int len;

    while (1) {
        len = recv(client_fd, recv_buf, sizeof(recv_buf) - 1, 0);
        if (len > 0) {
            recv_buf[len] = '\0';

            printf("\r[Server]: %s\nyou: ", recv_buf);
            fflush(stdout);
        } else if (len == 0) {
            printf("\nServer closed the connection.\n");
            break;
        } else {
            perror("recv error");
            break;
        }
    }
    close(client_fd);
    exit(0);

}

void *thread_send(void *arg){
	char send_buf[BUF_SIZE];

    while (1) {
        printf("you: ");
        fflush(stdout);
        
        if (fgets(send_buf, sizeof(send_buf), stdin) != NULL) {

            send_buf[strcspn(send_buf, "\n")] = 0;

            if (strlen(send_buf) > 0) {
                if (send(client_fd, send_buf, strlen(send_buf), 0) < 0) {
                    perror("send error");
                    break;
                }
            }
            
            if (strcmp(send_buf, "exit") == 0) {
                break;
            }
        }
    }
    close(client_fd);
    exit(0);
}



void main(){
	struct sockaddr_in server_addr;
//	int client_fd ,ret;
	int arg[2];
	pthread_t thread1, thread2;

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
	
/*	ret = pthread_create(&thread1, NULL, thread_send, (arg +0));
	if(ret != 0){
		printf("thread send creat error: %d \n", ret);
 		return;
	}
*/
	arg[1] =2;

/*
	if (pthread_create(&thread1, NULL, thread_send, NULL) != 0){
	
	}
	
*/		
		pthread_create(&thread1, NULL, thread_send, NULL);
		ret = pthread_create(&thread2, NULL, thread_recv, NULL);
		
		if(ret != 0){
		        printf("tCould not create receive thread: %d \n", ret);
		        return;
		}
		
		pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
		
	/*	ret = pthread_join(thread1, NULL);
		if(ret != 0){
			printf("thread send join erreo\n");
			return;
		}
	*/
		//printf("thread recv exited , main continues\n");

	//	ret = pthread_join(thread2, NULL);
	   /*		if(ret != 0){
		    		 printf("thread recv join erreo\n");
				 return;
			}
*/
		//printf("client_fd %d, send : %d bytes\n",client_fd,ret);
/*
	while(1){
	printf("you:");
	fflush(stdout);
	
		//printf("client_fd :%d , recv: %d bytes\n",client_fd,ret);
		//printf(":recevived: %s \n", buffer);
		
		close(client_fd);
	}

*/

			close(client_fd);
}



