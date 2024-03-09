#include "max.h"

#include <limits>

#include "absl/log/log.h"

int max_spending(const std::vector<std::vector<int> >& values) {
  // Just remove the lowest value from each of the vectors .back()
  // until we have no more values left.
  std::vector<std::vector<int> > v = values;  // Make a copy for editing.

  auto remove_and_return_min_price = [&v]() -> int {
    auto min_iter = v.begin();
    int min_price = std::numeric_limits<int>::max();
    for (auto iter = v.begin(); iter != v.end(); ++iter) {
      if (!iter->empty() && iter->back() < min_price) {
        min_price = iter->back();
        min_iter = iter;
      }
    }
    int min_value = min_iter->back();
    if (min_iter->size() > 1) {
      min_iter->pop_back();
    } else {
      // Avoid iterating over this obj as there's nothing left to return.
      v.erase(min_iter);
    }
    return min_value;
  };

  int day = 1;
  int max_spend = 0;
  while (!v.empty()) {
    int min_price = remove_and_return_min_price();
    LOG(ERROR) << "day " << day << " price " << min_price;
    max_spend += day * min_price;
    LOG(ERROR) << "max spend: " << max_spend;
    ++day;
  }
  return max_spend;
}
