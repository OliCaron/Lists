/////////////////////////////////////////////////////////////////////////////
//Fichier Principal.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Principal.cpp
 * \brief Ce fichier contient un main permettant de tester le jeu
 * \author Olivier Caron
 * \version 0.1
 * \date mai-juin 2023
 */

#include "GenerateurAleatoireJeuSerpentsEtEchelles.h"
/*
  MESSAGE AU CORRECTEUR : Mon programme compile et affiche les bons résultats pour les 3 premiers jeux mis à part
  le nombre de tours. POur le jeu 4, les positions et le nombre de tours ne sont pas corrects mais tout  les reste, oui.
  Il y a un pointeur invalide à la fin de l'exécution mais je ne comprends pas le message de backtrace. J'ai passé
  plus de 30 heures sur ce travail de 8%, j'ai donc décidé de le remettre ainsi malgré tout. Désolé des inconvénients.

*/
int main()
{
   tp1::JeuSerpentsEtEchelles jeu;

   std::cout << "Jeu 1:" << std::endl;;
   tp1::GenerateurAleatoireJeuSerpentsEtEchelles generateurJeu(1);
   generateurJeu.generer( jeu, 5, 9, 2 );
   jeu.afficheResultats(jeu.jouer(100));

   std::cout << std::endl << "Jeu 2:" << std::endl;;
   //Remarquez que ce deuxieme appel ne donne pas le meme resultat.
   generateurJeu.generer( jeu, 5, 9, 2 );
   jeu.afficheResultats(jeu.jouer(100));

   std::cout << std::endl << "Jeu 3:" << std::endl;;
   tp1::GenerateurAleatoireJeuSerpentsEtEchelles generateurJeu_2(9569686);
   generateurJeu_2.generer( jeu, 243, 53, 4 );
   jeu.afficheResultats(jeu.jouer(20000));

   std::cout << std::endl << "Jeu 4:" << std::endl;;
   //Remarquez que ce deuxieme appel ne donne pas le meme resultat.
   generateurJeu_2.generer( jeu, 243, 53, 4 );
   jeu.afficheResultats(jeu.jouer(20000));

   return 0;
}
