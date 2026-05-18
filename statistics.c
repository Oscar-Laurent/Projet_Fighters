#include "statistics.h"

#define Dict_size 7
#define Dict_threshold 0.75

struct Dictionary {
    int size; 
    int len;
    entry_t* tab;
};

struct Entry {
    char* key;  // The fighter name
    fighterStat_t value;
};

struct FighterStat {
    int damage_done;
    int damage_get;
    int resurection_nbr;
    InjuredFigtherLL_t injuredFighters;
};

struct InjuredFigtherNode {
    char* name;
    int damageDone;
    struct InjuredFigtherNode* next;
};

struct InjuredFigtherLL {
    int len;
    struct InjuredFigtherNode* first;
    struct InjuredFigtherNode* last;
};

InjuredFigtherLL_t newIFList(void) {
  InjuredFigtherLL_t liste = malloc(sizeof(*liste));
  liste->len = 0;
  liste->first = NULL;
  liste->last = NULL;
  return liste;
}

void addInjuredFigther(InjuredFigtherLL_t liste, char* name, int damage) {
  struct InjuredFigtherNode* noeud = malloc(sizeof(*noeud));
  noeud->name = strdup(name);
  noeud->damageDone = damage;
  noeud->next = NULL;
  if(liste->len==0){
    liste->first = noeud;
  }
  else{
    liste->last->next = noeud;
  }
  liste->last = noeud;
  liste->len++;
}

bool isNameInList(InjuredFigtherLL_t liste, char* name) {
    struct InjuredFigtherNode* node_i = liste->first;
    bool isIn = false;
    while (node_i != NULL) {
        if (strcmp(node_i->name, name) == 0) {
            isIn = true;
            break;
        }
        node_i = node_i->next;
    }
    return isIn;
}

void addDamage(InjuredFigtherLL_t liste, char* name, int dammageToAdd) {
    struct InjuredFigtherNode* node_i = liste->first;
    while (node_i != NULL) {
        if (strcmp(node_i->name, name) == 0) {
            node_i->damageDone += dammageToAdd;
            break;
        }
        node_i = node_i->next;
    }
}

void updateDamageStat(dict_t statList, char* shooterName, char* targetName, int damage) {
    // Shooter not in the stat list
    if (!isInDict(statList, shooterName)) {
        fighterStat_t shooterStat = malloc(sizeof(*shooterStat));
        shooterStat->damage_done = damage;
        shooterStat->damage_get = 0;
        shooterStat->resurection_nbr = 0;
        shooterStat->injuredFighters = newIFList();
        addToDict(statList, shooterName, shooterStat);
    } 
    // target not in the stat list
    if (!isInDict(statList, targetName)) {
        fighterStat_t targetStat = malloc(sizeof(*targetStat));
        targetStat->damage_done = 0;
        targetStat->damage_get = damage;
        targetStat->resurection_nbr = 0;
        targetStat->injuredFighters = newIFList();
        addToDict(statList, targetName, targetStat);
    } 
    // both target and shooter in the stat list
    if (isInDict(statList, shooterName) && isInDict(statList, targetName)) {
        fighterStat_t shooterStat = getFromDict(statList, shooterName);
        fighterStat_t targetStat = getFromDict(statList, targetName);
        shooterStat->damage_done += damage;
        if (isNameInList(shooterStat->injuredFighters, targetName)) 
            addDamage(shooterStat->injuredFighters, targetName, damage);
        else 
            addInjuredFigther(shooterStat->injuredFighters, targetName, damage);
        targetStat->damage_get += damage;
    }
}

void updateResurectionNumber(dict_t statList, char* name) {
    fighterStat_t fighterStat = getFromDict(statList, name);
    fighterStat->resurection_nbr += 1;
}

//PRE: word in a string initialized
//POST: Retunr the somme of each character modolu n
int hashFunction(char* word, int n) {
    unsigned long hash = 5381;
    int c;
    while ((c = *word++) != '\0') {
        hash = ((hash << 5) + hash) + (unsigned long)c; // hash * 33 + c
    }
    return (int)(hash % (unsigned long) n);
}   

