#pragma once

#include <stddef.h>
#include "snakequeue.h"

typedef struct {
	size_t row;
	size_t col;
	Direction dir;
	unsigned growth_points;
	SnakeQueue queue;
} Snake;

void snake_init(Snake *snake);
Direction snake_move(Snake *snake, bool grow);
bool snake_render(const Snake *snake, Direction del_dir);
