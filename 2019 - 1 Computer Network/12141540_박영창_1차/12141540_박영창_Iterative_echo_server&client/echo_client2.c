#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]){
  int sock;                               // client 소켓의 file descriptor
  char message[BUF_SIZE];                 // 주고 받을 데이터
  int str_len, recv_len, recv_cnt;        // 서버로 보낼 데이터의 크기, 서버로부터 받은 데이터의 크기, 서버로부터 받은 데이터와 보낸 데이터의 크기 비교를 위한 변수

  struct sockaddr_in serv_adr;            // 연결할 server 소켓의 주소 정보 구조체

  if(argc!=3){
    // command line 인자로 IP주소와 port 번호를 받는다
    printf("Usage : %s <port>\n", argv[0]);
    exit(1);
  }

  // 1. socket() - 소켓 생성

  sock=socket(PF_INET, SOCK_STREAM, 0);
  // 인자 순서대로 프로토콜 체계 정보 / 데이터 전송 방식 / 통신에 사용될 프로토콜 정보를 지정
  if(sock==-1)
    // 소켓 생성 및 정보 지정에 실패했을 경우 file descriptor는 -1로 return
    error_handling("socket() error");

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;                  // 주소 체계 할당
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]);  // 인자로 받은 IP주소 할당
  serv_adr.sin_port = htons(atoi(argv[2]));       // 인자로 받은 port 번호 할당

  // 2. connect() - 서버 연결

  if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
    // server 소켓에 연결한다
    error_handling("connect() error");
  else
    puts("Connected~~~~~");

  while(1){
    fputs("Input message(Q to quit): ", stdout);
    fgets(message, BUF_SIZE, stdin);
    // 주고 받을 데이터를 입력받는다

    if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
    // q를 입력 받으면 반복문 종료
      break;

    str_len = write(sock, message, strlen(message));
    // 입력받은 데이터를 server로 전송

    // 3. read() / write() - 데이터 송수신

    recv_len = 0;
    while(recv_len < str_len){
      recv_cnt = read(sock, &message[recv_len], BUF_SIZE - 1);
      // server로부터 받은 데이터의 길이를 확인하여 문제 해결
      if(recv_cnt == -1)
        error_handling("read() error!");
      recv_len += recv_cnt;
    }
    message[recv_len] = 0;
    printf("Message from server: %s", message);
  }

  close(sock);
  // 소켓 연결 종료
  return 0;
}

void error_handling(char *message){
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
