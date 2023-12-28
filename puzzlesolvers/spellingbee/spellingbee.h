#ifndef PUZZLESOLVERS_SPELLINGBEE_SPELLINGBEE_H
#define PUZZLESOLVERS_SPELLINGBEE_SPELLINGBEE_H

#include "puzzlesolvers/spellingbee/dictionary.h"

#include <set>
#include <string>
#include <vector>

namespace puzzlesolvers {

class SpellingBee {
 public:
  explicit SpellingBee(const Dictionary& dictionary) : dictionary_(dictionary) {}
  ~SpellingBee() = default;
  SpellingBee(const SpellingBee&) = delete;

  // Returns words that match the characters provided.
  std::vector<std::string> FindWords(std::set<char> characters);

 private:
  const Dictionary& dictionary_;  // Not owned.
};

}  // namespace puzzlesolvers

#endif  // PUZZLESOLVERS_SPELLINGBEE_SPELLINGBEE_H