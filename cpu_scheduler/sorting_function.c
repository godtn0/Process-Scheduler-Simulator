#include "process.h"
#include "queue.h"
#include <stdio.h>

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
