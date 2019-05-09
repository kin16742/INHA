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
#include <time.h>
#include <string.h>

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE                 512       /* Size of each task's stacks (# of WORDs)            */
#define  N_TASKS                         1       /* Number of identical tasks                          */

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

OS_STK        TaskStk[N_TASKS][TASK_STK_SIZE];        /* Tasks stacks                                  */
OS_STK        TaskStartStk[TASK_STK_SIZE];

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  Task(void *data);                       /* Function prototypes of tasks                  */
void  TaskStart(void *data);                  /* Function prototypes of Startup task           */
static  void  TaskStartCreateTasks(void);
static  void  TaskStartDispInit(void);
static  void  TaskStartDisp(void);

/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/
int cmd;
void  main(void)
{
	scanf("%d", &cmd);

	srand(time(NULL));
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
void  TaskStart(void *pdata)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
	OS_CPU_SR  cpu_sr;
#endif
	char       s[100];
	INT16S     key;
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

static  void  TaskStartDispInit(void)
{
	/*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
	/*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
	PC_DispStr(0, 0, "                         uC/OS-II, The Real-Time Kernel                         ", DISP_FGND_WHITE + DISP_BGND_RED + DISP_BLINK);
	PC_DispStr(0, 1, "                                Jean J. Labrosse                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 2, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 3, "                                    EXAMPLE #1                                  ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 4, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 5, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
	PC_DispStr(0, 6, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
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

/*$PAGE*/
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

/*$PAGE*/
/*
*********************************************************************************************************
*                                             CREATE TASKS
*********************************************************************************************************
*/

static  void  TaskStartCreateTasks(void)
{
	OSTaskCreate(Task, (void *)0, &TaskStk[0][TASK_STK_SIZE - 1], 1);
}

// Define maximum random number and tables
INT8U  const  myMapTbl[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
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
INT8U const  myUnMapTbl_max[] = {
	0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
}; 
/*
*********************************************************************************************************
*                                                  TASKS
*********************************************************************************************************
*/

void  Task(void *pdata)
{
	// Variable declaration section
	INT8U  myRdyTbl[8]; // 과정이 새로 시작될 때 초기화 해줘야 함
	INT8U  myRdyGrp; // 과정이 새로 시작될 때변수들 적절한 시기에 초기화 해줘야 함
					 // For compiler warning OR Command 1: mandatory, 2: optional
	INT8U colorCount = 0;
	INT8U tmp = 0;
	INT8U FINAL;
	INT8U VAL;
	INT8U zCount = 0;

	INT8U i;

	INT8U pX;
	INT8U pY;

	INT8U disp_x = 0;
	INT8U disp_y = 0;

	char colors[4] = {0x40, 0x10, 0x20, 0x60};

	pdata = pdata;
	if (cmd == 1) {
		FINAL = 63;
		for (;;) {
			PC_DispStr(0, 3, "                                    EXAMPLE #111                                  ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
			
			myRdyGrp = 0;
			memset(myRdyTbl, 0x00, sizeof(myRdyTbl));
			
			for (i = 0; i < 4; i++) {
				tmp = random(64);

				myRdyGrp |= myMapTbl[tmp / 8];
				myRdyTbl[tmp / 8] |= myMapTbl[tmp % 8];

				PC_DispChar(disp_x++, disp_y % 16 + 5, (tmp / 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
				PC_DispChar(disp_x++, disp_y % 16 + 5, (tmp % 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
				PC_DispChar(disp_x++, disp_y % 16 + 5, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
			}

			pY = myUnMapTbl[myRdyGrp];
			pX = myUnMapTbl[myRdyTbl[pY]];
			VAL = pX + pY * 8;

			if (VAL < FINAL) {
				FINAL = VAL;
				PC_DispChar(disp_x++, disp_y % 16 + 5, (FINAL / 10) + 48, DISP_FGND_WHITE + colors[colorCount % 4]);
				PC_DispChar(disp_x++, disp_y % 16 + 5, (FINAL % 10) + 48, DISP_FGND_WHITE + colors[colorCount % 4]);
				colorCount++;
			}
			else if (VAL == 63 && FINAL == 63) {
				PC_DispChar(disp_x++, disp_y % 16 + 5, (FINAL / 10) + 48, DISP_FGND_WHITE + colors[colorCount % 4]);
				PC_DispChar(disp_x++, disp_y % 16 + 5, (FINAL % 10) + 48, DISP_FGND_WHITE + colors[colorCount % 4]);
				colorCount++;
			}
			else {
				PC_DispChar(disp_x++, disp_y % 16 + 5, ' ', DISP_BGND_LIGHT_GRAY);
				PC_DispChar(disp_x++, disp_y % 16 + 5, ' ', DISP_BGND_LIGHT_GRAY);
			}

			if (FINAL == 0) {
				FINAL = 63;
				zCount++;
			}

			disp_y++;
			if (disp_y == 80) disp_y = 0;
			disp_x = (disp_y / 16) * 16;

			OSTimeDlyHMSM(0, 0, 0, 200);

			if (zCount == 3) break;
		}
	}
	else if (cmd == 2) {
		FINAL = 0;
		for (;;){
			PC_DispStr(0, 3, "                                    EXAMPLE #222                                  ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
			
			myRdyGrp = 0;
			memset(myRdyTbl, 0x00, sizeof(myRdyTbl));

			for (i = 0; i < 4; i++) {
				tmp = random(64);

				myRdyGrp |= myMapTbl[tmp / 8];
				myRdyTbl[tmp / 8] |= myMapTbl[tmp % 8];

				PC_DispChar(disp_x++, disp_y % 16 + 5, (tmp / 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
				PC_DispChar(disp_x++, disp_y % 16 + 5, (tmp % 10) + 48, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
				PC_DispChar(disp_x++, disp_y % 16 + 5, ' ', DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
			}

			pY = myUnMapTbl_max[myRdyGrp];
			pX = myUnMapTbl_max[myRdyTbl[pY]];
			VAL = pX + pY * 8;

			if (VAL > FINAL) {
				FINAL = VAL;
				PC_DispChar(disp_x++, disp_y % 16 + 5, (FINAL / 10) + 48, DISP_FGND_WHITE + colors[colorCount % 4]);
				PC_DispChar(disp_x++, disp_y % 16 + 5, (FINAL % 10) + 48, DISP_FGND_WHITE + colors[colorCount % 4]);
				colorCount++;
			}
			else if (VAL == 0 && FINAL == 0) {
				PC_DispChar(disp_x++, disp_y % 16 + 5, (FINAL / 10) + 48, DISP_FGND_WHITE + colors[colorCount % 4]);
				PC_DispChar(disp_x++, disp_y % 16 + 5, (FINAL % 10) + 48, DISP_FGND_WHITE + colors[colorCount % 4]);
				colorCount++;
			}
			else {
				PC_DispChar(disp_x++, disp_y % 16 + 5, ' ', DISP_BGND_LIGHT_GRAY);
				PC_DispChar(disp_x++, disp_y % 16 + 5, ' ', DISP_BGND_LIGHT_GRAY);
			}

			if (FINAL == 63) {
				FINAL = 0;
				zCount++;
			}

			disp_y++;
			if (disp_y == 80) disp_y = 0;
			disp_x = (disp_y / 16) * 16;

			OSTimeDlyHMSM(0, 0, 0, 200);

			if (zCount == 3) break;
		}
	}

	// Your code would be here


	// Kill the task itself. Without this, the task is run 2 times.
	OSTaskDel(OS_PRIO_SELF);
}