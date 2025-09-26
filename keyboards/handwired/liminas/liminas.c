#include "liminas.h"

#include <math.h>
#include "report.h"


const float sin_phi = sin(30 * (M_PI / 180.0));

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
	return mouse_report;
}

