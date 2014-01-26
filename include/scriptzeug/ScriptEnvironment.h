#pragma once


#include <string>
#include <scriptzeug/Variant.h>


namespace zeug {
    class PropertyGroup;
}


namespace scriptzeug
{


class AbstractScriptEnvironment;


/** \brief The entry point to managing a scripting engine in your application
 */
class SCRIPTZEUG_API ScriptEnvironment
{
public:
    ScriptEnvironment(const std::string & backend = "javascript");
    virtual ~ScriptEnvironment();

    void registerObject(zeug::PropertyGroup * obj);

    Variant evaluate(const std::string & code);

protected:
    AbstractScriptEnvironment * m_backend;
};


} // namespace zeug
