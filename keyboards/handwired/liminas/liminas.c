#include "liminas.h"

#include <math.h>
#include "report.h"


const float phi = sin(30 * (M_PI / 180.0));
const float R = 1;
const float r = R * phi;

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {

/*
	float y_h = sqrt(2 * r * mouse_report.x - mouse_report.x * mouse_report.x);
	float y_h = 0.f;
	float c = mouse_report.x + y_h;

	float x_c = c / phi;
	float y_c = mouse_report.y > 0 ? mouse_report.y - y_h : mouse_report.y + y_h;

	mouse_report.v = x_c;
	mouse_report.h = y_c;
*/

	return mouse_report;
}
