#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUEUE_SIZE 100

typedef struct Process * process_ptr;
typedef struct Process {
	int processID;
	int cpu_burst_time;
	int io_burst_time;
	int io_start_time;
	int io_remain_time;
	int arrival_time;
	int remain_time;
	int priority;
	int waiting_time;
	int turnarround_time;
	int terminate_time;
	int aging_time;
}process;

typedef struct Queue * queue_ptr;
typedef struct Queue {
	int front;
	int rear;
	int element_num;
	process arr[MAX_QUEUE_SIZE];
}queue;

void queueFull(queue_ptr q);

void enqueue(queue_ptr q, process p);
void enqueue_ready(queue_ptr q, process p);

process_ptr queueEmpty();

process_ptr dequeue(queue_ptr q);

void print_all_element(queue q);

void sort_by_priority(queue_ptr q);
void sort_by_bursttime(queue_ptr q);
void sort_by_ioRemainTime(queue_ptr q);
void sort_by_agingTime(queue_ptr q);

void initialize_queue(queue_ptr q);

void queueFull(queue_ptr q) {
	printf("Queue is full\n");
}

void enqueue(queue_ptr q, process p) {
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	if (q->rear == q->front) {
		queueFull(q);
		return;
	}
	q->arr[q->rear] = p;
	q->element_num++;
}

void enqueue_ready(queue_ptr q, process p) {
	enqueue(q, p);
	sort_by_priority(q);
}

process_ptr queueEmpty() {
	//printf("Queue is empty.\n");
	return NULL;
}

