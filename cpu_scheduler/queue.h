#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include "process.h"
#define MAX_QUEUE_SIZE 100

typedef struct Queue * queue_ptr;
typedef struct Queue {
	int front;
	int rear;
	int element_num;
	process arr[MAX_QUEUE_SIZE];
}queue;

extern queue job_queue;
extern queue ready_queue;
extern queue ready_queue2;
extern queue waiting_queue;
extern queue backup_queue;
extern queue terminated_queue;

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
void initialize_all_queue();

#endif
