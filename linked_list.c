#include "linked_list.h"
#include "Fighters.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

struct Node{
  fighter_t valeur;
  struct Node* next;
};

struct LinkedList {
  int taille;
  struct Node* first;
  struct Node* last;
};

//PRE: /
//POST: initialise une liste chainée vide et renvoie un pointeur vers celle-ci 
LL_t new_list(void){
  LL_t liste = malloc(sizeof(*liste));
  liste->taille = 0;
  liste->first = NULL;
  liste->last = NULL;
  return liste;
}

//PRE: list est initialisée
//POST: renvoie le nombre d'éléments présents dans list. list n'est pas modifiée.
int length(LL_t liste){
  return liste->taille;
}

//PRE: liste est initialisée
//POST: length(liste') = length(liste)+1 et le premier élément de liste est val. Le reste n'a pas été modifié
void add_item(LL_t liste, fighter_t val){
  struct Node* noeud = malloc(sizeof(*noeud));
  noeud->valeur = val;
  noeud->next = NULL;
  if(liste->taille==0){
    liste->first = noeud;
  }
  else{
    liste->last->next = noeud;
  }
  liste->last = noeud;
  liste->taille++;
}

//PRE: liste est initialisé, length(liste)>0
//POST: renvoie le premier élément de liste (élément le plus "à gauche") et l'enlève de la liste.
//      length(liste)=length(liste)-1 
//      Le reste n'est pas modifié.
fighter_t get_first(LL_t liste){
  fighter_t val = liste->first->valeur;
  struct Node* save_first = liste->first;
  liste->first = liste->first->next;
  free(save_first);
  liste->taille--;
  if(liste->taille==0){
    liste->last = NULL;
  }
  return val;
}

//PRE: liste est initialisé, length(liste)>0
//POST: renvoie le dernier élément de liste (élément le plus "à droite") et l'enlève de la liste.
//      length(liste)=length(liste)-1 
//      Le reste n'est pas modifié.
fighter_t get_last(LL_t liste){
    fighter_t val = liste->last->valeur;
    if(liste->taille==1){
      free(liste->last);
      liste->last = NULL;
      liste->first = NULL;
    }
    else{
      struct Node* iterator = liste->first;
      while(iterator->next!=liste->last){
        iterator = iterator->next;
      }
      free(liste->last);
      liste->last = iterator;
      liste->last->next = NULL;
    }
    liste->taille--;
    return(val);
}

fighter_t get_by_idx(LL_t fighter_list, int x) {
  if (x >= length(fighter_list) || x < 0)
    return NULL;

  struct Node* node_i = fighter_list->first;
  for (int i = 0; i < x; i++) {
    node_i = node_i->next;
  }
  return node_i->valeur;
}

//PRE: liste est initialisée
//POST: toute la mémoire allouée pour liste est libérée
void destroy_list(LL_t liste){
  while(liste->taille>0){
    get_first(liste);
  }
  free(liste);
}

fighter_t remove_by_idx(LL_t liste, int idx) {
  if (idx < 0 || idx >= liste->taille)
    return NULL;
  if (idx == 0)
    return get_first(liste);
  if (idx == liste->taille - 1)
    return get_last(liste);

  // Got at the idx-1 node
  struct Node* prev_node = liste->first;
  for (int i = 0; i < idx - 1; i++) {
    prev_node = prev_node->next;
  }
  
  struct Node* node_i = prev_node->next;
  fighter_t val = node_i->valeur;
  prev_node->next = node_i->next;
  free(node_i);
  liste->taille--;
  return val;
}

