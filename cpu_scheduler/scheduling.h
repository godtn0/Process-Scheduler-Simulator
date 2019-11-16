#pragma once
#ifndef SCHEDULING_H
#define SCHEDULING_H
#include "queue.h"
#include "process.h"

void job_schedule_2levelQueue(int time);
void job_schedule(int time, int * count);
void aging_multi(int time);
void rising_aging_time(int time);
void aging(int time);
void inference_IO();
void cpu_schedule_FCFS(int time, queue_ptr q);
void cpu_schedule_Priority_nonpreemptive(int time);
void cpu_schedule_Priority_preemptive(int time);
void cpu_schedule_SJF_nonpreemptive(int time);
void cpu_schedule_SJF_preemptive(int time);
void cpu_schedule_RR(int time, int quantum, int * remain_quantum);

#endif
