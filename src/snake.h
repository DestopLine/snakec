#pragma once

#include <stddef.h>
#include "snakequeue.h"

typedef struct {
	size_t row;
	size_t col;
	unsigned growth_points;
	SnakeQueue queue;
} Snake;
