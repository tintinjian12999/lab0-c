#pragma once
#include "fixed_point.h"
#define ITERATIONS 10000
#define EXPLORATION_FACTOR fixed_sqrt(int2fix(2))

int mcts(char *table, char player);
