/*
 * scheduler.c
 *
 *  Created on: Nov 21, 2024
 *      Author: camho
 */
#include "scheduler.h"
sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t cur_index_task = 0;

void SCH_Init(void){
	for (int i = 0; i < cur_index_task; i++){
		SCH_Delete_Tasks(i);
	}
	cur_index_task = 0;
}

void SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if(cur_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[cur_index_task].pTask = pFunction;
		SCH_tasks_G[cur_index_task].Delay = DELAY;
		SCH_tasks_G[cur_index_task].Period = PERIOD;
		SCH_tasks_G[cur_index_task].Runme = 0;

		SCH_tasks_G[cur_index_task].TaskID = cur_index_task;

		cur_index_task++;
	}
}

void SCH_Update(void){
	for(int i = 0; i < cur_index_task; i++){
		if(SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay --;
		}
		else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].Runme += 1;
		}
	}
}

void SCH_Dispatch_Tasks(void){
	for(int i = 0; i < cur_index_task; i++){
		if(SCH_tasks_G[i].Runme > 0){
			SCH_tasks_G[i].Runme --;
			(*SCH_tasks_G[i].pTask)();
			if (SCH_tasks_G[i].Period == 0)
				SCH_Delete_Tasks(i);
		}
	}
}

void SCH_Delete_Tasks(unsigned char TASK_INDEX){
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].Runme = 0;

}
