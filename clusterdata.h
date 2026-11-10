#ifndef CLUSTERDATA_H
#define CLUSTERDATA_H

#include <QObject>
#include <QQmlEngine>
#include <QString>

#include "turnsignals.h"
class ClusterData : public QObject {
  Q_OBJECT

  Q_PROPERTY(GearType gear READ gear WRITE setGear NOTIFY gearChanged);
  Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged);
  Q_PROPERTY(int miles READ miles WRITE setMiles NOTIFY milesChanged);
  Q_PROPERTY(TurnSignals turnSignals READ turnSignals NOTIFY turnSignalsChanged)
  Q_PROPERTY(int outsideTemp READ outsideTemp NOTIFY outsideTempChanged)
  Q_PROPERTY(double fuelLiters READ fuelLiters NOTIFY fuelLitersChanged)
  Q_PROPERTY(int fuelPercent READ fuelPercent NOTIFY fuelLitersChanged)
  Q_PROPERTY(int batterySoc READ batterySoc NOTIFY batterySocChanged)
  Q_PROPERTY(int rangeMiles READ rangeMiles NOTIFY fuelLitersChanged)

  QML_ELEMENT;
  QML_UNCREATABLE("C++")

public:
  enum GearType : int {
    GearParking,
    GearReverse,
    GearNeutral,
    GearDrive,
    GearB,
    GearUnknown
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

  TurnSignals turnSignals() const;
  void setTurnSignals(const TurnSignals &turn);

  int outsideTemp() const { return m_outsideTemp; }
  double fuelLiters() const { return m_fuelLiters; }
  int fuelPercent() const { return qRound(m_fuelLiters / kTankLiters * 100.0); }
  int batterySoc() const { return m_batterySoc; }

  void setOutsideTemp(int celsius);
  void setFuelLiters(double liters);
  void setBatterySoc(int percent);
  int rangeMiles() const;

signals:
  void gearChanged();
  void speedChanged();
  void milesChanged();
  void turnSignalsChanged();
  void outsideTempChanged();
  void fuelLitersChanged();
  void batterySocChanged();

private:
  int m_speed = 0;
  int m_miles = 400;
  TurnSignals m_signals;
  GearType m_gear = GearParking;
  static constexpr double kTankLiters = 36.0;
  int m_outsideTemp = 0;
  static constexpr double kLitersPerGallon = 3.78541;
  static constexpr double kMpg = 50.0;
  double m_fuelLiters = 0.0;
  int m_batterySoc = 0;
};

#endif
