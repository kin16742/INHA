// 12141540 박영창
// OS 3차 과제
// Virtual Memory Manager
#include <stdio.h>

typedef struct _frame {		// frame table에 쓰일 구조체
	int used;	// free = 0, used = 1
	int pageN;	// 할당되어 있는 page #
}frame;

typedef struct pf_ {		// TLB table에 쓰일 구조체
	int pageN;	// page #
	int frameN;	// frame #
}pf;

int p_table[256];	// 2^8개의 entry를 갖는 page table
pf TLB[32];			// 32개의 entry를 갖는 TLB table
frame f_table[256];	// 2^8의 entry를 갖는 frame table

int l_Add;			// 입력받은 logical address
double inputs = 0;	// 입력 받은 logical address의 개수
int frameUses = 0;	// 할당 중인 frame의 개수
double TLBhits = 0;	// TLB hit의 횟수
int TLBidx = 0;		// TLB의 FIFO algorithm을 통한 갱신에 쓰일 인덱스

int main(void) {

	FILE * in_lAdd;		// input 파일
	FILE * out_pAdd;	// output 파일 1 - physical address
	FILE * out_Frame;	// output 파일 2 - frame table
	FILE * out_TLB;		// output 파일 3 - 최종 TLB

	in_lAdd = fopen("Addresses.txt", "r");		// file들 open
	out_pAdd = fopen("Physical.txt", "w");
	out_Frame = fopen("Frame_table.txt", "w");
	out_TLB = fopen("TLB.txt", "w");

	if (in_lAdd == NULL)					// file 입출력 오류
		printf("File error!\n");
	else {
		for (int i = 0; i < 256; i++) {		// page table 초기화
			p_table[i] = -1;
		}
		for (int i = 0; i < 32; i++) {		// TLB 초기화
			TLB[i].pageN = -1;
			TLB[i].frameN = -1;
		}

		while (!feof(in_lAdd)) {								// 파일의 끝까지 탐색
			fscanf(in_lAdd, "%d", &l_Add);						// logical address 입력
			inputs++;											// 입력의 개수 증가
			if (p_table[l_Add / 256] == -1) {					// 입력 받은 logical address의 page에 frame이 할당되어 있지 않은 경우
				p_table[l_Add / 256] = frameUses;				// 비어 있는 frame에 할당

				f_table[frameUses].used = 1;					// frame table 갱신
				f_table[frameUses].pageN = l_Add / 256;
				frameUses++;									// 할당 중인 frame의 개수 증가

				TLB[TLBidx].pageN = l_Add / 256;				// TLB table 갱신 -> 이 경우에는 frame이 할당되어 있지 않던 page를 확인하므로 TLB에 무조건 삽입한다
				TLB[TLBidx].frameN = p_table[l_Add / 256];
				TLBidx = (TLBidx + 1) % 32;						// FIFO algorithm을 위해 가장 TLB에 들어간지 오래 된 부분의 인덱스를 유지
			}
			else {
				int hit = 0;									// TLB hit가 발생했는지 확인
				for (int i = 0; i < 32; i++) {
					if (TLB[i].pageN == -1) break;				// TLB table의 비어 있는 부분에서 break
					if (TLB[i].pageN == l_Add / 256) {			// 입력받은 logical address의 page #가 TLB 내에 존재하는지 확인
						TLBhits++;								// 존재한다면 TLB hit 횟수를 증가시키고 여부를 1로 표시 후 break
						hit = 1;
						break;
					}
				}
				if (hit == 0) {									// TLB hit가 발생하지 않았다면
					TLB[TLBidx].pageN = l_Add / 256;			// TLB table 에 들어온 logical address에 해당하는 page #, frame #를 TLB table에 FIFO algorithm을 통해 저장, 갱신
					TLB[TLBidx].frameN = p_table[l_Add / 256];
					TLBidx = (TLBidx + 1) % 32;
				}
			}
			int p_Add = p_table[l_Add / 256] * 256 + l_Add % 256;	// physical address = (logical address에 해당하는 page #를 통해 구한 frame #) * frame size + offset
			fprintf(out_pAdd, "%d ", p_Add);						// physical address file에 출력
		}

		for (int i = 0; i < 256; i++) {			// frame table의 상태를 file에 출력
			fprintf(out_Frame, "%d %d %d\n", i, f_table[i].used, f_table[i].pageN);
		}

		double TLBratio = TLBhits / inputs;								// TLB hit ratio = (TLB hit 횟수) / (입력받은 logical address의 개수)
		fprintf(out_TLB, "TLB hit ratio : %lf\n", TLBratio);			// TLB hit ratio file에 출력
		for (int i = 0; i < 32; i++) {									// TLB table이 비어있는 부분을 제외하고 file에 출력
			if (TLB[i].pageN == -1) break;
			fprintf(out_TLB, "%d %d\n", TLB[i].pageN, TLB[i].frameN);
		}
	}

	fclose(in_lAdd);			// file 입출력 종료
	fclose(out_pAdd);
	fclose(out_Frame);
	fclose(out_TLB);

	return 0;
}