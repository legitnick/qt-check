

#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

//![0]
class DataObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString number READ number WRITE setNumber NOTIFY numberChanged)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
//![0]

public:
    DataObject(QObject *parent=0);
    DataObject(const QString &name,const QString & number, const QString &color, QObject *parent=0);

    QString name() const;
    void setName(const QString &name);


    QString number() const;
    void setNumber(const QString &number);

    QString color() const;
    void setColor(const QString &color);

signals:
    void nameChanged();
    void numberChanged();
    void colorChanged();

private:
    QString m_name;
    QString m_number;
    QString m_color;
//![1]
};
//![1]

#endif // DATAOBJECT_H
