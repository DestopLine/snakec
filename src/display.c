#include <stdio.h>
#include "ansi.h"
#include "display.h"
#include "params.h"

static void render_edge_h() {
	printf("%c", CORNER);
	
	for (size_t i = 0; i < DISPLAY_WIDTH; i++) {
		printf("%c", EDGE_H);
	}
	
	printf("%c", CORNER);
}

static void render_edge_v() {
	printf("%c" ANSI_MOVE_CURSOR_DOWN("1") ANSI_MOVE_CURSOR_LEFT("1"), CORNER);
	
	for (size_t i = 0; i < DISPLAY_HEIGHT; i++) {
		printf("%c" ANSI_MOVE_CURSOR_DOWN("1") ANSI_MOVE_CURSOR_LEFT("1"), EDGE_V);
	}
	
	printf("%c", CORNER);
}

void render_frame() {
	printf(ANSI_MOVE_CURSOR_HOME);
	render_edge_h();
	printf(ANSI_MOVE_CURSOR_HOME);
	render_edge_v();
	printf(ANSI_MOVE_CURSOR_LEFT("1"));
	render_edge_h();
	printf(ANSI_MOVE_CURSOR_LEFT("1") ANSI_MOVE_CURSOR_UP("9999"));
	render_edge_v();
	
	fflush(stdout);
}
