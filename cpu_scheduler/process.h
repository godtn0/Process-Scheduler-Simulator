#pragma once
#ifndef TYPE_HEADER_H
#define TYPE_HEADER_H

typedef struct Process * process_ptr;
typedef struct Process {
	int processID;         //process 고유 ID
	int cpu_burst_time;    //cpu burst time
	int io_burst_time;     //io burst time
	int io_start_time;     //상대적인 io start time(cpu start를 0으로 기준함)
	int io_remain_time;    //io 수행이 남은 시간
	int arrival_time;      //ready queue에 도착 시간
	int remain_time;       //cpu remain time
	int priority;          //priority number
	int waiting_time;      //waiting time
	int turnarround_time;  //turnaround time
	int terminate_time;    //process 종료 시간
	int aging_time;        //aging time
}process;

extern process_ptr running_process_ptr;
extern process running_process;
extern int pid;
extern int num_process;
void create_process();

#endif
