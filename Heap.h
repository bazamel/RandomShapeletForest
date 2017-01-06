#ifndef TAS_MAX_H_INCLUDED
#define TAS_MAX_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct tas *tas;
typedef int sommet;

char getValeurT(tas T, sommet s);
char valeurRac(tas T);
sommet filsGT(sommet s);
sommet filsDT(sommet s);
sommet pereT(sommet s);
bool tasPlein(tas T);

tas creerT(char x);
void ajouterT(tas T, char x);
void changeValeurT(tas T, sommet s, char x);
void supprimerT(tas T);
void detruireT(tas T);

void reorganisationMT(tas T, sommet s);
void reorganisationDT(tas T, sommet s);

bool estFeuilleT(tas T);
void afficherTableauTas(tas T);
void afficherTDecroissant(tas T);

#endif // TAS_H_INCLUDED
