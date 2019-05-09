/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                           (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
*********************************************************************************************************
*/

#include "includes.h"


/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/
#define  TASK_STK_SIZE                 512       /* Size of each task's stacks (# of WORDs)            */
#define N_VOTING_TASKS					3
#define N_DECISION_TASK					1

#define  N_TASKS						N_VOTING_TASKS+N_DECISION_TASK                              /* Number of identical tasks      */

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

OS_STK        TaskStk[N_TASKS][TASK_STK_SIZE];        /* Tasks stacks                                  */
OS_STK        TaskStartStk[TASK_STK_SIZE];

char          TaskData[N_TASKS];                      /* Parameters to pass to each task               */

OS_EVENT	 *mutex;												   /* Semaphore										*/

OS_EVENT	 *MessageQueue;										   /* Message Queue									*/

void *MsgQueue_Table[N_VOTING_TASKS];

OS_FLAG_GRP  *s_grp;											   // Master Task에서 'O' 또는 'X'의 Count를 체크했는지 여부를 기록하는 Flag 
OS_FLAG_GRP  *m_grp;											   // Voting Task에서 'O'와 'X'를 임의로 생성한 여부를 기록하는 Flag 
OS_FLAG_GRP  *n_grp;											   // Decision Task에서 Master Task를 결정한 여부를 알려주기 위한 Flag 

INT8U  selectMasterTask;										   /* 결정 된 Master Task의 번호가 저장				*/

																   /* 생성 된 'O'와 'X'의 수가 저장 될 변수 */
INT8U  o_cnt;
INT8U  x_cnt;
/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  TaskStart(void *data);                  /* Function prototypes of Startup task           */
static  void  TaskStartCreateTasks(void);
static  void  TaskStartDispInit(void);
static  void  TaskStartDisp(void);
static void VotingTask(void *pdata);
static void DecisionTask(void *pdata);

/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

void  main(void)
{
	INT8U err;

	PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);      /* Clear the screen                         */

	OSInit();                                              /* Initialize uC/OS-II                      */

	PC_DOSSaveReturn();                                    /* Save environment to return to DOS        */
	PC_VectSet(uCOS, OSCtxSw);                             /* Install uC/OS-II's context switch vector */

	OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], 0);
	OSStart();                                             /* Start multitasking                       */
}


/*
*********************************************************************************************************
*                                              STARTUP TASK
*********************************************************************************************************
*/
static void  TaskStart(void *pdata)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
	OS_CPU_SR  cpu_sr;
#endif
	char       s[100];
	INT16S     key;
	INT8U i;

	pdata = pdata;                                         /* Prevent compiler warning                 */

	TaskStartDispInit();                                   /* Initialize the display                   */

	OS_ENTER_CRITICAL();
	PC_VectSet(0x08, OSTickISR);                           /* Install uC/OS-II's clock tick ISR        */
	PC_SetTickRate(OS_TICKS_PER_SEC);                      /* Reprogram tick rate                      */
	OS_EXIT_CRITICAL();

	OSStatInit();                                          /* Initialize uC/OS-II's statistics         */

	srand(time(0));


	TaskStartCreateTasks();                                /* Create all the application tasks         */

	for (;;) {
		TaskStartDisp();                                  /* Update the display                       */

		if (PC_GetKey(&key) == TRUE) {                     /* See if key has been pressed              */
			if (key == 0x1B) {                             /* Yes, see if it's the ESCAPE key          */
				PC_DOSReturn();                            /* Return to DOS                            */
			}
		}

		OSCtxSwCtr = 0;                                    /* Clear context switch counter             */
		OSTimeDlyHMSM(0, 0, 1, 0);                         /* Wait one second                          */
	}
}

/*
*********************************************************************************************************
*                                        INITIALIZE THE DISPLAY
*********************************************************************************************************
*/

