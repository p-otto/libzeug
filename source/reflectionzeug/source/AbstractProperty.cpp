
#include <reflectionzeug/AbstractValueProperty.h>
#include <reflectionzeug/AbstractPropertyCollection.h>
#include <reflectionzeug/PropertyGroup.h>
#include <reflectionzeug/util.h>

#include <reflectionzeug/AbstractProperty.h>


namespace reflectionzeug 
{
    
const std::string AbstractProperty::s_nameRegexString("[a-zA-Z_]+\\w*");

AbstractProperty::AbstractProperty()
{
}

AbstractProperty::AbstractProperty(const std::string & name)
{
    setName(name);
}

AbstractProperty::~AbstractProperty()
{
}

const std::string & AbstractProperty::name() const
{
    return m_name;
}
    
bool AbstractProperty::setName(const std::string & name)
{    
    if (!util::matchesRegex(name, s_nameRegexString))
        return false;
    
    m_name = name;
    return true;
}
    
bool AbstractProperty::hasName() const
{
    return !m_name.empty();
}

bool AbstractProperty::hasOption(const std::string & key) const
{
    return m_options.count(key) != 0;
}

Variant2 AbstractProperty::option(const std::string & key) const
{
    if (!this->hasOption(key))
        return Variant2();

    return m_options.at(key);
}

void AbstractProperty::setOption(const std::string & key, const Variant2 & value)
{
    m_options.insert({ key, value });
}

void AbstractProperty::setOptions(const VariantMap & map)
{
    m_options.insert(map.begin(), map.end());
}

bool AbstractProperty::flagSet(const std::string & flag) const
{
    return m_flags.count(flag) == 1;
}
    
void AbstractProperty::addFlag(const std::string & flag)
{
    m_flags.insert(flag);
}

bool AbstractProperty::removeFlag(const std::string & flag)
{
    if (!flagSet(flag))
        return false;

    m_flags.erase(flag);
    return true;
}

const std::set<std::string> & AbstractProperty::flags() const
{
    return m_flags;
}

void AbstractProperty::setFlags(const std::set<std::string> & flags)
{
    m_flags = flags;
}

AbstractValueProperty * AbstractProperty::asValue()
{
    return dynamic_cast<AbstractValueProperty *>(this);
}

const AbstractValueProperty * AbstractProperty::asValue() const
{
    return dynamic_cast<const AbstractValueProperty *>(this);
}

AbstractPropertyCollection * AbstractProperty::asCollection()
{
    return dynamic_cast<AbstractPropertyCollection *>(this);
}

const AbstractPropertyCollection * AbstractProperty::asCollection() const
{
    return dynamic_cast<const AbstractPropertyCollection *>(this);
}

PropertyGroup * AbstractProperty::asGroup()
{
    return dynamic_cast<PropertyGroup *>(this);
}

const PropertyGroup * AbstractProperty::asGroup() const
{
    return dynamic_cast<const PropertyGroup *>(this);
}
    
bool AbstractProperty::isCollection() const
{
    return false;
}

bool AbstractProperty::isValue() const
{
    return false;
}
    
bool AbstractProperty::isGroup() const
{
    return false;
}

} // namespace reflectionzeug
