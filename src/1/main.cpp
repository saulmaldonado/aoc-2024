#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Missing input file argument" << '\n';
    return 1;
  }

  char *input_file = argv[1];

  std::ifstream input(input_file);

  if (!input.is_open()) {
    std::cerr << "Failed to open input file" << '\n';
    return 1;
  }

  std::string line;

  int distance = 0;

  std::vector<int> list1;
  std::vector<int> list2;

  std::unordered_map<int, int> map;

  while (std::getline(input, line)) {
    std::stringstream ss(line);

    std::string value1, value2;
    int id1, id2;

    ss >> value1 >> value2;

    id1 = std::stoi(value1);
    id2 = std::stoi(value2);

    list1.push_back(id1);
    list2.push_back(id2);

    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());
  }

  int n = list1.size();

  for (int i = 0; i < n; i++) {
    std::cout << "ID 1: " << list1[i] << " ID 2: " << list2[i] << '\n';
    map[list2[i]]++;
    distance += abs(list1[i] - list2[i]);
  }

  int score = 0;

  for (int i = 0; i < n; i++) {
    score += (list1[i] * map[list1[i]]);
  }

  input.close();

  std::cout << "Distance: " << distance << '\n';
  std::cout << "Score: " << score << '\n';

  return 0;
}