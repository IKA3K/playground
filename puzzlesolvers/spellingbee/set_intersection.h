#ifndef PUZZLESOLVERS_SPELLINGBEE_SET_INTERSECTION_H
#define PUZZLESOLVERS_SPELLINGBEE_SET_INTERSECTION_H

#include <cstddef>
#include <iterator>
#include <set>

#include "absl/log/log.h"

namespace puzzlesolvers {

// Generates the set intersection of multiple sets pointed to in `sets`.
template<class T>
std::set<T> Intersection(std::vector<const std::set<T>*> sets) {
  std::set<T> output;
  std::vector<typename std::set<T>::const_iterator> iterators;
  iterators.reserve(sets.size()); 
  // Prepare iterators.
  for (const std::set<T>* set : sets) {
    if (set == nullptr) {
      LOG(FATAL) << "set pointing at null";
    }
    iterators.push_back(set->begin());
  }
  if (iterators.size() != sets.size()) {
    LOG(FATAL) << "Couldn't correctly create iterator vec";
  }

  // Walk through all sets.
  auto no_more_data = [&iterators, &sets] () {
    for (int i = 0; i < sets.size(); ++i) {
      if (iterators[i] != sets[i]->end()) {
        LOG(INFO) << i << ": not at end";
        return false;
      }
    }
    LOG(INFO) << "At end";
    return true;
  };

  int step_count = 0;
  while (!no_more_data()) {
    if (step_count > 100000) {
      LOG(FATAL) << "Failed to finish within 100000 steps";
    }
    LOG(INFO) << "starting loop";
    for (int i = 0; i < sets.size(); ++i) {
      int lowest_value_iter_index = 0;
      auto lowest_value_iter = iterators[lowest_value_iter_index];
      if (lowest_value_iter == sets[i]->end()) {
        // Choose new lowest.
        ++step_count;
        continue;
      }
      // Advance the lowest iterator in each set.
      bool is_same_value = true;
      for (int j = 1; j < sets.size(); ++j) {
        ++step_count;
        auto next_iter = iterators[j];
        if (next_iter == sets[j]->end()) {
          continue;
        }
        if (*next_iter != *lowest_value_iter) {
          is_same_value = false;
        }
        if (*next_iter < *lowest_value_iter) {
          lowest_value_iter = next_iter;
          lowest_value_iter_index = j;
        }
      }  // j
      if (is_same_value) {
        output.insert(*lowest_value_iter);
        LOG(INFO) << "Inserting found word " << *lowest_value_iter;
        // Advance all iterators again.
        for (int k = 0; k < sets.size(); ++k) {
          ++step_count;
          if (iterators[k] != sets[k]->end()) {
            ++iterators[k];
            if (iterators[k] != sets[k]->end()) {
              LOG(INFO) << k << ": pointing at word " << *iterators[k];
            } else {
              LOG(INFO) << k << ": at end";
            }
          }
        }
        // Restart the loop from the first set.
        break;
      }
      // If they're not the same value, step forward the most behind iterator.
      if (lowest_value_iter != sets[lowest_value_iter_index]->end()) {
        ++iterators[lowest_value_iter_index];
        LOG(INFO) << "no match";
      } else {
        LOG(INFO) << "at end";
        break;
      }
    }  // i
  }  // !no_more_data
  if (output.size()) {
    LOG(INFO) << "Finished computing intersection w/"
              << output.size() << " results in " << step_count << " steps";
  } else {
    LOG(INFO) << "no matches in " << step_count << " steps";
  }
  return output;
}

}  // namespace puzzlesolvers

#endif  // PUZZLESOLVERS_SPELLINGBEE_SET_INTERSECTION_H