#include "tas_max.h"

#define TAILLE 10

struct tas{
    char tab[TAILLE];
    int tailleTas;
};

char getValeurT(tas T, sommet s){
    return T->tab[s];
}

char valeurRac(tas T){
    return T->tab[1];
}

sommet filsGT(sommet s){
    return s*2;
}

sommet filsDT(sommet s){
    return s*2+1;
}

sommet pereT(sommet s){
    return s/2;
}


tas creerT(char x){
    tas T = malloc(sizeof(*T));
    T->tab[0] = '#';
    T->tab[1] = x;
    T->tailleTas = 2;
    return T;
}

void ajouterT(tas T, char x){
    T->tab[T->tailleTas] = x;
    reorganisationMT(T,T->tailleTas);
    T->tailleTas++;
}

void supprimerT(tas T){
    --(T->tailleTas);
    T->tab[1] = T->tab[T->tailleTas];
    reorganisationDT(T, 1);
}

void detruireT(tas T){
    free(T);
}

void reorganisationMT(tas T, sommet s){
    if(s != 1){
        sommet p = pereT(s);
        if(getValeurT(T,p) > getValeurT(T,s)){
            char tmp = T->tab[p];
            T->tab[p] = T->tab[s];
            T->tab[s] = tmp;
            reorganisationMT(T, pereT(s));
        }
    }
}

void reorganisationDT(tas T, sommet s){
    if(s < (T->tailleTas)){
        sommet o = filsGT(s);
        sommet p = filsDT(s);
        if(o < T->tailleTas){
            if(p < T->tailleTas){
                if(getValeurT(T,p)<getValeurT(T,o)){
                    o=p;
                }
            }
            if(getValeurT(T,o)<getValeurT(T,s)){
                char tmp = T->tab[o];
                T->tab[o] = T->tab[s];
                T->tab[s] = tmp;
                reorganisationDT(T,o);
            }
        }
    }
}

bool estFeuilleT(tas T){
    return(T->tailleTas == 2);
}

void changeValeurT(tas T, sommet s, char x){
    T->tab[s] = x;
    if(getValeurT(T,s)>getValeurT(T,pereT(s))){
        reorganisationMT(T,s);
    }
    if(getValeurT(T,s)<getValeurT(T,filsDT(s)) || getValeurT(T,s)<getValeurT(T,filsGT(s))){
        reorganisationDT(T,s);
    }
}

void afficherTableauTas(tas T){
    int i = 1;
    while(i<T->tailleTas-1){
        printf("%c", getValeurT(T, i));
        i++;
    }
    printf("%c", getValeurT(T,i));
    printf("\n");
}

void afficherTDecroissant(tas T){
    printf("Affichage par suppression : ");
    while(!estFeuilleT(T)){
        printf("%c", valeurRac(T));
        supprimerT(T);
    }
    printf("%c", valeurRac(T));
    printf("\n");
}
