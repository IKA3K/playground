#ifndef BUYSELL_H_
#define BUYSELL_H_

#include <vector>

// 121: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
// Note that their problem statement sucks and doesn't actually maximize profit.
int max_profit(const std::vector<int>& prices, int max_transactions);

#endif  // BUYSELL_H_