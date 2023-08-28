/////////////////////////////////////////////////////////////////////////////
//Fichier GenerateurNombresAleatoires.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file GenerateurNombresAleatoires.cpp
 * \brief Ce fichier contient une implémentation de la classe GenerateurNombresAleatoires
 * \author IFT-2008
 * \version 0.1
 * \date mai-juin 2023
 */

#include "GenerateurNombresAleatoires.h"

namespace tp1
{
    /**
     * \fn GenerateurNombresAleatoires::GenerateurNombresAleatoires( unsigned int init, unsigned int max )
   * \brief Constructeur avec parametre
   *  Initialisation de l'état et du Max plus un selon les valeurs recues en parametre
   * \param[in] init unsigned int pour l'état
   * \param[in] max unsigned int pour le maxPlusUn
   * \return Un objet GenerateurNombresAleatoires
   */
    GenerateurNombresAleatoires::GenerateurNombresAleatoires( unsigned int init, unsigned int max ):
          m_etat( init ), m_maxPlusUn( max + 1 )
    {
    }

    /**
     * \fn int GenerateurNombresAleatoires::pige()
      * \brief ???
      * \return int modulo entre l'état et le maximum plus un
      */
    int GenerateurNombresAleatoires::pige()
    {
        m_etat *= ENTROPIE;
        return m_etat % m_maxPlusUn;
    }
}
