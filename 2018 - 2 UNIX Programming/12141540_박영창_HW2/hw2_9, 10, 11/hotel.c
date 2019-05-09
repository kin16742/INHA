// 12141540 �ڿ�â
// ���н� ���α׷��� 001

// �������� 2.11
// getoccupier, freeroom, addguest, findfree �ڷ� ȭ���� �����ϴ� ��ƿ��Ƽ ���α׷�
// <printf�� ȣ���ϴ� ��ȭ�� ���α׷�>

//		listfile���� ����ִ� ���� ���� 3���� ���ڿ��� ǥ���ϱ� ������
//		listfile�� ������ �����ؾ߸� ��� �Լ��� ���� �����մϴ�.. 

//		Makefile�� make�� ���� ���ս�ŵ�ϴ�.

#include "hotel.h"
#include "getoccupier.h"
#include "findfree.h"
#include "freeroom.h"
#include "addguest.h"
#include <stdio.h>

#ifndef NROOMS
#define NROOMS 10
#endif

int main(){
	char* name;		// ���ڿ��� ������ ����
	int cmd = 0;	// ������ command�� ��ȣ
	
	while(cmd != 5){
		printf("--------------------------------------\n");
		printf("              FRONTDESK               \n");
		printf("--------------------------------------\n");
		printf("1 : View all Guests                   \n");
		printf("2 : Find Empty Room                   \n");
		printf("3 : Free Room                         \n");
		printf("4 : Add Guest                         \n");
		printf("5 : Exit                              \n");
		printf("--------------------------------------\n");
		printf("Input : ");
		scanf("%d", &cmd);

		if(cmd == 1){	
			// getoccupier�� ����� ��� �������� ���� Ȯ��

			printf("-----------------LIST-----------------\n");
			for(int i = 1;i <= NROOMS;i++){
				if(name = getoccupier(i))
					printf("Room %d, %s \n", i, name);
				else
					fprintf(stderr, "Error on calling 'getoccupier'\n");
			}
		}
		else if(cmd == 2){
			// findfree�� ����� ����ִ� ���� ���� �� ��ȣ Ȯ��

			int freen = findfree();

			if(freen <= 10)
				printf("Room  %d is empty.\n",freen);
			else
				printf("No Room`s empty.\n");
		}
		else if(cmd == 3){
			// freeroom�� ����� �Է¹��� �� ��ȣ�� ���� ���

			int a;
			
			printf("Room # to be Free : ");
			scanf("%d", &a);
			freeroom(a);
		}
		else if(cmd == 4){
			// addguest�� ����� �Է¹��� �� ��ȣ�� �Է¹��� �������� ������ �߰�
			
			int a;
			char* name[LINELENGTH];
			
			printf("Room # to be Used : ");
			scanf("%d", &a);
			printf("Guest`s Name : ");
		    scanf("%s", name);
			addguest(a,name);
		}
		else if(cmd == 5){
			// ����
			break;
		}
		else{
			// �Է��� �߸��� ���
			printf("         Command Not Exist          \n");
			printf("Input : ");
			scanf("%d", &cmd);
		}
	}
	return 0;
}
