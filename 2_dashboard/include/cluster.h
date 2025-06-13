

#ifndef CLUSTER_H
#define CLUSTER_H

#include <QObject>
#include <QVariant>
#include <QTimer>

class Cluster : public QObject
{
    Q_OBJECT
  /*  Q_PROPERTY(type name
               (READ getFunction [WRITE setFunction] |
                MEMBER memberName [(READ getFunction | WRITE setFunction)])
               [RESET resetFunction]
               [NOTIFY notifySignal]
               [REVISION int]
               [DESIGNABLE bool]
               [SCRIPTABLE bool]
               [STORED bool]
               [USER bool]
               [CONSTANT]
               [FINAL])*/
    Q_PROPERTY(QVariant speed READ speed NOTIFY speedChanged)

    Q_PROPERTY(QVariant rpm   READ rpm   NOTIFY rpmChanged)
    Q_PROPERTY(QVariant fuel  READ fuel  NOTIFY fuelChanged)
    Q_PROPERTY(QVariant temp READ temp NOTIFY tempChanged)
    Q_PROPERTY(QVariant r_value READ r_value NOTIFY r_valueChanged)
    Q_PROPERTY(QVariant l_value READ l_value NOTIFY l_valueChanged)

public:
    static Cluster &instance();

private:
    explicit Cluster(QObject *parent = 0);

public:

    QVariant m_rpm;
    QVariant m_speed;
    QVariant m_fuel;
    QVariant m_temp;
    QVariant m_r_value;
    QVariant m_l_value;

public:

    QVariant speed() const;
    void setSpeed(QVariant value);

    QVariant rpm() const;
    void setRpm(QVariant value);

    QVariant fuel() const;
    void setFuel(const QVariant &fuel);

    QVariant temp()const;
    void setTemp(const QVariant & temp);

    QVariant r_value()const;
    void set_r_value(const QVariant &value);
    QVariant l_value()const;
    void set_l_value(const QVariant &value);


signals:
    void speedChanged();
    void rpmChanged();
    void fuelChanged();
    void tempChanged();
    void r_valueChanged();
    void l_valueChanged();

};

#endif // CLUSTER_H
