/////////////////////////////////////////////////////////////////////////////
//Fichier File.hpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file File.hpp
 * \brief Ce fichier contient une implémentation générique de la classe File
 * \author Olivier Caron
 * \version 0.1
 * \date mai-juin 2023
 */


namespace tp1
{
     /**
      * \fn  template<typename T>
    File<T>::File() : liste(ListeCirculaire<T>())
     * \brief Constructeur sans paramètres de la classe File
      * Initialisation de la liste par une liste circulaire vide par défaut
     * \return Un objet File
     */
    template<typename T>
    File<T>::File() : liste(ListeCirculaire<T>())
    {
    }

    /**
     * \fn  template<typename T>
    void File<T>::enfiler ( const T& element )
    * \brief Enfile un élément à la fin de la file
    * \param[in] element L'élément à enfiler
    */
    template<typename T>
    void File<T>::enfiler ( const T& element )
    {
        liste.ajouterFin(element);
    }

    /**
     * \fn  template<typename T>
    T File<T>::defiler ()
    * \brief Défile et supprime un élément du début de la file
    * \return element L'élément défilé
    */
    template<typename T>
    T File<T>::defiler ()
    {
        if(liste.taille() <= 0) throw std::logic_error("File vide");
        T valeur = liste.element(1);
        liste.enleverPos(1);
        return valeur;
    }

    /**
     * \fn  template<typename T>
    unsigned int File<T>::taille ()
    * \brief Donne la taille de la file
    * \return int liste.taille() la taille de la liste
    */
    template<typename T>
    unsigned int File<T>::taille ()
    {
       return liste.taille();
    }

    //Ne touchez pas à cette fonction.
    /**
     * \fn  template< typename T >
    std::ostream& operator<<(std::ostream& os, const File<T> & file)
    * \brief Surcharge de l'opérateur <<
    */
    template< typename T >
    std::ostream& operator<<(std::ostream& os, const File<T> & file)
    {
       os << file.liste;
       return os;
    }
}
