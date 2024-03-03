#include "points.h"

#include <limits>
#include <list>

namespace {

struct Line {
  // The points that make up this line.
  Points line;
  // The point after the next point in the line. This allows us to avoid
  // looping over points before, which clearly cannot be part of the line.
  typename Points::iterator next;
  // Rate of change between points (expressed as y-axis). -inf and inf are valid values.
  double rate;
};

}  // namespace

int max_points(Points& points) {
  if (points.empty()) {
    return 0;
  }
  // Constraints:
  // 1 <= points.length <= 300
  // points[i].length == 2
  // -104 <= xi, yi <= 104
  // All the points are unique.

  // Thinking out aloud:
  //
  // Note: the problem definition does not specify what order any of the points are in
  // (as in this is not a polyline)
  //
  // At first glance, seems like the way to do this is to build ALL possible lines, and then
  // attempt to add points that are not part of the line to each.
  //
  // This has its drawbacks, as for example 2 in the test set:
  //    [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
  //
  // if you have the points [1,4] and [4,1] in a line, then [3,2] added afterwards
  // would not satisfy the constraint as the delta of -x would not work. 

  // First step: Sort the array based on the x value (followed by y), to prevent unnecessary line construction.
  std::sort(points.begin(), points.end(), [](const Point& l, const Point& r) {
    return l[0] < r[0] || (l[0] == r[0] && l[1] < r[1]);
  });

  // Second step: Permute every single line combination, and add it to list of lines.
  auto rate = [](const Point& a, const Point& b) {
    // Compute rate, with special case for a[0] == b[0] (which means a rate of positive inf)
    if (a[0] == b[0]) {
      return std::numeric_limits<double>::infinity();
    }
    return (b[1] - a[1]) / static_cast<double>(b[0] - a[0]);
  };

  std::list<Line> lines;
  for (auto iter1 = points.begin(); iter1 != points.end(); ++iter1) {
    for (auto iter2 = iter1 + 1; iter2 != points.end(); ++iter2) {
      const Point& a = *iter1;
      const Point& b = *iter2;
      Line line;
      line.line = {a, b};
      line.next = iter2 + 1;
      line.rate = rate(a, b);
      lines.emplace_back(line);
    }
  }

  // Third step: Exhaustively attempt to add every point to each other line, removing lines
  // from the set if no other point can be added. Since we know that the list of points is sorted,
  // we only need to consider.
  //
  // (Removing is handled by emptying lines one by one and putting them in a temp var, then restoring it.
  int max = 1;
  while (!lines.empty()) {
    // Update `max` as we start the evaluation cycle.
    max = lines.front().line.size();
    
    // Pop a line from lines, and attempt insert a point. If successful, place it in 
    // temp.
    std::list<Line> temp;
    auto inserter = [&temp](Line line, typename Points::iterator iter) {
      line.line.push_back(*iter);
      line.next = iter + 1;
      temp.push_back(line);
    };

    while (!lines.empty()) {
      Line line = std::move(lines.front());
      lines.pop_front();
      for (auto iter = line.next; iter != points.end(); ++iter) {
        // Compute rate between this point and the last point in the existing line.
        // If it's a valid line, insert it into the list of lines to consider.
        double new_rate = rate(line.line.back(), *iter);

        // Special case for infinity.
        if (line.rate == std::numeric_limits<double>::infinity() &&
            new_rate == std::numeric_limits<double>::infinity()) {
          inserter(line, iter);
        } else if (std::fabs(new_rate - line.rate) <= std::numeric_limits<double>::epsilon()) {
            // Should work for values given in set.
          inserter(line, iter);
        }
      }
    }
    lines = std::move(temp);
  }
  return max;
}