/////////////////////////////////////////////////////////////////////////////
//Fichier ListeDeCases.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file ListeDeCases.cpp
 * \brief Ce fichier contient une implémentation de la classe ListeDeCases
 * \author Olivier Caron
 * \version 0.1
 * \date mai-juin 2023
 */

#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "ListeDeCases.h"

using std::string;
using std::ostringstream;
using std::out_of_range;
using std::range_error;

namespace tp1
{
    /**
     * \fn  ListeDeCases::ListeDeCases()
   * \brief Constructeur sans parametre
   *  Initialisation des pointeurs de noeuds m_debut et m_fin ainsi que la taille selon des valeurs par défaut
   * \return Un objet ListeDeCases
   */
    ListeDeCases::ListeDeCases() : m_debut(0), m_fin(0), m_taille(0) {}

    /**
     * \fn ListeDeCases::~ListeDeCases()
   * \brief Destructeur
   *  Destruction des pointeurs
   */
    ListeDeCases::~ListeDeCases()
    {
        while(m_debut != m_fin)
        {
            Noeud * premierNoeud = m_debut;
            m_debut = m_debut->m_suivant;
            delete premierNoeud;
        }
        delete m_fin;
    }

    /**
     * \fn int ListeDeCases::taille() const
    * \brief Retourne la taille de la liste
    * \return m_taille, la taille de la liste
    */
    int ListeDeCases::taille() const
    {
        return m_taille;
    }

    /**
     * \fn bool ListeDeCases::estVide() const
    * \brief Retourne un booléen pour savoir si la liste est vide ou non
    * \return bool, true si la taille de la liste est égale à 0, false sinon
    */
    bool ListeDeCases::estVide() const
    {
        return m_taille == 0;
    }

    /**
  * \fn void ListeDeCases::ajouterCase(const Case& uneCase, int position)
  * \brief Permet d'ajouter une case à la liste
  * \param[in] uneCase la case à ajouter
  * \param[in] position la position à laquelle ajouter la case
  * \pre Il y a assez de mémoire pour ajouter la case
  * \pre La position d'ajout est comprise entre 1 et m_taille + 1
  * \exception range_error si la position est hors borne
  * \exception bad_alloc s'il n'y a pas assez de mémoire
*/
    void ListeDeCases::ajouterCase(const Case& uneCase, int position) {

        if (position < 1 || position > taille() + 1)
        {
            throw std::range_error ("Position a l'exterieur de la liste");
        }

        if (m_taille == 0)
        {
            m_debut = m_fin = new Noeud(uneCase);
        }
        else if ( position == 1)
        {
            m_debut = new Noeud(uneCase, m_debut);
            m_debut->m_suivant->m_precedent = m_debut;
        }
        else if (position == m_taille + 1)
        {
            m_fin = new Noeud(uneCase, nullptr, m_fin);
            m_fin->m_precedent->m_suivant = m_fin;
        }
        else
        {
            Noeud * sentinelle = noeudAt(position - 1);
            sentinelle = new Noeud(uneCase, sentinelle->m_suivant, sentinelle);
            sentinelle->m_suivant->m_precedent = sentinelle;
            sentinelle->m_precedent->m_suivant = sentinelle;
        }
        m_taille++;
    }

    /**
     * \fn void ListeDeCases::ajouterCaseALaFin(const Case& uneCase)
     * \brief Ajoute une case à la fin de la liste de case
     * \param[in] uneCase La case à ajouter
    */
    void ListeDeCases::ajouterCaseALaFin(const Case& uneCase)
    {
        ajouterCase(uneCase, m_taille + 1);
    }

    /**
     * \brief Enlève une case à une position donnée dans la liste de case
     * \param[in] position La position de la case à enlever
     * \pre La liste n'est pas vide
     * \pre La position d'ajout est comprise entre 1 et m_taille + 1
     * \exception range_error si la position est hors borne
     * \exception logic_error si la liste est vide
    */
    void ListeDeCases::enleverCase(int position)
    {
        if (position < 1 || position > taille() + 1)
        {
            throw std::range_error ("Position a l'exterieur de la liste");
        }
        else if (m_taille == 0)
        {
            throw std::logic_error ("Vous essayez d'enlever un élément sur une liste vide");
        }

        Noeud* sentinelle = noeudAt(position);

        if(m_taille == 1)
        {
            m_debut = m_fin = nullptr;
        }
        else if ( position == 1)
        {
            m_debut = m_debut->m_suivant;
            m_debut->m_precedent = nullptr;
        }
        else if (position == m_taille)
        {
            m_fin = m_fin->m_precedent;
            m_fin->m_suivant = nullptr;
        }
        else
        {
            sentinelle->m_precedent->m_suivant = sentinelle->m_suivant;
            sentinelle->m_suivant->m_precedent = sentinelle->m_precedent;
        }
        sentinelle->m_suivant = nullptr;
        sentinelle->m_precedent = nullptr;
        delete sentinelle;
        m_taille--;
    }

