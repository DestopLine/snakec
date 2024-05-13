#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "ansi.h"

static struct termios orig_termios;

void enable_raw_mode() {
	tcgetattr(STDIN_FILENO, &orig_termios);

	struct termios raw = orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void init_terminal() {
	printf(ANSI_ENABLE_ALT_BUF ANSI_HIDE_CURSOR);
	fflush(stdout);  // This is needed to enter without needing to print newline
	enable_raw_mode();
}

void restore_terminal() {
	disable_raw_mode();
	printf(ANSI_DISABLE_ALT_BUF ANSI_SHOW_CURSOR);
}
