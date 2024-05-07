#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "display.h"
#include "termconfig.h"

int main(void) {
	init_terminal();
	atexit(restore_terminal);

	render_frame();

	while (1) {
		char c = '\0';
		read(STDIN_FILENO, &c, 1);

		if (iscntrl(c)) {
			printf("%d\r\n", c);
		} else {
			printf("%d ('%c')\r\n", c, c);
		}
		
		if (c == 'q') {
			break;
		}
	}
}
