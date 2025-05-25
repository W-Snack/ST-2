#include "tasks.h"
#include <cmath>
#include "circle.h"


double calculateRopeGap() {
  const double earthRadius = 6378100.0;
  Circle earth(earthRadius);

  earth.setFerence(earth.getFerence() + 1.0);

  return earth.getRadius() - earthRadius;
}

void calculatePoolCost(double& concreteCost, double& fenceCost) {
  const double poolRadius = 3.0;
  const double pathWidth = 1.0;
  const double concretePrice = 1000.0;
  const double fencePrice = 2000.0;

  Circle pool(poolRadius);

  Circle outer(poolRadius + pathWidth);

  double area = outer.getArea() - pool.getArea();
  concreteCost = area * concretePrice;

  fenceCost = outer.getFerence() * fencePrice;
}