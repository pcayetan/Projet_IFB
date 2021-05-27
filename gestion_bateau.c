//
// Created by Admin on 27/05/2021.
//
#include "gestion_bateau.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void generation_bateau(bateau * boat, tableau *grid ) {
    int i=0;



    srand(time(NULL)*boat->id);

    do {
        boat->orientation = rand() % 2;
        switch(boat->orientation) {
            case 1 :
                boat->CooX = rand() % N ;
                boat->CooY = rand() % (N-boat->length) ;
                break;
            case 0 :
                boat->CooX = rand() % (N-boat->length) ;
                boat->CooY = rand() % N ;
                break;
            default :
                printf("Erreur : orientation ni 0 ni 1");
                exit(0);
        }
    } while(verification_emplacement_bateau(boat, grid) != 1);

    do {
        i++;
        implentation_bateau(boat, grid);
    } while (grid->grid[boat->CooX][boat->CooY] == '_');
    if (i<1)
        printf("%d implementations !\n",i);
}


void implentation_bateau(bateau  * boat, tableau * grid) {
    int i;
    if(boat->orientation == 0) { //implentation verticale (axe des x)
        for (i=0; i < boat->length ; i++) {
            grid->grid[boat->CooX+i][boat->CooY] = boat->id;
        }
    } else {
        for (i=0; i < boat->length; i++) { //implentation horizontale (axe des y)
            grid->grid[boat->CooX][boat->CooY+i] = boat->id;
        }
    }

}



int verification_emplacement_bateau(bateau * boat, tableau * grid) {
    int X = boat->CooX, Y = boat->CooY;


    if(boat->orientation == 0) { //regarde pour orientation verticale
        for (; X - boat->CooX < boat->length; X++) { //la vérification doit être fait pour toutes les cases occupées par le bateau
            if (grid->grid[X][Y] != '_') { //'_' représente une case vide : si elle n'est pas vide, un bateau est déjà à cette endroit là et on ne peut donc pas générer le nouveau bateau

                return(0);
            }
        }
        return(1);

    } else {if(boat->orientation == 1) {

            for (; Y - boat->CooY < boat->length; Y++ ) {

                if (grid->grid[X][Y] != '_') {
                    return(0);
                }
            }
            return(1);
        }
    }

    return(0);
}



void generer_caracteristique_bateaux (bateau *  l_bateaux,int i ){
    if (l_bateaux == NULL){
        exit(1);
        }

        l_bateaux->length = i + 1;
        l_bateaux->id = 'a' + i;
        l_bateaux->id_dead = 'A' + i;
        l_bateaux->pv = l_bateaux->length;



}


void initialisation_pv_detaille (bateau * baot ){
    int j=0;
    for (j=0 ; j<10 ; j++){
        baot->pv_detaille[j]= 1;
    }

}


void sauvegarde_pv_detaille (bateau * baot,tableau user){
    int j=0;


    if (baot-> pv != baot->length){ // pour optimiser le programme (si le bateau n'a pas perdu de vie pas besoin de précise la ou il a été toucher ...
        switch (baot->orientation){
            case  1 :
                for ( j=0 ; j< baot->length ; j++)
                    if ( user.grid[baot->CooX][baot->CooY+j]  == 'O' ){

                        baot->pv_detaille[j] = 0;  // bateau touché sur ca j ieme case
                    }

                break ;
            case 0 :
                if ( user.grid[baot->CooX+j][baot->CooY] == 'O' ){

                    baot->pv_detaille[j] = 0;  // bateau touché sur ca j ieme case
                }

                break;


        }
    }

}