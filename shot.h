#ifndef SHOT_H
#define SHOT_H

#include "Fighters.h"
struct shot;
typedef struct shot* shot_t;

//PRE: /
//POST: initialise a shot from a fighter f and return a pointer to it
shot_t init_shot(fighter_t f);

int get_priority(shot_t shot);

int get_power(shot_t shot);

int* get_target(shot_t shot);

fighter_t get_shooter(shot_t shot);

#endif
