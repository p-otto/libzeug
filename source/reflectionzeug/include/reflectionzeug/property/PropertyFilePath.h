
#pragma once


#include <reflectionzeug/base/FilePath.h>
#include <reflectionzeug/property/AbstractValueProperty.h>


namespace reflectionzeug
{


/**
*  @brief
*    Implementation for type FilePath
*/
class PropertyFilePath : public AbstractValueProperty<FilePath>
{
public:
    template <typename... Args>
    PropertyFilePath(Args&&... args);

    virtual ~PropertyFilePath();

    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyFilePath.hpp>
