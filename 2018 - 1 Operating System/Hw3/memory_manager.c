// 12141540 �ڿ�â
// OS 3�� ����
// Virtual Memory Manager
#include <stdio.h>

typedef struct _frame {		// frame table�� ���� ����ü
	int used;	// free = 0, used = 1
	int pageN;	// �Ҵ�Ǿ� �ִ� page #
}frame;

typedef struct pf_ {		// TLB table�� ���� ����ü
	int pageN;	// page #
	int frameN;	// frame #
}pf;

int p_table[256];	// 2^8���� entry�� ���� page table
pf TLB[32];			// 32���� entry�� ���� TLB table
frame f_table[256];	// 2^8�� entry�� ���� frame table

int l_Add;			// �Է¹��� logical address
double inputs = 0;	// �Է� ���� logical address�� ����
int frameUses = 0;	// �Ҵ� ���� frame�� ����
double TLBhits = 0;	// TLB hit�� Ƚ��
int TLBidx = 0;		// TLB�� FIFO algorithm�� ���� ���ſ� ���� �ε���

int main(void) {

	FILE * in_lAdd;		// input ����
	FILE * out_pAdd;	// output ���� 1 - physical address
	FILE * out_Frame;	// output ���� 2 - frame table
	FILE * out_TLB;		// output ���� 3 - ���� TLB

	in_lAdd = fopen("Addresses.txt", "r");		// file�� open
	out_pAdd = fopen("Physical.txt", "w");
	out_Frame = fopen("Frame_table.txt", "w");
	out_TLB = fopen("TLB.txt", "w");

	if (in_lAdd == NULL)					// file ����� ����
		printf("File error!\n");
	else {
		for (int i = 0; i < 256; i++) {		// page table �ʱ�ȭ
			p_table[i] = -1;
		}
		for (int i = 0; i < 32; i++) {		// TLB �ʱ�ȭ
			TLB[i].pageN = -1;
			TLB[i].frameN = -1;
		}

		while (!feof(in_lAdd)) {								// ������ ������ Ž��
			fscanf(in_lAdd, "%d", &l_Add);						// logical address �Է�
			inputs++;											// �Է��� ���� ����
			if (p_table[l_Add / 256] == -1) {					// �Է� ���� logical address�� page�� frame�� �Ҵ�Ǿ� ���� ���� ���
				p_table[l_Add / 256] = frameUses;				// ��� �ִ� frame�� �Ҵ�

				f_table[frameUses].used = 1;					// frame table ����
				f_table[frameUses].pageN = l_Add / 256;
				frameUses++;									// �Ҵ� ���� frame�� ���� ����

				TLB[TLBidx].pageN = l_Add / 256;				// TLB table ���� -> �� ��쿡�� frame�� �Ҵ�Ǿ� ���� �ʴ� page�� Ȯ���ϹǷ� TLB�� ������ �����Ѵ�
				TLB[TLBidx].frameN = p_table[l_Add / 256];
				TLBidx = (TLBidx + 1) % 32;						// FIFO algorithm�� ���� ���� TLB�� ���� ���� �� �κ��� �ε����� ����
			}
			else {
				int hit = 0;									// TLB hit�� �߻��ߴ��� Ȯ��
				for (int i = 0; i < 32; i++) {
					if (TLB[i].pageN == -1) break;				// TLB table�� ��� �ִ� �κп��� break
					if (TLB[i].pageN == l_Add / 256) {			// �Է¹��� logical address�� page #�� TLB ���� �����ϴ��� Ȯ��
						TLBhits++;								// �����Ѵٸ� TLB hit Ƚ���� ������Ű�� ���θ� 1�� ǥ�� �� break
						hit = 1;
						break;
					}
				}
				if (hit == 0) {									// TLB hit�� �߻����� �ʾҴٸ�
					TLB[TLBidx].pageN = l_Add / 256;			// TLB table �� ���� logical address�� �ش��ϴ� page #, frame #�� TLB table�� FIFO algorithm�� ���� ����, ����
					TLB[TLBidx].frameN = p_table[l_Add / 256];
					TLBidx = (TLBidx + 1) % 32;
				}
			}
			int p_Add = p_table[l_Add / 256] * 256 + l_Add % 256;	// physical address = (logical address�� �ش��ϴ� page #�� ���� ���� frame #) * frame size + offset
			fprintf(out_pAdd, "%d ", p_Add);						// physical address file�� ���
		}

		for (int i = 0; i < 256; i++) {			// frame table�� ���¸� file�� ���
			fprintf(out_Frame, "%d %d %d\n", i, f_table[i].used, f_table[i].pageN);
		}

		double TLBratio = TLBhits / inputs;								// TLB hit ratio = (TLB hit Ƚ��) / (�Է¹��� logical address�� ����)
		fprintf(out_TLB, "TLB hit ratio : %lf\n", TLBratio);			// TLB hit ratio file�� ���
		for (int i = 0; i < 32; i++) {									// TLB table�� ����ִ� �κ��� �����ϰ� file�� ���
			if (TLB[i].pageN == -1) break;
			fprintf(out_TLB, "%d %d\n", TLB[i].pageN, TLB[i].frameN);
		}
	}

	fclose(in_lAdd);			// file ����� ����
	fclose(out_pAdd);
	fclose(out_Frame);
	fclose(out_TLB);

	return 0;
}