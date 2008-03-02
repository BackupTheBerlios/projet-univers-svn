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
#include <rlog/rlog.h>

#include <opencxx/TypeInfo.h>

#include <tools/compilateur/test_meta_class.h>
#include <tools/compilateur/traceur.h>
#include <tools/compilateur/utilitaires_opencxx.h>

using namespace std;
using namespace Opencxx ;
using namespace ProjetUnivers::Tools::Compiler ;

MetaClasse::MetaClasse()
{}

bool MetaClasse::Initialize() 
{
  OuvrirTraceur() ;
  Class::ChangeDefaultMetaclass("MetaClasse") ;
  return true ;
  
}

void MetaClasse::TranslateClass(Environment* env)
{
  
  rDebug("MetaClasse::TranslateClass") ;
  
  rDebug("fin MetaClasse::TranslateClass") ;
}

Ptree* MetaClasse::FinalizeClass()
{
  // ici on fait ce qu'on veut :
  FermerTraceur() ;

  return 0 ;
  
}