    /**
     * \fn const Case& ListeDeCases::caseA(int position) const
     * \brief Accesseur pour la case à une position donnée
     * \param[in] position La position de la case à enlever
     * \return Case, La case à la position donnée
    */
    const Case& ListeDeCases::caseA(int position) const
    {
        return noeudAt(position)->m_case;
    }

    /**
     * \fn ListeDeCases::Noeud* ListeDeCases::noeudAt(int position) const
     * \brief Accesseur pour le noeud à une position donnée
     * \param[in] position La position de la case à enlever
     * \pre La position d'ajout est comprise entre 1 et m_taille + 1
     * \exception range_error si la position est hors borne
     * \return Noeud, Le noeud à la position donnée
    */
    ListeDeCases::Noeud* ListeDeCases::noeudAt(int position) const
    {
        if (position < 1 || position > taille() + 1)
        {
            throw std::range_error ("Position a l'exterieur de la liste");
        }

        Noeud* nPtr = m_debut;
        for (int i = 1; i < position; ++i) {
            nPtr = nPtr->m_suivant;
        }
        return nPtr;
    }

    // Le reste du code qui utilise surtout l'itérateur est fourni.
    // Ajoutez simplement les balises Doxygen.

    /**
     * \fn  ListeDeCases::Iterateur ListeDeCases::debut() const
     * \brief Création d'un pointeur au début de la liste
     * \return Iterateur créé par son constructeur
    */
    ListeDeCases::Iterateur ListeDeCases::debut() const
    {
       return Iterateur(*this);
    }

    /**
     * \fn  ListeDeCases::Iterateur::Iterateur(const ListeDeCases& liste)
   * \brief Constructeur avec parametre
   *  Initialisation de la liste de cases et du pointeur de noeud m_debut selon les valeurs reçues en paramètres
   * \return Un objet Iterateur
   */
    ListeDeCases::Iterateur::Iterateur(const ListeDeCases& liste) :
       m_liste(liste), m_courant(liste.m_debut)
    {
    }

    /**
     * \fn ListeDeCases::Iterateur::~Iterateur()
   * \brief Destructeur
   *  Remise de l'itérateur m_courant à 0
   * \return Un objet Iterateur
   */
    ListeDeCases::Iterateur::~Iterateur()
    {
       m_courant = 0;
    }

    /**
     * \fn  const Case& ListeDeCases::Iterateur::caseCourante() const
   * \brief Accesseur à la case du noeud courant
   * \return Un objet Case contenu dans le noeud pointé par l'itérateur
   */
    const Case& ListeDeCases::Iterateur::caseCourante() const
    {
       return m_courant->m_case;
    }

    /**
     * \fn  bool ListeDeCases::Iterateur::existeCaseSuivante() const
   * \brief Vérifie s'il existe une case suivante à la case courante
   * \return Un booléen Vrai si le pointeur à la case suivante n'est pas null, Faux sinon
   */
    bool ListeDeCases::Iterateur::existeCaseSuivante() const
    {
       return (m_courant != 0 && m_courant->m_suivant != 0);
    }

    /**
     * \fn ListeDeCases::Iterateur& ListeDeCases::Iterateur::operator ++()
   * \brief Incrémente l'itérateur à la case suivante
   * \return Itérateur pointant à la case suivante
   */
    ListeDeCases::Iterateur& ListeDeCases::Iterateur::operator ++()
    {
       if (existeCaseSuivante())
       {
          m_courant = m_courant->m_suivant;
       }
       else
       {
          m_courant = 0;
          throw out_of_range("L'iterateur ne peut pas aller à une case suivante.");
       }
       return *this;
    }

    /**
     * \fn  ListeDeCases::Noeud* ListeDeCases::Iterateur::noeudSuivant(Case::Couleur couleur, int& distance) const
   * \brief Incrémente l'itérateur à la case suivante contenant la couleur reçue en paramètre
     * \param[in] couleur La couleur de la case à aller
     * \param[in] distance La distance de cette case
   * \return Noeud*, Pointeur de noeud pointant à la case suivante contenant la couleur reçue en paramètre
   */
    ListeDeCases::Noeud* ListeDeCases::Iterateur::noeudSuivant(Case::Couleur couleur, int& distance) const
    {
       distance = 0;
       if (m_courant == 0)
       {
          return 0;
       }

       ListeDeCases::Noeud* suivant = m_courant->m_suivant;
       while (noeudMauvaiseCouleur(suivant, couleur))
       {
          suivant = suivant->m_suivant;
          distance++;
       }
       return suivant;
    }

    /**
     * \fn bool ListeDeCases::Iterateur::noeudMauvaiseCouleur(ListeDeCases::Noeud *noeud,
          Case::Couleur couleur) const
   * \brief Vérifie si la case contenue dans le noeud contient la couleur reçue en paramètre
     * \param[in] *noeud Le noeud à vérifier
     * \param[in] couleur La couleur à vérifier
   * \return bool, Vrai si la case contient la couleur, Faux sinon
   */
    bool ListeDeCases::Iterateur::noeudMauvaiseCouleur(ListeDeCases::Noeud *noeud,
          Case::Couleur couleur) const
    {
       return (noeud != 0 && noeud->m_case.couleur != couleur);
    }

