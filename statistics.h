# ifndef STAT_H
# define STAT_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "linked_list.h"

struct Dictionary;
struct Entry;
struct FighterStat;
struct OverAllStats;
struct InjuredFigtherNode;
struct InjuredFigtherLL;

typedef struct FighterStat* fighterStat_t;
typedef struct Entry* entry_t;
typedef struct Dictionary* dict_t;
typedef struct OverAllStats* OverAllStats_t;
typedef struct InjuredFigtherLL* InjuredFigtherLL_t;
typedef struct InjuredFigtherNode* InjuredFigtherNode_t;

//PRE: /
//POST: Return an empty list
InjuredFigtherLL_t newIFList(void);

//PRE: statlist is initalized
//POST: Add or update the damage stat and handle if either shooter or target names are not in the list
void updateDamageStat(dict_t statList, char* shooterName, char* targetName, int damage);

//PRE: statlist is initalized and name in the list
//POST: Add the resurection number of 1 and handle if the name is not in the list
void updateResurectionNumber(dict_t statList, char* name);

//PRE: list is initialised and the name is not is the list already
//POST: add the name at the end of the linked list along with the damage
void addInjuredFigther(InjuredFigtherLL_t liste, char* name, int damage);

//PRE: list is initialised 
//POST: return true if the name is in the list and false if not
bool isNameInList(InjuredFigtherLL_t liste, char* name);

//PRE: list is initialised and name is in the list
//POST: add the damage to the value already here
void addDamage(InjuredFigtherLL_t liste, char* name, int dammageToAdd);

//PRE: /
//POST: Return an empty dict
dict_t newDict(int size);

//PRE: dict is initialized and (key:value) not in dict
//POST: dict = dict' U {(key:valeur)}
void addToDict(dict_t dict, char* key, fighterStat_t value);

//PRE: dict is initialized and (key:value) in dict
//POST: Return valeur tq. (key:valeur) in dict
fighterStat_t getFromDict(dict_t dict, char* key);

//PRE: dict is initialized and (key:value) in dict
//POST: dict = dict' \ {(key:old_value)}
void removeFromDict(dict_t dict, char* key);

//PRE: dict is initialized
//POST: return true if (key:value) in dict
//      return false if not
bool isInDict(dict_t dict, char* key);

int sizeOfDict(dict_t dict);

//PRE: Statdict is initialized 
//POST: Print all rows of the satadict that are not empty
void printStatDict(dict_t statDict);

#endif
