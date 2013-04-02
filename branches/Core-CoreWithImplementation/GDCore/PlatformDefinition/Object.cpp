/** \file
 *  Game Develop
 *  2008-2013 Florian Rival (Florian.Rival@gmail.com)
 */
#include "GDCore/PlatformDefinition/Object.h"
#include "GDCore/PlatformDefinition/Automatism.h"
#include "GDCore/PlatformDefinition/Platform.h"
#include "GDCore/PlatformDefinition/Project.h"
#include "GDCore/PlatformDefinition/Layout.h"
#include "GDCore/TinyXml/tinyxml.h"

namespace gd
{

Object::~Object()
{
    //Do not forget to delete automatisms which are managed using raw pointers.
    for (std::map<std::string, Automatism* >::const_iterator it = automatisms.begin() ; it != automatisms.end(); ++it )
    	delete it->second;
}

Object::Object(const std::string & name_) :
    name(name_)
{
}

void Object::Init(const gd::Object & object)
{
    name = object.name;
    type = object.type;
    objectVariables = object.objectVariables;

    //Do not forget to delete automatisms which are managed using raw pointers.
    for (std::map<std::string, Automatism* >::const_iterator it = automatisms.begin() ; it != automatisms.end(); ++it )
    	delete it->second;

    automatisms.clear();
    for (std::map<std::string, Automatism* >::const_iterator it = object.automatisms.begin() ; it != object.automatisms.end(); ++it )
    	automatisms[it->first] = it->second->Clone();
}

#if defined(GD_IDE_ONLY)
std::vector < std::string > Object::GetAllAutomatismNames() const
{
    std::vector < std::string > allNameIdentifiers;

    for (std::map<std::string, Automatism* >::const_iterator it = automatisms.begin() ; it != automatisms.end(); ++it )
    	allNameIdentifiers.push_back(it->first);

    return allNameIdentifiers;
}

void Object::RemoveAutomatism(const std::string & name)
{
    //Do not forget to delete automatisms which are managed using raw pointers.
    delete(automatisms[name]);

    automatisms.erase(name);
}

gd::Automatism * Object::AddNewAutomatism(gd::Project & project, const std::string & type, const std::string & name)
{
    Automatism * automatism = project.GetPlatform().CreateAutomatism(type);
    automatism->SetName(name);
    automatisms[automatism->GetName()] = automatism;

    return automatism;
}

std::map<std::string, std::string> Object::GetInitialInstanceProperties(const gd::InitialInstance & position, gd::Project & project, gd::Layout & layout)
{
    std::map<std::string, std::string> nothing;
    return nothing;
}

gd::Automatism & Object::GetAutomatism(const std::string & name)
{
    return *automatisms.find(name)->second;
}

const gd::Automatism & Object::GetAutomatism(const std::string & name) const
{
    return *automatisms.find(name)->second;
}

bool Object::HasAutomatismNamed(const std::string & name) const
{
    return automatisms.find(name) != automatisms.end();
}
#endif

void Object::LoadFromXml(gd::Project & project, const TiXmlElement * elemScene)
{
    //Name and type are already loaded.

    if ( elemScene->FirstChildElement( "Variables" ) != NULL ) { objectVariables.LoadFromXml(elemScene->FirstChildElement( "Variables" )); }

    if ( elemScene->FirstChildElement( "Automatism" ) != NULL )
    {
        const TiXmlElement * elemAutomatism = elemScene->FirstChildElement( "Automatism" );
        while ( elemAutomatism )
        {
            std::string autoType = elemAutomatism->Attribute("Type") != NULL ? elemAutomatism->Attribute("Type") : "";
            std::string autoName = elemAutomatism->Attribute("Name") != NULL ? elemAutomatism->Attribute("Name") : "";

            Automatism* newAutomatism = AddNewAutomatism(project, autoType, autoName);
            if ( newAutomatism != NULL )
                newAutomatism->LoadFromXml(elemAutomatism);
            else
                std::cout << "Unknown automatism" << elemAutomatism->Attribute("Type") << std::endl;

            elemAutomatism = elemAutomatism->NextSiblingElement("Automatism");
        }
    }

}

#if defined(GD_IDE_ONLY)
void Object::SaveToXml(TiXmlElement * elem)
{
    //Name and type are already saved.

    TiXmlElement * variables = new TiXmlElement( "Variables" );
    elem->LinkEndChild( variables );
    objectVariables.SaveToXml(variables);

    std::vector < std::string > allAutomatisms = GetAllAutomatismNames();
    for (unsigned int i = 0;i<allAutomatisms.size();++i)
    {
        TiXmlElement * automatism = new TiXmlElement( "Automatism" );
        elem->LinkEndChild( automatism );
        automatism->SetAttribute( "Type", GetAutomatism(allAutomatisms[i]).GetTypeName().c_str() );
        automatism->SetAttribute( "Name", GetAutomatism(allAutomatisms[i]).GetName().c_str() );

        GetAutomatism(allAutomatisms[i]).SaveToXml(automatism);
    }
}
#endif

}

void DestroyBaseObject(gd::Object * object)
{
    delete object;
}

gd::Object * CreateBaseObject(std::string name)
{
    return new gd::Object(name);
}