
#include <QDebug>
#include "dataobject.h"

DataObject::DataObject(QObject *parent)
    : QObject(parent)
{
}

DataObject::DataObject(const QString &name,const QString &number,const QString &color, QObject *parent)
    : QObject(parent), m_name(name), m_color(color),m_number(number)
{
}

QString DataObject::number() const{return m_number;}

void DataObject::setNumber(const QString& number) {m_number = number;}


QString DataObject::name() const
{
    return m_name;
}

void DataObject::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged();
    }
}

QString DataObject::color() const
{
    return m_color;
}

void DataObject::setColor(const QString &color)
{
    if (color != m_color) {
        m_color = color;
        emit colorChanged();
    }
}