static  void  TaskStartDispInit(void)
{
	/*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
	/*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
	PC_DispStr(0, 0, "                         uC/OS-II, The Real-Time Kernel                         ", DISP_FGND_WHITE + DISP_BGND_RED + DISP_BLINK);
	PC_DispStr(0, 1, "                                Embedded System 2                               ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 2, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 3, "                                     Lab. #6                                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 4, "                                                                                ", DISP_FGND_BLUE + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 5, "                                                                                ", DISP_FGND_BLUE + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 6, "                                                                                ", DISP_FGND_BLUE + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 7, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 8, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 9, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 10, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 11, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 12, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 13, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 14, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 15, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 16, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 17, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 18, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 19, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 20, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 21, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 22, "#Tasks          :        CPU Usage:     %                                       ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 23, "#Task switch/sec:                                                               ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 24, "                            <-PRESS 'ESC' TO QUIT->                             ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY + DISP_BLINK);
	/*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
	/*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
}

/*
*********************************************************************************************************
*                                           UPDATE THE DISPLAY
*********************************************************************************************************
*/

static  void  TaskStartDisp(void)
{
	char   s[80];


	sprintf(s, "%5d", OSTaskCtr);                                  /* Display #tasks running               */
	PC_DispStr(18, 22, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

#if OS_TASK_STAT_EN > 0
	sprintf(s, "%3d", OSCPUUsage);                                 /* Display CPU usage in %               */
	PC_DispStr(36, 22, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);
#endif

	sprintf(s, "%5d", OSCtxSwCtr);                                 /* Display #context switches per second */
	PC_DispStr(18, 23, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

	sprintf(s, "V%1d.%02d", OSVersion() / 100, OSVersion() % 100); /* Display uC/OS-II's version number    */
	PC_DispStr(75, 24, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

	switch (_8087) {                                               /* Display whether FPU present          */
	case 0:
		PC_DispStr(71, 22, " NO  FPU ", DISP_FGND_YELLOW + DISP_BGND_BLUE);
		break;

	case 1:
		PC_DispStr(71, 22, " 8087 FPU", DISP_FGND_YELLOW + DISP_BGND_BLUE);
		break;

	case 2:
		PC_DispStr(71, 22, "80287 FPU", DISP_FGND_YELLOW + DISP_BGND_BLUE);
		break;

	case 3:
		PC_DispStr(71, 22, "80387 FPU", DISP_FGND_YELLOW + DISP_BGND_BLUE);
		break;
	}
}

/* You can write your own program here... */
/*
*********************************************************************************************************
*                                             CREATE TASKS
*********************************************************************************************************
*/

static  void  TaskStartCreateTasks(void)
{
	INT8U	i;
	INT8U	err;
	// 메시지 큐 초기화, 이벤트 플래그 초기화, 뮤텍스 초기화
	mutex = OSMutexCreate(10, &err);
	MessageQueue = OSQCreate(MsgQueue_Table, N_VOTING_TASKS);
	s_grp = OSFlagCreate(0x00, &err);											   
	m_grp = OSFlagCreate(0x00, &err);
	n_grp = OSFlagCreate(0x00, &err);											   

	// Decision, Voting Task 생성 및 Voting Task 인자 넘겨줌
	for (i = 0; i < N_VOTING_TASKS; i++) {
		TaskData[i] = i;
		OSTaskCreate(VotingTask, (void *)&TaskData[i], &TaskStk[i][TASK_STK_SIZE - 1], i + 1);
	}
	OSTaskCreate(DecisionTask, (void *)0, &TaskStk[i][TASK_STK_SIZE - 1], i + 1);

}

/*
*********************************************************************************************************
*                                                  TASKS
*********************************************************************************************************
*/


void  VotingTask(void *pdata)
{
	/* 변수 선언부 */
	INT8U  i;
	INT8U  err;					// err 정보 저장
	INT8U number;
	INT8U number_of_votingtask;
	INT8U flagP = 1;
	INT8U dispX;
	INT8U dispY;
	INT8U cntO;
	INT8U cntX;
	char vote;
	char *tmp;

	number_of_votingtask = *(INT8U*)pdata;	// 인자 저장

	for (i = 0; i < number_of_votingtask; i++) flagP *= 2;

	while (1) {
		dispX = number_of_votingtask * 30;
		dispY = 5;
		cntO = 0;
		cntX = 0;
		// Random으로 0 또는 1을 생성하고, 0인 경우 'O', 1인 경우 'X'의 값을 생성해줌
		number = random(2);
		if (number == 0)
			vote = 'O';
		else if (number == 1)
			vote = 'X';

		// Voting Task 번호 출력 
		PC_DispChar(dispX++, dispY, 'T', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, 'a', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, 's', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, 'k', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, number_of_votingtask + 49, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ':', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);

		// Decision Task로 Post, 3개의 Voting Task가 모두 Post하면 Master Task를 결정하도록 해줌 
		OSFlagPost(m_grp, flagP, OS_FLAG_SET, &err);

		// Decision Task가 Master Task를 결정할 때 까지 Wait 
		OSFlagPend(n_grp, flagP, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, 0, &err);

		// Master Task가 결정되었을 때, 해당 Task의 Number가 결정 된 Master Task 같은 경우 아래의 조건문으로 들어가며, 다른 경우, else문 으로 들어감 
		if (selectMasterTask == number_of_votingtask) {
			// Master Task
			// Cyan O, X 칠함
			// Message Queue를 통해서 값('O' 또는 'X')을 전달받음
			// Master Task는 자신이 생성한 값과 나머지 Task들로 부터 받은 값을 가지고 'O'와 'X'의 수를 계산함. 
			// Mutex를 사용하여 공유 변수 보호 
			// 하나의 값을 체크(카운트 증가) 할 때 마다 Event Flag의 Flag bit를 하나씩 Set 해줌 

			PC_DispChar(dispX++, dispY, '[', DISP_FGND_WHITE + DISP_BGND_CYAN);
			PC_DispChar(dispX++, dispY, ' ', DISP_FGND_WHITE + DISP_BGND_CYAN);
			PC_DispChar(dispX++, dispY, vote, DISP_FGND_WHITE + DISP_BGND_CYAN);
			PC_DispChar(dispX++, dispY, ' ', DISP_FGND_WHITE + DISP_BGND_CYAN);
			PC_DispChar(dispX++, dispY, ']', DISP_FGND_WHITE + DISP_BGND_CYAN);
			
			OSMutexPend(mutex, 0, &err);

			if (vote == 'O') cntO++;
			else if (vote == 'X') cntX++;
			OSFlagPost(s_grp, 0x01, OS_FLAG_SET, &err);

			for (i = 1; i < N_VOTING_TASKS; i++) {
				tmp = (char*)OSQPend(MessageQueue, 0, &err);

				if (*tmp == 'O') {
					cntO++;
				}
				else if (*tmp == 'X') {
					cntX++;
				}

				OSFlagPost(s_grp, 2 * i, OS_FLAG_SET, &err);
			}

			o_cnt = cntO;
			x_cnt = cntX;

			OSMutexPost(mutex);
		}
		else {
			// else
			// Black으로 O, X 칠함 
			// Message Queue로 값 전달
			
			PC_DispChar(dispX++, dispY, '[', DISP_FGND_WHITE + DISP_BGND_BLACK);
			PC_DispChar(dispX++, dispY, ' ', DISP_FGND_WHITE + DISP_BGND_BLACK);
			PC_DispChar(dispX++, dispY, vote, DISP_FGND_WHITE + DISP_BGND_BLACK);
			PC_DispChar(dispX++, dispY, ' ', DISP_FGND_WHITE + DISP_BGND_BLACK);
			PC_DispChar(dispX++, dispY, ']', DISP_FGND_WHITE + DISP_BGND_BLACK);

			OSQPost(MessageQueue, &vote);
		}
		OSTimeDlyHMSM(0, 0, 4, 0);
	}
}

void  DecisionTask(void *pdata)
{
	/* 변수 선언부 */
	INT8U  err;
	INT8U  i;
	INT8U dispX;
	INT8U dispY;
	// avoid compiler warning prevention
	pdata = pdata;

	while (1) { 
		// 변수 초기화

		// Voting Task에서 O와 X가 모두 생성될 때 까지 Wait
		OSFlagPend(m_grp, 0x07, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, 0, &err);

		// Voting Task에서 O와 X가 모두 생성되면, Master Task를 결정하기 위해서 Random Number 생성 
		selectMasterTask = random(3);

		// Master Task가 결정되면, Waiting 상태의 Voting Task들에게 Post 
		for (i = 1; i <= 4; i *= 2) OSFlagPost(n_grp, i, OS_FLAG_SET, &err);

		// Master Task가 'O'와 'X'의 수를 체크할 때까지 Wait
		OSFlagPend(s_grp, 0x07, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, 0, &err);

		// O, X 개수에 따라서 화면 색칠
		if (o_cnt > x_cnt) {
			for (dispY = 7; dispY < 21; dispY++) {
				for (dispX = 0; dispX < 80; dispX++) {
					PC_DispChar(dispX, dispY, ' ', DISP_BGND_BLUE);
				}
			}
		}
		else {
			for (dispY = 7; dispY < 21; dispY++) {
				for (dispX = 0; dispX < 80; dispX++) {
					PC_DispChar(dispX, dispY, ' ', DISP_BGND_RED);
				}
			}
		}
	}
}