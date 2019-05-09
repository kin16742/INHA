// 12141540 �ڿ�â
// ���н� ���α׷��� 001

// �������� 2.9
// ����ִ� �� �߿� ���� �� ��ȣ�� ���� ���� ã�� �Լ�

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "hotel.h"
#include "findfree.h"

#ifndef NROOMS
#define NROOMS 10		// ���� ����
#endif

char buffer[LINELENGTH];// ������ ������ ������ buffer

int findfree(){
	int fd;				// file descriptor�� ������ ����
	int nread;			// read�� return���� ����� ����
	int roomno = 1;		// �� ��ȣ

	fd = open(listfile, O_RDONLY);	// listfile�� �б� �������� open

	while(roomno <= 10){	
		// 1�� ����� 10�� ����� �ݺ�

		nread = read(fd, buffer, LINELENGTH);	// ���� file pointer�κ��� LINELENGTH��ŭ �о�� buffer�� ����
		
		if(buffer[0] == ' ') return roomno;		// ���� ����ִٸ� ���� roomno return		

		roomno++;								// ������� �ʴٸ� roomno�� ������Ų��.
	}

	// �ݺ��� ������ �� ���� ã�� ���� ���
	printf("NO Empty Room!!\n");			
	return -1;
}
