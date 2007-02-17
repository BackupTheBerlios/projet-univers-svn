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
      
      Ce compilateur est un compilateur C++ qui :
      - v�rifie un ensemble de r�gles de programmation
      - g�n�re du code "cach�", notament pour la persistance.
  
      @section verification R�gles de programmation
      
      Le compilateur v�rifie les r�gles de programmation suivantes : 
      -# Chaque classe du namespace ProjetUnivers est soit une 
         classe d'objets soit une classe de valeurs.
        - les classes d'objets 
          - doivent h�riter de Base::Objet
          - ne doivent pas comporter :
            - de surcharge de l'op�rateur ==
            - de surcharge de l'op�rateur !=
        - les classes de valeurs 
          - doivent h�riter de Base::Valeur
          - doivent comporter 
            - un constructeur de copie
            - un constructeur par d�faut
            - une surcharge de l'op�rateur d'affectation
            - une surcharge de l'op�rateur ==
            - une surcharge de l'op�rateur !=          
      -# Chaque classe du namespace ProjetUnivers a uniquement des attributs 
         d'un des types suivants :
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
        - n'importe quel type du moment qu'il n'est pas bas� sur des classes 
          du namespace ProjetUnivers
      -# Chaque classe parente d'une classe est Abstraite.
      
      @section persistance Persistance 

      Ce compilateur r�alise la persistance <b>transparente</b> des 
      sous-classes de Base::Persistant.
      
      Cette persistance est totalement transparente, c'ets � dire qu'il sufffit 
      d'utiliser les classes comme d'habitude. Lorsque les objets sont modifi�s 
      cette modification est r�percut�e automatiquement dans la base de donn�es.
      
      Cette persistance ne fonctionne que si les r�gles expos�es ci-dessus sont 
      v�rifi�es.
    */
    namespace Compilateur 
    {} 
  }
}

#endif //_PU_OUTILS_COMPILATEUR_COMPILATEUR_H_
