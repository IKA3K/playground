#ifndef POINTS_H_
#define POINTS_H_

#include <vector>
#include <utility>

// Solution for https://leetcode.com/problems/max-points-on-a-line/
typedef std::vector<int> Point;
typedef std::vector<Point> Points;

int max_points(Points& points);

#endif  // POINTS_H_