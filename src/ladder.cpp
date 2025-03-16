#include "ladder.h"
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>

void error(string word1, string word2, string msg) {
  cout << word1 << " " << word2 << " " << msg;
}

bool edit_distance_within(const std::string &str1, const std::string &str2,
                          int d) {
  int len1 = str1.size();
  int len2 = str2.size();
  if (abs(len1 - len2) > d) {
    return false;
  }

  int diff = 0;
  int index1 = 0;
  int index2 = 0;
  while (index1 < len1 && index2 < len2) {
    if (str1[index1] != str2[index2]) {

      if (diff++ > d) {
        return false;
      }

      if (len1 > len2) {
        index1++;
      } else if (len2 > len1) {
        index2++;
      } else {
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
                                    const unordered_set<string> &word_list) {
  if (begin_word == end_word) {
    return {begin_word};
  }

  queue<string> q;
  unordered_map<string, string> parent;
  unordered_set<string> visited;

  q.push(begin_word);
  visited.insert(begin_word);

  while (!q.empty()) {
    int size = q.size();
    unordered_set<string> level_visited;

    for (int i = 0; i < size; i++) {
      string current = q.front();
      q.pop();

      string temp = current;
      for (size_t j = 0; j < temp.size(); j++) {
        char original = temp[j];
        for (char c = 'a'; c <= 'z'; c++) {
          if (c == original) {
            continue;
          }
          temp[j] = c;

          if (temp == end_word) {
            vector<string> path = {end_word};
            while (current != begin_word) {
              path.push_back(current);
              current = parent[current];
            }
            path.push_back(begin_word);
            reverse(path.begin(), path.end());
            return path;
          }

          if (word_list.count(temp) && !visited.count(temp)) {
            q.push(temp);
            level_visited.insert(temp);
            parent[temp] = current;
          }
        }
        temp[j] = original;
      }
    }

    for (const auto &w : level_visited) {
      visited.insert(w);
    }
  }

  return {};
}

void load_words(set<string> &word_list, const string &file_name) {
  ifstream file(file_name);
  string word;
  while (file >> word) {
    word_list.insert(word);
  }
}

void print_word_ladder(const vector<string> &ladder) {
  for (size_t i = 0; i < ladder.size(); i++) {
    cout << ladder[i];
    if (i < ladder.size() - 1)
      cout << " ";
  }
  cout << "\n";
}

void verify_word_ladder(const vector<string> &ladder, const string &begin_word,
                        const string &end_word,
                        const unordered_set<string> &word_list) {
  if (ladder.empty()) {
    error(begin_word, end_word, "Empty");
    return;
  }

  for (size_t i = 1; i < ladder.size(); i++) {

    if (!word_list.count(ladder[i])) {
      error(begin_word, end_word, "Wrong word in ladder");
      return;
    }

    int diff = 0;

    for (size_t j = 0; j < ladder[i].size(); j++) {
      if (ladder[i - 1][j] != ladder[i][j])
        diff++;
    }

    if (diff != 1) {
      error(begin_word, end_word, "Words not adjacent");
      return;
    }
    
  }
}
