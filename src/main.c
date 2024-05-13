#include <stdlib.h>
#include <unistd.h>
#include "display.h"
#include "game.h"
#include "termconfig.h"

int main(void) {
	init_terminal();
	atexit(restore_terminal);

	render_frame();
	run_game();
}
