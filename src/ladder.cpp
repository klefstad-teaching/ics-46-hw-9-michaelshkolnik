#include "ladder.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

void error(string word1, string word2, string msg) {
  cout << word1 << " " << word2 << " " << msg;
}

bool edit_distance_within(const string &str1, const string &str2, int d) {
  int len1 = str1.size();
  int len2 = str2.size();

  if (abs(len1 - len2) > d) {
    return false;
  }

  int diff = 0, index1 = 0, index2 = 0;

  while (index1 < len1 && index2 < len2) {
    if (str1[index1] != str2[index2]) {
      if (diff++ > d)
        return false;
      if (len1 > len2)
        index1++;
      else if (len2 > len1)
        index2++;
      else {
        index1++;
        index2++;
      }
    } else {
      index1++;
      index2++;
    }
  }
  return true;
}

bool is_adjacent(const string &word1, const string &word2) {
  return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string &begin_word,
                                    const string &end_word,
                                    const set<string> &word_list) {
  if (begin_word == end_word) {
    return {begin_word};
  }

  queue<vector<string>> ladder_queue;
  set<string> visited;

  ladder_queue.push({begin_word});
  visited.insert(begin_word);

  while (!ladder_queue.empty()) {
    int size = ladder_queue.size();
    set<string> level_visited;

    for (int i = 0; i < size; i++) {
      vector<string> current_ladder = ladder_queue.front();
      ladder_queue.pop();
      string last_word = current_ladder.back();

      for (const string &word : word_list) {
        if (!visited.count(word) && is_adjacent(last_word, word)) {
          vector<string> new_ladder = current_ladder;
          new_ladder.push_back(word);

          if (word == end_word) {
            return new_ladder;
          }

          ladder_queue.push(new_ladder);
          level_visited.insert(word);
        }
      }
    }

    visited.insert(level_visited.begin(), level_visited.end());
  }

  return {};
}

void load_words(set<string> &word_list, const string &file_name) {
  ifstream file(file_name);
  string word;
  while (file >> word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    word_list.insert(word);
  }
}

void print_word_ladder(const vector<string> &ladder) {
  if (ladder.empty()) {
    cout << "No word ladder found.\n";
    return;
  }

  cout << "Word ladder found: ";
  for (size_t i = 0; i < ladder.size(); i++) {
    cout << ladder[i];
    if (i < ladder.size() - 1)
      cout << " ";
  }
  cout << " \n";
}

void verify_word_ladder(const vector<string> &ladder, const string &begin_word,
                        const string &end_word, const set<string> &word_list) {
  if (ladder.empty()) {
    error(begin_word, end_word, "Empty ladder");
    return;
  }

  if (ladder.front() != begin_word || ladder.back() != end_word) {
    error(begin_word, end_word, "Incorrect start or end word");
    return;
  }

  for (size_t i = 1; i < ladder.size(); i++) {
    if (!word_list.count(ladder[i]) && ladder[i] != end_word) {
      error(ladder[i - 1], ladder[i], "Word not in dictionary");
      return;
    }
    if (!is_adjacent(ladder[i - 1], ladder[i])) {
      error(ladder[i - 1], ladder[i], "Words are not adjacent");
      return;
    }
  }
}
