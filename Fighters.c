#include "Fighters.h"
#include "linked_list.h"
#include "utils.h"
#define MAX_X 10
#define MAX_Y 10

struct Fighter {
    char* name;
    int pv;
    int speed;
    int x;
    int y;
};

fighter_t rand_init_fighter(fighters_list_t fighters_list) {
    fighter_t new_fighter = malloc(sizeof(*new_fighter));
    int new_name_lenght = random_number(4, 10);
    char *new_name = malloc(sizeof(char) * (unsigned long)(new_name_lenght + 1));
    random_name(new_name_lenght, new_name);

    new_fighter->name = new_name;
    new_fighter->pv = random_number(1, 5);
    new_fighter->speed = random_number(1, 5);
    int new_x, new_y;
    if (free_position(fighters_list, &new_x, &new_y)) {
        new_fighter->x = new_x;
        new_fighter->y = new_y;
    }

    return new_fighter;
}

fighters_list_t new_fighters_list(void) {
    return new_list();
}

void add_fighter(fighters_list_t fighters_list, fighter_t new_fighter) {
    add_item(fighters_list, new_fighter);
}


char* get_name(fighter_t fighter) {
    return fighter->name;
}


bool is_same_position(fighter_t f1, fighter_t f2) {
    return f1->x == f2->x && f1->y == f2->y;
}

bool free_position(LL_t fighters_list, int *out_x, int *out_y) {
    int x, y;
    int n_try = 0;
    int max_try = 2 * (length(fighters_list) + 5);
    bool found = false;

    while (!found && n_try < max_try){
        x = random_number(0, MAX_X - 1);
        y = random_number(0, MAX_Y - 1);
        found = true;
        n_try++;

        for (int i = 0; i < length(fighters_list); i++){
            fighter_t fighter_i = get_by_idx(fighters_list, i);
            if (x == fighter_i->x && y == fighter_i->y) {
                found = false;
                break;
            }
        }
    }
    if (found) {
        *out_x = x;
        *out_y = y;
    }
    return found;
}

void print_attribute(fighter_t f) {
    printf("Fighter named: %-16s | pv: %-3i | speed: %-3i | x: %-2i | y: %-2i\n",
         f->name, f->pv, f->speed, f->x, f->y);
}

void print_fighter_list(fighters_list_t fighters_list) {
    for (int i = 0; i < length(fighters_list); i++) {
        print_attribute(get_by_idx(fighters_list, i));
    }
}

int get_pv(fighter_t f) {
    return f->pv;
}

void set_pv(fighter_t f, int pv) {
    f->pv = pv;
}

int get_x(fighter_t f) {
    return f->x;
}

int get_y(fighter_t f) {
    return f->y;
}

int get_speed(fighter_t f) {
    return f->speed;
}

void set_position(fighter_t f, int x, int y) {
    f->x = x;
    f->y = y;
}

void destroy_fighter(fighter_t f) {
    if (f != NULL) {
        free(f->name);
        free(f);
    }
}

bool is_alive(fighter_t f) {
    return f->pv > 0;
}

bool apply_damage(fighter_t f) {
    int dodge_roll = random_number(1, 100);
    if (dodge_roll <= f->speed * 10) {
        printf("%s esquive le tir!\n", f->name);
        return f->pv > 0;
    }
    f->pv -= 1;
    return f->pv > 0;
}

int compute_average_pv(LL_t fighters_list) {
    int total = 0;
    int len = length(fighters_list);
    for (int i = 0; i < len; i++) {
        total += get_by_idx(fighters_list, i)->pv;
    }
    int avg = total / len;
    return avg;
}

void move_fighter(fighter_t f, LL_t fighters_list) {
    int dx[] = {0, 0, 1, -1, 1, -1, -1, 1};  // All the differents tile availble around the fighter
    int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};  // position (e.i. the 8 tiles right next to him )
    int valid_x[8];  // array of all valid (within the board boundaries and unoccupied) tile 
    int valid_y[8];  // available around the fighter
    int valid_count = 0;

    for (int tile_i = 0; tile_i < 8; tile_i++) {
        int new_x = f->x + dx[tile_i];
        int new_y = f->y + dy[tile_i];
        if (new_x < 0 || new_x >= MAX_X || new_y < 0 || new_y >= MAX_Y) 
            continue; // Skip this new position of not within the board boundaries

        bool occupied = false;  // Check if the new postion is already occupied
        for (int i = 0; i < length(fighters_list); i++) {
            fighter_t other = get_by_idx(fighters_list, i);
            if (other != f && other->x == new_x && other->y == new_y) {
                occupied = true;
                break;
            }
        }
        if (!occupied) {
            valid_x[valid_count] = new_x;
            valid_y[valid_count] = new_y;
            valid_count++;
        }
    }
    if (valid_count > 0) {
        int choice = random_number(0, valid_count - 1);
        f->x = valid_x[choice];
        f->y = valid_y[choice];
    }
}
