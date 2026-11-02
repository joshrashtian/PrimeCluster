#include "clusterdata.h"

ClusterData::ClusterData(QObject *parent) : QObject(parent) {}

int ClusterData::speed() const { return m_speed; }

ClusterData::GearType ClusterData::gear() const { return m_gear; }

int ClusterData::miles() const { return m_miles; 
}
void ClusterData::setSpeed(const int &speed) 
{
  if(m_speed != speed) { m_speed = speed; emit speedChanged(); }
}

void ClusterData::setGear(const ClusterData::GearType &gear) 
{
  if(m_gear != gear) { m_gear = gear; emit gearChanged(); }
}

void ClusterData::setMiles(const int &miles)
{
  if(m_miles != miles) { m_miles = miles; emit milesChanged(); }
}


void ClusterData::resetData () {
  setSpeed(0);
  setGear(GearParking);
  setMiles(400);
}
