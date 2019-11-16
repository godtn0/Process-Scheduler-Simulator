#pragma once
#ifndef GANTT_CHART_H
#define GANTT_CHART_H
#include "process.h"

typedef struct Gantt {
	int id;
	int start;
	int terminate;
}gantt;

extern gantt gantt_chart[100];
extern int gantt_index;

void append_GanttChart(process p, int time, int mode);
void print_GanttChart();

#endif
