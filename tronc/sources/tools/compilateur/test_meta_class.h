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
#ifndef PU_COMPILER_TEST_META_CLASSE_H_
#define PU_COMPILER_TEST_META_CLASSE_H_

#include <set>
#include <string>

#include <opencxx/mop.h>

#include <tools/compilateur/attribut.h>

using namespace Opencxx ;


///  Classe des classes C++.
/*!
*/
class MetaClasse : public Class {
public:


  /// Constructeur par d�faut.
  MetaClasse() ;

  /// Fabrique les informations.
  /*!
    Construit les informations de types des attributs et des classes parentes. 
    C'est un pr�alable � la v�rification et �a la traduction.
    
    Le drapeau this->initialisee est vrai une fois que cette classe a �t� 
    initialis�e (permettant ainsi d'initialiser une seule fois toutes les 
    classes utilis�es).
    
    @remark
      Cette m�thode est diff�rente de l'initialisation OpenC++. C'est une 
      m�thode "maison" qui est appel�e soit par Initialize soit par 
      l'interm�diaire des types des attributs et des classes parentes.
  */
  void Initialiser() ;

  /// MetaClasse est la m�ta classe par d�faut.
  /*!
    Est appel�e une fois, au tout d�but, par le compilateur.

    Changer la m�ta-classe par d�faut est tr�s pratique : le code C++ n'a pas � 
    �tre chang� et les v�rifications, transformations sont tout de m�me 
    appliqu�es.
    
    On peut donc ainsi introspecter et modifier du code qui reste du 
    pur C++.  
   
  */
  static bool Initialize() ;

  /// Ferme ce qu'on a ouvert
  static Ptree* FinalizeClass();

  /// Modifie la classe.
  void TranslateClass(Opencxx::Environment* env) ;

};


#endif //PU_COMPILER_TEST_META_CLASSE_H_
