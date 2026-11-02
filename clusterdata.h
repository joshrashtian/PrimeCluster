#ifndef CLUSTERDATA_H
#define CLUSTERDATA_H

#include <QObject>
#include <QQmlEngine>
#include <QString>
class ClusterData : public QObject {
  Q_OBJECT

  Q_PROPERTY(GearType gear READ gear WRITE setGear NOTIFY gearChanged);
  Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged);
  Q_PROPERTY(int miles READ miles WRITE setMiles NOTIFY milesChanged);
  QML_ELEMENT;
public:
  enum GearType : int {
    GearParking,
    GearReverse,
    GearNeutral,
    GearDrive,
    GearB
  };
  Q_ENUM(GearType);

  explicit ClusterData(QObject *parent = nullptr);

  GearType gear() const;
  void setGear(const GearType &gear);

  int speed() const;
  void setSpeed(const int &speed);
  
  int miles() const;
  void setMiles(const int &miles);
  void resetData();

signals:
  void gearChanged();
  void speedChanged();
  void milesChanged();


private:
  int m_speed = 0;
  int m_miles = 400;
  GearType m_gear = GearParking;
};

#endif 
