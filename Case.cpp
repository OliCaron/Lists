/////////////////////////////////////////////////////////////////////////////
//Fichier Case.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Case.cpp
 * \brief Ce fichier contient une implémentation de la classe Case
 * \author Olivier Caron
 * \version 0.1
 * \date mai-juin 2023
 */

#include "Case.h"

namespace tp1
{
    /**
     * \fn Case::Case(Case::Couleur couleur, Case::Decoration decoration) : couleur(couleur), decoration(decoration)
   * \brief Constructeur avec parametre
   *  Initialisation de couleur et de decoration de l'objet Case selon les valeurs recues en parametre
   * \param[in] couleur la couleur de la case
   * \param[in] decoration la decoration de la case
   * \return Un objet Case
   */
    Case::Case(Case::Couleur couleur, Case::Decoration decoration) : couleur(couleur), decoration(decoration)
    {
    }

    /**
     * \fn Case::~Case()
    * \brief Destructeur de la classe Case
    */
    Case::~Case()
    {
    }

    /**
     * \fn std::string decorationEnLettre(Case::Decoration decoration)
    * \brief Fonction pour aider à afficher plus naturellement une case à l'écran.
    * \param[in] decoration la decoration de la case
    * \return un string qui contient l'information de la decoration de la case
    */
    std::string decorationEnLettre(Case::Decoration decoration)
    {
       switch (decoration)
       {
          case Case::Serpent:
             return "S";
          case Case::Echelle:
             return "E";
          default:
             return "A";
       }
    }

    /**
     * \fn std::ostream& operator<<(std::ostream& os, const Case & uneCase)
    * \brief Surcharge de l'opérateur <<
    */
    std::ostream& operator<<(std::ostream& os, const Case & uneCase)
    {
       os << "(" << uneCase.couleur << "," << decorationEnLettre(uneCase.decoration) << ")";

       return os;
    }
}
