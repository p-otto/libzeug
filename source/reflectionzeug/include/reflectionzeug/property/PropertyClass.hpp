
#pragma once


#include <iostream>

#include <reflectionzeug/property/PropertyClass.h>
#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


template <typename T>
template <typename... Args>
PropertyClass<T>::PropertyClass(Args&&... args)
: AbstractValueProperty<T>(std::forward<Args>(args)...)
{
}

template <typename T>
PropertyClass<T>::~PropertyClass()
{
}

template <typename T>
void PropertyClass<T>::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyClass<T>>(this);
}


} // namespace reflectionzeug
