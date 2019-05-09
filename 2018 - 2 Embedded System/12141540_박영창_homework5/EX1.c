/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                           (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
*                                               EXAMPLE #1
*********************************************************************************************************
*/

#include "includes.h"
/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/
 
#define  TASK_STK_SIZE                 512       /* Size of each task's stacks (# of WORDs)            */
#define  N_RANDOM_TASKS                         4       /* Number of identical tasks                          */
#define  N_DECISION_TASKS                       1
/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

OS_STK        TaskDecisionStk[TASK_STK_SIZE];   
OS_STK        TaskRandomStk[N_RANDOM_TASKS][TASK_STK_SIZE];        /* Tasks stacks                                  */
OS_STK        TaskStartStk[TASK_STK_SIZE];

OS_EVENT     *Sem;                                                 /* Semaphore                                     */

// Event Flag
OS_FLAG_GRP  *s_grp;            
OS_FLAG_GRP  *r_grp;
/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

        void  RandomTask(void *pdata);                       /* Function prototypes of tasks                  */
        void  DecisionTask(void *pdata);                       /* Function prototypes of tasks                  */
        void  TaskStart(void *pdata);                  /* Function prototypes of Startup task           */
static  void  TaskStartCreateTasks(void);
static  void  TaskStartDispInit(void);
static  void  TaskStartDisp(void);

/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/
int C;

char receive_array[N_RANDOM_TASKS]; 
int send_array[N_RANDOM_TASKS]; 
INT8U TaskData[N_RANDOM_TASKS];

void  main (void)
{
    srand((unsigned int)time(0));
    PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);      /* Clear the screen                         */

    OSInit();                 

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
void  TaskStart (void *pdata)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif
    char       s[100];
    INT16S     key;
    int err;

    pdata = pdata;                                         /* Prevent compiler warning                 */
   
    

    TaskStartDispInit();                                   /* Initialize the display                   */

    OS_ENTER_CRITICAL();
    PC_VectSet(0x08, OSTickISR);                           /* Install uC/OS-II's clock tick ISR        */
    PC_SetTickRate(OS_TICKS_PER_SEC);                      /* Reprogram tick rate                      */
    OS_EXIT_CRITICAL();

    OSStatInit();                                          /* Initialize uC/OS-II's statistics         */

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

/*$PAGE*/
/*
*********************************************************************************************************
*                                        INITIALIZE THE DISPLAY
*********************************************************************************************************
*/

static  void  TaskStartDispInit (void)
{
/*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
/*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
    PC_DispStr( 0,  0, "                         uC/OS-II, The Real-Time Kernel                         ", DISP_FGND_WHITE + DISP_BGND_RED + DISP_BLINK);
    PC_DispStr( 0,  1, "                                Jean J. Labrosse                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  2, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  3, "                                    EXAMPLE #1                                  ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  4, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  5, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  6, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  7, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  8, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  9, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 10, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 11, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 12, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 13, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 14, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 15, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 16, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 17, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 18, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 19, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 20, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 21, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 22, "#Tasks          :        CPU Usage:     %                                       ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 23, "#Task switch/sec:                                                               ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0, 24, "                            <-PRESS 'ESC' TO QUIT->                             ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY + DISP_BLINK);
/*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
/*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                           UPDATE THE DISPLAY
*********************************************************************************************************
*/

static  void  TaskStartDisp (void)
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

/*$PAGE*/
/*
*********************************************************************************************************
*                                             CREATE TASKS
*********************************************************************************************************
*/

static  void  TaskStartCreateTasks (void)
{
    INT8U	i;
	INT8U err;
	
	Sem = OSSemCreate(N_RANDOM_TASKS);

	s_grp = OSFlagCreate(0x00, &err);
	r_grp = OSFlagCreate(0x00, &err);

    // Task Create
	for(i = 0; i < N_RANDOM_TASKS; i++){
		TaskData[i] = i;
		OSTaskCreate(RandomTask, (void *)&TaskData[i], &TaskRandomStk[i][TASK_STK_SIZE - 1], i + 1);
	}
	OSTaskCreate(DecisionTask, (void *)0, &TaskDecisionStk[TASK_STK_SIZE - 1], i + 1);
}

//Colors
INT8U const colors[4] = { DISP_BGND_RED,
DISP_BGND_BLUE,
DISP_BGND_GREEN,
DISP_BGND_BROWN };

// Define maximum random number and tables
#define MAX_RANDOM_NUMBER 64
INT8U  const  myMapTbl[]   = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
INT8U  const  myUnMapTbl[] = {
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x00 to 0x0F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x10 to 0x1F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x20 to 0x2F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x30 to 0x3F                             */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x40 to 0x4F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x50 to 0x5F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x60 to 0x6F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x70 to 0x7F                             */
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x80 to 0x8F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x90 to 0x9F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xA0 to 0xAF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xB0 to 0xBF                             */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xC0 to 0xCF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xD0 to 0xDF                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xE0 to 0xEF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0        /* 0xF0 to 0xFF                             */
};
// Color circulation
/*
*********************************************************************************************************
*                                                  TASKS
*********************************************************************************************************
*/

void  RandomTask (void *pdata)
{
	INT8U i;
	INT8U err;
	INT8U number; 
	INT8U number_of_randomtask;
	INT8U flagP = 1;

	INT8U dispX;
	INT8U dispY;

	number_of_randomtask=*(INT8U*)pdata;

	dispX = number_of_randomtask * 20;
	dispY = 5;

	for (i = 0; i < number_of_randomtask; i++) flagP *= 2;

    while(1){
		OSSemPend(Sem, 0, &err);
		number = random(64);
		send_array[number_of_randomtask] = number;
		OSSemPost(Sem);

		// 숫자 생성
		PC_DispChar(dispX++, dispY, 'T', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, 'a', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, 's', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, 'k', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, number_of_randomtask + 49, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ':', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);

		PC_DispChar(dispX++, dispY, (number / 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, (number % 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		
		OSFlagPost(s_grp, flagP, OS_FLAG_SET, &err);
		// Send_Array[i]에 데이터 저장, 출력 후 기다림

		OSFlagPend(r_grp, flagP, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, 0, &err);
        // Receive_Array[i] 받고 결과 출력

		OSSemPend(Sem, 0, &err);

		PC_DispChar(dispX++, dispY, '[', DISP_FGND_WHITE + colors[number_of_randomtask]);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_WHITE + colors[number_of_randomtask]);
		PC_DispChar(dispX++, dispY, receive_array[number_of_randomtask], DISP_FGND_WHITE + colors[number_of_randomtask]);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_WHITE + colors[number_of_randomtask]);
		PC_DispChar(dispX++, dispY, ']', DISP_FGND_WHITE + colors[number_of_randomtask]);

		if (receive_array[number_of_randomtask] == 'W') {
			for (dispY = 7; dispY < 21; dispY++) {
				for (dispX = 0; dispX < 80; dispX++) {
					PC_DispChar(dispX, dispY, ' ', colors[number_of_randomtask]);
				}
			}
		}

		OSSemPost(Sem);

		dispX = number_of_randomtask * 20;
		dispY = 5;
        OSTimeDlyHMSM(0, 0, 4, 0);
    }
}

void  DecisionTask (void *pdata)
{
	INT8U i;
	INT8U chk;
	INT8U err;

	INT8U myRdyTbl[8];
	INT8U myRdyGrp;

	INT8U pX;
	INT8U pY;
	INT8U VAL;

	pdata=pdata;   

    while(1){
		chk = 0;

		myRdyGrp = 0;
		for (i = 0; i < 8; i++) myRdyTbl[i] = 0;
		// RdyTable 초기화

		OSFlagPend(s_grp, 0x0F, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, 0, &err);
        // 4개의 Random Number를 받을때 까지 기다림

		OSSemPend(Sem, 0, &err);

		for (i = 0; i < N_RANDOM_TASKS; i++) {
			myRdyGrp |= myMapTbl[send_array[i] / 8];
			myRdyTbl[send_array[i] / 8] |= myMapTbl[send_array[i] % 8];
		}

		pY = myUnMapTbl[myRdyGrp];
		pX = myUnMapTbl[myRdyTbl[pY]];
		VAL = pX + pY * 8;
        // 가장 작은 값을 찾음 

		for (i = 0; i < N_RANDOM_TASKS; i++) {
			if (VAL == send_array[i] && chk == 0) {
				receive_array[i] = 'W';
				chk = 1;
			}
			else
				receive_array[i] = 'L';
		}

		OSSemPost(Sem);
        // Receive_Array에 값 저장

		for (i = 1; i <= 8; i *= 2) OSFlagPost(r_grp, i, OS_FLAG_SET, &err);
    }
}
