// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>

#include <cstdint>

#include "circle.h"

TEST(CircleTest, Constructor) {
  Circle c(5.0);
  EXPECT_NEAR(c.getRadius(), 5.0, EPS);
  EXPECT_NEAR(c.getFerence(), 2 * Circle::PI * 5.0, EPS);
  EXPECT_NEAR(c.getArea(), Circle::PI * 25.0, EPS);
}

TEST(CircleTest, SetRadius) {
  Circle c(0.0);
  c.setRadius(10.0);
  EXPECT_NEAR(c.getRadius(), 10.0, EPS);
  EXPECT_NEAR(c.getFerence(), 2 * Circle::PI * 10.0, EPS);
  EXPECT_NEAR(c.getArea(), Circle::PI * 100.0, EPS);
}

TEST(CircleTest, SetFerence) {
  Circle c(0.0);
  c.setFerence(31.415926535);
  EXPECT_NEAR(c.getRadius(), 5.0, EPS);
  EXPECT_NEAR(c.getArea(), Circle::PI * 25.0, EPS);
}

TEST(CircleTest, SetArea) {
  Circle c(0.0);
  c.setArea(78.5398);
  EXPECT_NEAR(c.getRadius(), 5.0, EPS);
  EXPECT_NEAR(c.getFerence(), 2 * Circle::PI * 5.0, EPS);
}

TEST(CircleTest, ZeroRadius) {
  Circle c(0.0);
  EXPECT_NEAR(c.getFerence(), 0.0, EPS);
  EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleTest, LargeRadius) {
  Circle c(1e6);
  EXPECT_NEAR(c.getFerence(), 2 * Circle::PI * 1e6, EPS);
  EXPECT_NEAR(c.getArea(), Circle::PI * 1e12, EPS);
}

TEST(CircleTest, MultipleUpdates) {
  Circle c(2.0);
  c.setFerence(2 * Circle::PI * 3.0);
  EXPECT_NEAR(c.getRadius(), 3.0, EPS);
  c.setArea(Circle::PI * 4.0);
  EXPECT_NEAR(c.getRadius(), 2.0, EPS);
}

TEST(RopeTaskTest, BasicCalculation) {
  double gap = calculateRopeGap();
  EXPECT_NEAR(gap, 1.0 / (2 * Circle::PI), EPS);
}

TEST(RopeTaskTest, PrecisionCheck) {
  double expected_gap = 0.15915494309189535;
  double gap = calculateRopeGap();
  EXPECT_NEAR(gap, expected_gap, EPS);
}

TEST(PoolTaskTest, ConcreteArea) {
  double concrete, fence;
  calculatePoolCost(concrete, fence);
  double expected_area = Circle::PI * (4.0 * 4.0 - 3.0 * 3.0);
  EXPECT_NEAR(concrete / 1000.0, expected_area, EPS);
}

TEST(PoolTaskTest, FenceLength) {
  double concrete, fence;
  calculatePoolCost(concrete, fence);
  double expected_length = 2 * Circle::PI * 4.0;
  EXPECT_NEAR(fence / 2000.0, expected_length, EPS);
}

TEST(PoolTaskTest, CostValues) {
  double concrete, fence;
  calculatePoolCost(concrete, fence);
  EXPECT_NEAR(concrete, 1000.0 * (Circle::PI * 7.0), 1.0);
  EXPECT_NEAR(fence, 2000.0 * (2 * Circle::PI * 4.0), 1.0);
}

TEST(CircleEdgeCases, SetFerenceToZero) {
  Circle c(5.0);
  c.setFerence(0.0);
  EXPECT_NEAR(c.getRadius(), 0.0, EPS);
  EXPECT_NEAR(c.getArea(), 0.0, EPS);
}

TEST(CircleEdgeCases, SetAreaToZero) {
  Circle c(5.0);
  c.setArea(0.0);
  EXPECT_NEAR(c.getRadius(), 0.0, EPS);
  EXPECT_NEAR(c.getFerence(), 0.0, EPS);
}

TEST(CircleConsistency, RadiusFerenceConsistency) {
  Circle c(10.0);
  c.setFerence(c.getFerence() + 10.0);
  double new_radius = c.getRadius();
  c.setRadius(new_radius);
  EXPECT_NEAR(c.getFerence(), 2 * Circle::PI * new_radius, EPS);
}

TEST(CircleConsistency, FerenceAreaConsistency) {
  Circle c(5.0);
  c.setArea(100.0);
  c.setFerence(c.getFerence());
  EXPECT_NEAR(c.getArea(), 100.0, EPS);
}

TEST(CircleConsistency, AreaRadiusConsistency) {
  Circle c(3.0);
  c.setRadius(7.0);
  c.setArea(c.getArea());
  EXPECT_NEAR(c.getRadius(), 7.0, EPS);
}

TEST(NegativeCases, NegativeArea) {
  Circle c(5.0);
  c.setArea(-100.0);
  EXPECT_TRUE(std::isnan(c.getRadius()));
}

TEST(CircleConsistency, MultipleSetters) {
  Circle c(2.0);
  c.setFerence(c.getFerence() + 10.0);
  double new_radius = c.getRadius();
  c.setArea(c.getArea() * 2.0);
  c.setRadius(c.getRadius());

  EXPECT_NEAR(c.getRadius(),
              sqrt((2 * Circle::PI * new_radius * new_radius) / Circle::PI),
              EPS);
}

TEST(RopeTaskTest, DifferentEarthRadius) {
  const double testRadius = 1000.0;
  Circle earth(testRadius);
  double initialFerence = earth.getFerence();

  earth.setFerence(initialFerence + 1.0);
  double gap = earth.getRadius() - testRadius;

  EXPECT_NEAR(gap, 1.0 / (2 * Circle::PI), EPS);
}