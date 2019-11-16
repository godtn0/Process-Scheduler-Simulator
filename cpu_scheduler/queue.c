#include <stdio.h>
#include "queue.h"

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

void enqueue_priority(queue_ptr q, process p) {
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	if (q->rear == q->front) {
		queueFull(q);
		return;
	}
	q->arr[q->rear] = p;
	q->element_num++;
	sort_by_priority(q);
}

void enqueue_ready(queue_ptr q, process p) {
	enqueue(q, p);
	sort_by_priority(q);
}

process_ptr queueEmpty() {
	printf("Queue is empty.\n");
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
	for (i = (q.front + 1) % MAX_QUEUE_SIZE; i != q.rear; i = (i+1)%MAX_QUEUE_SIZE) {
		printf("processID : %d, arrival_time : %d, cpu_burst_time : %d, priority : %d, io_start_time : %d, io_busrt_time : %d, remain_time : %d\n", q.arr[i].processID, q.arr[i].arrival_time,q.arr[i].cpu_burst_time,q.arr[i].priority, q.arr[i].io_start_time, q.arr[i].io_burst_time, q.arr[i].remain_time);
	}
	printf("processID : %d, arrival_time : %d, cpu_burst_time : %d, priority : %d, io_start_time : %d, io_busrt_time : %d, remain_time : %d\n", q.arr[i].processID, q.arr[i].arrival_time, q.arr[i].cpu_burst_time, q.arr[i].priority, q.arr[i].io_start_time, q.arr[i].io_burst_time, q.arr[i].remain_time);
	
	printf("\n");
}


void initialize_queue(queue_ptr q) {
	q->element_num = 0;
	q->front = 0;
	q->rear = 0;
}

void initialize_all_queue() {
	//initialize_queue(&job_queue);
	initialize_queue(&ready_queue);
	initialize_queue(&ready_queue2);
	initialize_queue(&waiting_queue);
	initialize_queue(&terminated_queue);
}

