// 12141540 �ڿ�â
// �������� 4.1
// my_double_ls ��ƾ�� ����
// skip�� ���ο� ���ڷ�, 0�̸� �״�� ���� 1�̸� '.'���� �����ϴ� ȭ�� �����ϸ� ����

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

int main(int argc, char * argv[]){
	struct dirent *d;
	DIR *dd;
	
	if(argc != 3){
		// ���� ������ 3���� �ƴ� ���
		printf("Paramter Error\n");
		return (-1);
	}
	else{
		// ���ڰ� �˸°� ���� ���
		if(argv[2][1] != '\0'){
			// skip ���ڰ� �� �ڸ� ������ Ȯ�� 0, 1 ���� �ϳ��� �ƴϸ� �ƹ��͵� ���� ����
			printf("Invalid Parameter\n");
			return -1;
		}
	
		if((dd = opendir(argv[1])) == NULL){
			// ù ��° ���ڷ� ���� ��� directory open
			printf("Invalid Path\n");
			return -1;
		}

		if(argv[2][0] == '0'){
			// skip == 0
			while(d = readdir(dd))
				// dirent ����ü�� dd�κ��� �ϳ��� �о��
				if(d->d_ino != 0) printf("%s\n", d->d_name); // i-node �����ϸ� ���
			
			rewinddir(dd); // dd�� open ���� ���� �ʱⰪ���� rewind
	
			while(d=readdir(dd))
				// �� �� �� �ݺ�
				if(d->d_ino != 0) printf("%s\n", d->d_name);
		
		}
		else if(argv[2][0] == '1'){
			// skip == 1
			while(d = readdir(dd)){
				// dirent ����ü�� dd�κ��� �ϳ��� �о��.
				if(d->d_ino != 0 && d->d_name[0] != '.'){
					// i-node ���� �� ù ���ڰ� '.'�� �ƴϸ� ���
					printf("%s\n", d->d_name);
				}
			}
	
			rewinddir(dd); // dd�� open ���� ���� �ʱⰪ���� rewind
	
			while(d=readdir(dd)){
				// �� �� �� �ݺ�
				if(d->d_ino != 0 && d->d_name[0] != '.'){ 
					printf("%s\n", d->d_name);
				}
			}
		}
	
		closedir(dd); // dd close
		return 0;
	}
}
