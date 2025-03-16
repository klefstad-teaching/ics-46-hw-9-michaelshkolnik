#include "ladder.h"
#include <queue>
#include <set>

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
                                    const set<string> &word_list) {
  if (begin_word == end_word)
    return {begin_word};

  queue<vector<string>> ladders;
  set<string> visited;
  ladders.push({begin_word});
  visited.insert(begin_word);

  while (!ladders.empty()) {
    int size = ladders.size();
    set<string> level_visited;

    for (int i = 0; i < size; i++) {
      auto l = ladders.front();
      ladders.pop();
      string last = l.back();

      for (const string &word : word_list) {
        if (!visited.count(word) && is_adjacent(last, word)) {
          vector<string> l2 = l;
          l2.push_back(word);

          if (word == end_word)
            return l2;

          ladders.push(l2);
          level_visited.insert(word);
        }
      }
    }

    for (const string &w : level_visited) {
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
        if (i < ladder.size() - 1) cout << " ";
    }
    cout << "\n";  
}


void verify_word_ladder() {
  // TODO
}