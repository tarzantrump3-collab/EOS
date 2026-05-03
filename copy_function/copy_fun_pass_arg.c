#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void copy_byte_by_byte(int fd1, int fd2);
void copy_in_chunks(int fd1, int fd2);
void main(int argc, char *argv[]) {

	/*sanitize input correct or not*/
	/*
	 * first arg is ./a.out then two files names so 3
	 * argv[0] = ./a.out
	 * argv[1] = file1.txt
	 * argv[2] = file2.txt
	 * argv[3] = c or b
	 * */

	if(argc != 4) {
		printf("invalid args counts :%d, expected: 3\n", argc);
		return;
	}

	printf("argv[0]:%s\n  argv[1]: %s\n argv[2]: %s\n", argv[0], argv[1], argv[2]);

	/*open both file descriptors for file1 and file2*/

	int fd1, fd2;
	
	/* 
	 * opening file 1 in read only mode
	 * not using O_TRUNC as that will zero its size
	 * not using O_CREAT as that will create file 
	 * we don't want here
	 *
	 */
	fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1) {
		/*errno from errno.h is set on error, only 
		 * rely on errno if specified in man page,
		 * strerror converts error no to printable string
		 */
		printf("%s open fail : %s\n", argv[1], strerror(errno));
		return;
	}

	printf("opened: %s fd: %d for reading \n", argv[1], fd1);
	
	/* 
	 * opening file 2 in write only mode
	 * create file if it doesnt exist
	 * truncating file if some data pre exists
	 * and give permission of read write if new file is 
	 * created
	 *
	 */
	fd2 = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if(fd2 == -1) {
		printf("%s open fail: %s\n", argv[2], strerror(errno));
		close(fd1); //closing file 1 already created fd
		return;
	}

	printf("opened %s fd: %d for writing \n", argv[2], fd2);
	
	if(strcasecmp(argv[3], "b") == 0) {
		copy_byte_by_byte(fd1, fd2);
	} else {
		copy_in_chunks(fd1, fd2);
	}	

	/*close both file 
	 * descriptors after use*/
	close(fd1);
	close(fd2);
}

void copy_in_chunks(int src_fd, int dst_fd) {
	
	if((src_fd < 0) || (dst_fd < 0)) {
		printf("invalid fds passed\n");
		return;
	}

	char buf[256];
	int read_bytes, write_bytes;
	
	do {
		read_bytes = read(src_fd, (void *)buf, sizeof(buf) / sizeof(buf[0]));
		if(read_bytes == -1) {
			printf("error reading: %s\n", strerror(errno));
			return;
		}

		if(read_bytes == 0) {
			printf("reached EOF, Operation complete\n");
			return;
		}

		printf("read: %d bytes from file 1\n", read_bytes);


		write_bytes = write(dst_fd, (const void *)buf, read_bytes);
		if(write_bytes == -1) {
			printf("error writing: %s\n", strerror(errno));
			return;
		}

		printf("write: %d bytes to file 2\n", write_bytes);
	
	} while(1);
}
void copy_byte_by_byte(int src_fd, int dst_fd) {
	
	if((src_fd < 0) || (dst_fd < 0)) {
		printf("invalid fds passed\n");
		return;
	}

	char buf;
	int read_bytes, write_bytes;
	
	do {
		read_bytes = read(src_fd, (void *)&buf, sizeof(buf));
		if(read_bytes == -1) {
			printf("error reading: %s\n", strerror(errno));
			return;
		}

		if(read_bytes == 0) {
			printf("reached EOF, Operation complete\n");
			return;
		}

		printf("read:\t%c,\t %d\t bytes from file\t1\n", buf, read_bytes);

		sleep(1);
		write_bytes = write(dst_fd, (const void *)&buf, sizeof(buf));
		if(write_bytes == -1) {
			printf("error writing: %s\n", strerror(errno));
			return;
		}

		printf("write:\t%c,\t %d\t bytes to file   2\n", buf, write_bytes);
	
	} while(1);
}
