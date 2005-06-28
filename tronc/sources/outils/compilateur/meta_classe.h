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
  Cette méta classe a pour instances les classes C++ passée à ce 
  compilateur, pendant la traduction de cette classe (TranslateClass) 
  on vérifie que les règles sont appliquées et on modifie la classe 
  compilée en fonction des besoins.

*/
class MetaClasse : public Class {
public:

  /*!
    @name Accès
    
    Methodes d'accès permettant de détecter des propriétés sur la classe.
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
    Determine si la classe est définie dans le namespace ::ProjetUnivers mais 
    pas dans ::ProjetUnivers::Base. Permet de filtrer les classes à vérifier et 
    à traduire.
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
    @name Méthodes spécifiques à OpenC++
    
    
  */  
  //@{

  /// Constructeur par défaut.
  MetaClasse() ;

  /// Fabrique les informations.
  /*!
    Construit les informations de types des attributs et des classes parentes. 
    C'est un préalable à la vérification et àa la traduction.
    
    Le drapeau this->initialisee est vrai une fois que cette classe a été 
    initialisée (permettant ainsi d'initialiser une seule fois toutes les 
    classes utilisées).
    
    @remark
      Cette méthode est différente de l'initialisation OpenC++. C'est une 
      méthode "maison" qui est appelée soit par Initialize soit par 
      l'intermédiaire des types des attributs et des classes parentes.
  */
  void Initialiser() ;

  /// MetaClasse est la méta classe par défaut.
  /*!
    Est appelée une fois, au tout début, par le compilateur.

    Changer la méta-classe par défaut est très pratique : le code C++ n'a pas à 
    étre changé et les vérifications, transformations sont tout de même 
    appliquées.
    
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

  
  /// Génère la partie d'un schéma XML pour cet attribut.
  void GenererSchemaXml() const ;


  /*!
    @name Vérification des règles
    
    Une classe est soit Concrète soit Abstraite.
    Une classe est soit Objet soit Valeur.
    Une classe Valeur est Concrete.
    
  */
  //@{


  /// Determine si la classe vérifie les règles de programmations.
  bool VerifieRegles() ;


  /// La classe est-elle abstraite.
  /*!
    Une classe abstraite possède 
    - des méthode virtuelles pures
    - un destructeur virtuel non pur public
    - un constructeur protégé
    - des méthodes non virtuelles
    - des attributs
  */
  bool Abstraite() const ;

  /// La classe est-elle concrète.
  /*!
    Une classe concrète possède 
    - au moins un constructeur public
    - uniquement des méthodes non virtuelles
    - des attributs
    - éventuellement des destructeurs
  */
  bool Concrete() const ;


  /// Calcule si la classe est une classe de valeur
  /*!
    Une classe de valeur possède :
    - un constructeur par défaut
    - un constructeur de copie
    - un opérateur ==
    - un opérateur !=
    - aucune méthode virtuelle
  */
  bool EstValeur() const ;
  
  /// Calcule si la classe est une classe d'objet
  /*!
    Une classe d'objet possède :
    - aucun constructeur de copie
    - aucun opérateur ==
    - aucun opérateur !=
  */
  bool EstObjet() const ;
  
  bool ExisteDeclarationConstructeurParDefautPublic ;
  bool ExisteDeclarationConstructeurParDefautProtege ;
  bool ExisteConstructeurDeCopiePublic ;
  
//  bool ExisteDeclarationConstructeurPublic ;
//  bool ExisteDeclarationConstructeur ;
//  bool ExisteDeclarationConstructeurParDefaut ;
  
  bool ExisteDestructeurVirtuelNonPur ;

  bool ExisteOperateurEgalPublic ;
  bool ExisteOperateurDifferentPublic ;

  bool ExisteMethodeVirtuellePure ;
  bool ExisteMethodeVirtuelleNonPure ;
  

  //@}
  ///@name Attributs
  //@{


  /// Les attributs de la classe
  ProjetUnivers::Base::EnsembleComposition<ProjetUnivers::Outils::Compilateur::Attribut> attributs ;

  /// Le nom de la classe
  ProjetUnivers::Base::Chaine nom ;
  
  /// Les constructeurs
  
  /// Les méthodes statiques ??
  
  
  
  /// Les classes parentes
  /*!
    C'ets un ensemble en association vers des MetaClasse, elle ne doivent pas 
    être détruites par le conteneur.
  */
  std::set<MetaClasse*> parents ;
  
  /// Un drapeau pour dire que la classe a été initialisée
  bool initialisee ;

  //@}
};


#endif //_PU_COMPILATEUR_META_CLASSE_H_