    /**
     * \fn  void ListeDeCases::Iterateur::caseSuivante(Case::Couleur couleur)
   * \brief Incrémente l'itérateur à la case suivante contenant la couleur reçue en paramètre
     * \param[in] couleur La couleur de la case à aller
   */
    void ListeDeCases::Iterateur::caseSuivante(Case::Couleur couleur)
    {
       int distance = 0;
       m_courant = noeudSuivant(couleur, distance);
       if (m_courant == 0)
       {
          ostringstream message;
          message << "L'iterateur ne peut pas aller à une case suivante de couleur " << couleur << ".";
          throw out_of_range(message.str());
       }
    }

    /**
     * \fn  bool ListeDeCases::Iterateur::existeCaseSuivante(Case::Couleur couleur) const
   * \brief Vérifie s'il existe une case ayant la couleur reçue en paramètre dans la suite du plateau de jeu
     * \param[in] couleur La couleur à vérifier
   * \return bool, Vrai si une case contient la couleur, Faux sinon
   */
    bool ListeDeCases::Iterateur::existeCaseSuivante(Case::Couleur couleur) const
    {
       int distance = 0;
       return noeudSuivant(couleur, distance) != 0;
    }

    /**
     * \fn ListeDeCases::Noeud* ListeDeCases::Iterateur::noeudPrecedent(Case::Couleur couleur, int& distance) const
   * \brief Décrémente l'itérateur à la case précédente contenant la couleur reçue en paramètre
     * \param[in] couleur La couleur de la case à aller
     * \param[in] distance La distance de cette case
   * \return Noeud*, Pointeur de noeud pointant à la case précédente contenant la couleur reçue en paramètre
   */
    ListeDeCases::Noeud* ListeDeCases::Iterateur::noeudPrecedent(Case::Couleur couleur, int& distance) const
    {
       distance = 0;
       if (m_courant == 0)
       {
          return 0;
       }

       ListeDeCases::Noeud* precedent = m_courant->m_precedent;
       while (noeudMauvaiseCouleur(precedent, couleur))
       {
          precedent = precedent->m_precedent;
          distance++;
       }
       return precedent;
    }

    /**
     * \fn void ListeDeCases::Iterateur::casePrecedente(Case::Couleur couleur)
   * \brief Décrémente l'itérateur à la case précédente contenant la couleur reçue en paramètre
     * \param[in] couleur La couleur de la case à aller
   */
    void ListeDeCases::Iterateur::casePrecedente(Case::Couleur couleur)
    {
       int distance;
       m_courant = noeudPrecedent(couleur, distance);
       if (m_courant == 0)
       {
          ostringstream message;
          message << "L'iterateur ne peut pas aller à une case precedente de couleur " << couleur
                << ".";
          throw out_of_range(message.str());
       }
    }

    /**
     * \fn  bool ListeDeCases::Iterateur::existeCasePrecedente(Case::Couleur couleur) const
   * \brief Vérifie s'il existe une case ayant la couleur reçue en paramètre dans la précédence du plateau de jeu
     * \param[in] couleur La couleur à vérifier
   * \return bool, Vrai si une case contient la couleur, Faux sinon
   */
    bool ListeDeCases::Iterateur::existeCasePrecedente(Case::Couleur couleur) const
    {
       int distance = 0;
       return noeudPrecedent(couleur, distance) != 0;
    }

    /**
     * \fn int ListeDeCases::Iterateur::positionCourante() const
   * \brief Retourne la position courante de l'itérateur dans la liste de cases
     * \return int, La position courante de l'itérateur
   */
    int ListeDeCases::Iterateur::positionCourante() const
    {
       Noeud *courant = m_liste.m_debut;
       if (courant == 0)
          throw range_error("positionCourante: La liste est vide");

       int i = 1;
       while (courant != m_courant)
       {
          courant = courant->m_suivant;
          i++;
       }
       return i;
    }

    /**
     * \fn bool ListeDeCases::Iterateur::estADerniereCase() const
   * \brief Vérifie si l'itérateur est à la dernière case du plateau de jeu
   * \return bool, Vrai si l'itérateur est à la dernière case, Faux sinon
   */
    bool ListeDeCases::Iterateur::estADerniereCase() const
    {
       return m_courant == m_liste.m_fin && m_courant != 0;
    }

    //Ne touchez surtout pas à cette fonction.
    /**
     * \fn  std::ostream& operator<<(std::ostream& os, const ListeDeCases & liste)
    * \brief Surcharge de l'opérateur <<
    */
    std::ostream& operator<<(std::ostream& os, const ListeDeCases & liste)
    {
       if (liste.estVide())
       {
          os << "Liste de cases vide";
       }
       else
       {
          ListeDeCases::Iterateur iter = liste.debut();
          while (!iter.estADerniereCase())
          {
             os << iter.caseCourante() << "; ";
             ++iter;
          }
          os << iter.caseCourante();
       }

       return os;
    }
}
