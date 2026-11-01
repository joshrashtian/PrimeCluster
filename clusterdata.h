#ifndef CLUSTERDATA_H
#define CLUSTERDATA_H

#include <QObject>
#include <QString>
class ClusterData : public QObject {
  Q_OBJECT

  Q_PROPERTY(GearType gear READ gear WRITE setGear NOTIFY gearChanged);
  Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged);

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
  
  void resetData();

signals:
  void gearChanged();
  void speedChanged();


private:
  int m_speed = 0;
  GearType m_gear = GearParking;
};

#endif 