process_ptr dequeue(queue_ptr q) {
	if (q->rear == q->front) {
		return queueEmpty();
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	q->element_num--;
	return &(q->arr[q->front]);
}

void print_all_element(queue q) {
	int i = 0;
	if (q.element_num == 0) {
		printf("empty\n");
		return;
	}
	for (i = (q.front + 1) % MAX_QUEUE_SIZE; i != q.rear; i = (i + 1) % MAX_QUEUE_SIZE) {
		printf("processID : %d, arrival_time : %d, cpu_burst_time : %d, priority : %d, io_start_time : %d, io_busrt_time : %d, remain_time : %d, aging time : %d\n", q.arr[i].processID, q.arr[i].arrival_time, q.arr[i].cpu_burst_time, q.arr[i].priority, q.arr[i].io_start_time, q.arr[i].io_burst_time, q.arr[i].remain_time,q.arr[i].aging_time);
	}
	printf("processID : %d, arrival_time : %d, cpu_burst_time : %d, priority : %d, io_start_time : %d, io_busrt_time : %d, remain_time : %d, aging time : %d\n", q.arr[i].processID, q.arr[i].arrival_time, q.arr[i].cpu_burst_time, q.arr[i].priority, q.arr[i].io_start_time, q.arr[i].io_burst_time, q.arr[i].remain_time, q.arr[i].aging_time);

	printf("\n");
}

void sort_by_priority(queue_ptr q) {
	int count_i = 0;
	for (int i = (q->front + 1) % MAX_QUEUE_SIZE; count_i < q->element_num; i = (i + 1) % MAX_QUEUE_SIZE) {
		//printf("count_i = %d\n", count_i);
		int count_j = 0;
		for (int j = (q->front + 1) % MAX_QUEUE_SIZE; count_j < q->element_num - 1; j = (j + 1) % MAX_QUEUE_SIZE) {
			if (q->arr[j].priority > q->arr[j + 1].priority) {
				process tmp = q->arr[j];
				q->arr[j] = q->arr[j + 1];
				q->arr[j + 1] = tmp;
			}
			count_j++;
		}
		//print_all_element(*q);
		count_i++;
	}
}

void sort_by_bursttime(queue_ptr q) {
	int count_i = 0;
	for (int i = (q->front + 1) % MAX_QUEUE_SIZE; count_i < q->element_num; i = (i + 1) % MAX_QUEUE_SIZE) {
		//printf("count_i = %d\n", count_i);
		int count_j = 0;
		for (int j = (q->front + 1) % MAX_QUEUE_SIZE; count_j < q->element_num - 1; j = (j + 1) % MAX_QUEUE_SIZE) {
			if (q->arr[j].remain_time > q->arr[j + 1].remain_time) {
				process tmp = q->arr[j];
				q->arr[j] = q->arr[j + 1];
				q->arr[j + 1] = tmp;
			}
			count_j++;
		}
		//print_all_element(*q);
		count_i++;
	}
}

void sort_by_ioRemainTime(queue_ptr q) {
	int count_i = 0;
	for (int i = (q->front + 1) % MAX_QUEUE_SIZE; count_i < q->element_num; i = (i + 1) % MAX_QUEUE_SIZE) {
		//printf("count_i = %d\n", count_i);
		int count_j = 0;
		for (int j = (q->front + 1) % MAX_QUEUE_SIZE; count_j < q->element_num - 1; j = (j + 1) % MAX_QUEUE_SIZE) {
			if (q->arr[j].io_remain_time > q->arr[j + 1].io_remain_time) {
				process tmp = q->arr[j];
				q->arr[j] = q->arr[j + 1];
				q->arr[j + 1] = tmp;
			}
			count_j++;
		}
		//print_all_element(*q);
		count_i++;
	}
}

void sort_by_agingTime(queue_ptr q) {
	int count_i = 0;
	for (int i = (q->front + 1) % MAX_QUEUE_SIZE; count_i < q->element_num; i = (i + 1) % MAX_QUEUE_SIZE) {
		//printf("count_i = %d\n", count_i);
		int count_j = 0;
		for (int j = (q->front + 1) % MAX_QUEUE_SIZE; count_j < q->element_num - 1; j = (j + 1) % MAX_QUEUE_SIZE) {
			if (q->arr[j].aging_time < q->arr[j + 1].aging_time) {
				process tmp = q->arr[j];
				q->arr[j] = q->arr[j + 1];
				q->arr[j + 1] = tmp;
			}
			count_j++;
		}
		//print_all_element(*q);
		count_i++;
	}
}

void initialize_queue(queue_ptr q) {
	q->element_num = 0;
	q->front = 0;
	q->rear = 0;
}

typedef struct Gantt {
	int id;
	int start;
	int terminate;
}gantt;
gantt gantt_chart[100];
int gantt_index = 0;

queue job_queue = { 0, 0, 0,{ 0, } };
queue ready_queue = { 0, 0, 0,{ 0, } };
queue ready_queue2 = { 0,0,0,{ 0, } };
queue waiting_queue = { 0, 0, 0,{ 0, } };
queue backup_queue = { 0, 0, 0,{ 0, } };
queue terminated_queue = { 0, 0, 0,{ 0, } };

void initialize_all_queue() {
	//initialize_queue(&job_queue);
	initialize_queue(&ready_queue);
	initialize_queue(&ready_queue2);
	initialize_queue(&waiting_queue);
	initialize_queue(&terminated_queue);
}

void initialize_all_setting() {
	initialize_all_queue();
	gantt_index = 0;
}

process_ptr running_process_ptr;
process running_process;
int pid = 1;
int num_process = 0;

void create_process() {
	num_process++;
	int cpu_burst_time = rand() % 11 + 5;
	int io_burst_time = rand() % 8 + 3;
	int arrival_time = rand() % (num_process);
	int io_start_time = 1 + rand() % (cpu_burst_time - 1);
	int io_remain_time = io_burst_time;
	int priority = rand() % (num_process)+1;
	int remain_time = cpu_burst_time;
	process p = { pid, cpu_burst_time, io_burst_time, io_start_time, io_remain_time, arrival_time, remain_time, priority,0,0,0,0 };
	enqueue(&job_queue, p);
	enqueue(&backup_queue, p);
	pid++;
}

void append_GanttChart(process p, int time, int mode) {
	gantt_chart[gantt_index].id = p.processID;
	if (mode == 1) {
		gantt_chart[gantt_index].start = time;
	}
	else if (mode == 0) {
		gantt_chart[gantt_index].terminate = time;
		gantt_index++;
	}
}

void print_GanttChart() {
	printf("---------------gantt chart---------------\n");
	for (int i = 0; i < gantt_index; i++) {
		printf("%d ~ %d process %d\n", gantt_chart[i].start, gantt_chart[i].terminate, gantt_chart[i].id);
	}
}

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
	//sort_by_priority(&ready_queue);
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
	//sort_by_priority(&ready_queue);
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
	//printf("---------time %d---------\n", time);
	if (running_process_ptr == NULL) {
		running_process_ptr = dequeue(q);
		if (running_process_ptr != NULL) {
			append_GanttChart(*running_process_ptr, time, 1);
		}
		//running_process_ptr = &running_process;
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
		//running_process_ptr = &running_process;
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
		//running_process_ptr = &running_process;
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
		//running_process_ptr = &running_process;
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
		//running_process_ptr = &running_process;
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
		//printf("-----------time %d-----------\n", time);
		//print_all_element(ready_queue);
		/*if (running_process_ptr != NULL) {
		printf("running process : %d, remain time : %d\n", running_process_ptr->processID, running_process_ptr->remain_time);
		}
		else {
		printf("running process : NULL\n");
		}*/
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
			//print_all_element(ready_queue);
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

		//printf("running process : %d\n", running_process_ptr->processID);
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
		//print_all_element(terminated_queue);
	}
	//print_all_element(terminated_queue);

	print_GanttChart();
	evaluation();
	initialize_all_setting();
	running_process_ptr = NULL;
	//sort_by_priority(&terminated_queue);
	//print_all_element(terminated_queue);
}

int main() {
	srand((unsigned int)time(NULL));
	int input_num;
	printf("process num : ");
	scanf_s("%d", &input_num);
	for (int i = 0; i < input_num; i++) {
		create_process();
	}
	//sort_by_bursttime(&job_queue);
	print_all_element(job_queue);
	printf("-------start!--------------\n");
	//sort_by_priority(&job_queue);
	//print_all_element(job_queue);
	for (int i = 1; i <= 9; i++) {
		simulation(i);
	}

}



