#pragma once

#include <stddef.h>

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	HEAD,
} RelPos;

typedef struct {
	size_t head;
	size_t tail;
	size_t capacity;
	RelPos *buf;
} SnakeQueue;

void snakeq_init(SnakeQueue *q);
size_t snakeq_length(const SnakeQueue *q);
void snakeq_enqueue(SnakeQueue *q, RelPos rel_pos);
RelPos snakeq_dequeue(SnakeQueue *q);
RelPos snakeq_get(const SnakeQueue *q, size_t idx);
void snakeq_set(SnakeQueue *q, size_t idx, RelPos value);
