// 12141540 박영창
// 연습문제 4.2
// my_double_ls 루틴을 변경
// 그대로 수행하되 디렉토리를 만났을 때 뒤에 '*'를 출력

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char * argv[]){
	struct dirent *d;
	struct stat s;
	DIR *dd;
	
	if(argc != 2){
		// 인자의 개수가 2개가 아닌 경우
		printf("Paramter Error\n");
		return -1;
	}
	else{
		// 인자가 알맞게 들어온 경우
		if((dd = opendir(argv[1])) == NULL){
			// 첫 번째 인자로 받은 경로 directory open
			printf("Invalid Path\n");
			return -1;
		}
	
		while(d = readdir(dd)){
			// dirent 구조체에 dd로부터 하나씩 읽어간다
			if(d->d_ino != 0){// i-node가 존재하면 stat 호출
				if(stat(d->d_name, &s) == -1){
					// stat 불가능 시 return
					printf("Can`t execute STAT\n");
					return -1;
				}

				if(S_ISDIR(s.st_mode))
					// stat 구조체의 st_mode를 확인해 디렉토리라면 *과 함께 출력
				       	printf("%s *\n", d->d_name);
			        else
				       	printf("%s\n", d->d_name);
			}
		}

		rewinddir(dd); // dd를 open 했을 때의 초기값으로 rewind
	
		while(d=readdir(dd)){
			// 한 번 더 반복
			if(d->d_ino != 0){
			 	if(stat(d->d_name, &s) == -1){
				       	printf("Can`t execute STAT\n");
				       	return -1;
				}	  
				
				if(S_ISDIR(s.st_mode))
					printf("%s *\n", d->d_name);
				else
					printf("%s\n", d->d_name);
			}
		}

		closedir(dd); // dd close
		
		return 0;
	}
}
