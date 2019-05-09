// 12141540 박영창
// 연습문제 4.1
// my_double_ls 루틴을 변경
// skip을 새로운 인자로, 0이면 그대로 수행 1이면 '.'으로 시작하는 화일 무시하며 수행

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

int main(int argc, char * argv[]){
	struct dirent *d;
	DIR *dd;
	
	if(argc != 3){
		// 인자 개수가 3개가 아닌 경우
		printf("Paramter Error\n");
		return (-1);
	}
	else{
		// 인자가 알맞게 들어온 경우
		if(argv[2][1] != '\0'){
			// skip 인자가 한 자리 수인지 확인 0, 1 둘중 하나가 아니면 아무것도 하지 않음
			printf("Invalid Parameter\n");
			return -1;
		}
	
		if((dd = opendir(argv[1])) == NULL){
			// 첫 번째 인자로 받은 경로 directory open
			printf("Invalid Path\n");
			return -1;
		}

		if(argv[2][0] == '0'){
			// skip == 0
			while(d = readdir(dd))
				// dirent 구조체에 dd로부터 하나씩 읽어간다
				if(d->d_ino != 0) printf("%s\n", d->d_name); // i-node 존재하면 출력
			
			rewinddir(dd); // dd를 open 했을 때의 초기값으로 rewind
	
			while(d=readdir(dd))
				// 한 번 더 반복
				if(d->d_ino != 0) printf("%s\n", d->d_name);
		
		}
		else if(argv[2][0] == '1'){
			// skip == 1
			while(d = readdir(dd)){
				// dirent 구조체에 dd로부터 하나씩 읽어간다.
				if(d->d_ino != 0 && d->d_name[0] != '.'){
					// i-node 존재 및 첫 글자가 '.'이 아니면 출력
					printf("%s\n", d->d_name);
				}
			}
	
			rewinddir(dd); // dd를 open 했을 때의 초기값으로 rewind
	
			while(d=readdir(dd)){
				// 한 번 더 반복
				if(d->d_ino != 0 && d->d_name[0] != '.'){ 
					printf("%s\n", d->d_name);
				}
			}
		}
	
		closedir(dd); // dd close
		return 0;
	}
}
