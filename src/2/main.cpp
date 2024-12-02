#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool check(const std::vector<int>& values);

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Missing input argument" << '\n';
    return 1;
  }

  char* inputFile = argv[1];

  std::ifstream input(inputFile);

  if (!input.is_open()) {
    std::cerr << "Error opening file" << '\n';
    return 1;
  }

  std::string line;

  std::vector<int> report;

  int ans = 0;

  while (std::getline(input, line)) {
    std::stringstream ss(line);

    std::string val;

    while (ss >> val) {
      report.push_back(std::stoi(val));
    }

    if (report.size() < 2) {
      report.clear();
      continue;
    }

    // ans += check(report);

    int n = report.size();

    if (check(report)) {
      ans++;
    } else {
      for (int i = 0; i < n; i++) {
        std::vector<int> newReport;
        for (int j = 0; j < n; j++) {
          if (i == j) {
            continue;
          }
          newReport.push_back(report[j]);
        }
        if (check(newReport)) {
          ans++;
          break;
        }
      }
    }

    report.clear();
  }

  input.close();

  std::cout << "Number of safe reports: " << ans << '\n';

  return 0;
}

bool check(const std::vector<int>& values) {
  int n = values.size();

  int dir = 0;

  for (int i = 1; i < n; i++) {
    if (abs(values[i] - values[i - 1]) > 3) {
      return false;
    }

    if (values[i] <= values[i - 1]) {
      dir--;
    }

    if (values[i] >= values[i - 1]) {
      dir++;
    }

    if (abs(dir) != i) {
      return false;
    }
  }

  return true;
}
