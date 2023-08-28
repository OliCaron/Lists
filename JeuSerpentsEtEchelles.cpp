/////////////////////////////////////////////////////////////////////////////
//Fichier JeuSerpentsEtEchelles.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file JeuSerpentsEtEchelles.cpp
 * \brief Ce fichier contient une implémentation de la classe JeuSerpentsEtEchelles
 * \author Olivier Caron
 * \version 0.1
 * \date mai-juin 2023
 */

#include "JeuSerpentsEtEchelles.h"

using std::cout;
using std::endl;
using std::string;
using std::ostream;

namespace tp1
{
    /**
     * \fn JeuSerpentsEtEchelles::JeuSerpentsEtEchelles()
   * \brief Constructeur sans parametre
   *  Initialisation de la liste de cases, de la liste de choix de cartes et de la liste de joueurs selon des valeurs par défaut
   * \return Un objet JeuSerpentsEtEchelles
   */
    JeuSerpentsEtEchelles::JeuSerpentsEtEchelles() : m_cases(), m_choix(), m_joueurs()
    {
    }

    /**
     * \fn Resultat JeuSerpentsEtEchelles::jouer(unsigned int maximumDeTours)
   * \brief Boucle de jeu
   * \param[in] maximumDeTours Le nombre maximum de tours
   * \return Resultat Le Résultat de la partie
   */
    Resultat JeuSerpentsEtEchelles::jouer(unsigned int maximumDeTours)
    {
        cartePige = 1;
        for (int i = 1; i < maximumDeTours - 1; ++i) {

            nbDeTours++;

            for (int j = 0; j < m_joueurs.taille(); ++j) {

                Joueur joueurActuel = m_joueurs.defiler();
                bool peutAller = false;

                Case::Couleur cartePigee = pigerCarte();
                cartePige++;

                if (joueurActuel.position.existeCaseSuivante(cartePigee))
                {
                    joueurActuel.position.caseSuivante(cartePigee);
                    peutAller = true;
                }

                if(joueurActuel.position.caseCourante().decoration == Case::Decoration::Echelle && peutAller)
                {
                    Case::Couleur cartePigee = pigerCarte();
                    cartePige++;
                    if (joueurActuel.position.existeCaseSuivante(cartePigee))
                    {
                        joueurActuel.position.caseSuivante(cartePigee);
                    }
                    peutAller = false;
                }
                else if(joueurActuel.position.caseCourante().decoration == Case::Decoration::Serpent & peutAller)
                {
                    Case::Couleur cartePigee = pigerCarte();
                    cartePige++;
                    if (joueurActuel.position.existeCasePrecedente(cartePigee))
                    {
                        joueurActuel.position.casePrecedente(cartePigee);
                    }
                    peutAller = false;
                }

                m_joueurs.enfiler(joueurActuel);

                if (joueurActuel.position.estADerniereCase())
                {
                    return Resultat(nbDeTours, joueurActuel.nom);
                }
            }

        }

        // Aide sur l'utilisation des itérateurs de cases que possèdent les joueurs.
        // Supposer que unJoueur est une instance de la classe Joueur, alors :
        // unJoueur.position.existeCaseSuivante(uneCouleur) : permet de savoir si une case de couleur «uneCouleur»
        // se trouve après la case où se trouve unJoueur.
        // unJoueur.position.caseSuivante(uneCouleur) : permet de déplacer un joueur sur la prochaine case de couleur uneCouleur.
        // unJoueur.position.caseCourante().decoration : permet de connaître la décoration de la case sur laquelle
        // se trouve unJoueur.
        // Voir la classe ListeDeCases::Iterateur pour connaitre les autres fonctions disponibles.
    }

    //Les quatre méthodes suivantes sont utilisées par le générateur jeu.
    //Normalement, vous ne devriez pas avoir besoin de les appeler.

    //Ne pas modifier cette méthode.
    /**
     * \fn void JeuSerpentsEtEchelles::effacer()
    * \brief Efface le jeu afin d'en créer un nouveau
    */
    void JeuSerpentsEtEchelles::effacer()
    {
       while ( m_cases.taille() > 0 )
          m_cases.enleverCase(1);
       while ( m_choix.taille() > 0 )
          m_choix.enleverPos(1);
       while ( m_joueurs.taille() > 0 )
          m_joueurs.defiler();
    }

    //Ne pas modifier cette méthode.
    /**
     * \fn void JeuSerpentsEtEchelles::ajouterCase( Case &_case )
    * \brief Ajoute une case à la fin de la liste de cases
    * \param[in] _case La case à ajouter
    */
    void JeuSerpentsEtEchelles::ajouterCase( Case &_case )
    {
       m_cases.ajouterCaseALaFin( _case );
    }

    //Ne pas modifier cette méthode.
    /**
     * \fn  void JeuSerpentsEtEchelles::ajouterChoix( Case::Couleur couleur )
     * \brief Ajoute un choix de couleur à la fin de la liste de choix de couleur
     * \param[in] _case La couleur à ajouter
     */
    void JeuSerpentsEtEchelles::ajouterChoix( Case::Couleur couleur )
    {
       m_choix.ajouterFin( couleur );
    }

    //Ne pas modifier cette méthode.
    /**
     * \fn void JeuSerpentsEtEchelles::ajouterJoueur( Joueur joueur )
     * \brief Ajoute un joueur à la fin de la liste de joueurs
     * \param[in] joueur Le joueur à ajouter
     */
    void JeuSerpentsEtEchelles::ajouterJoueur( Joueur joueur )
    {
       m_joueurs.enfiler( joueur );
    }

    //Ne pas modifier cette méthode.
    /**
     * \fn ListeDeCases::Iterateur JeuSerpentsEtEchelles::premiereCase()
   * \brief Accesseur pour un itérateur débutant à la première case du jeu
   * \return Iterateur l'itérateur créé
   */
    ListeDeCases::Iterateur JeuSerpentsEtEchelles::premiereCase()
    {
       return m_cases.debut();
    }


    //Ne pas modifier cette fonction.
    /**
     * \fn ostream& operator<<(ostream& os, const Joueur & joueur)
    * \brief Surcharge de l'opérateur <<
    */
    ostream& operator<<(ostream& os, const Joueur & joueur)
    {
       os << joueur.nom << " : " << joueur.position.positionCourante();
       return os;
    }

    //Ne pas modifier cette méthode.
    /**
     * \fn  void JeuSerpentsEtEchelles::afficheResultats(Resultat gagnant)
     * \brief Affiche le résultat lorsque le jeu se termine
     * \param[in] gagnant Le joueur gagnant
     */
    void JeuSerpentsEtEchelles::afficheResultats(Resultat gagnant)
    {

       if (gagnant.nom != "")
          cout << "Gagnant : " << gagnant.nom << endl;
       else
          cout << "Aucun gagnant" << endl;
       cout << "Nombre de tours realises : " << gagnant.nombreDeTours << endl;
       cout << "Position des joueurs : " << endl;
       cout << m_joueurs << endl;

       cout << "Plateau de jeu:" << endl;
       cout << m_cases << endl;

       cout << "Liste de choix:" << endl;
       cout << m_choix << endl;
    }

    /**
     * \fn   Case::Couleur JeuSerpentsEtEchelles::pigerCarte()
   * \brief Méthode permettant de piger une carte et d'avancer dans la liste de cartes
   * \return Case::Couleur La couleur de la carte pigée
   */
    Case::Couleur JeuSerpentsEtEchelles::pigerCarte()
    {
        if(cartePige > m_choix.taille())
        {
            cartePige = 1;
        }

        return m_choix.element(cartePige);
    }
}
