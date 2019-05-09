// 12141540 �ڿ�â
// �������� 4.2
// my_double_ls ��ƾ�� ����
// �״�� �����ϵ� ���丮�� ������ �� �ڿ� '*'�� ���

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
		// ������ ������ 2���� �ƴ� ���
		printf("Paramter Error\n");
		return -1;
	}
	else{
		// ���ڰ� �˸°� ���� ���
		if((dd = opendir(argv[1])) == NULL){
			// ù ��° ���ڷ� ���� ��� directory open
			printf("Invalid Path\n");
			return -1;
		}
	
		while(d = readdir(dd)){
			// dirent ����ü�� dd�κ��� �ϳ��� �о��
			if(d->d_ino != 0){// i-node�� �����ϸ� stat ȣ��
				if(stat(d->d_name, &s) == -1){
					// stat �Ұ��� �� return
					printf("Can`t execute STAT\n");
					return -1;
				}

				if(S_ISDIR(s.st_mode))
					// stat ����ü�� st_mode�� Ȯ���� ���丮��� *�� �Բ� ���
				       	printf("%s *\n", d->d_name);
			        else
				       	printf("%s\n", d->d_name);
			}
		}

		rewinddir(dd); // dd�� open ���� ���� �ʱⰪ���� rewind
	
		while(d=readdir(dd)){
			// �� �� �� �ݺ�
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
