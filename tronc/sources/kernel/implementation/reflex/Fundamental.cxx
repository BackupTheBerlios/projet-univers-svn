// @(#)root/reflex:$Id: Fundamental.cxx 32016 2010-01-14 15:23:00Z axel $
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

#include "Fundamental.h"

#include "Reflex/Type.h"
#include "Reflex/internal/OwnedMember.h"

//-------------------------------------------------------------------------------
Reflex::Fundamental::Fundamental( const Reflex::Dictionary& dictionary,
                                  const char * typ,
                                        size_t size,
                                        const std::type_info & ti ) 
//-------------------------------------------------------------------------------
   : TypeBase( dictionary, typ, size, FUNDAMENTAL, ti ) {
   // Create dictionary info for this fundamental type.
}
