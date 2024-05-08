#include <stddef.h>
#include <stdlib.h>
#include "snakequeue.h"

void snakeq_init(SnakeQueue *q) {
	const size_t capacity = 4;
	q->head = 0;
	q->tail = 1;
	q->capacity = capacity;
	q->buf = calloc(capacity, sizeof(RelPos));
}

size_t snakeq_length(const SnakeQueue *q) {
	return (q->tail - q->head + q->capacity) % q->capacity;
}

static void snakeq_grow(SnakeQueue *q) {
	const size_t length = snakeq_length(q);
	const size_t new_capacity = q->capacity * 2;

	RelPos *new_buf = calloc(new_capacity, sizeof(RelPos));
	for (size_t i = 0; i < length; i++) {
		new_buf[i] = snakeq_get(q, i);
	}
	free(q->buf);

	q->head = 0;
	q->tail = length;
	q->capacity = new_capacity;
	q->buf = new_buf;
}

void snakeq_enqueue(SnakeQueue *q, RelPos rel_pos) {
	if (q->head == q->tail) {
		snakeq_grow(q);
	}
	q->buf[q->tail] = rel_pos;
	q->tail = (q->tail + 1) % q->capacity;
}

RelPos snakeq_dequeue(SnakeQueue *q) {
	if (snakeq_length(q) == 1) {
		return HEAD;
	}
	RelPos rel_pos = q->buf[q->head];
	q->head = (q->head + 1) % q->capacity;
	return rel_pos;
}

static size_t circular_idx(const SnakeQueue *q, size_t idx) {
	return (q->head + idx) % q->capacity;
}

RelPos snakeq_get(const SnakeQueue *q, size_t idx) {
	if (idx >= snakeq_length(q)) {
		return HEAD;
	}
	return q->buf[circular_idx(q, idx)];
}

void snakeq_set(SnakeQueue *q, size_t idx, RelPos value) {
	if (idx >= snakeq_length(q)) {
		return;
	}
	q->buf[circular_idx(q, idx)] = value;
}
