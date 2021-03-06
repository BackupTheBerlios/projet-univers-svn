// @(#)root/reflex:$Id: TemplateInstance.cxx 32016 2010-01-14 15:23:00Z axel $
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

#include "TemplateInstance.h"

#include "Reflex/Builder/TypeBuilder.h"
#include "Reflex/internal/OwnedMember.h"


//-------------------------------------------------------------------------------
//Reflex::TemplateInstance::~TemplateInstance() {}
//-------------------------------------------------------------------------------


//-------------------------------------------------------------------------------
Reflex::TemplateInstance::TemplateInstance(const Reflex::Dictionary& dictionary, const std::string & templateArguments ) {
//-------------------------------------------------------------------------------
// Create the dictionary info for a template instance.
   std::vector<std::string> templArgStrVec = Tools::GenTemplateArgVec(templateArguments);

   for (std::vector<std::string>::const_iterator it = templArgStrVec.begin();
        it != templArgStrVec.end(); ++it ) {
      fTemplateArguments.push_back(TypeBuilder(dictionary, it->c_str()));
   }
}


//-------------------------------------------------------------------------------
std::string
Reflex::TemplateInstance::Name(unsigned int mod) const {
//-------------------------------------------------------------------------------
// Return the name of the template instance.
   std::string s = "<";

   for ( size_t i = 0; i < fTemplateArguments.size(); ++i ) {
      s += fTemplateArguments[ i ].Name( mod );

      if (i < (fTemplateArguments.size() - 1)) {
         s += ",";
      }
   }
   s += ">";
   return s;
}
