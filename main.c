#include <stdio.h>
#include <stdlib.h>


#include "type_missile.h"
#include "gestion_bateau.h"
#include "initialisation_interface.h"
#include "arbitre_de_la_partie.h"
#include "donnees_du_jeux.h"
#include "sauvegarde.h"
#include "load sauvegarde.h"
#include "fonctions_tour_de_jeu.h"


int main() {
    int i;
    int nb_bateaux=5; //donne le nombre de bateau sur la grille (dans notre cas, 5)
    int missile_choisie;
    int choix_mode_de_jeux=0,choix_difficulte=0;
    int deux_case = 0; // pour sauvegarder les Coo des bateaux




    affichage_titre_credit();



    //déclaration des structures utilisées par le jeu
    Grid boat_grid, user_grid;
    Inventory liste_missile = {0,0,0,0};
    Missile_Coordinates Coordonnees_missile = {'\0',0,0};
    save sauvegarde;
    //initialisation de la liste des 5 bateaux
    boat *liste_bateaux = NULL;
    liste_bateaux = malloc(sizeof(boat) * nb_bateaux);


    initialization_default(&boat_grid, &user_grid, liste_bateaux, nb_bateaux);



    //Le programme démarre : menu principal

    switch(affichage_menu_demarrage()) {

        case 3 :
            return 0;

        case 2 :
            fonction_lecture_sauvegarde(&sauvegarde);
            fonction_load (sauvegarde,&liste_missile,&user_grid ,&boat_grid,&choix_mode_de_jeux);

            for (i =0  ; i < nb_bateaux ; i++ ){
                load_orientation(&liste_bateaux[i],sauvegarde,i );
                load_pv (&liste_bateaux[i],sauvegarde,i);
                load_Coo (&liste_bateaux[i],sauvegarde, deux_case);
                deux_case += 2;
            }





            i = 0;
            do {
                i++;
                implentation_bateau(&liste_bateaux[i], &boat_grid);
            } while (boat_grid.grid[liste_bateaux[i].CooX][liste_bateaux[i].CooY] == '_');






            break;

        case 1 :
            for (i = 0; i < nb_bateaux; i++) {
                generation_bateau(&liste_bateaux[i], &boat_grid);
            }

            choix_mode_de_jeux= affichage_menu_mode_de_jeux();
            do {
                choix_difficulte= affichage_menu_difficulte();
                modifier_nombre_missile (choix_difficulte, &liste_missile);
            } while(choix_difficulte > 3 || choix_difficulte < 0);



            break;
        default:
            break;
    }




    ///Boucle principale du jeu

    do{
        if(check_lose_condition(liste_missile) == 0){printf("Vous avez perdu !"); exit(0);}


        if (choix_mode_de_jeux != 2 )//Si on n'est pas en mode blind, on affiche la grille à l'utilisateur
        {
            show_grid(&user_grid, liste_bateaux);
        }
        else{
            afficher_bateau_couler_et_pv(liste_bateaux,nb_bateaux);
        }

        show_grid(&boat_grid,liste_bateaux);


        affichage_choix_missile(liste_missile);

        if ( continuer_partie() == 'N' ){ //le joueur a choisie d'arreter de jouer, donc on sauvegarde avant de "fermer" le programme
            // On choisit d'abord de sauvegarder toues les donné utiles dans une structure.
            fonction_sauvegarde(&sauvegarde,liste_bateaux,liste_missile,user_grid,boat_grid,nb_bateaux,choix_mode_de_jeux);
            fonction_ecriture_sauvegarde(sauvegarde);
            return 0 ; // on quitte le programme après avoir écrit dans un fichier.txt la sauvegarde
        }
        missile_choisie = choix_missile();

        coordonnees_tir(&Coordonnees_missile);

        lancement_tir(Coordonnees_missile, missile_choisie, &boat_grid, &user_grid, &liste_bateaux, &liste_missile);

        if (choix_mode_de_jeux == 3 ){
            active_mode(choix_difficulte, liste_bateaux, &boat_grid);
        }

    } while(check_win_condition(liste_bateaux, nb_bateaux) != 0);

    printf("Vous avez gagne%d !\n",130);
    show_grid(&user_grid,liste_bateaux);
    show_grid(&boat_grid,liste_bateaux);
    return (0);
}