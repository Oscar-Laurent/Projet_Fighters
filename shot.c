#include "utils.h"
#include "Fighters.h"
#include "shot.h"

struct shot {
    fighter_t shooter;
    int priority;
    int power;
    int target[2]; // [x, y]
};

shot_t init_shot(fighter_t f) {
    shot_t new_shot = malloc(sizeof(*new_shot));
    new_shot->shooter = f;
    new_shot->priority = get_speed(f);
    new_shot->power = random_number(2, 10);
    new_shot->target[0] = random_number(0, MAX_X);
    new_shot->target[1] = random_number(0, MAX_Y);
    return new_shot;
}

int get_priority(shot_t shot) {
    return shot->priority;
}

int get_power(shot_t shot) {
    return shot->power;
}

int* get_target(shot_t shot) {
    return shot->target;
}

fighter_t get_shooter(shot_t shot) {
    return shot->shooter;
}


