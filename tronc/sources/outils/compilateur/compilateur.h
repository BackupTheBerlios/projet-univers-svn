/***************************************************************************
 *   Copyright (C) 2004 by Equipe Projet Univers                           *
 *   rogma.boami@free.fr                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/



#ifndef _PU_OUTILS_COMPILATEUR_COMPILATEUR_H_
#define _PU_OUTILS_COMPILATEUR_COMPILATEUR_H_


namespace ProjetUnivers {

  namespace Outils {

    /// Un compilateur C++ �tendu.
    
    /*! 
      Ce compilateur transforme certaine classes C++ pour implanter 
      automatiquement un certain nombre de fonctionnalit�s :
      
  
      - La v�rification des r�gles de programmation du projet
        
        Ces r�gles imposent notamment : 
        
        - de distinguer classes d'objets et classes de valeurs, c'est � dire :
        
          - les classes d'objets 
            
            - doivent h�riter de Base::Objet
            - ne doivent pas comporter de :
            
              - op�rateur ==, !=
            
            
          - les classes de valeurs 
          
            - doivent h�riter de Base::Valeur
            - doivent comporter 
          
        - de n'utiliser comme types d'attributs que les types suivants :
          
          - Base::Entier
          
          - Base::Reel
          
          - Base::Booleen
          
          - Base::Chaine
          
          - VALEUR
            o� VALEUR est une classe de valeurs
            
          - Base::Association<OBJET>
            o� OBJET est une classe d'objets
  
          - Base::Composition<OBJET>
            o� OBJET est une classe d'objets
  
          - Base::EnsembleAssociation<OBJET>
            o� OBJET est une classe d'objets
  
          - Base::EnsembleComposition<OBJET>
            o� OBJET est une classe d'objets
  
          - Base::FonctionObjetValeur<OBJET,VALEUR>
            o� OBJET est une classe d'objets et VALEUR est une classe de valeurs
         
          - Base::FonctionCompositionValeurObjet<VALEUR,OBJET>
            o� OBJET est une classe d'objets et VALEUR est une classe de valeurs
  
          - Base::FonctionAssociationValeurObjet<VALEUR,OBJET>
            o� OBJET est une classe d'objets et VALEUR est une classe de valeurs
          
        de n'utiliser comme types d'attributs que les classes 
        suivantes :
  
      - La persistance <b>transparente</b> des sous-classes de Base::Persistant.
        
        Cette persistance est totalement transparente, c'ets � dire qu'il sufffit 
        d'utilise les classes comme d'habitude. Lorsque les objets sont modifi�s 
        cette modification est r�percut�e automatiquement dans la base de donn�es.
        
        L'inconv�nient est qu'il faut absolument respecter les r�gles expos�es 
        ci-dessus.
        
        \example
        
          
    */
    namespace Compilateur 
    {} 
  }
}

#endif //_PU_OUTILS_COMPILATEUR_COMPILATEUR_H_
