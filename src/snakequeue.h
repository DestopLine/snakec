#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	HEAD,
	TAIL,
} Direction;

Direction dir_opposite(Direction dir);
bool dir_is_valid(Direction dir);

typedef struct {
	size_t head;
	size_t tail;
	size_t capacity;
	Direction *buf;
} SnakeQueue;

void snakeq_init(SnakeQueue *q);
size_t snakeq_length(const SnakeQueue *q);
void snakeq_enqueue(SnakeQueue *q, Direction prev_direction);
Direction snakeq_dequeue(SnakeQueue *q);
Direction snakeq_peek(const SnakeQueue *q);
Direction snakeq_get(const SnakeQueue *q, size_t idx);
void snakeq_set(SnakeQueue *q, size_t idx, Direction value);
void snakeq_free(SnakeQueue *q);
