#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);
void read_childproc(int sig);

int main(int argc, char *argv[]){
  int serv_sock, clnt_sock;                   // server 소켓의 file descriptor / 연결할 client 소켓의 file descriptor
  struct sockaddr_in serv_adr, clnt_adr;      // server 소켓과 client 소켓의 주소 정보 구조체

  pid_t pid;                    // fork() 호출 후 부모/자식을 구분하는 process id
  struct sigaction act;         // signal handling에 사용할 sigaction 구조체
  socklen_t adr_sz;             // client 소켓의 주소 정보의 크기
  int str_len, state;           // 주고 받을 데이터의 크기 / sigaction()의 반환값을 저장할 변수 (?)
  char buf[BUF_SIZE];           // 주고 받을 데이터

  if(argc!=2){
    // command line 인자로 port 번호를 받는다.
    printf("Usage : %s <port>\n", argv[0]);
    exit(1);
  }

  act.sa_handler = read_childproc;      // siganl handler 함수 설정
  sigemptyset(&act.sa_mask);            // signal handling mask 초기화
  act.sa_flags = 0;                     // signal handling flag 초기화
  state = sigaction(SIGCHLD, &act, 0);  // SIGCHLD의 signal handling을 act 구조체의 정보로 지정

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  // 인자 순서대로 프로토콜 체계 정보 / 데이터 전송 방식 / 통신에 사용될 프로토콜 정보를 지정
  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;                  // 주소 체계 할당
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);   // 서버 소켓의 주소 설정
  serv_adr.sin_port = htons(atoi(argv[1]));       // 인자로 받은 port 번호 할당

  if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
  // 주소 정보 구조체에 저장된 정보를 server 소켓에 설정
    error_handling("bind() error");

  if(listen(serv_sock, 5)==-1)
  // 연결 요청 대기상태로 두고, 연결 요청 대기 큐의 크기 설정
    error_handling("listen() error");

  while(1){
    adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
    // client 소켓에서 연결 요청이 올 때까지 block 상태, 연결이 되었다면 ??

    if(clnt_sock == -1)
    // 연결 오류 발생 시 -1 반환 -> continue
      continue;
    else
    // 연결 성공 시 아래 코드 실행
      puts("new client connected!!");

      pid = fork(); // fork() 호출로 자식 프로세스 생성,
      // 메모리 / 코드 / file descriptor를 복사
      // socket은 복사하지 않지만 부모/자식 모두 접근 가능
      // 부모 프로세스에서는 자식 프로세스 id를 반환
      // 자식 프로세스에서는 0을 반환

      if(pid == -1){
        // fork() 에러 발생시
        close(clnt_sock);
        continue;
      }

      if(pid == 0){
        // 자식 프로세스 실행 부분
        close(serv_sock); // 서버 소켓과의 연결을 종료해 클라이언트와 통신하는 역할만 수행
        while((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)
        // client와 데이터 송수신
          write(clnt_sock, buf, str_len);

        close(clnt_sock);
        // 데이터 송수신 종료 후 client와의 연결 종료
        puts("client disconnected!!");

        return 0;
        // 연결 종료 후 프로세스도 종료 -> time wait 상태 됨
      }

      else{
        // 부모 프로세스 실행 부분
        printf("child process pid : %d \n", pid);                     // 자식 프로세스 id 출력
        printf("Client`s IP : %s \n", inet_ntoa(clnt_adr.sin_addr));  // client의 IP주소 출력
        // inet_ntoa 함수를 사용해 IPv4 주소를 문자열로 변환
        printf("Client`s Port : %d \n", ntohs(clnt_adr.sin_port));    // client의 port 출력
        // ntohs 함수를 사용해 네트워크 정렬 방식(Big Endian)으로 정렬된 2바이트 데이터를 호스트 바이트 정렬 방식으로 변환
        close(clnt_sock);
        // client 소켓을 종료 후 server의 역할만 수행
      }
  }
  close(serv_sock); // 모든 작업을 수행한 뒤 server 소켓 close
  return 0;
}

void read_childproc(int sig){
  // signal handler로 지정할 함수
  pid_t pid;
  int status;
  pid = waitpid(-1, &status, WNOHANG);    // 임의의 자식 프로세스가 종료되었을 때 blocking 없이 반환
  printf("removed proc id : %d \n", pid); // 종료된 자식 프로세스의 id를 출력
}

void error_handling(char *message){
  // error 메세지를 출력
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
