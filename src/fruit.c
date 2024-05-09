#include <stdlib.h>
#include <stdio.h>
#include "ansi.h"
#include "fruit.h"
#include "params.h"

void fruit_gen(struct Fruit *fruit) {
	fruit->row = rand() % DISPLAY_HEIGHT + 1;
	fruit->col = rand() % DISPLAY_WIDTH + 1;
	fruit->growth_points = 1;
}

void fruit_render(const struct Fruit *fruit) {
	printf(ANSI_MOVE_CURSOR("%zu", "%zu"), fruit->row, fruit->col);
	printf("%c", FRUIT);
}
