// 12141540 �ڿ�â
// �������� 3.12
// chmod ����

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char * argv[]){
	int perm = 0;			// ������ ����
	int arr[3] = {0,0,0};	// ���� ������ 8������ ������ ������ �迭
	int opeidx = 0;			// �������� ��ġ�� ������ �ε���
	int temp = 0;			// �ӽ� ������ ������ ����
	struct stat buf;		// ������ stat�� �޾ƿ� ����ü

	if(argc != 3){
		// ������ ������ 3���� �ƴ� ���
		perror("Parameter Error\n");
		return -1;
	}
	else{
		// ������ ������ 3���� ���
		if(open(argv[2], O_RDWR) == -1){
			// �� ��° ���ڷ� ���� ������ ����
			perror("No Such File\n");
			return -1;
		}
		
		if(argv[1][0] >= '0' && argv[1][0] <= '9'){
			// ù ��° ���ڷ� ���� ������ 8������ ���
			perm = (argv[1][0] - '0') * 64 + (argv[1][1] - '0') * 8 + argv[1][2] -'0';
		}
		else if(argv[1][0] == 'r' || argv[1][0] == '-'){
			// ù ��° ���ڷ� ���� ������ ls ������ ���
			for(int i=0;i<3;i++){
				if(argv[1][i*3]=='r') arr[i]+=4;
				if(argv[1][i*3+1]=='w') arr[i]+=2;
				if(argv[1][i*3+2]=='x') arr[i]+=1;
			}
			perm = arr[0] * 64 + arr[1] * 8 + arr[2];
		}
		else{
			// ù ��° ���ڷ� ���� ������ �����ڸ� �����ϴ� ������ ���
			if(stat(argv[2], &buf) == -1){
				// stat �Լ��� ���� ������ �޾ƿ´�.
				perror("Can`t call stat\n");
				return -1;
			}

			while(argv[1][opeidx] != '+' && argv[1][opeidx] != '-' && argv[1][opeidx] != '=') opeidx++;
			// �������� ��ġ�� ã�Ƴ���.

			if(buf.st_mode & S_IRUSR) arr[0] += 4;
			if(buf.st_mode & S_IWUSR) arr[0] += 2;
			if(buf.st_mode & S_IXUSR) arr[0] += 1;
			if(buf.st_mode & S_IRGRP) arr[1] += 4;
			if(buf.st_mode & S_IWGRP) arr[1] += 2;
			if(buf.st_mode & S_IXGRP) arr[1] += 1;
			if(buf.st_mode & S_IROTH) arr[2] += 4;
			if(buf.st_mode & S_IWOTH) arr[2] += 2;
			if(buf.st_mode & S_IXOTH) arr[2] += 1;
			// ������ ���� ������ 8���� �������� �޾ƿ´�.

			for(int i=opeidx+1;i<strlen(argv[1]);i++){
				// ������ �ӽ� ������ �����Ѵ�.
				if(argv[1][i] == 'r') temp += 4;
				if(argv[1][i] == 'w') temp += 2;
				if(argv[1][i] == 'x') temp += 1;
			}

			for(int i=0;i<opeidx;i++){
				// ������ ���� ������ ������ ������ ��� ���� �����Ѵ�.
				if(argv[1][i] == 'u'){
					// user�� �����ؾ� �ϴ� ���
					if(argv[1][opeidx] == '=') arr[0] = temp;		// ����
					if(argv[1][opeidx] == '+') arr[0] |= temp;		// �߰�
					if(argv[1][opeidx] == '-') arr[0] &= (7 - temp);// ����
				}
				if(argv[1][i] == 'g'){
					// group�� �����ؾ� �ϴ� ���
					if(argv[1][opeidx] == '=') arr[1] = temp;		// ����
					if(argv[1][opeidx] == '+') arr[1] |= temp;		// �߰�
					if(argv[1][opeidx] == '-') arr[1] &= (7-temp);	// ����
				}
				if(argv[1][i] == 'o'){
					// �� ���� others�� �����ؾ� �ϴ� ���
					if(argv[1][opeidx] == '=') arr[2] = temp;		// ����
					if(argv[1][opeidx] == '+') arr[2] |= temp;		// �߰�
					if(argv[1][opeidx] == '-') arr[2] &= (7-temp);	// ����
				}
			
			}
			perm = arr[0] * 64 + arr[1] * 8 + arr[2];
		}
		if(chmod(argv[2], perm)== -1){
			// �� ��° ���ڷ� ���� ������ ������ ����
			perror("chmod fail\n");
			return -1;
		}
		printf("Success\n");
		return 0;
	}
}

