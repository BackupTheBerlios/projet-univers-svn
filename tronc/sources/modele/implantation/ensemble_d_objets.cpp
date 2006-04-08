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


#include <modele/ensemble_d_objet.h>

namespace ProjetUnivers {

  namespace Modele {
  
    EnsembleDObjets* EnsembleDObjets::Contruire(const Nom& _nom)
    {
      return NULL ;
    }
    
    void EnsembleDObjets::Ajouter(const Base::Association<Objet>& _objet)
    {
      this->objets.Ajouter(_objet) ;
    }
    
    void EnsembleDObjets::Enlever(const Base::Association<Objet>& _objet)
    {
      this->objets.Enlever(_objet) ;
      
    }
    
    EnsembleDObjets::~EnsembleDObjets()
    {}
    
    EnsembleDObjets::EnsembleDObjets(const Nom& _nom)
    : nom(_nom)
    {}
  } 
  
}

