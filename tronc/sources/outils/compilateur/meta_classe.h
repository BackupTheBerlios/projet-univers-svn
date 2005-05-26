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


#ifndef _PU_COMPILATEUR_META_CLASSE_H_
#define _PU_COMPILATEUR_META_CLASSE_H_

#include <set>

#include <opencxx/mop.h>

#include <base/ensemble_composition.h>
#include <base/chaine.h>
#include <outils/compilateur/attribut.h>

using namespace Opencxx ;


///  Classe des classes C++.

/*!
  Cette m�ta classe a pour instances les classes C++ pass�e � ce 
  compilateur, pendant la traduction de cette classe (TranslateClass) 
  on v�rifie que les r�gles sont appliqu�es et on modifie la classe 
  compil�e en fonction des besoins.

*/
class MetaClasse : public Class {
public:

  /*!
    @name Acc�s
    
    Methodes d'acc�s permettant de d�tecter des propri�t�s sur la classe.
  */
  //@{


  /// Determine si la classe est une classe de valeur.
  bool Valeur() ;
  
  /// Determine si la classe est une classe d'objets.
  bool Objet() ;
  
  /// Determine si la classe est une classe persistante.
  bool Persistante() ;

  /// Vrai si la classe fait partie de ProjetUnivers.
  /*!
    Determine si la classe est d�finie dans le namespace ::ProjetUnivers mais 
    pas dans ::ProjetUnivers::Base. Permet de filtrer les classes � v�rifier et 
    � traduire.
  */
  bool NamespaceProjetUnivers() ;


  //@}
  ///@name Affichage
  //@{


  /// Affichage
  /*!
    \todo
      remplacer par string
  */
  const char* Afficher() ;


  //@}
  /*!
    @name M�thodes sp�cifiques � OpenC++
    
    
  */  
  //@{

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

  /// Traduit les lectures d'attributs.
  virtual Opencxx::Ptree* TranslateMemberRead(
               Opencxx::Environment*,
               Opencxx::Ptree* object, 
               Opencxx::Ptree* access_op,
               Opencxx::Ptree* member_name);

  /// Traduit les lectures d'attributs.                     
  virtual Opencxx::Ptree* TranslateMemberRead(
               Opencxx::Environment*, 
               Opencxx::Ptree* member_name);


  //@}


private:

  
  /// G�n�re la partie d'un sch�ma XML pour cet attribut.
  void GenererSchemaXml() const ;

  /// Determine si la classe v�rifie les r�gles de programmatoins.
  bool VerifieRegles() ;

  ///@name Attributs
  //@{


  /// Les attributs de la classe
  ProjetUnivers::Base::EnsembleComposition<ProjetUnivers::Outils::Compilateur::Attribut> attributs ;

  /// Le nom de la classe
  ProjetUnivers::Base::Chaine nom ;
  
  /// Les classes parentes
  /*!
    C'ets un ensemble en association vers des MetaClasse, elle ne doivent pas 
    �tre d�truites par le conteneur.
  */
  std::set<MetaClasse*> parents ;
  
  /// Un drapeau pour dire que la classe a �t� initialis�e
  bool initialisee ;

  //@}
};


#endif //_PU_COMPILATEUR_META_CLASSE_H_
