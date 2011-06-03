/***************************************************************************
 *   This file is part of ProjetUnivers                                    *
 *   see http://www.punivers.net                                           *
 *   Copyright (C) 2006-2010 Mathieu ROGER                                 *
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
#include <OgreVector3.h>
#include <OgreStringConverter.h>
#include <Reflex/Reflex.h>
#include <Reflex/Builder/CollectionProxy.h>
#include <kernel/text_serialiser.h>
#include <kernel/string.h>
#include <kernel/error.h>
#include <kernel/object_reference.h>
#include <kernel/implementation/reflex/ClassTemplateInstance.h>

namespace ProjetUnivers
{
  namespace Kernel
  {

    TextSerialiser::TextSerialiser(ObjectMapper* mapper)
    : Serialiser(mapper)
    {
      open_group = '(' ;
      close_group = ')' ;
      separate = ',' ;
      equal = '=' ;
    }

    bool finished(Reflex::Object iterator,Reflex::Object end,Reflex::Member operator_equal)
    {
      bool result = true ;
      Reflex::Object finished(Reflex::Type::ByName("bool"),&result) ;
      std::vector<void*> parameters ;
      parameters.push_back(end.Address()) ;
      operator_equal.Invoke(iterator,&finished,parameters) ;

      return Reflex::Object_Cast<bool>(finished) ;
    }


    /*
    @todo use other separators :
    if a serialised string contains a '=' or ',' or ')' ... crash... !!

    */
    std::string TextSerialiser::valueToString(const Reflex::Object& value)
    {
      Reflex::Type value_type = value.TypeOf() ;
      if (value_type == Reflex::Type::ByName("std::string"))
      {
        return Reflex::Object_Cast<std::string>(value) ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("float")))
      {
        return toString(Reflex::Object_Cast<float>(value)) ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("int")) || value_type.IsEnum())
      {
        return toString(Reflex::Object_Cast<int>(value)) ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type(Reflex::Type::ByName("int"),Reflex::REFERENCE)))
      {
        return toString(*Reflex::Object_Cast<int*>(value)) ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("unsigned int")))
      {
        return toString(Reflex::Object_Cast<unsigned int>(value)) ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("ProjetUnivers::Kernel::ObjectReference")))
      {
        return toString(Reflex::Object_Cast<ObjectReference>(value).m_object_identifier) ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("bool")))
      {
        return toString(Reflex::Object_Cast<bool>(value)) ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("Ogre::Vector3")))
      {
        return ::Ogre::StringConverter::toString(Reflex::Object_Cast< ::Ogre::Vector3>(value)) ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("Ogre::Quaternion")))
      {
        return ::Ogre::StringConverter::toString(Reflex::Object_Cast< ::Ogre::Quaternion>(value)) ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("Ogre::Degree")))
      {
        return ::Ogre::StringConverter::toString(Reflex::Object_Cast< ::Ogre::Degree>(value)) ;
      }
      else if (value_type.IsTemplateInstance())
      {
        const Reflex::ClassTemplateInstance* class_template = dynamic_cast<const Reflex::ClassTemplateInstance*>(value_type.ToTypeBase()) ;

        if (!class_template)
        {
          ErrorMessage("TextSerialiser::valueToString") ;
          return "std::set()" ;
        }

        std::string template_name(class_template->TemplateFamily().Name(Reflex::SCOPED)) ;

        if (template_name == "std::set" || template_name == "std::vector"  || template_name == "std::list")
        {
          std::string result(template_name) ;
          result += open_group ;

          Reflex::Type collection_value_type = Reflex::Type::ByName(value_type.Name(Reflex::SCOPED)+"::value_type").FinalType() ;

          Reflex::Member createCollFuncTable = value_type.MemberByName("createCollFuncTable") ;
          Reflex::CollFuncTable* collFuncTable ;
          createCollFuncTable.Invoke<Reflex::CollFuncTable*>(value,collFuncTable) ;
          Reflex::EnvironBase* env = (Reflex::EnvironBase*)collFuncTable->create_env() ;
          // feed env
          env->fObject = value.Address() ;
          env->fIdx = 1 ;

          std::string separator ;
          for (void* element = collFuncTable->first_func(env) ; element ; env->fIdx = 1, element = collFuncTable->next_func(env))
          {
            result += separator ;
            separator = separate ;
            Reflex::Object element_value(collection_value_type,element) ;
            result += valueToString(element_value) ;
          }

          delete collFuncTable ;
          delete env ;

          result += close_group ;
          return result ;
        }
        else if (template_name == "std::map")
        {
          std::string result(template_name) ;
          result += open_group ;

          Reflex::Type pair_type = Reflex::Type::ByName(value_type.Name(Reflex::SCOPED)+"::value_type").FinalType() ;

          Reflex::Type key_type = Reflex::Type::ByName(value_type.Name(Reflex::SCOPED)+"::key_type").FinalType() ;
          Reflex::Type mapped_type = Reflex::Type::ByName(value_type.Name(Reflex::SCOPED)+"::mapped_type").FinalType() ;

          Reflex::Member createCollFuncTable = value_type.MemberByName("createCollFuncTable") ;
          Reflex::CollFuncTable* collFuncTable ;
          createCollFuncTable.Invoke<Reflex::CollFuncTable*>(value,collFuncTable) ;
          Reflex::EnvironBase* env = (Reflex::EnvironBase*)collFuncTable->create_env() ;
          // feed env
          env->fObject = value.Address() ;
          env->fIdx = 1 ;

          std::string separator ;
          for (void* element = collFuncTable->first_func(env) ; element ; env->fIdx = 1, element = collFuncTable->next_func(env))
          {
            result += separator ;
            separator = separate ;
            Reflex::Object element_value(pair_type,element) ;
            Reflex::Object first_value(key_type,element_value.Address()) ;

            // value_offset
            result += valueToString(first_value) ;
            result += "," ;

            Reflex::Object second_value(mapped_type,(char*)element_value.Address()+collFuncTable->value_offset) ;
            result += valueToString(second_value) ;
          }

          delete collFuncTable ;
          delete env ;

          result += close_group ;
          return result ;
        }
        else
        {
          ErrorMessage("TextSerialiser::valueToString") ;
        }
        return "std::set()" ;
      }
      else if (value_type.IsClass())
      {
        return serialiseObject(value_type,value) ;
      }
      ErrorMessage("TextSerialiser Unsupported type " + value_type.Name(Reflex::SCOPED)) ;
      return "" ;
    }

    void TextSerialiser::setValue(Reflex::Object target_value,const std::string& value,Model* model)
    {
      Reflex::Type value_type = target_value.TypeOf() ;
      if (value_type == Reflex::Type::ByName("std::string"))
      {
        *(std::string*)target_value.Address() = value ;
      }
      else if (value_type == Reflex::Type::ByName("float"))
      {
        static float real_value ;
        real_value = (float)atof(value.c_str()) ;
        *(float*)target_value.Address() = real_value ;
      }
      else if (value_type == Reflex::Type::ByName("int")  || value_type.IsEnum())
      {
        static int real_value ;
        real_value = (int)atoi(value.c_str()) ;
        *(int*)target_value.Address() = real_value ;
      }
      else if (value_type == Reflex::Type::ByName("unsigned int"))
      {
        static unsigned int real_value ;
        real_value = (unsigned int)atoi(value.c_str()) ;
        *(unsigned int*)target_value.Address() = real_value ;
      }
      else if (value_type == Reflex::Type::ByName("ProjetUnivers::Kernel::ObjectReference"))
      {
        *(ObjectReference*)target_value.Address() = m_mapper->getMappedObject(model,atoi(value.c_str())) ;
      }
      else if (value_type == Reflex::Type::ByName("bool"))
      {
        static bool real_value ;
        real_value = (bool)atoi(value.c_str()) ;
        *(bool*)target_value.Address() = real_value ;
      }
      else if (value_type == Reflex::Type::ByName("Ogre::Vector3"))
      {
        ::Ogre::Vector3 real_value = ::Ogre::StringConverter::parseVector3(value) ;
        *(::Ogre::Vector3*)target_value.Address() = real_value ;
      }
      else if (value_type == Reflex::Type::ByName("Ogre::Quaternion"))
      {
        ::Ogre::Quaternion real_value = ::Ogre::StringConverter::parseQuaternion(value) ;
        *(::Ogre::Quaternion*)target_value.Address() = real_value ;
      }
      else if (value_type == Reflex::Type::ByName("Ogre::Degree"))
      {
        ::Ogre::Degree real_value(::Ogre::StringConverter::parseReal(value)) ;
        *(::Ogre::Degree*)target_value.Address() = real_value ;
      }
      else if (value_type.IsTemplateInstance())
      {
        const Reflex::ClassTemplateInstance* class_template = dynamic_cast<const Reflex::ClassTemplateInstance*>(value_type.ToTypeBase()) ;

        if (!class_template)
        {
          ErrorMessage("TextSerialiser::setValue") ;
          return ;
        }

        std::string template_name(class_template->TemplateFamily().Name(Reflex::SCOPED)) ;

        if (template_name == "std::set" || template_name == "std::vector"  || template_name == "std::list")
        {
          Reflex::Type set_value_type = Reflex::Type::ByName(value_type.Name(Reflex::SCOPED)+"::value_type").FinalType() ;

          Reflex::Member createCollFuncTable = value_type.MemberByName("createCollFuncTable") ;
          Reflex::CollFuncTable* collFuncTable ;
          createCollFuncTable.Invoke<Reflex::CollFuncTable*>(target_value,collFuncTable) ;
          Reflex::EnvironBase* env((Reflex::EnvironBase*)collFuncTable->create_env()) ;

          env->fObject = target_value.Address() ;

          std::list<std::string> values = parseListValues(value) ;
          for (std::list<std::string>::iterator collection_value = values.begin() ; collection_value != values.end() ; ++collection_value)
          {
            Reflex::Object temp(set_value_type,set_value_type.Allocate()) ;
            // recursive...
            setValue(temp,*collection_value,model) ;

            // call insert
            env->fSize = 1;
            env->fStart = temp.Address() ;
            collFuncTable->feed_func(env);

            set_value_type.Deallocate(temp.Address()) ;
          }

          delete collFuncTable ;
          delete env ;
        }
        else if (template_name == "std::map")
        {
          Reflex::Type pair_type = Reflex::Type::ByName(value_type.Name(Reflex::SCOPED)+"::value_type").FinalType() ;
          Reflex::Type key_type = Reflex::Type::ByName(value_type.Name(Reflex::SCOPED)+"::key_type").FinalType() ;
          Reflex::Type mapped_type = Reflex::Type::ByName(value_type.Name(Reflex::SCOPED)+"::mapped_type").FinalType() ;

          Reflex::Member createCollFuncTable = value_type.MemberByName("createCollFuncTable") ;
          Reflex::CollFuncTable* collFuncTable ;
          createCollFuncTable.Invoke<Reflex::CollFuncTable*>(target_value,collFuncTable) ;
          Reflex::EnvironBase* env = (Reflex::EnvironBase*)collFuncTable->create_env() ;
          // feed env
          env->fObject = target_value.Address() ;
          env->fIdx = 1 ;

          std::map<std::string,std::string> values = parseMapValues(value) ;
          for (std::map<std::string,std::string>::iterator collection_value = values.begin() ; collection_value != values.end() ; ++collection_value)
          {
            // because we do not have the size of pair_type so we suppose it is
            // sum of size of key,value
            void* memory = new char[key_type.SizeOf()+mapped_type.SizeOf()] ;
            Reflex::Object pair(pair_type,memory) ;

            // recursive on key...
            Reflex::Object key(key_type,pair.Address()) ;
            setValue(key,collection_value->first,model) ;

            // ...and value
            Reflex::Object mapped(mapped_type,(char*)memory+collFuncTable->value_offset) ;
            setValue(mapped,collection_value->second,model) ;

            // add
            env->fSize = 1;
            env->fStart = pair.Address() ;
            collFuncTable->feed_func(env) ;

            pair_type.Deallocate(pair.Address()) ;
          }


          delete collFuncTable ;
          delete env ;
        }
      }
      else if (value_type.IsClass())
      {
        // assignment operator for the member type
        Reflex::Member assignement = value_type.MemberByName("operator=") ;

        // a temporary value
        void* memory = value_type.Allocate() ;
        Reflex::Object input(value_type,memory) ;
        fillTrait(value.substr(value.find('(')),input,value_type,model) ;

        // perform assignment
        std::vector<void*> paramList ;
        paramList.push_back(input.Address()) ;
        Reflex::Object result ;
        assignement.Invoke(target_value,&result,paramList) ;

        // clean
        value_type.Deallocate(memory) ;
      }
      else
      {
        ErrorMessage("TextSerialiser Unsupported type " + value_type.Name(Reflex::SCOPED)) ;
        std::cerr << "TextSerialiser Unsupported type " << value_type.Name(Reflex::SCOPED) << std::endl ;
      }
    }

    bool isSupported(const Reflex::Type& value_type)
    {
      if (value_type == Reflex::Type::ByName("std::string"))
      {
        return true ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("float")))
      {
        return true ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("int")) || value_type.IsEnum())
      {
        return true ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type(Reflex::Type::ByName("int"),Reflex::REFERENCE)))
      {
        return true ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("unsigned int")))
      {
        return true ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("ProjetUnivers::Kernel::ObjectReference")))
      {
        return true ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("bool")))
      {
        return true ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("Ogre::Vector3")))
      {
        return true ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("Ogre::Quaternion")))
      {
        return true ;
      }
      else if (value_type.IsEquivalentTo(Reflex::Type::ByName("Ogre::Degree")))
      {
        return true ;
      }
      else if (value_type.IsTemplateInstance())
      {
        const Reflex::ClassTemplateInstance* class_template = dynamic_cast<const Reflex::ClassTemplateInstance*>(value_type.ToTypeBase()) ;

        if (!class_template)
        {
          return false ;
        }

        std::string template_name(class_template->TemplateFamily().Name(Reflex::SCOPED)) ;

        if (template_name == "std::set" || template_name == "std::vector"  || template_name == "std::list")
        {
          return true ;
        }
        else if (template_name == "std::map")
        {
          return true ;
        }
        return false ;
      }
      else if (value_type.IsClass() &&
               value_type.SizeOf() != 0 && // not undefined
               value_type.Name().find('<') == std::string::npos) // not a hidden template
      {
        return true ;
      }
      return false ;
    }

    void TextSerialiser::displaySupport(const Reflex::Type& type) const
    {
      bool displayed_name = false ;
      for(Reflex::Member_Iterator member = type.Member_Begin() ; member != type.Member_End() ; ++member)
      {
        if (member->IsDataMember() && !isSupported(member->TypeOf()))
        {
          if (!displayed_name)
          {
            std::cout << std::endl << "type " << type.Name(Reflex::SCOPED) << std::endl ;
            displayed_name = true ;
          }

          std::cout << "  member " << member->Name() << " " << member->TypeOf().Name(Reflex::SCOPED) << std::endl ;
        }
      }
    }

    std::string TextSerialiser::serialiseObject(const Reflex::Type& type,Reflex::Object object)
    {
      std::string result(type.Name(Reflex::SCOPED)) ;
      result += open_group ;

      bool has_member = false ;

      for(Reflex::Member_Iterator member = type.Member_Begin() ; member != type.Member_End() ; ++member)
      {
        if (member->IsDataMember())
        {
          if (has_member)
            result += separate ;
          else
            has_member = true ;
          result += member->Name() ;
          result += equal ;
          result += valueToString(member->Get(object)) ;
        }
      }

      result += close_group ;
      return result ;
    }

    std::string TextSerialiser::serialiseTrait(const Trait& trait)
    {
      Reflex::Type type(Reflex::Type::ByTypeInfo(typeid(trait))) ;

      Reflex::Object object(type,const_cast<Trait*>(&trait)) ;

      std::string result(type.Name(Reflex::SCOPED)) ;
      result += open_group ;

      bool has_member = false ;

      for(Reflex::Member_Iterator member = type.Member_Begin() ; member != type.Member_End() ; ++member)
      {
        if (member->IsDataMember())
        {
          if (has_member)
            result += separate ;
          else
            has_member = true ;
          result += member->Name() ;
          result += equal ;
          result += valueToString(member->Get(object)) ;
        }
      }

      result += close_group ;
      return result ;
    }

    Trait* TextSerialiser::deserialiseTrait(const std::string& text,Model* model)
    {
      std::string trait_name ;
      std::string::size_type position_of_parenthesis = text.find(open_group) ;
      if (position_of_parenthesis == std::string::npos)
        return NULL ;

      trait_name = text.substr(0,position_of_parenthesis) ;
      Reflex::Type type(Reflex::Type::ByName(trait_name)) ;

      if (!type)
        return NULL ;

      // create the result
      Reflex::Object instance = type.Construct() ;

      fillTrait(text,instance,type,model) ;

      return static_cast<Trait*>(instance.Address()) ;
    }

    void TextSerialiser::deserialiseTrait(const std::string& text,Trait* trait)
    {
      std::string trait_name ;
      std::string::size_type position_of_parenthesis = text.find(open_group) ;
      if (position_of_parenthesis == std::string::npos)
        return ;

      trait_name = text.substr(0,position_of_parenthesis) ;
      Reflex::Type type(Reflex::Type::ByName(trait_name)) ;

      if (!type)
        return ;

      Reflex::Object instance(type,trait) ;
      fillTrait(text,instance,type,trait->getObject()->getModel()) ;

      trait->notify() ;
    }

    void TextSerialiser::fillTrait(const std::string& text,Reflex::Object instance,const Reflex::Type& type,Model* model)
    {
      std::list<std::pair<std::string,std::string> > members = parseValues(text) ;

      for (std::list<std::pair<std::string,std::string> >::iterator member = members.begin() ; member != members.end() ; ++member)
      {
        Reflex::Member meta_member = type.MemberByName(member->first) ;

        CHECK(meta_member && meta_member.IsDataMember(),"cannot find member") ;

        // deserialise value

        setValue(meta_member.Get(instance),member->second,model) ;

      }
    }

    std::list<std::pair<std::string,std::string> > TextSerialiser::parseValues(const std::string& text) const
    {
      std::list<std::pair<std::string,std::string> > result ;
      std::string::size_type begin_member = text.find(open_group) ;
      std::string::size_type end_member ;
      // fill members
      do
      {
        ++begin_member ;
        end_member = text.find(equal,begin_member) ;
        if (end_member == std::string::npos)
          break ;

        std::string member_name = text.substr(begin_member,end_member-begin_member) ;

        std::string::size_type end_member_value ;
        std::string::size_type begin_member_value = end_member ;

        // @todo handle final )
        int number_of_openned_parenthesis = 0 ;

        do
        {
          end_member_value = text.find_first_of(",)(",begin_member_value) ;

          if (text[end_member_value] == open_group)
          {
            ++number_of_openned_parenthesis ;
          }
          else if (text[end_member_value] == close_group)
          {
            --number_of_openned_parenthesis ;
          }

          begin_member_value = end_member_value + 1 ;
        }
        while (number_of_openned_parenthesis > 0 ||(number_of_openned_parenthesis == 0 && text[end_member_value] == close_group)) ;

        std::string member_value = text.substr(end_member+1,end_member_value-end_member-1) ;

        result.push_back(std::make_pair(member_name,member_value)) ;

        begin_member = text.find(separate,end_member_value) ;
      }
      while (begin_member != std::string::npos) ;

      return result ;
    }

    std::string::size_type TextSerialiser::move(const std::string& text,const std::string::size_type& begin) const
    {
      std::string::size_type begin_member = begin ;
      std::string::size_type end_member ;
      int number_of_openned_parenthesis = 0 ;

      do
      {
        ++begin_member ;
        end_member = text.find_first_of(",)(",begin_member) ;

        if (text[end_member] == open_group)
        {
          ++number_of_openned_parenthesis ;
        }
        else if (text[end_member] == close_group)
        {
          --number_of_openned_parenthesis ;
        }
        begin_member = end_member ;
      }
      while (number_of_openned_parenthesis > 0 ||(number_of_openned_parenthesis == 0 && text[end_member] == close_group)) ;

      return end_member ;
    }

    std::list<std::string> TextSerialiser::parseListValues(const std::string& text) const
    {
      std::list<std::string> result ;
      std::string::size_type begin_member = text.find(open_group) ;
      std::string::size_type end_member ;
      do
      {
        ++begin_member ;
        end_member = move(text,begin_member) ;

        if (end_member == std::string::npos)
          break ;

        std::string member_value = text.substr(begin_member,end_member-begin_member) ;
        result.push_back(member_value) ;
        begin_member = end_member ;
      }
      while (begin_member != std::string::npos) ;

      return result ;
    }

    std::map<std::string,std::string> TextSerialiser::parseMapValues(const std::string& text) const
    {
      std::map<std::string,std::string> result ;

      std::list<std::string> result_as_list = parseListValues(text) ;

      for (std::list<std::string>::const_iterator element = result_as_list.begin() ; element != result_as_list.end() ; ++element)
      {
        const std::string& key = *element ;
        ++element ;
        const std::string& value = *element ;

        result.insert(std::make_pair(key,value)) ;
      }

      return result ;
    }

    std::string TextSerialiser::serialiseRelation(const Relation& relation)
    {
      std::string result("ProjetUnivers::") ;
      const TypeIdentifier& type = relation.getType() ;
      result += type.fullName() ;
      result += open_group ;
      result += toString(m_mapper->getMappedIdentifier(relation.getObjectFrom())) ;
      result += separate ;
      result += toString(m_mapper->getMappedIdentifier(relation.getObjectTo())) ;
      result += close_group ;

      return result ;
    }

    void TextSerialiser::addRelation(const std::string& text,Model* model)
    {
      std::string relation_name ;
      std::string::size_type position_of_parenthesis = text.find(open_group) ;
      if (position_of_parenthesis == std::string::npos)
        return ;

      relation_name = text.substr(0,position_of_parenthesis) ;
      TypeIdentifier type(relation_name) ;

      std::string::size_type position_of_column = text.find(separate,position_of_parenthesis) ;

      std::string identifier1 = text.substr(position_of_parenthesis+1,
                                            position_of_column-position_of_parenthesis-1) ;

      std::string identifier2 = text.substr(position_of_column+1,
                                            text.length()-position_of_column-2) ;


      Object* object1 = m_mapper->getMappedObject(model,atoi(identifier1.c_str())) ;
      Object* object2 = m_mapper->getMappedObject(model,atoi(identifier2.c_str())) ;

      Relation::createLink(TypeIdentifier(type),object1,object2) ;
    }

    void TextSerialiser::removeRelation(const std::string& text,Model* model)
    {
      std::string relation_name ;
      std::string::size_type position_of_parenthesis = text.find(open_group) ;
      if (position_of_parenthesis == std::string::npos)
        return ;

      relation_name = text.substr(0,position_of_parenthesis) ;
      TypeIdentifier type(relation_name) ;

      std::string::size_type position_of_column = text.find(separate,position_of_parenthesis) ;

      std::string identifier1 = text.substr(position_of_parenthesis+1,
                                            position_of_column-position_of_parenthesis-1) ;

      std::string identifier2 = text.substr(position_of_column+1,
                                            text.length()-position_of_column-2) ;


      Object* object1 = m_mapper->getMappedObject(model,atoi(identifier1.c_str())) ;
      Object* object2 = m_mapper->getMappedObject(model,atoi(identifier2.c_str())) ;

      Relation::destroyLink(TypeIdentifier(type),object1,object2) ;
    }

  }
}

