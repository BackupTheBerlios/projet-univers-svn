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

#ifndef _PU_BASE_ASSOCIATION_VIRTUELLE_H_
#define _PU_BASE_ASSOCIATION_VIRTUELLE_H_

// Definition de macros utilis�es pour les
// associations virtuelles.


// UTILISATION :

// Quand on veut d�clarer une association virtuelle :

// la classe de base d�clare la association virtuelle � l'aide
// de la macro DECLARATION_ASSOCIATION_VIRTUELLE()

// les classes d�riv�es utilisent UTILISATION_ASSOCIATION_VIRTUELLE()


#include <base/association.h>

/// Le nom de l'attribut est "camoufl�" � l'aide d'un pr�fixe
/// "_vref_" afin de r�duire le risque d'utilisation directe 
/// de ce pointeur.
#define BASE_VREF(name) _vref_ ## name

/// Ici type d�signe le type "abstrait" de l'attribut
/// c'est � dire le nom de la classe de base. 
#define DECLARATION_ASSOCIATION_VIRTUELLE(type,name) \
	protected: \
	ProjetUnivers::Base::Association< type > BASE_VREF(name) ; \
	public: \
	ProjetUnivers::Base::Association< type > name() const { return BASE_VREF(name) ; } \
	ProjetUnivers::Base::Association< type >& name() { return BASE_VREF(name) ; }

/// Ici type d�signe le nom de la classe d�riv�e
/// vers laquelle on veut convertir l'association. 
#define UTILISATION_ASSOCIATION_VIRTUELLE(type,name) \
	protected: \
  ProjetUnivers::Base::Association< type > name() const \
	{ \
    if(dynamic_cast<type*>(BASE_VREF(name).operator->()) == NULL)  \
      throw ExceptionBase("association virtuelle") ; \
	  return ProjetUnivers::Base::Association< type >(*(static_cast<type*>(BASE_VREF(name).operator->()))) ; \
	}			


#endif


