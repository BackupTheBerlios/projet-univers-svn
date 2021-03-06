// @(#)root/reflex:$Id: DictionaryBuilder.cxx 32420 2010-03-01 11:41:17Z axel $
// Author: Philippe Bourgau 2009

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

#include <Reflex/SharedLibraryUtils.h>
#include <Reflex/Builder/DictionaryBuilder.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include "Namespace.h"

namespace {

time_t getMTime(const std::string& fileName) {
   struct stat status = {0};
   if (stat(fileName.c_str(), &status) < 0)
      return 0;
   return status.st_mtime;
}

Reflex::Dictionary CreateGlobalScope(const Reflex::Dictionary& dictionary) {
   Reflex::Namespace::GlobalScope(dictionary);
   return dictionary;
}
#if defined(_WIN32) && !defined(__GNUC__)
std::string os_command(const std::string& command) {
   return "\""+command+"\"";
}
#else
std::string os_command(const std::string& command) {
   return command;
}
#endif

}

void Reflex::CollectSharedLibraryDependencies(const std::string& sharedLibraryPath, std::vector<std::string>& result) {

   // we had to output to another file because there is not portable process library
   // to handle the spawned process output.
   std::string depsFile = sharedLibraryPath+".deps";

   time_t binMTime = getMTime(sharedLibraryPath);
   time_t depsMTime = getMTime(depsFile);

   if (0 == binMTime)
      throw std::domain_error("Could not get stats for file \""+sharedLibraryPath+"\"");

   if (depsMTime < binMTime) {
      std::string reflexLibPath = SharedLibraryDefining((void*)&CollectSharedLibraryDependencies);
      std::string command = os_command("\""+DirectoryPartOfPath(reflexLibPath)+"reflex-ldd\" \""+sharedLibraryPath+"\" \""+depsFile+"\"");
      int exitCode = system(command.c_str());
      if (0 != exitCode) {
         std::ostringstream message;
         message << "Command failed \"" << command << "\" with code" << exitCode << '.';
         throw std::domain_error(message.str());
      }
   }

   std::ifstream deps(depsFile.c_str());
   deps >> std::skipws;
   while(!deps.eof()) {
      std::string dep;
      deps >> dep >> std::skipws;
      result.push_back(dep);
   }
}

//-------------------------------------------------------------------------------
Reflex::Dictionary Reflex::DictionaryBuilder(const std::string& sharedLibraryPath) {
//-------------------------------------------------------------------------------

   std::string sharedLibraryName = NamePartOfPath(sharedLibraryPath);
   if (Dictionary::ExistsForSharedLibrary(sharedLibraryName))
      return Dictionary::BySharedLibrary(sharedLibraryName);

   std::vector<std::string> dependenciesNames;
   CollectSharedLibraryDependencies(sharedLibraryPath, dependenciesNames);

   std::vector<Dictionary> dependencies;
   for(size_t i = 0; i < dependenciesNames.size(); ++i) {

      if (Dictionary::ExistsForSharedLibrary(dependenciesNames[i]))
         dependencies.push_back(Dictionary::BySharedLibrary(dependenciesNames[i]));
   }

   if (dependencies.empty())
      dependencies.push_back(Dictionary::Main());

   return CreateGlobalScope(Dictionary(sharedLibraryName, dependencies));
}

//-------------------------------------------------------------------------------
Reflex::Dictionary Reflex::DictionaryBuilderMain() {
//-------------------------------------------------------------------------------

   return CreateGlobalScope(Dictionary::Main());
}



