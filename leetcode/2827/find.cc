#include "find.h"

#include "absl/log/check.h"
#include "absl/log/log.h"

int num_beautiful_integers(int low, int high, int k) {
  CHECK(k > 0 && k <= 20);
  CHECK(low > 0 && high <= 1e9 && high >= low);

  LOG(ERROR) << "low: " << low << " high: " << high << " k: " << k;

  int count = 0;
  if (low % k) {
    low += k - (low % k);
  }

  auto digit_distribution = [](int i) -> std::pair<int, int> {
    int odd = 0, even = 0;
    do {
      int last_digit = i % 10;
      if (last_digit % 2) {
        ++odd;
      } else {
        ++even;
      }
      i /= 10;
    } while (i >= 1);
    return std::make_pair(odd, even);
  };
  while (low <= high) {
    // The count of even digits in the number is equal to the count of odd
    // digits.
    auto [odd_count, even_count] = digit_distribution(low);
    //LOG(ERROR) << "odd: " << odd_count << " even: " << even_count << " i: " << low;
    if (odd_count == even_count) {
      LOG(ERROR) << low << " is a 'beautiful' integer";
      ++count;
    }
    low += k;
  }
  
  return count;
}