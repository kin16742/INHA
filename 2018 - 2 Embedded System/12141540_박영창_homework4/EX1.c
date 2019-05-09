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
#define TASK_STK_SIZE 512 /* Size of each task's stacks (# of WORDs)            */
#define RANDOM_TASKS 4
#define DECISION_TASK 1
#define MSG_QUEUE_SIZE 4
/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

OS_STK TaskStk[RANDOM_TASKS + DECISION_TASK][TASK_STK_SIZE];
OS_STK TaskStartStk[TASK_STK_SIZE];
INT8U TaskData[RANDOM_TASKS]; /* Parameters to pass to each task               */

char cmd;
OS_EVENT *RandomSem;

// Mail Box
OS_EVENT *Mbox_RandomNumbers[RANDOM_TASKS];
OS_EVENT *Mbox_Result[RANDOM_TASKS];

// Message Queue
OS_EVENT *MsgQueue_RandomNumbers;
OS_EVENT *MsgQueue_Result;

void *MsgQueue_RandomNumbers_Table[MSG_QUEUE_SIZE];
void *MsgQueue_Result_Table[MSG_QUEUE_SIZE];

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void TaskStart(void *data); /* Function prototypes of Startup task           */
static void TaskStartCreateTasks(void);
static void TaskStartDispInit(void);
static void TaskStartDisp(void);
static void RandomTask(void *pdata);
static void DecisionTask(void *pdata);

/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

void main(void) {
    printf("Command 1: mailbox, 2: message queue\n");
    scanf("%c", &cmd);
    if (cmd != '1' && cmd != '2') exit(1);

    PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK); /* Clear the screen                         */

    OSInit(); /* Initialize uC/OS-II                      */

    PC_DOSSaveReturn();        /* Save environment to return to DOS        */
    PC_VectSet(uCOS, OSCtxSw); /* Install uC/OS-II's context switch vector */

    RandomSem = OSSemCreate(RANDOM_TASKS);

    OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], 0);
    OSStart(); /* Start multitasking                       */
}

/*
*********************************************************************************************************
*                                              STARTUP TASK
*********************************************************************************************************
*/
static void TaskStart(void *pdata) {
#if OS_CRITICAL_METHOD == 3 /* Allocate storage for CPU status register */
    OS_CPU_SR cpu_sr;
#endif
    char s[100];
    INT16S key;
    INT8U i;

    pdata = pdata; /* Prevent compiler warning                 */

    TaskStartDispInit(); /* Initialize the display                   */

    OS_ENTER_CRITICAL();
    PC_VectSet(0x08, OSTickISR);      /* Install uC/OS-II's clock tick ISR        */
    PC_SetTickRate(OS_TICKS_PER_SEC); /* Reprogram tick rate                      */
    OS_EXIT_CRITICAL();

    OSStatInit(); /* Initialize uC/OS-II's statistics         */

    srand(time(0));

    TaskStartCreateTasks(); /* Create all the application tasks         */

    for (;;) {
        TaskStartDisp(); /* Update the display                       */

        if (PC_GetKey(&key) == TRUE) { /* See if key has been pressed              */
            if (key == 0x1B) {         /* Yes, see if it's the ESCAPE key          */
                PC_DOSReturn();        /* Return to DOS                            */
            }
        }

        OSCtxSwCtr = 0;            /* Clear context switch counter             */
        OSTimeDlyHMSM(0, 0, 1, 0); /* Wait one second                          */
    }
}

/*
*********************************************************************************************************
*                                        INITIALIZE THE DISPLAY
*********************************************************************************************************
*/

