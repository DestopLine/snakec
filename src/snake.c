#include <stdio.h>
#include "ansi.h"
#include "params.h"
#include "snake.h"

void snake_init(Snake *snake) {
	snake->row = FRAME_HEIGHT / 2;
	snake->col = FRAME_WIDTH / 2;
	snake->dir = RIGHT;
	snake->growth_points = 5;
	snakeq_init(&snake->queue);
}

Direction snake_move(Snake *snake, bool grow) {
	switch (snake->dir) {
		case UP:
			snake->row--;
			break;
		case DOWN:
			snake->row++;
			break;
		case LEFT:
			snake->col--;
			break;
		case RIGHT:
			snake->col++;
			break;
		default:
			break;
	}
	snakeq_enqueue(&snake->queue, dir_opposite(snake->dir));
	if (grow) {
		return snakeq_peek(&snake->queue);
	}
	return snakeq_dequeue(&snake->queue);
}

bool snake_render(const Snake *snake, Direction del_dir) {
	size_t curr_row = snake->row;
	size_t curr_col = snake->col;
	bool at_end = false;
	bool dead = false;
	const size_t length = snakeq_length(&snake->queue);

	for (size_t i = length - 1; ; i--) {
		size_t dir = snakeq_get(&snake->queue, i);

		if (dir == TAIL) {
			at_end = true;
			dir = del_dir;
		}

		if (dir_is_valid(dir)) {
			switch (dir) {
				case UP:
					curr_row--;
					break;
				case DOWN:
					curr_row++;
					break;
				case LEFT:
					curr_col--;
					break;
				case RIGHT:
					curr_col++;
					break;
			}
		}

		printf(ANSI_MOVE_CURSOR("%zu", "%zu"), curr_row, curr_col);

		if (at_end) {
			printf(" ");  // clean up the
			break;
		}

		printf("%c", dir == HEAD ? SNAKE_HEAD : SNAKE_BODY);

		// Collision with tail
		if (dir != HEAD && curr_row == snake->row && curr_col == snake->col) {
			dead = true;
		}
	}

	// Collision with wall
	if ((snake->row == 0 || snake->row > DISPLAY_HEIGHT)
		|| (snake->col == 0 || snake->col > DISPLAY_WIDTH)) {
		dead = true;
	}

	return dead;
}
