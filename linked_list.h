/*

Auteur: Cédric Libert
Description: liste chainée d'entiers

*/

#ifndef LL_H
#define LL_H

struct Node;
struct LinkedList; //déclaration du nom de ma structure
typedef struct LinkedList* LL_t; //déclaration d'un alias qui désigne le type "pointeur vers struct Linked_list"

#include <stdlib.h>
#include <stdio.h>
#include "Fighters.h"


//PRE: /
//POST: initialise une liste chainée vide et renvoie un pointeur vers celle-ci 
LL_t new_list(void);

//PRE: list est initialisée
//POST: renvoie le nombre d'éléments présents dans list. list n'est pas modifiée.
int length(LL_t liste);

//PRE: liste est initialisée
//POST: length(liste') = length(liste)+1 et le premier élément de liste est val. Le reste n'a pas été modifié
void add_item(LL_t liste, fighter_t val);

//PRE: liste est initialisé, length(liste)>0
//POST: renvoie le premier élément de liste (élément le plus "à gauche") et l'enlève de la liste.
//      length(liste)=length(liste)-1 
//      Le reste n'est pas modifié.
fighter_t get_first(LL_t liste);

//PRE: liste est initialisé, length(liste)>0
//POST: renvoie le dernier élément de liste (élément le plus "à droite") et l'enlève de la liste.
//      length(liste)=length(liste)-1 
//      Le reste n'est pas modifié.
fighter_t get_last(LL_t liste);

//PRE: la liste est initialisé 
//POST: return le x^th element of the list
fighter_t get_by_idx(LL_t fighter_list, int x);

//PRE: liste est initialisée
//POST: toute la mémoire allouée pour liste est libérée
void destroy_list(LL_t liste);

//PRE: liste est initialisee, 0 <= idx < length(liste)
//POST: enleve l'element a l'index idx et le renvoie. 
//      length(liste) = length(liste) - 1
fighter_t remove_by_idx(LL_t liste, int idx);

#endif
