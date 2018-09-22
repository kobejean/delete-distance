#include <iostream>
#include <string>
#include <unordered_map>
#include <iterator>
#include <list>
#include <vector>
#include <string>
#include <utility>


using namespace std;

void initCharIdxMap(const string& str, unordered_map<char, list<size_t>>& map) {
  map = {};
  for(size_t i = 0; i < str.size(); ++i) {
    char c = str[i];
    auto it = map.find(c);
    if (it != map.end()) {
      auto indices = it->second;
      indices.push_back(i);
    } else {
      list<size_t> indices = {i};
      map[c] = indices;
    }
  }
}

size_t findPos(char c, const unordered_map<char, list<size_t>>& map, size_t pos) {
  auto it = map.find(c);
  if (it != map.end()) {
    auto indices = it->second;
    size_t i = 0;
    while (!indices.empty() && i <= pos) {
      i = indices.front();
      if (i >= pos) {
        return i;
      } else {
        indices.pop_front();
      }
    }
  }
  return string::npos;
}

size_t searchDepth(pair<size_t, size_t> coords,
                const string& str1, const string& str2,
                const unordered_map<char, list<size_t>>& char_idx_map1,
                const unordered_map<char, list<size_t>>& char_idx_map2) {
  size_t i1 = coords.first+1, i2 = coords.second+1;
  size_t min_size = min(str1.size()-i1, str2.size()-i2);
  for (size_t i = 0; i < min_size; ++i) {
    char c1 = str1[i1+i], c2 = str2[i2+i];
    size_t char_pos1 = findPos(c2, char_idx_map1, i1+i);
    size_t char_pos2 = findPos(c1, char_idx_map2, i2+i);
    size_t relative_depth = string::npos;
    if (char_pos1 < relative_depth) {
      relative_depth = char_pos1 - i1;
    }
    if (char_pos2 < relative_depth) {
      relative_depth = char_pos2 - i2;
    }
    if (relative_depth != string::npos) {
      return relative_depth;
    }
  }
  return string::npos;
}


vector<pair<size_t, size_t>> adjacentNodes(pair<size_t, size_t> coords,
                const string& str1, const string& str2,
                const unordered_map<char, list<size_t>>& char_idx_map1,
                const unordered_map<char, list<size_t>>& char_idx_map2) {
  vector<pair<size_t, size_t>> adjacent_nodes {};
  size_t i1 = coords.first, i2 = coords.second;

  size_t search_depth = searchDepth(coord, str1, str2, char_idx_map1, char_idx_map2);
  for (size_t i = 0; i < search_depth; ++i) {

  }
  pair<size_t, size_t> endCoord = make_pair(str1.size()-1, str2.size()-1);
  adjacent_nodes.push_back(endCoord);
  return adjacent_nodes;
}


int deletionDistance(const string& str1, const string& str2) {
  unordered_map<char, list<size_t>> char_idx_map1, char_idx_map2;
  initCharIdxMap(str1, char_idx_map1);
  initCharIdxMap(str2, char_idx_map2);

  int del_dist = 0;
  size_t min_size = min(str1.size(), str2.size());
  size_t pos1 = 0, pos2 = 0;

  for (size_t i = 0; i < min_size; ++i) {
    pair<size_t, size_t> coord = make_pair(pos1,pos2);
    auto adjNodes = adjacentNodes(coord, str1, str2, char_idx_map1, char_idx_map2);
    char c1 = str1[i], c2 = str2[i];
    size_t char_pos1 = findPos(c2, char_idx_map1, pos1);
    size_t char_pos2 = findPos(c1, char_idx_map2, pos2);
    if (char_pos1 != string::npos) {
      pos1 = char_pos1;
    }
    if (char_pos2 != string::npos) {
      pos2 = char_pos2;
    }

    cout << c2 << char_pos1 << '\n';
    cout << c1 << char_pos2 << '\n';
  }
  return del_dist;
}

int main() {
  cout << deletionDistance("hitt","heat") << '\n';
  return 0;
}
