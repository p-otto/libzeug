
#pragma once

#include <reflectionzeug/NumberProperty.h>

#include <limits>
#include <sstream>

#include <reflectionzeug/util.h>

namespace reflectionzeug
{

template <typename Type>
template <typename... Arguments>
NumberProperty<Type>::NumberProperty(Arguments&&... args)
:   ValueProperty<Type>(std::forward<Arguments>(args)...)
{
    this->setOptions({
        { "min", Variant(std::numeric_limits<Type>::min()) },
        { "max", Variant(std::numeric_limits<Type>::max()) }
    });
}

template <typename Type>
NumberProperty<Type>::~NumberProperty()
{
}

template <typename Type>
std::string NumberProperty<Type>::toString() const
{
    std::string prefix, suffix;
    if (hasOption("prefix"))
        prefix = option("prefix").value<std::string>();
    if (hasOption("suffix"))
        suffix = option("suffix").value<std::string>();

    return prefix + util::toString(this->value()) + suffix;
}

template <typename Type>
bool NumberProperty<Type>::fromString(const std::string & string)
{
    if (!util::matchesRegex(string, matchRegex()))
        return false;

    this->setValue(util::fromString<Type>(string));
    return true;
}

} // namespace reflectionzeug
