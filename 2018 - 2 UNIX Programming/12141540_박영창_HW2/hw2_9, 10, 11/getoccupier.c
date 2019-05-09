// 12141540 �ڿ�â
// ���н� ���α׷��� 001

// �ǽ� �ð��� ����� ���� �ڵ� - getoccupier.c
// ���ڷ� ���� �� ��ȣ�� �������� return�ϴ� �Լ�

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "hotel.h"
#include "getoccupier.h"

char buffer[LINELENGTH];	// �˸´� �������� ������ �о�� ������ buffer

char *getoccupier(int roomno){
	off_t offset;	// roomno�� ���� offset�� ����� ����
	ssize_t nread;	// read�� return���� ������ ����

	if(listfiledes == -1 && (listfiledes = open(listfile, O_RDONLY))==-1){
		// listfile�� open, ���� �� Error ��°� NULL return
		fprintf(stderr, "Error on opening list file \n");
		return NULL;
	}

	offset = (roomno - 1) * LINELENGTH; // offset ���

	if(lseek(listfiledes, offset, SEEK_SET) == -1){
		// ����� offset���� file pointer �̵�, ���� �� Error ��°� NULL return
		fprintf(stderr, "Error on setting offset \n");
		return NULL;
	}

	if((nread = read(listfiledes, buffer, LINELENGTH))<0){
		// file pointer�������� buffer�� listfile�� ���� �о�� ����, ���� �� Error ��°� NULL return
		fprintf(stderr, "Error on reading ofset \n");
		return NULL;
	}

	buffer[LINELENGTH - 1] = '\0'; // buffer�� �������� NULL�� �ٲ� ���ڿ��� ������ ��Ÿ��

	return buffer;
}
