#include "Scene.h"
#include <stddef.h>
#include <raylib.h>
#include <stdint.h>
#include <string.h>

#define LOGS_COUNT (sizeof(boot_logs) / sizeof(boot_logs[0]))

void  BRender (int *levelN, Camera3D *cam) {
	static const char *boot_logs[] = {
		"1991.03.04 03:32:43 [OK] System V started",
		"1991.03.04 03:32:43 [0K] device /dev/serial inited",
		"1991.03.04 03:32:43 [ERROR] wrong checksum 0x23F",
		"1991.03.04 03:32:44 [OK] cheksum test complete",
		"1991.03.04 03:32:46 [0K] central node connection estabilished",
		"1991.03.04 03:32:47 [0K] NetDive subsystem inited",
		"1991.03.04 03:32:47 [WARN] neural interface bio-rejection in progress",
		"1991.03.04 03:32:47 [ERROR] neural port returned error code -1",
		"1991.03.04 03:32:47 [OK] entered safe mode",
		"1991.03.04 03:32:47 [WARN] high impedance on synaptic lines",
		"1991.03.04 03:32:47 [OK] initiating emergency dopamine injection",
		"1991.03.04 03:32:47 [OK] synaptic impedance nominal",
		"1991.03.04 03:32:48 [OK] synaptic nodes test finished",
		"1991.03.04 03:32:50 [OK] NetDive system started",
		"press any key to continue.."
		};
	ClearBackground(BLACK); 
	static int  VisibleLines = 0;
	static double latency = 0;
	if (VisibleLines < LOGS_COUNT) {
		if ( strstr(boot_logs[VisibleLines], "[ERROR]") || strstr(boot_logs[VisibleLines], "[WARN]") ) {
				latency += GetFrameTime() / 2;
			}
		else {
			latency += GetFrameTime();
		}
			
		if (latency >= 0.4f) {
			latency = 0.0f;
			VisibleLines++;
		}
	}
	for (int i = 0; i < VisibleLines; i++) {
	    if (strstr(boot_logs[i], "[ERROR]") != NULL) {
			DrawText(boot_logs[i], 40, 90 + (i * 24), 20, RED);
	    }
	    else if (strstr(boot_logs[i], "[WARN]") != NULL) {
	    	DrawText(boot_logs[i], 40, 90 + (i * 24), 20, YELLOW);
	    }
	    else {
	    	DrawText(boot_logs[i], 40, 90 + (i * 24), 20, GREEN);
	    }
	}
	if ( GetKeyPressed() && VisibleLines == LOGS_COUNT )  {
		(*levelN)++; 
	}
}

__attribute__((visibility("default"))) Scene bootan =  { 
	.n = 1,
	.render = BRender,
};
