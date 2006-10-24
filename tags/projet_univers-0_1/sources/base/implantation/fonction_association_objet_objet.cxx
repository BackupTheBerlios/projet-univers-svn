/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Lesser Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


 
namespace ProjetUnivers 
{

  namespace Base 
  {


    template <class ObjetCle, class ObjetValeur>
    FonctionAssociationObjetObjet<ObjetCle,ObjetValeur>::
    FonctionAssociationObjetObjet()
    {}
    
    template <class ObjetCle, class ObjetValeur>
    FonctionAssociationObjetObjet<ObjetCle,ObjetValeur>::
    FonctionAssociationObjetObjet(
      const FonctionAssociationObjetObjet<ObjetCle,ObjetValeur>& _copie)
    : fonction(_copie.fonction)
    {}
    
    template <class ObjetCle, class ObjetValeur>
    void 
    FonctionAssociationObjetObjet<ObjetCle,ObjetValeur>::Ajouter(
      const Association<ObjetCle>& _cle, const Association<ObjetValeur>& _valeur)
    {
      this->fonction[_cle.operator->()] = _valeur.operator->() ;
    }
  
    template <class ObjetCle, class ObjetValeur>
    void 
    FonctionAssociationObjetObjet<ObjetCle,ObjetValeur>::Changer(
      const Association<ObjetCle>& _cle, const Association<ObjetValeur>& _valeur)
    {
      this->Ajouter(_cle,_valeur) ;
    }

    template <class ObjetCle, class ObjetValeur>
    Association<ObjetValeur> FonctionAssociationObjetObjet<ObjetCle,ObjetValeur>::Acces(
        const Association<ObjetCle>& _cle) const
    {
      /// l'élément est-il dans la fonction ?
      class std::map<ObjetCle*,ObjetValeur*>::const_iterator estDedans 
          = this->fonction.find(_cle.operator->()) ;
          
      if (estDedans == this->fonction.end())
      {
        /// pas d'objet associé à @c _cle
        /*!
          @todo
            trouver un moye nde différencier entre 
            - _cle est associé à NULL
            - _cle n'est associé à personne
        */
        return Association<ObjetValeur>() ;
      }
      else
      {
        return *(estDedans->second) ;
      }
    }
  
  
    
    
    
  }
}