dict_t newDict(int taille) {
    dict_t new_dict = malloc(sizeof(*new_dict));
    new_dict->tab = calloc((unsigned long) taille, sizeof(entry_t)); // malloc puting 0 evrywhere
    new_dict->len = 0;
    new_dict->size = taille;
    return new_dict;
}

//POST: Create a new Hash table of double size and fill it with all the entry of dict
void doubleDict(dict_t dict) {
    dict_t new_dict = newDict(dict->size * 2);
    for (int i = 0; i < dict->size; i++) {
        if (dict->tab[i] != NULL && strcmp(dict->tab[i]->key, "") != 0) 
            addToDict(new_dict, dict->tab[i]->key, dict->tab[i]->value);  // add all value wite their new hash
    }
    free(dict->tab);
    dict->tab = new_dict->tab;  // copy of the new doubled tab into the old tab
    dict->size = new_dict->size;
    free(new_dict);
}

bool isInDict(dict_t dict, char* key) {
    int hashed_key = hashFunction(key, dict->size);
    while (dict->tab[hashed_key] != NULL && strcmp(dict->tab[hashed_key]->key, key)) {
        hashed_key = (hashed_key + 1) % dict->size;
    }
    if (dict->tab[hashed_key] == NULL)
        return false;
    else 
        return true;
}   

void addToDict(dict_t dict, char* key, fighterStat_t value) {
    entry_t new_entry = malloc(sizeof(*new_entry));
    new_entry->key = strdup(key);  // copy the key into another memory space 
    if (new_entry->key == NULL) {
        perror("strdup error");
        exit(-1);
    }
    new_entry->value = value;
    int hashed_key = hashFunction(key, dict->size);
    entry_t* tab = dict->tab;
    while (dict->tab[hashed_key] != NULL) {
        hashed_key = (hashed_key + 1) % dict->size;
    }
    tab[hashed_key] = new_entry;
    dict->len++;
    
    if ((float) dict->len / (float) dict->size >= Dict_threshold)  // check if the dict full and double it if so
        doubleDict(dict);
}

fighterStat_t getFromDict(dict_t dict, char* key) {
    int hashed_key = hashFunction(key, dict->size);
    while (dict->tab[hashed_key] != NULL && strcmp(dict->tab[hashed_key]->key, key)) {
        hashed_key = (hashed_key + 1) % dict->size;
    }
    if (dict->tab[hashed_key] == NULL) {
        perror("getFromdict: key not in Hash table");
        exit(-1);
    }
    else
        return dict->tab[hashed_key]->value;
        
}

void removeFromDict (dict_t dict, char* key) {
    int hashed_key = hashFunction(key, dict->size);
    entry_t* tab = dict->tab;
    while(tab[hashed_key] != NULL &&  strcmp(tab[hashed_key]->key, key) != 0)  { // tab[hashed_key]->key != key
        hashed_key = (hashed_key + 1) % dict->size; //  Sondage linéaire
    }
    if (tab[hashed_key] != NULL) {
        tab[hashed_key]->key[0] = '\0';
        dict->len--;
    }
}

int sizeOfDict(dict_t dict) {
    return dict->size;
}

void printStatDict(dict_t statDict) {
    if (statDict->size <= 0)
        printf("No Statistic to print.\n");
    else {
    char* name_i = NULL;
    fighterStat_t Fstat_i = NULL;
    for (int i = 0; i < statDict->size; i++) {
        if (statDict->tab[i] == NULL)
            continue;

        Fstat_i = statDict->tab[i]->value;
        name_i = statDict->tab[i]->key;
        printf("- Fighter : %-11s\n Dégats Subis : %i\n Dégats infligé : %i\n Nombre de résurection %i\n",
             name_i, Fstat_i->damage_get, Fstat_i->damage_done, Fstat_i->resurection_nbr);
        InjuredFigtherLL_t injuredF_list = Fstat_i->injuredFighters;
        InjuredFigtherNode_t node_i = injuredF_list->first;
        printf(" Fighter(s) blessé(s) : ");
        for (int j = 0; j < injuredF_list->len; j++) {
            char* injuredF_name = node_i->name;
            int damage = node_i->damageDone;
            printf("%s (%i)", injuredF_name, damage);
            node_i = node_i->next;
            if (j != injuredF_list->len -1)
                printf(", ");
        }
        printf("\n\n");
        
    }
    }
}

