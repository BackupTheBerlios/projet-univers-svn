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

#ifndef _PU_BASE_LISTE_ABSTRAITE_H_
#define _PU_BASE_LISTE_ABSTRAITE_H_

#include <base/composition.h>
#include <base/implantation/noeud_abstrait.h>


namespace ProjetUnivers {

  namespace Base {
  
      
    
    ///  Classe de base des listes.
    class ListeAbstraite {
    public:
    
      /// Constructeur par d�faut.
      /// \todo 
      ///   v�rifier si ce constructeur doit �tre public
      ListeAbstraite() ;
    
      /// Destructeur virtuel, ne sert pas � 
      /// grand chose � part rendre la classe 
      /// polymorphe.
      virtual ~ListeAbstraite() ;
    
      /// Acc�s au nombre d'�l�ments.
      unsigned int NombreDElements() const ;
    
      /// Vide la liste.
      void Vider() ;
    
    protected:
    
      // Premier noeud.
      Composition< NoeudAbstrait > premierNoeud ;
    
      /// Dernier noeud.
      Association< NoeudAbstrait > dernierNoeud ;
    
    
      /// Nombre d'�l�ments.
      unsigned int nombreDElements ;
    
      // Ajoute un noeud en d�but de liste.
      void AjouterEnTete(NoeudAbstrait* _n) ;
    
      /// Ajoute un noeud en fin de liste.
      void AjouterEnQueue(NoeudAbstrait* _n) ;
    
      /// 
      friend class IterateurListe ;
    
    
    };
  }
}

#endif


