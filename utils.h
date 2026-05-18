#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

//PRE: /
//POST: return a random int between min and max
int random_number(int min, int max);


//PRE: n is already initialized
//POST: fill n with a random name of a given lenght 
void random_name(int length, char n[]);

#endif
