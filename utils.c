#include <stdio.h>
#include <stdlib.h>
char *tab_alphabet = "abcdefghijklmnopqrstuvwxyz";

int random_number(int min, int max){
    return (rand()%(max-min+1) + min);
}

void random_name(int length, char n[]){
    int i ;
    for (i=0;i<length;i++){
        int k = random_number(1,26);// from the table of the alphabet
        n[i] = tab_alphabet[k-1];
    }
    n[i] = '\0';
}
