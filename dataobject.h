

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
    Q_PROPERTY(bool checked READ getChecked WRITE setChecked NOTIFY checkedChanged)
//![0]

public:
    DataObject(QObject *parent=0);
    DataObject(const QString &name,const QString & number, const QString &color, QObject *parent=0);

    Q_INVOKABLE

    void setChecked(){checked=!checked;}
    bool getChecked(){return checked;}

    QString name() const;
    void setName(const QString &name);


    QString number() const;
    void setNumber(const QString &number);

    QString color() const;
    void setColor(const QString &color);

signals:
    void nameChanged();
    void numberChanged();
    void checkedChanged();
    void colorChanged();

private:
    QString m_name;
    QString m_number;
    QString m_color;
    bool checked = false;
//![1]
};
//![1]

#endif // DATAOBJECT_H
