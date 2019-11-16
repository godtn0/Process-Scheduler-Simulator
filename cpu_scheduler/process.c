#include "process.h"
#include "queue.h"
#include <time.h>
#include <stdlib.h>

int num_process;

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

