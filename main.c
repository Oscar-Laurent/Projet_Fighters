#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linked_list.h"
#include "Fighters.h"
#include "utils.h"

int main(void) {
    //srand((unsigned int)time(NULL));

    int fighter_number;
    LL_t fighters_list = new_list();

    printf("Entrez le nombre de joueur: ");
    int matches = scanf("%i", &fighter_number);
    while (matches != 1) {
            printf("\nCe n'est pas un nombre !\n");
            scanf("%*[^\n]");
            matches = scanf("%i", &fighter_number);
        }

    if (fighter_number < 2) {
        printf("Il faut au moins 2 joueurs!\n");
        destroy_list(fighters_list);
        return 1;
    }

    for (int i = 0; i < fighter_number; i++) {
        fighter_t new_fighter = rand_init_fighter(fighters_list);
        add_item(fighters_list, new_fighter);
    }

    printf("\n=== Etat initial ===\n");
    print_fighter_list(fighters_list);

    fighter_t last_dead = NULL;
    int resurrection_chance = 10;
    int turn = 0;

    while (1) {
        turn++;
        printf("\n=== Tour %d ===\n", turn);

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
                    last_dead = NULL;
                }
            }
        }

        // Degats
        for (int i = 0; i < length(fighters_list); i++) {
            apply_damage(get_by_idx(fighters_list, i));
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

    // Cleanup
    destroy_list(fighters_list);
    if (last_dead != NULL) {
        destroy_fighter(last_dead);
    }

    return 0;
}
