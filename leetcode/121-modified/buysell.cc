#include "buysell.h"

#include <memory>
#include <utility>
#include <set>
#include <vector>

#include "absl/log/log.h"

/**
  Problem Statement

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
 */

/**
 Thinking out aloud:

  0. Use a std::unique_ptr<std::pair<int, int> > (buy sell) time.

  1. On the first index (or after any drop in price after a potential sale), create a new pair with the current index as a buy.
  2. If on successive days, the price drops, update back().first to the new index.
  3. If it goes up, immediately sell, updating back().second.
  4. If the price goes down the next day, reset the ptr and return to step 1. Otherwise keep looking for increasing prices
     and update back().second.
  5. Store each transaction in a std::set which is sorted based on the PNL.
*/

struct Compare {
  explicit Compare(const std::vector<int>& p) : prices(p) {}
  bool operator()(const std::pair<int, int>& left, const std::pair<int, int>& right) {
    int pnl_left = prices[left.second] - prices[left.first];
    int pnl_right = prices[right.second] - prices[right.first];
    return pnl_left > pnl_right;  // Move more profitable trades to the front.
  }
  const std::vector<int>& prices;  // Not owned.
};

int max_profit(const std::vector<int>& prices, int max_transacations) {
  if (prices.size() < 2) {
    return 0;  // No day to sell!
  }

  // Create a std::set where operator< is overridden to compute PNL.
  std::multiset<std::pair<int, int>, Compare> trades((Compare(prices)));

  std::unique_ptr<std::pair<int, int> > buy_sell_accounting =
      std::make_unique<std::pair<int, int> >(0, -1);
  LOG(INFO) << "Initial buy day 0 @ " << prices[0];

  for (int i = 1; i < prices.size(); ++i) {
    int this_price = prices[i];
    int buy_price = prices[buy_sell_accounting->first];
    int sell_index = buy_sell_accounting->second;
    int sell_price = sell_index == -1 ? buy_price : prices[buy_sell_accounting->second];
    if (this_price > sell_price) {
      // Update new sale price.
      LOG(INFO) << "Pushing sell to day " << i << " @ " << this_price;
      buy_sell_accounting->second = i;
      continue;
    }

    if (sell_index == -1) {
      // Sneakily update the buy price to this day, because we shouldn't have bought
      // the other day.
      buy_sell_accounting->first = i;
      LOG(INFO) << "Updating buy to day " << i << " @ " << this_price;
      continue;
    }

    // Price has dropped, sell everything at last known good price and move on.
    LOG(INFO) << "Price dropped, selling on day " << buy_sell_accounting->second << " @ " << sell_price;
    LOG(INFO) << "Theoretical P&L: " << sell_price - buy_price;
    trades.insert(*buy_sell_accounting);

    buy_sell_accounting = std::make_unique<std::pair<int, int> >(i, -1);
    LOG(INFO) << "Initiate buy day " << i << " @ " << this_price;
  }

  // TODO: need to replace trades with an optimizer in case
  // trades.size() exceeds max_transactions. So we'd have to basically go
  // through and see if we could combine trades e.g.:
  // [1, 5, 3, 6, 2, 8] with max transactions 2 should result in the
  // transactions [0, 3] and [4, 5]. If max transactions 1, should
  // then be dropped even further.
  //
  // There might be some other method where we drop the # of transactions
  // to the limit, and check to see if those ranges can be combined with
  // close by transactions to increase PnL.

  // Compute PNL.
  int pnl = 0;
  int transactions = 0;
  for (auto iter = trades.begin();
       iter != trades.end() && transactions < max_transacations;
       ++transactions, ++iter) {
    int buy = iter->first;
    int sell = iter->second;
    int buy_price = prices[buy];
    int sell_price = prices[sell];
    int profit = sell_price - buy_price;
    LOG(INFO) << "Taking trade buy on day " << buy << " @ " << buy_price
              << ", sell on day " << sell << " @ " << sell_price
              << " for profit " << profit;
    pnl += profit;
  }
  LOG(INFO) << "P&L = " << pnl << " in " << transactions << " transactions";
  return pnl;
}