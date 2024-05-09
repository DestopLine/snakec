#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "snakequeue.h"

Direction dir_opposite(Direction dir) {
	switch (dir) {
		case UP:
			return DOWN;
		case DOWN:
			return UP;
		case LEFT:
			return RIGHT;
		case RIGHT:
			return LEFT;
		case HEAD:
			return TAIL;
		case TAIL:
			return HEAD;
	}
}

bool dir_is_valid(Direction dir) {
	return dir != HEAD && dir != TAIL;
}

void snakeq_init(SnakeQueue *q) {
	const size_t capacity = 4;
	q->head = 0;
	q->tail = 1;
	q->capacity = capacity;
	q->buf = calloc(capacity, sizeof(Direction));
	q->buf[0] = HEAD;
}

size_t snakeq_length(const SnakeQueue *q) {
	if (q->head == q->tail) {
		return q->capacity;
	}
	return (q->tail - q->head + q->capacity) % q->capacity;
}

static void snakeq_grow(SnakeQueue *q) {
	const size_t length = snakeq_length(q);
	const size_t new_capacity = q->capacity * 2;

	Direction *new_buf = calloc(new_capacity, sizeof(Direction));
	for (size_t i = 0; i < length; i++) {
		new_buf[i] = snakeq_get(q, i);
	}
	free(q->buf);

	q->head = 0;
	q->tail = length;
	q->capacity = new_capacity;
	q->buf = new_buf;
}

void snakeq_enqueue(SnakeQueue *q, Direction prev_direction) {
	if (q->head == q->tail) {
		snakeq_grow(q);
	}
	snakeq_set(q, snakeq_length(q) - 1, prev_direction);
	q->buf[q->tail] = HEAD;
	q->tail = (q->tail + 1) % q->capacity;
}

Direction snakeq_dequeue(SnakeQueue *q) {
	if (snakeq_length(q) == 1) {
		return HEAD;
	}
	Direction direction = q->buf[q->head];
	q->head = (q->head + 1) % q->capacity;
	return direction;
}

static size_t circular_idx(const SnakeQueue *q, size_t idx) {
	return (q->head + idx) % q->capacity;
}

Direction snakeq_peek(const SnakeQueue *q) {
	return q->buf[q->head];
}

Direction snakeq_get(const SnakeQueue *q, size_t idx) {
	if (idx >= snakeq_length(q)) {
		return TAIL;
	}
	return q->buf[circular_idx(q, idx)];
}

void snakeq_set(SnakeQueue *q, size_t idx, Direction value) {
	if (idx >= snakeq_length(q)) {
		return;
	}
	q->buf[circular_idx(q, idx)] = value;
}

void snakeq_free(SnakeQueue *q) {
	free(q->buf);
	q->buf = NULL;
}
