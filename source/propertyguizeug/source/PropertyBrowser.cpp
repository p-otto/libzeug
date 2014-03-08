
#include <propertyguizeug/PropertyModel.h>
#include <propertyguizeug/PropertyDelegate.h>
#include <propertyguizeug/PropertyEditorFactory.h>
#include <propertyguizeug/PropertyPainter.h>

#include <propertyguizeug/PropertyBrowser.h>

using namespace reflectionzeug;
namespace propertyguizeug
{
    
PropertyBrowser::PropertyBrowser(QWidget * parent)
:   PropertyBrowser(nullptr,
                    parent)
{
    
}

PropertyBrowser::PropertyBrowser(
    PropertyGroup * root,
    QWidget * parent)
:   PropertyBrowser(root,
                    new PropertyEditorFactory(),
                    new PropertyPainter(),
                    parent)
{
    
}
    
PropertyBrowser::PropertyBrowser(
    PropertyEditorFactory * editorFactory,
    PropertyPainter * painter,
    QWidget * parent)
:   PropertyBrowser(nullptr,
                    editorFactory,
                    painter,
                    parent)
{
    this->setItemDelegateForColumn(1, m_delegate);
    
    initView();
}
    
PropertyBrowser::PropertyBrowser(
    PropertyGroup * root,
    PropertyEditorFactory * editorFactory,
    PropertyPainter * painter,
    QWidget * parent)
:   QTreeView(parent)
,   m_model(new PropertyModel(root))
,   m_delegate(new PropertyDelegate(editorFactory, painter, this))
{
    this->setModel(m_model);
    this->setItemDelegateForColumn(1, m_delegate);
    
    initView();
}

PropertyBrowser::~PropertyBrowser()
{
    delete m_model;
}
    
void PropertyBrowser::setRoot(reflectionzeug::PropertyGroup * root)
{
    PropertyModel * newModel = new PropertyModel(root);
    this->setModel(newModel);
    
    delete m_model;
    m_model = newModel;
}
    
void PropertyBrowser::initView()
{
    this->setEditTriggers(QAbstractItemView::DoubleClicked  |
                          QAbstractItemView::EditKeyPressed |
                          QAbstractItemView::CurrentChanged);
    this->setAlternatingRowColors(true);
    this->setUniformRowHeights(true);
    this->setColumnWidth(0, 150);
    this->setColumnWidth(1, 200);
    this->expandAll();
}

} // namespace propertyguizeug
