#ifndef FIGHTER_H
#define FIGHTER_H

struct Fighter;
typedef struct Fighter* fighter_t;

#include <stdbool.h>
#include "linked_list.h"

typedef LL_t fighters_list_t;

//PRE: /
//POST: Renvoi une instance fighter générée aléatoirement
fighter_t rand_init_fighter(fighters_list_t fighters_list);

//POST: print all the atribute of the fighter f
void print_attribute(fighter_t f);

//PRE: The fighter list is already inisialized
//POST: Sets out_x, out_y to a free position. Returns true if found, false otherwise.
bool free_position(LL_t fighters_list, int *out_x, int *out_y);

//PRE: fighter_list eis initialized
//POST: Print all the attributes of all the fighters in fighter_list
void print_fighter_list(fighters_list_t fighters_list);

//PRE: The fighter is already inisialized
//POST: Free the moemory of the fighter name and fighter instence
void destroy_fighter(fighter_t f);

//PRE: The fighter is already inisialized
//POST: Return true if damaged was applied (e.i. the fighter did not dodge) 
//      Return False is damage was not applied (e.i. the fighter dodge)
//      Modify the fighter pv accordingly
bool apply_damage(fighter_t f);

//PRE: The fighter list is already inisialized 
//POST: Return de average of pv of all the fighters in fighters_list (return 0 in the list is empty)
int compute_average_pv(LL_t fighters_list);

//PRE: f and fighter_list are initialized 
//POST: change the position of the fighter f randomly within all free adjacant tiles of f
void move_fighter(fighter_t f, LL_t fighters_list);

// ###### SELF EXPLANATORY SECTION #######
char* get_name(fighter_t fighter);

int get_pv(fighter_t f);

void set_pv(fighter_t f, int pv);

int get_x(fighter_t f);

int get_y(fighter_t f);

int get_speed(fighter_t f);

void set_position(fighter_t f, int x, int y);

bool is_alive(fighter_t f);

bool is_same_position(fighter_t f1, fighter_t f2);

#endif
