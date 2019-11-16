#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"
#include "queue.h"
#include "gantt_chart.h"
#include "scheduling.h"
#define MAX_QUEUE_SIZE 100

gantt gantt_chart[100] = { 0, };
int gantt_index = 0;

queue job_queue = { 0, 0, 0,{ 0, } };
queue ready_queue = { 0, 0, 0,{ 0, } };
queue ready_queue2 = { 0,0,0,{ 0, } };
queue waiting_queue = { 0, 0, 0,{ 0, } };
queue backup_queue = { 0, 0, 0,{ 0, } };
queue terminated_queue = { 0, 0, 0,{ 0, } };

void initialize_all_setting() {
	initialize_all_queue();
	gantt_index = 0;
}

process_ptr running_process_ptr;
process running_process;
int pid = 1;
int num_process = 0;

void evaluation() {
	printf("--------evaluation---------\n");
	int count_j = 0;
	double average_waiting_time = 0;
	double average_turnaround_time = 0;
	for (int j = (terminated_queue.front + 1) % MAX_QUEUE_SIZE; count_j < terminated_queue.element_num; j = (j + 1) % MAX_QUEUE_SIZE) {
		terminated_queue.arr[j].turnarround_time = terminated_queue.arr[j].terminate_time - terminated_queue.arr[j].arrival_time;
		terminated_queue.arr[j].waiting_time = terminated_queue.arr[j].turnarround_time - terminated_queue.arr[j].cpu_burst_time - terminated_queue.arr[j].io_burst_time;
		average_waiting_time += terminated_queue.arr[j].waiting_time / terminated_queue.element_num;
		average_turnaround_time += terminated_queue.arr[j].turnarround_time / terminated_queue.element_num;
		count_j++;
		//printf("j : %d\n",j);
	}
	printf("average waiting time = %.4lf, average turnaround time = %.4lf\n", average_waiting_time, average_turnaround_time);
}

void simulation(int algo) {
	switch (algo) {
	case 1:
		printf("-------------FCFS------------\n");
		break;
	case 2:
		printf("-----------Priority_nonpreemptive------------\n");
		break;
	case 3:
		printf("-------------Priority_preemptive------------\n");
		break;
	case 4:
		printf("-------------SJF_nonpreemptive------------\n");
		break;
	case 5:
		printf("-------------SJF_preemptive------------\n");
		break;
	case 6:
		printf("-------------RR------------\n");
		break;
	case 7:
		printf("------------aging priority preemptive------------\n");
		break;
	case 8:
		printf("------------aging priority nonpreemptive------------\n");
		break;
	case 9:
		printf("------------multilevel feedback queue------------\n");
		break;
	default:
		break;
	}
	int time = 0;
	int count = 0;
	int quantum = 3;
	int quantum_remain = 3;
	while ((terminated_queue.element_num < num_process)) {
		int select_queue = rand() % 1;
		switch (algo) {
		case 1:
			job_schedule(time, &count);
			cpu_schedule_FCFS(time, &ready_queue);
			break;
		case 2:
			job_schedule(time, &count);
			cpu_schedule_Priority_nonpreemptive(time);
			break;
		case 3:
			job_schedule(time, &count);
			cpu_schedule_Priority_preemptive(time);
			break;
		case 4:
			job_schedule(time, &count);
			cpu_schedule_SJF_nonpreemptive(time);
			break;
		case 5:
			job_schedule(time, &count);
			cpu_schedule_SJF_preemptive(time);
			break;
		case 6:
			job_schedule(time, &count);
			cpu_schedule_RR(time, quantum, &quantum_remain);
			break;
		case 7:
			job_schedule(time, &count);
			aging(time);
			cpu_schedule_Priority_preemptive(time);
			rising_aging_time(time);
			break;
		case 8:
			job_schedule(time, &count);
			aging(time);
			cpu_schedule_Priority_nonpreemptive(time);
			rising_aging_time(time);
			break;
		case 9:
			job_schedule_2levelQueue(time);
			aging_multi(time);
			if (select_queue < 0.8) {
				if (ready_queue.element_num != 0)
					cpu_schedule_FCFS(time, &ready_queue);
				else
					cpu_schedule_FCFS(time, &ready_queue2);
			}
			else {
				if (ready_queue2.element_num != 0)
					cpu_schedule_FCFS(time, &ready_queue2);
				else
					cpu_schedule_FCFS(time, &ready_queue);
			}
			break;
		default:
			break;
		}

		inference_IO();

		time++;
		if (running_process_ptr == NULL) {

		}
		else {
			running_process_ptr->remain_time--;
			if (running_process_ptr->remain_time == 0) {
				append_GanttChart(*running_process_ptr, time, 0);
				running_process_ptr->terminate_time = time;
				enqueue(&terminated_queue, *running_process_ptr);
				running_process_ptr = NULL;
			}
		}
	}
	print_GanttChart();
	evaluation();
	initialize_all_setting();
	running_process_ptr = NULL;
}

int main() {
	srand((unsigned int)time(NULL));
	int input_num;
	printf("process num : ");
	scanf_s("%d", &input_num);
	for (int i = 0; i < input_num; i++) {
		create_process();
	}
	print_all_element(job_queue);
	printf("-------start!--------------\n");
	for (int i = 1; i <= 9; i++) {
		simulation(i);
	}

}



