#include "cluster.h"
#include <QLocale>
#include<QDebug>

static Cluster * clusterInstance = Q_NULLPTR;

Cluster::Cluster(QObject *parent)
    : QObject(parent), m_speed(), m_rpm(), m_fuel() {
        this->setSpeed(QVariant(0));
        this->setRpm(0);
        this->setTemp(0);
        this->setFuel(0);
    }

Cluster &Cluster::instance()
{
    static Cluster instance; 
    return instance;
}

QVariant Cluster::speed() const{ return m_speed; }
void Cluster::setSpeed(QVariant value)
{
    m_speed = value;
    qDebug() << "Setting Speed:"<<value ;
    emit speedChanged();
}

QVariant Cluster::rpm() const{ return m_rpm; }
void Cluster::setRpm(QVariant value)
{
    m_rpm = value;
    qDebug() << "Setting RPM:"<<value ;
    emit rpmChanged();
}

QVariant Cluster::fuel() const{ return m_fuel; }
void Cluster::setFuel(const QVariant &fuel)
{
    m_fuel = fuel;
      qDebug() << "Setting fuel:"<<fuel ;
    emit fuelChanged();
}

QVariant Cluster::temp() const{ return m_temp; }
void Cluster::setTemp(const QVariant &temp)
{
    m_temp = temp;
      qDebug() << "Setting Temp:"<<temp ;
    emit tempChanged();
}

QVariant Cluster::r_value() const{ return m_r_value; }
void Cluster::set_r_value (const QVariant &value)
{
       m_r_value = value;
      qDebug() << "Setting r_value:"<<value ;
    emit r_valueChanged();
}

QVariant Cluster::l_value() const{ return m_l_value; }
void Cluster::set_l_value (const QVariant &value)
{
       m_l_value = value;
      qDebug() << "Setting l_value:"<<value ;
    emit l_valueChanged();
}
