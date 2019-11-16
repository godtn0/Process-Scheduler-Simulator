#include "process.h"
#include "queue.h"
#include "gantt_chart.h"
#include <stdio.h>

void job_schedule_2levelQueue(int time) {
	for (int i = (job_queue.front + 1) % MAX_QUEUE_SIZE; i <= job_queue.rear; i = (i + 1) % MAX_QUEUE_SIZE) {
		if (job_queue.arr[i].arrival_time == time) {
			if (job_queue.arr[i].priority < 6) {
				enqueue(&ready_queue, job_queue.arr[i]);
			}
			else {
				enqueue(&ready_queue2, job_queue.arr[i]);
			}
		}
	}
	sort_by_ioRemainTime(&waiting_queue);
	int count_i = 0;
	int count = waiting_queue.element_num;
	for (int i = (waiting_queue.front + 1) % MAX_QUEUE_SIZE; count_i < count; i = (i + 1) % MAX_QUEUE_SIZE) {
		if (waiting_queue.arr[i].io_remain_time == 0) {
			if (waiting_queue.arr[i].priority < 6) {
				enqueue(&ready_queue, *(dequeue(&waiting_queue)));
			}
			else {
				enqueue(&ready_queue2, *(dequeue(&waiting_queue)));
			}
		}
		count_i++;
	}
}

void job_schedule(int time, int * count) {
	for (int i = (job_queue.front + 1) % MAX_QUEUE_SIZE; i <= job_queue.rear; i = (i + 1) % MAX_QUEUE_SIZE) {
		if (job_queue.arr[i].arrival_time == time) {
			enqueue(&ready_queue, job_queue.arr[i]);
			(*count)++;
		}
	}
	sort_by_ioRemainTime(&waiting_queue);
	int count_i = 0;
	int count_num = waiting_queue.element_num;
	for (int i = (waiting_queue.front + 1) % MAX_QUEUE_SIZE; count_i < count_num; i = (i + 1) % MAX_QUEUE_SIZE) {
		if (waiting_queue.arr[i].io_remain_time == 0) {
			enqueue(&ready_queue, *(dequeue(&waiting_queue)));
		}
		count_i++;
	}
}

void aging_multi(int time) {
	int count_i = 0;
	int count = ready_queue2.element_num;
	for (int i = (ready_queue2.front + 1) % MAX_QUEUE_SIZE; count_i < count; i = (i + 1) % MAX_QUEUE_SIZE) {
		if ((ready_queue2.arr[i].cpu_burst_time == ready_queue2.arr[i].remain_time) && time>30) {
			enqueue(&ready_queue, *(dequeue(&ready_queue2)));
		}
		count_i++;
	}
}

void rising_aging_time(int time) {
	int count_i = 0;
	int count = ready_queue.element_num;
	for (int i = (ready_queue.front + 1) % MAX_QUEUE_SIZE; count_i < count; i = (i + 1) % MAX_QUEUE_SIZE) {
		ready_queue.arr[i].aging_time++;
		count_i++;
	}
}
void aging(int time) {
	int count_i = 0;
	int count = ready_queue.element_num;
	for (int i = (ready_queue.front + 1) % MAX_QUEUE_SIZE; count_i < count; i = (i + 1) % MAX_QUEUE_SIZE) {
		if (ready_queue.arr[i].aging_time > 20) {
			ready_queue.arr[i].priority--;
			ready_queue.arr[i].aging_time = 0;
		}
		count_i++;
	}
}


void inference_IO() {
	int count_i = 0;
	for (int i = (waiting_queue.front + 1) % MAX_QUEUE_SIZE; count_i < waiting_queue.element_num; i = (i + 1) % MAX_QUEUE_SIZE) {
		if (waiting_queue.arr[i].io_remain_time > 0) {
			(waiting_queue.arr[i].io_remain_time)--;
		}
		count_i++;
	}
}

void cpu_schedule_FCFS(int time, queue_ptr q) {
	if (running_process_ptr == NULL) {
		running_process_ptr = dequeue(q);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
	else if (running_process_ptr->io_start_time == running_process_ptr->cpu_burst_time - running_process_ptr->remain_time) {
		append_GanttChart(*running_process_ptr, time, 0);
		enqueue(&waiting_queue, *running_process_ptr);
		running_process_ptr = dequeue(q);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
}

void cpu_schedule_Priority_nonpreemptive(int time) {
	sort_by_priority(&ready_queue);
	if (running_process_ptr == NULL) {
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
	else if (running_process_ptr->io_start_time == running_process_ptr->cpu_burst_time - running_process_ptr->remain_time) {
		append_GanttChart(*running_process_ptr, time, 0);
		enqueue(&waiting_queue, *running_process_ptr);
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
}

void cpu_schedule_Priority_preemptive(int time) {
	sort_by_priority(&ready_queue);
	if (running_process_ptr == NULL) {
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
	else if (running_process_ptr->io_start_time == running_process_ptr->cpu_burst_time - running_process_ptr->remain_time) {
		append_GanttChart(*running_process_ptr, time, 0);
		enqueue(&waiting_queue, *running_process_ptr);
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
	else if (ready_queue.arr[(ready_queue.front + 1) % MAX_QUEUE_SIZE].priority<running_process_ptr->priority && ready_queue.element_num>0) {
		append_GanttChart(*running_process_ptr, time, 0);
		enqueue(&ready_queue, *running_process_ptr);
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
}

void cpu_schedule_SJF_nonpreemptive(int time) {
	sort_by_bursttime(&ready_queue);
	if (running_process_ptr == NULL) {
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
	else if (running_process_ptr->io_start_time == running_process_ptr->cpu_burst_time - running_process_ptr->remain_time) {
		append_GanttChart(*running_process_ptr, time, 0);
		enqueue(&waiting_queue, *running_process_ptr);
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
}

void cpu_schedule_SJF_preemptive(int time) {
	sort_by_bursttime(&ready_queue);
	if (running_process_ptr == NULL) {
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
	else if (running_process_ptr->io_start_time == running_process_ptr->cpu_burst_time - running_process_ptr->remain_time) {
		append_GanttChart(*running_process_ptr, time, 0);
		enqueue(&waiting_queue, *running_process_ptr);
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
	else if (ready_queue.arr[(ready_queue.front + 1) % MAX_QUEUE_SIZE].remain_time < running_process_ptr->remain_time && ready_queue.element_num>0) {
		append_GanttChart(*running_process_ptr, time, 0);
		enqueue(&ready_queue, *running_process_ptr);
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
}

void cpu_schedule_RR(int time, int quantum, int * remain_quantum) {
	if (running_process_ptr == NULL) {
		(*remain_quantum) = quantum;
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
	else if (running_process_ptr->io_start_time == running_process_ptr->cpu_burst_time - running_process_ptr->remain_time) {
		append_GanttChart(*running_process_ptr, time, 0);
		(*remain_quantum) = quantum;
		enqueue(&waiting_queue, *running_process_ptr);
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
	else if ((*remain_quantum) == 0) {
		append_GanttChart(*running_process_ptr, time, 0);
		(*remain_quantum) = quantum;
		enqueue(&ready_queue, *running_process_ptr);
		running_process_ptr = dequeue(&ready_queue);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
	}
	(*remain_quantum)--;
}