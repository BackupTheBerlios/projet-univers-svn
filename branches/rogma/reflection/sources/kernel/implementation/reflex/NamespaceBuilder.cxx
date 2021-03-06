// @(#)root/reflex:$Id: NamespaceBuilder.cxx 32016 2010-01-14 15:23:00Z axel $
// Author: Stefan Roiser 2004

// Copyright CERN, CH-1211 Geneva 23, 2004-2010, All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives.
//
// This software is provided "as is" without express or implied warranty.

#ifndef REFLEX_BUILD
#define REFLEX_BUILD
#endif

#include "Reflex/Builder/NamespaceBuilder.h"

#include "Reflex/PropertyList.h"
#include "Reflex/Scope.h"

#include "Namespace.h"

#include "Reflex/internal/OwnedMember.h"

//-------------------------------------------------------------------------------
Reflex::NamespaceBuilder::NamespaceBuilder( const Reflex::Dictionary& dictionary, const char * nam ) {
//-------------------------------------------------------------------------------
// Create dictionary info for a namespace.
   Scope sc = Scope::ByNameShallow(nam, dictionary);

   if ( sc && sc.IsNamespace() ) {
      fNamespace       = sc;
   } else {
      fNamespace       = (new Namespace( dictionary, nam ))->ThisScope();
   }
}


//-------------------------------------------------------------------------------
Reflex::NamespaceBuilder & 
Reflex::NamespaceBuilder::AddProperty( const char * key, 
                                             const char * value ) {
//-------------------------------------------------------------------------------
// Add property to this namespace as string.
   fNamespace.Properties().AddProperty( key , value );
   return * this;
}


//-------------------------------------------------------------------------------
Reflex::NamespaceBuilder & 
Reflex::NamespaceBuilder::AddProperty( const char * key, 
                                             Any value ) {
//-------------------------------------------------------------------------------
// Add property to this namespace as Any object.
   fNamespace.Properties().AddProperty( key , value );
   return * this;
}
    

//-------------------------------------------------------------------------------
Reflex::Scope
Reflex::NamespaceBuilder::ToScope() {
//-------------------------------------------------------------------------------
// Return the scope currently being built.
   return fNamespace;
}
