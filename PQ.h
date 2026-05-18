/*

Auteur: Cédric Libert
Description: file d'entiers. On peut y ajouter des éléments et récupérer à chaque fois l'élément qui est dans la
file depuis le plus longtemps.

*/
#ifndef PQ_H
#define PQ_H

#include <stdlib.h>
#include <stdio.h>
#include "shot.h"

struct PQ; //déclaration du nom de ma structure
typedef struct PQ* PQ_t; //déclaration d'un alias qui désigne le type "pointeur vers struct Queue"

//PRE: /
//POST: initialise une PQ vide avec une relation d'ordre leq 
PQ_t new_PQ(void);

int PQ_len(PQ_t pq);

//POST: Return the left child index of the i^th element of the heap
int left_child(int i);

//POST: Return the parent index of the i^th element of the heap 
//      Retutn -1 if i == 0
int parent(int i);

//PRE: PQ is initialized and a and b are between 0 and len(PQ->heap)
//POST: Swap the element at the a an b^th index of the PQ->heap array
void swap(PQ_t PQ, int a, int b);

//PRE: pq est initialisée ET 
//     pq->last < pq->max
//POST: pq = pq' U {item}
void enqueue(PQ_t pq, shot_t item);

//PRE: pq est initialisée, taille(pq)>0
//POST: pq = pq' \ {x} tq x est l'élément le plus prioritaire de pq
//      renvoie x
shot_t serve_max(PQ_t pq);

//PRE: pq est initialisée, taille(pq)>0
//POST: renvoie x tq x est l'élément le plus prioritaire de pq      
int peek(PQ_t pq);

//PRE: pq initialisée
//POST: renvoie 1 si pq est vide, 0 sinon
int empty(PQ_t pq);

//PRE: pq est initialisée 
//POST: remonte l'élément à l'index idx au niveaux correct
void bubble_up(PQ_t pq, int idx);

//PRE: pq est initialisée 
//POST: descent l'élément à l'index idx au niveaux correct
void bubble_down(PQ_t pq, int idx);

#endif
