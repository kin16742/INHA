#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf, char *name);

int main(int argc, char *argv[]){
  int sock;                           // 소켓
  struct sockaddr_in serv_adr;        // 서버 소켓의 주소 정보

	fd_set reads, cpy_reads;            // file descriptor set와 그 복사본으로 사용할 것
  int fd_max, fd_num;                 // descriptor 중 가장 큰 값, select 함수의 반환 값
	struct timeval timeout;             // select 함수에 인자로 넘겨 줄 timeout 값

  char buf[BUF_SIZE];                 // 주고 받을 데이터

  if(argc!=4){
    // command line 인자로 IP주소, port 번호, 사용자 이름을 받는다
    printf("Usage : %s <port> <name>\n", argv[0]);
    exit(1);
  }

// ======================================== 소켓 생성 ========================================

  sock = socket(PF_INET, SOCK_STREAM, 0);
  // 인자 순서대로 프로토콜 체계 정보 / 데이터 전송 방식 / 통신에 사용될 프로토콜 정보를 지정
  if(sock==-1)
    // 소켓 생성 및 정보 지정에 실패했을 경우 file descriptor는 -1로 return
    error_handling("socket() error");


// ================================== 서버 소켓 주소 할당 ====================================

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;                  // 주소 체계 할당
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]);  // 인자로 받은 IP주소 할당
  serv_adr.sin_port = htons(atoi(argv[2]));       // 인자로 받은 port 번호 할당

// ======================================== 서버 연결 ========================================

  if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
    // 서버 소켓에 연결한다
    error_handling("connect() error");
  else
    puts("Connected~~~~~");

// =============================== file descriptor set 초기화 ================================

  FD_ZERO(&reads);      // reads의 모든 비트를 전부 0으로 초기화
	FD_SET(sock, &reads); // 소켓을 관찰 대상으로 추가
  FD_SET(0, &reads);    // 표준 입력을 관찰 대상으로 추가
	fd_max = sock;        // 현재 가장 큰 file descriptor = 소켓

// ============================== select 결과에 따른 함수 실행 ================================

  while(1){
		cpy_reads = reads;        // file descriptor table은 일회성이기 때문에 복사 후 사용한다

		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;   // timeout 값 설정

    if((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
      // select 함수 사용 -> 관찰 대상의 변화를 감지
      break;

    if(fd_num == 0)
      // timeout으로 return되었을 경우
      continue;

    // 현재 소켓, 표준 입력을 관찰 대상으로 지정해뒀으니
    // select 함수 호출 후 변화가 발생한 지점은 1 그렇지 않은 부분은 모두 0으로 설정됨
    // cpy_reads를 두 번째 인자로 넘겨주었으니 read 준비가 되었다면 변화가 발생한 것

    if(FD_ISSET(sock, &cpy_reads)){
      // 소켓에 대한 변화가 있었다면 read_routine
      read_routine(sock, buf);
    }
    else if(FD_ISSET(0, &cpy_reads)){
      // 입력에 대한 변화가 있었다면 write_routine
      // command line 인자로 받은 사용자 이름을 인자로 넘겨준다.
      write_routine(sock, buf, argv[3]);
    }
  }

  close(sock);
  // 소켓 연결 종료
  return 0;
}

void error_handling(char *message){
  // 에러 발생 시
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}

void read_routine(int sock, char *buf){
  int str_len = read(sock, buf, BUF_SIZE); // 소켓으로부터 read

  if(str_len == 0)
    // 소켓으로부터 read한 값이 없을 경우 ( 서버가 종료 )
    exit(1);

  buf[str_len] = 0;
  printf("%s", buf);                       // 단순히 소켓으로부터 받은 데이터 출력
}

void write_routine(int sock, char* buf, char* name){
  char buf2[BUF_SIZE];

  fgets(buf, BUF_SIZE, stdin);             // buf에 데이터를 입력받는다

  if(!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
    // 입력 종료
    exit(1);

  sprintf(buf2, "[%s] : %s", name, buf);   // buf2에 데이터를 형식에 맞게 저장
  write(sock, buf2, strlen(buf2));         // 소켓에 buf2의 데이터를 write
}
