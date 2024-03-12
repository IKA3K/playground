#include "reverse.h"

enum {
  UNKNOWN = -2,
  BANNED = -1,
  NO_CHANGE = 0
};

std::vector<int> min_reverse_operations(int n, int p, std::vector<int> banned, int k) {
  std::vector<int> out(n, UNKNOWN);
  out[p] = NO_CHANGE;
  for (const int banned_index : banned) {
    out[banned_index] = BANNED;  // Not possible to have integer here.
  }
  for (int i = 0; i < n; ++i) {
    if (out[i] != UNKNOWN) {
      continue;
    }

    
  }
  return out;
}