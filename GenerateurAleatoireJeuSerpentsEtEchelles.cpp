/////////////////////////////////////////////////////////////////////////////
//Fichier GenerateurAleatoireJeuSerpentsEtEchelles.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file GenerateurAleatoireJeuSerpentsEtEchelles.cpp
 * \brief Ce fichier contient une implémentation de la classe GenerateurAleatoireJeuSerpentsEtEchelles
 * \author IFT-2008
 * \version 0.1
 * \date mai-juin 2023
 */

#include <algorithm>
#include <sstream>
#include "GenerateurAleatoireJeuSerpentsEtEchelles.h"

using std::max;
using std::string;
using std::ostringstream;

namespace tp1
{


    /**
     * \fn GenerateurAleatoireJeuSerpentsEtEchelles::GenerateurAleatoireJeuSerpentsEtEchelles(
          unsigned int initAleatoire)
   * \brief Constructeur avec parametre
   *  Initialisation du m_generateurNombresAleatoires selon la valeur recue en parametre
   * \param[in] initAleatoire unsigned int pour aléatoire
   * \return Un objet GenerateurAleatoireJeuSerpentsEtEchelles
   */
    GenerateurAleatoireJeuSerpentsEtEchelles::GenerateurAleatoireJeuSerpentsEtEchelles(
          unsigned int initAleatoire) :
       m_compteurNomJoueurs(0), m_generateurNombresAleatoires(initAleatoire)
    {
    }

    /**
     * \fn void GenerateurAleatoireJeuSerpentsEtEchelles::generer(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreCases, unsigned int nombreDeChoix, unsigned int nombreDeJoueurs)
    * \brief Génère un jeu de Serpent et Échelles avec des valeurs aléatoires
    * \param[in] jeu Le jeu de Serpent Et Échelles
    * \param[in] nombreCases Le nombre de Cases
    * \param[in] nombreDeChoix Le nombre de choix de carte < piger
    * \param[in] nombreDeJoueurs Le nombre de joueurs
    */
    void GenerateurAleatoireJeuSerpentsEtEchelles::generer(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreCases, unsigned int nombreDeChoix, unsigned int nombreDeJoueurs)
    {
       m_compteurNomJoueurs = 0;
       jeu.effacer();
       genererCases(jeu, nombreCases);
       genererChoix(jeu, nombreDeChoix);
       genererJoueurs(jeu, nombreDeJoueurs);
    }

    /**
     * \fn  void GenerateurAleatoireJeuSerpentsEtEchelles::genererCases(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreCases)
   * \brief Génère les cases du jeu
   * \param[in] jeu Le jeu de Serpent Et Échelles
   * \param[in] nombreCases Le nombre de Cases
   */
    void GenerateurAleatoireJeuSerpentsEtEchelles::genererCases(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreCases)
    {
       for (unsigned int compteurCases = 0; compteurCases < nombreCases; compteurCases++)
       {
          Case nouvelleCase(choisirUneCouleurAleatoirement(), choisirUneDecorationAleatoirement());
          jeu.ajouterCase(nouvelleCase);
       }
    }

    /**
     * \fn   Case::Couleur GenerateurAleatoireJeuSerpentsEtEchelles::choisirUneCouleurAleatoirement()
   * \brief Choisit une couleur de façon aléatoire
   * \return Case::Couleur La couleur aléatoire
   */
    Case::Couleur GenerateurAleatoireJeuSerpentsEtEchelles::choisirUneCouleurAleatoirement()
    {
       return static_cast<Case::Couleur> (m_generateurNombresAleatoires.pige() % Case::nombreCouleurs);
    }

    /**
     * \fn Case::Decoration GenerateurAleatoireJeuSerpentsEtEchelles::choisirUneDecorationAleatoirement()
  * \brief Choisit une décoration de façon aléatoire
  * \return Case::Decoration La décoration aléatoire
  */
    Case::Decoration GenerateurAleatoireJeuSerpentsEtEchelles::choisirUneDecorationAleatoirement()
    {
       return static_cast<Case::Decoration> (m_generateurNombresAleatoires.pige()
             % Case::nombreDecorations);
    }

    /**
     * \fn  void GenerateurAleatoireJeuSerpentsEtEchelles::genererChoix(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreChoix)
    * \brief Génère une liste de choix de carte
    * \param[in] jeu Le jeu de Serpent Et Échelles
    * \param[in] nombreChoix Le nombre de choix
    */
    void GenerateurAleatoireJeuSerpentsEtEchelles::genererChoix(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreChoix)
    {
       for (unsigned int compteurChoix = 0; compteurChoix < nombreChoix; compteurChoix++)
       {
          jeu.ajouterChoix(choisirUneCouleurAleatoirement());
       }
    }

    /**
     * \fn void GenerateurAleatoireJeuSerpentsEtEchelles::genererJoueurs(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreJoueurs)
    * \brief Génère une liste de joueurs
    * \param[in] jeu Le jeu de Serpent Et Échelles
    * \param[in] nombreJoueurs Le nombre de joueurs
    */
    void GenerateurAleatoireJeuSerpentsEtEchelles::genererJoueurs(JeuSerpentsEtEchelles &jeu,
          unsigned int nombreJoueurs)
    {
       for (unsigned int indexJoueur = 0; indexJoueur < nombreJoueurs; indexJoueur++)
       {
          jeu.ajouterJoueur(genererUnJoueurAleatoirement(jeu.premiereCase()));
       }
    }

    /**
     * \fn Joueur GenerateurAleatoireJeuSerpentsEtEchelles::genererUnJoueurAleatoirement(
          ListeDeCases::Iterateur it)
    * \brief Génère un Joueur de façon aléatoire
    * \param[in] it L'itérateur
    * \return Le joueur généré
    */
    Joueur GenerateurAleatoireJeuSerpentsEtEchelles::genererUnJoueurAleatoirement(
          ListeDeCases::Iterateur it)
    {
       return Joueur(it, choisirUnNomAleatoirement());
    }

    /**
     * \fn  string GenerateurAleatoireJeuSerpentsEtEchelles::choisirUnNomAleatoirement()
    * \brief Choisit un nom de façon aléatoire
    * \return nom.str() Le nom du joueur
    */
    string GenerateurAleatoireJeuSerpentsEtEchelles::choisirUnNomAleatoirement()
    {
       m_compteurNomJoueurs++;
       ostringstream nom;
       nom << "Joueur " << m_compteurNomJoueurs;
       return nom.str();
    }

}
