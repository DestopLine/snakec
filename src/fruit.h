#pragma once

#include "stddef.h"

struct Fruit {
	size_t row;
	size_t col;
	unsigned growth_points;
};

void fruit_gen(struct Fruit *fruit);

void fruit_render(const struct Fruit *fruit);
