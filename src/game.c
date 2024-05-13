#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "ansi.h"
#include "fruit.h"
#include "params.h"
#include "snake.h"
#include "snakequeue.h"

static bool read_direction(Direction *buf) {
	char input[] = {0, 0, 0};
	const ssize_t amount = read(STDIN_FILENO, &input, 3);
	Direction dir = HEAD;
	
	if (amount == 0) {
		return false;
	}

	if (input[0] == 27 && input[1] == '[') {
		switch (input[2]) {
			case 'A':
				dir = UP;
				break;
			case 'B':
				dir = DOWN;
				break;
			case 'C':
				dir = RIGHT;
				break;
			case 'D':
				dir = LEFT;
				break;
		}
	}

	if (dir == HEAD) {
		switch (input[amount - 1]) {
			case 'w':
				dir = UP;
				break;
			case 'a':
				dir = LEFT;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'q':
				return true;
		}
	}

	if (dir != dir_opposite(*buf)) {
		*buf = dir;
	}
	return false;
}

void run_game() {
	Snake snake;
	snake_init(&snake);
	bool dead = false;
	srand(time(NULL));
	struct Fruit fruit;
	fruit_gen(&fruit);
	char c;

	while (!dead) {
		if (read_direction(&snake.dir)) {
			return;
		}

		bool grow = false;
		if (snake.growth_points > 0) {
			grow = true;
			snake.growth_points--;
		}

		const Direction del_dir = snake_move(&snake, grow);
		if (snake.row == fruit.row && snake.col == fruit.col) {
			snake.growth_points += fruit.growth_points;
			fruit_gen(&fruit);
		}

		fruit_render(&fruit);
		dead = snake_render(&snake, del_dir);
		printf(ANSI_MOVE_CURSOR("%zu", "1"), FRAME_HEIGHT + 1ul);
		printf("Score: %zu", snakeq_length(&snake.queue));

		fflush(stdout);
		usleep(MSPT);
	}

	snakeq_free(&snake.queue);
}
