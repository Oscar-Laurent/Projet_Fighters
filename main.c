#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linked_list.h"
#include "Fighters.h"
#include "utils.h"
#include "PQ.h"
#include "shot.h"
#include "statistics.h"

int main(void) {
    srand((unsigned int)time(NULL));

    int fighter_number;
    LL_t fighters_list = new_list();
    PQ_t shots_list = new_PQ();

    printf("Entrez le nombre de joueur: ");
    int matches = scanf("%i", &fighter_number);
    while (matches != 1) {
            printf("\nCe n'est pas un nombre !\n");
            scanf("%*[^\n]");
            matches = scanf("%i", &fighter_number);
        }

    if (fighter_number < 2 || fighter_number > MAX_X * MAX_Y) {
        printf("Le nombre de joueur doit se trouver entre 2 et %i\n", MAX_X * MAX_Y);
        destroy_list(fighters_list);
        return 1;
    }

    for (int i = 0; i < fighter_number; i++) {
        fighter_t new_fighter = rand_init_fighter(fighters_list);
        add_item(fighters_list, new_fighter);
    }

    printf("\n================ Etat initial ================\n");
    print_fighter_list(fighters_list);

    dict_t stats_list = newDict(fighter_number * 2);
    fighter_t last_dead = NULL;
    int resurrection_chance = 10;
    int turn = 0;

    while (1) {
        turn++;
        printf("\n\n================ Tour %d ================\n", turn);

        // Resurrection
        if (last_dead != NULL) {
            if (random_number(1, 100) <= resurrection_chance) {
                int new_pv = compute_average_pv(fighters_list);
                set_pv(last_dead, new_pv);
                int rx, ry;
                if (free_position(fighters_list, &rx, &ry)) {
                    set_position(last_dead, rx, ry);
                    add_item(fighters_list, last_dead);
                    printf("%s est ressuscite avec %d PV!\n", get_name(last_dead), new_pv);
                    updateResurectionNumber(stats_list, get_name(last_dead));
                    last_dead = NULL;
                }
            }
        }

        // Queueing all shots in the priority queue
        for (int i = 0; i < length(fighters_list); i++) {
            int shot_roll = random_number(0, 1);
            if (shot_roll)
                continue;  // Skip 50% of the time
            
            fighter_t fighter_i = get_by_idx(fighters_list, i);
            shot_t shot_i = init_shot(fighter_i);
            enqueue(shots_list, shot_i); 
        }

        // Traiter les tirs par ordre de vitesse
        while (PQ_len(shots_list) > 0) {
            shot_t shot_i = serve_max(shots_list);
            fighter_t shooter = get_shooter(shot_i);
            int* target_position = get_target(shot_i);
            fighter_t target_fighter = fighter_at_position(fighters_list, target_position[0], target_position[1]);
            if (!is_alive(shooter)) {
                free(shot_i);
                continue;
            }
            if (target_fighter == NULL) {
                printf("%s tire à la position (%i, %i) mais cette case est vide...\n", get_name(shooter), target_position[0], target_position[1]);
                free(shot_i);
                continue;
            }
            bool is_hit = apply_damage(target_fighter, get_power(shot_i));

            if (is_hit) {
                printf("%s tire à la position (%i, %i) et inflige %i dégat(s) à %s !\n",
                     get_name(shooter), target_position[0], target_position[1], get_power(shot_i), get_name(target_fighter));
                updateDamageStat(stats_list, get_name(shooter), get_name(target_fighter), get_power(shot_i));
            }
            else {
                printf("%s tire à la position (%i, %i) mais %s esquive !\n",
                     get_name(shooter), target_position[0], target_position[1], get_name(target_fighter));
            }
            free(shot_i);
        }

        // Retirer les morts (en arriere)
        for (int i = length(fighters_list) - 1; i >= 0; i--) {
            fighter_t f = get_by_idx(fighters_list, i);
            if (get_pv(f) <= 0) {
                remove_by_idx(fighters_list, i);
                printf("%s est mort!\n", get_name(f));
                if (last_dead != NULL) {
                    destroy_fighter(last_dead);
                }
                last_dead = f;
            }
        }

        // Verifier victoire
        if (length(fighters_list) <= 1) break;

        // Deplacement
        for (int i = 0; i < length(fighters_list); i++) {
            move_fighter(get_by_idx(fighters_list, i), fighters_list);
        }

        // Afficher etat
        print_fighter_list(fighters_list);
    }

    // Fin de jeu
    printf("\n=== Fin du jeu ===\n");
    if (length(fighters_list) == 1) {
        fighter_t winner = get_by_idx(fighters_list, 0);
        printf("Le gagnant est %s avec %d PV!\n", get_name(winner), get_pv(winner));
    } else {
        printf("Tous les combattants sont morts en meme temps!\n");
    }

    // Affichage des statisitiques de jeu
    printf("\n=== Statistique de jeu ===\n");
    printStatDict(stats_list);

    // Cleanup
    destroy_list(fighters_list);
    if (last_dead != NULL) {
        destroy_fighter(last_dead);
    }

    return 0;
}
