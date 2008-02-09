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
#ifndef PU_COMPILER_META_CLASSE_H_
#define PU_COMPILER_META_CLASSE_H_

#include <set>
#include <string>

#include <opencxx/mop.h>

#include <tools/compilateur/attribut.h>

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
    @todo
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


  /*!
    @name V�rification des r�gles
    
    Une classe est soit Concr�te soit Abstraite.
    Une classe est soit Objet soit Valeur.
    Une classe Valeur est Concrete.
    Une classe Abstraite poss�de certaines contraintes.
  */
  //@{


  /// Determine si la classe v�rifie les r�gles de programmations.
  bool VerifieRegles() ;


  /// Une r�gle v�rifi�e ou non
  /*!
    Abstraite => 
      - destructeur virtuel non pur
      - m�thodes virtuelles pures ou m�thodes non virtuelles
      - un constructeur prot�g�
  */
  bool RegleAbstrait() const ;

  /// Chaque classe est soit une classe abstraite soit une classe concr�te.
  bool RegleAbstraitConcret() const ;


  /// Chaque classe est soit une classe de valeur soit une classe d'objet.
  bool RegleObjetValeur() const ;

  /// Une classe de Valeur est Concrete.
  bool RegleValeurConcrete() const ;

  /// Chaque classe parente d'une classe est Abstraite.
  bool RegleParentsAbstraites() const ;
  
  // @}
  /*!
    @name Calcul des propri�t�s �l�mentaires de la classe
  
    Il s'agit de savoir si elle poss�de des constructeurs, lesquels et 
    certaines m�thodes bien particuli�res. Les propri�t�s �l�mentaires sont 
    calcul�es pendant Initialiser et sont stok�es.
  */
  //@{
  

  /// La classe est-elle abstraite.
  /*!
    Une classe est abstraite si et seulement si elle poss�de 
    - aucun constructeur public
  */
  bool Abstraite() const ;

  /// La classe est-elle concr�te.
  /*!
    Une classe concr�te poss�de 
    - au moins un constructeur public
  */
  bool Concrete() const ;

  /// Calcule si la classe est une classe de valeur
  /*!
    Une classe de valeur poss�de :
    - un constructeur par d�faut
    - un constructeur de copie
    - un op�rateur ==
    - un op�rateur !=
    - aucune m�thode virtuelle
  */
  bool EstValeur() const ;
  
  /// Calcule si la classe est une classe d'objet
  /*!
    Une classe d'objet poss�de :
    - aucun constructeur de copie
    - aucun op�rateur ==
    - aucun op�rateur !=
  */
  bool EstObjet() const ;
  
  
  /// Stokage des propri�t�s de la classe
  bool ExisteDeclarationConstructeurParDefautPublic ;
  bool ExisteDeclarationConstructeurParDefautProtege ;
  bool ExisteConstructeurDeCopiePublic ;
  bool ExisteDeclarationConstructeur ;
  bool ExisteDeclarationConstructeurPublic ;
  
  bool ExisteDestructeurVirtuelNonPur ;

  bool ExisteOperateurEgalPublic ;
  bool ExisteOperateurDifferentPublic ;

  bool ExisteMethodeVirtuellePure ;
  bool ExisteMethodeVirtuelleNonPure ;
  

  //@}
  ///@name Attributs
  //@{


  /// Les attributs de la classe
  std::set<ProjetUnivers::Tools::Compiler::Attribut*> attributs ;

  /// Le nom de la classe
  std::string nom ;
  
  /// Les constructeurs
  
  /// Les m�thodes
  /*!
    Ce sont des *fonctions* poss�dant un param�tre this.
  */
  
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


#endif //PU_COMPILER_META_CLASSE_H_