static void TaskStartDispInit(void) {
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

static void TaskStartDisp(void) {
    char s[80];

    sprintf(s, "%5d", OSTaskCtr); /* Display #tasks running               */
    PC_DispStr(18, 22, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

#if OS_TASK_STAT_EN > 0
    sprintf(s, "%3d", OSCPUUsage); /* Display CPU usage in %               */
    PC_DispStr(36, 22, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);
#endif

    sprintf(s, "%5d", OSCtxSwCtr); /* Display #context switches per second */
    PC_DispStr(18, 23, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

    sprintf(s, "V%1d.%02d", OSVersion() / 100, OSVersion() % 100); /* Display uC/OS-II's version number    */
    PC_DispStr(75, 24, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

    switch (_8087) { /* Display whether FPU present          */
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

static void TaskStartCreateTasks(void) {
	INT8U i;

	// cmd 값에 맞게
	if (cmd == '1') {
		// 1) Mail Box 초기화
		for (i = 0; i < RANDOM_TASKS; i++) {
			Mbox_RandomNumbers[i] = OSMboxCreate(NULL);
			Mbox_Result[i] = OSMboxCreate(NULL);
		}
	}
	else if (cmd == '2') {
		// 2) Message Queue 초기화
		MsgQueue_RandomNumbers = OSQCreate(MsgQueue_RandomNumbers_Table, MSG_QUEUE_SIZE);
		MsgQueue_Result = OSQCreate(MsgQueue_Result_Table, MSG_QUEUE_SIZE);
	}
	else exit(1);

	// Create RANDOM_TASKS & DECISION_TASK tasks
	OSTaskCreate(DecisionTask, (void*)0, &TaskStk[i][TASK_STK_SIZE - 1], 1);
	for (i = 0; i < RANDOM_TASKS; i++) {
		TaskData[i] = i + 1;
		OSTaskCreate(RandomTask, (void*)&TaskData[i], &TaskStk[i][TASK_STK_SIZE - 1], i + 2);
	}

}

/*
*********************************************************************************************************
*                                                  TASKS
*********************************************************************************************************
*/

//Colors
INT8U const colors[4] = {DISP_BGND_RED,
                         DISP_BGND_BLUE,
                         DISP_BGND_GREEN,
                         DISP_BGND_BROWN};

// Define maximum random number and tables
INT8U const myMapTbl[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
INT8U const myUnMapTbl[] = {
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0x00 to 0x0F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0x10 to 0x1F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0x20 to 0x2F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0x30 to 0x3F                             */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0x40 to 0x4F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0x50 to 0x5F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0x60 to 0x6F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0x70 to 0x7F                             */
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0x80 to 0x8F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0x90 to 0x9F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0xA0 to 0xAF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0xB0 to 0xBF                             */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0xC0 to 0xCF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0xD0 to 0xDF                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, /* 0xE0 to 0xEF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0  /* 0xF0 to 0xFF                             */
};

void RandomTask(void *pdata)  //task number를 인자로 받음
{
    INT8U err;
    
    INT8U number;
    char *result;
	char *data = (char*)pdata;

    INT8U dispX = ((*data) - 1) * 20;
    INT8U dispY = 5;

    while (1) {
        OSSemPend(RandomSem, 0, &err); /* Acquire semaphore to perform random numbers        */
        number = random(64);
        OSSemPost(RandomSem); /* Release semaphore                                  */

        // 화면에 생성된 숫자를 출력
		PC_DispChar(dispX++, dispY, 'T', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, 'a', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, 's', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, 'k', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, (*data) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ':', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);

		PC_DispChar(dispX++, dispY, (number / 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, (number % 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		PC_DispChar(dispX++, dispY, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
		// Mail Box, Massege Queue 각각의 경우 Random Number를 보내고 결과를 기다림
		if (cmd == '1') {
			OSMboxPost(Mbox_RandomNumbers[(*data) - 1], (void*)&number);
			result = (char*)OSMboxPend(Mbox_Result[(*data) - 1], 0, &err);
			
			PC_DispChar(dispX++, dispY, '[', DISP_FGND_WHITE + colors[*data - 1]);
			PC_DispChar(dispX++, dispY, ' ', DISP_FGND_WHITE + colors[*data - 1]);
			PC_DispChar(dispX++, dispY, (*result), DISP_FGND_WHITE + colors[*data - 1]);
			PC_DispChar(dispX++, dispY, ' ', DISP_FGND_WHITE + colors[*data - 1]);
			PC_DispChar(dispX++, dispY, ']', DISP_FGND_WHITE + colors[*data - 1]);

			if ((*result) == 'W') {
				for (dispY = 7; dispY < 21; dispY++) {
					for (dispX = 0; dispX < 80; dispX++) {
						PC_DispChar(dispX, dispY, ' ', colors[*data - 1]);
					}
				}
			}
		}
		else if (cmd == '2'){
			OSQPost(MsgQueue_RandomNumbers, &number);
			result = (char*)OSQPend(MsgQueue_Result, 0, &err);

			PC_DispChar(dispX++, dispY, '[', DISP_FGND_WHITE + colors[*data - 1]);
			PC_DispChar(dispX++, dispY, ' ', DISP_FGND_WHITE + colors[*data - 1]);
			PC_DispChar(dispX++, dispY, (*result), DISP_FGND_WHITE + colors[*data - 1]);
			PC_DispChar(dispX++, dispY, ' ', DISP_FGND_WHITE + colors[*data - 1]);
			PC_DispChar(dispX++, dispY, ']', DISP_FGND_WHITE + colors[*data - 1]); 

			if ((*result) == 'W') {
				for (dispY = 7; dispY < 21; dispY++) {
					for (dispX = 0; dispX < 80; dispX++) {
						PC_DispChar(dispX, dispY, ' ', colors[*data - 1]);
					}
				}
			}
		}

		dispX = ((*data) - 1) * 20;
		dispY = 5;
		OSTimeDlyHMSM(0, 0, 4, 0);
    }
}

void DecisionTask(void *pdata) {
	INT8U err;
	
	INT8U i;
	INT8U idx;
	INT8U chk;

	char *tmp;
	char W = 'W';
	char L = 'L';

	INT8U values[4];
	INT8U VAL;

	INT8U pX;
	INT8U pY;

	INT8U myRdyTbl[8];
	INT8U myRdyGrp;

	while (1) {
		chk = 0;
		// RdyTable 초기화
		myRdyGrp = 0;
		for (i = 0; i < 8; i++) myRdyTbl[i] = 0;

		if (cmd == '1') {
			for (i = 0; i < RANDOM_TASKS; i++) {
				tmp = (char*)OSMboxPend(Mbox_RandomNumbers[i], 0, &err);
				values[i] = *tmp;

				/*PC_DispChar(i*3, 6, (values[i] / 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
				PC_DispChar(i*3+1, 6, (values[i] % 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
				PC_DispChar(i*3+2, 6, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);*/

				myRdyGrp |= myMapTbl[values[i] / 8];
				myRdyTbl[values[i] / 8] |= myMapTbl[values[i] % 8];
			}

			pY = myUnMapTbl[myRdyGrp];
			pX = myUnMapTbl[myRdyTbl[pY]];
			VAL = pX + pY * 8;

			/*PC_DispChar(39, 7, (VAL / 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
			PC_DispChar(40, 7, (VAL % 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);*/
			for (i = 0; i < RANDOM_TASKS; i++) {
				if (VAL == values[i]) {
					OSMboxPost(Mbox_Result[i], (void*)&W);
					idx = i;
					break;
				}
			}

			for (i = 0; i < RANDOM_TASKS; i++) {
				if (i != idx) {
					OSMboxPost(Mbox_Result[i], (void*)&L);
				}
			}
		}
		else if (cmd == '2'){
			for (i = 0; i < RANDOM_TASKS; i++) {
				tmp = (char*)OSQPend(MsgQueue_RandomNumbers, 0, &err);
				values[i] = *tmp;

				/*PC_DispChar(i*3, 6, (values[i] / 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
				PC_DispChar(i*3+1, 6, (values[i] % 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
				PC_DispChar(i*3+2, 6, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);*/

				myRdyGrp |= myMapTbl[values[i] / 8];
				myRdyTbl[values[i] / 8] |= myMapTbl[values[i] % 8];
			}

			pY = myUnMapTbl[myRdyGrp];
			pX = myUnMapTbl[myRdyTbl[pY]];
			VAL = pX + pY * 8;
			/*PC_DispChar(39, 7, (VAL / 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
			PC_DispChar(40, 7, (VAL % 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);*/

 			for (i = 0; i < RANDOM_TASKS; i++) {
				if (VAL == values[i] && chk == 0) {
					OSQPost(MsgQueue_Result, (void*)&W);
					chk = 1;
				}
				else
					OSQPost(MsgQueue_Result, (void*)&L);					
			}
		}
		// 4개의 Random Number를 받음

		// 가장 작은 값을 찾음 

		// 각 Task에 해당 문자를 보내줌 W, L


		OSTimeDlyHMSM(0, 0, 4, 0);
	}
}