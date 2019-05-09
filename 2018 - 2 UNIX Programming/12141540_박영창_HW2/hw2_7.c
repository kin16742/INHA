#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if(argc < 3){
		printf("More Parameter need!\n");
		return 0;
	}
	else{
		int from = open(argv[1], O_RDWR);
		int to = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0644);
		int readn;
		int writen;
		char buffer[1024];

		if(from != -1){
			while(1){
				readn = read(from, buffer, 1024);
				writen = write(to, buffer, readn);
				if(readn <= 0){
					close(from);
					close(to);
					break;
				}
			}
		}
		else{
			printf("FILE OPEN FAIL\n");
		}
	}
	return 0;
}
