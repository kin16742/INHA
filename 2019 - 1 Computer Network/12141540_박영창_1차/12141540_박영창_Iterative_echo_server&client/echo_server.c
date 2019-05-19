#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]){
  int serv_sock, clnt_sock;         // server 소켓의 file descriptor / 연결할 client 소켓의 file descriptor
  char message[BUF_SIZE];           // 주고 받을 데이터
  int str_len, i;                   // 주고 받을 데이터의 크기 / 반복문에 사용할 변수

  struct sockaddr_in serv_adr, clnt_adr;  // server 소켓과 client 소켓의 주소 정보 구조체
  socklen_t clnt_adr_sz;                  // client 소켓의 주소 정보의 크기

  if(argc!=2){
    // command line 인자로 port 번호를 받는다.
    printf("Usage : %s <port>\n", argv[0]);
    exit(1);
  }

  // 1. socket() - 소켓 생성

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  // 인자 순서대로 프로토콜 체계 정보 / 데이터 전송 방식 / 통신에 사용될 프로토콜 정보를 지정
  if(serv_sock==-1)
    // 소켓 생성 및 정보 지정에 실패했을 경우 file descriptor는 -1로 return
    error_handling("socket() error");

  // 2. bind() - 소켓 주소 할당

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;                    // 주소 체계 할당
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);     // 서버 소켓의 주소 설정
  serv_adr.sin_port = htons(atoi(argv[1]));         // 인자로 받은 port 번호 할당

  if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
  // 주소 정보 구조체에 저장된 정보를 server 소켓에 설정
    error_handling("bind() error");

  // 3. listen() - 연결 요청 대기 상태

  if(listen(serv_sock, 2) == -1)
  // 서버 소켓의 file descriptor를 연결 요청 대기상태로 두고,
  // 연결 요청 대기 큐의 크기를 설정
    error_handling("listen() error");

  clnt_adr_sz = sizeof(clnt_adr);

  for(i=0;i<2;i++){

    // 4. accept() - 연결 허용

    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
    // client 소켓에서 연결 요청이 올 때까지 block 상태가 된다!
    if(clnt_sock == -1)
    // client 소켓에 error가 있다면 file descriptor는 -1을 return
      error_handling("accept() error");
    else
      printf("Connected client %d \n", i+1);

    // 5. read() / write() - 데이터 송수신

    while((str_len=read(clnt_sock, message, BUF_SIZE)) != 0)
    // client로부터 message를 read하고 client에게 받은 message를 그대로 write
      write(clnt_sock, message, str_len);

    close(clnt_sock);
    // 데이터 read/write가 끝난 뒤 client와의 연결 종료
  }
  close(serv_sock);
  // 모든 작업을 수행한 뒤 server 소켓 close
  return 0;
}

void error_handling(char *message){
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
