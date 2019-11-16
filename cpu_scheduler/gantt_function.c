#include "gantt_chart.h"
#include "process.h"
#include <stdio.h>

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