#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <time.h>

#define BUF_SIZE 1024
void error_handling(char *buf);

int main(int argc, char *argv[]){
	int serv_sock, clnt_sock;										// 서버, 클라이언트 소켓
	struct sockaddr_in serv_adr, clnt_adr;			// 서버, 클라이언트 소켓의 주소 정보
	socklen_t adr_sz;														// 주소 정보 구조체 크기를 저장할 변수

	fd_set reads, cpy_reads;										// file descriptor set와 그 복사본으로 사용할 것
	int fd_max, fd_num;													// descriptor 중 가장 큰 값, select 함수의 반환 값
	struct timeval timeout;											// select 함수에 인자로 넘겨 줄 timeout 값

	char buf[BUF_SIZE];												  // 주고 받을 데이터
	int str_len;																// 데이터 read의 반환값을 저장할 변수

	time_t ltime;
	struct tm *newtime;													// 시간 출력을 위해 사용하는 변수들

	if(argc!=2) {
    // command line 인자로 port 번호를 받는다
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

// ======================================== 소켓 생성 ========================================

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	// 인자 순서대로 프로토콜 체계 정보 / 데이터 전송 방식 / 통신에 사용될 프로토콜 정보를 지정


// ======================================== 주소 할당 ========================================

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;									// 주소 체계 할당
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);		// 서버 소켓 주소 할당
	serv_adr.sin_port=htons(atoi(argv[1]));				// 서버 소켓 port를 command line 인자로 받은 port 번호로 할당

	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");


// ===================================== 연결 요청 대기 ======================================

	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

// =============================== file descriptor set 초기화 ================================

	FD_ZERO(&reads);						// reads의 모든 비트를 전부 0으로 초기화
	FD_SET(serv_sock, &reads);	// 서버 소켓을 관찰 대상으로 추가
	fd_max = serv_sock;					// 현재 가장 큰 file descriptor = 서버 소켓

// ================================= select 결과에 따른 실행 ==================================

	while(1){
		cpy_reads = reads;        // file descriptor table은 일회성이기 때문에 복사 후 사용한다

		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;		// timeout 값 설정

		if((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
      // select 함수 사용 -> 관찰 대상의 변화를 감지
			break;

		if(fd_num == 0)
      // timeout으로 return되었을 경우
			continue;

		// 서버 소켓을 관찰 대상으로 지정해두고, 클라이언트가 새로 연결됨에 따라 관찰 대상으로 지정됨
		// select 함수 호출 후 변화가 발생한 지점은 1 그렇지 않은 부분은 모두 0으로 설정됨
		// cpy_reads를 두 번째 인자로 넘겨주었으니 read 준비가 되었다면 변화가 발생한 것

		for(int i = 0 ; i < fd_max + 1 ; i++)	{
			if(FD_ISSET(i, &cpy_reads)) {
				// 각 비트에 대해서 변화가 발생했는지 확인한다
				if(i == serv_sock) {
					// 서버 소켓에 변화가 있었다면
					adr_sz = sizeof(clnt_adr);
					clnt_sock =	accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
					FD_SET(clnt_sock, &reads);
					// 클라이언트의 연결 요청을 기다리고 클라이언트 소켓 또한 관찰 대상으로 지정한다

					if(fd_max < clnt_sock)
						// 새로 들어온 클라이언트 소켓의 file descriptor가 가장 큰 file descriptor라면 갱신
						fd_max = clnt_sock;

					printf("connected client: %d \n", clnt_sock); // 연결 확인
				}

				else {
					// 클라이언트 소켓에 변화가 있었다면
					str_len = read(i, buf, BUF_SIZE);			// 클라이언트 소켓으로부터 read

					if(str_len == 0){
						// read의 반환값이 0 -> 클라이언트 소켓이 종료되었음
						FD_CLR(i, &reads);									// 관찰 대상에서 제외 ( 0으로 set )
						close(i);														// 클라이언트 소켓 종료
						printf("closed client: %d \n", i);	// 연결 종료 확인
					}

					else{
						// read의 반환값이 0이 아니다
						struct sockaddr_in addr;
						socklen_t length = sizeof(addr);

						if (getpeername(i, (struct sockaddr *)&addr, &length) == 0){
							// 현재 확인 중에 있는 i번째 클라이언트의 주소 정보를 받아온다
							printf("==============================================\n");
					 		printf("Client`s IP : %s \n", inet_ntoa(addr.sin_addr));		// i번째 클라이언트의 IP주소 출력
 							printf("Client`s Port : %d \n", ntohs(addr.sin_port));			// i번째 클라이언트의 port 번호 출력
							time(&ltime);
							newtime = localtime(&ltime);
							printf("%s", asctime(newtime));															// asctime 함수를 이용해 문자열로 시간 출력
							write(1, buf, str_len);																			// i번째 클라이언트로부터 받아온 데이터를 출력
							printf("==============================================\n");
         		}

						for(int j = 0 ; j < fd_max + 1 ; j++){
							if(FD_ISSET(j, &reads)){
								if(j != serv_sock && j != i)
								// 관찰 대상 중 서버 소켓과 i번째 클라이언트를 제외하고
								// 나머지 관찰 대상에게 모두 데이터를 송신한다.
									write(j, buf, str_len);
							}
						}
					}
				}
			}
		}
	}

	close(serv_sock);
	// 서버 소켓 종료
	return 0;
}

void error_handling(char *buf){
	// 에러 발생 시
	fputs(buf, stderr);
	fputc('\n', stderr);
	exit(1);
}
