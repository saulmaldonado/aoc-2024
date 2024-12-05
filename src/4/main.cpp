#include <fstream>
#include <iostream>
#include <vector>

int find(const std::vector<std::string>& grid, std::string pattern, int i,
         int j, int di, int dj);

int search(const std::vector<std::string>& grid, int i, int j);

int findxmas(const std::vector<std::string>& grid, int i, int j);

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Missing input file" << '\n';
    return 1;
  }

  char* inputFile = argv[1];

  std::ifstream input(inputFile);

  std::string line;

  std::vector<std::string> grid;

  while (std::getline(input, line)) {
    grid.push_back(line);
  }

  int n = grid.size();
  int m = grid[0].size();

  int res = 0;

  for (int i = 1; i < n - 1; i++) {
    for (int j = 1; j < m - 1; j++) {
      // PART1

      // res += (search(grid, i, j));

      // PART 2

      if (grid[i][j] == 'A') {
        res += findxmas(grid, i, j);
      }
    }
  }

  std::cout << res << '\n';

  return 0;
}

const std::pair<int, int> directions[] = {
    {-1, -1},  // up left
    {-1, 0},   // up
    {-1, 1},   // up right
    {0, -1},   // left
    {0, 1},    // right
    {1, -1},   // down left
    {1, 0},    // down
    {1, 1}     // down right
};

const std::string pattern = "XMAS";

int search(const std::vector<std::string>& grid, int i, int j) {
  int res = 0;

  for (const auto& [di, dj] : directions) {
    res += (find(grid, pattern, i, j, di, dj));
  }

  return res;
}

int find(const std::vector<std::string>& grid, std::string pattern, int i,
         int j, int di, int dj) {
  int n = grid.size();
  int m = grid[0].size();
  int p = pattern.size();

  for (int k = 0; k < p; k++) {
    if (i >= 0 && i < n && j >= 0 && j < m && grid[i][j] == pattern[k]) {
      i += di;
      j += dj;
    } else {
      return false;
    }
  }

  return true;
}

const std::vector<std::vector<std::pair<int, int>>> dirs = {
    {
        {-1, -1},  // up left
        {-1, 1},   // up right
        {1, -1},   // down left
        {1, 1},    // down right

    },
    {
        {-1, -1},  // up left
        {1, -1},   // down left
        {-1, 1},   // up right
        {1, 1},    // down right

    },
    {
        {1, -1},   // down left
        {1, 1},    // down right
        {-1, -1},  // up left
        {-1, 1},   // up right
    },
    {
        {-1, 1},   // up right
        {1, 1},    // down right
        {-1, -1},  // up left
        {1, -1},   // down left
    }};

int findxmas(const std::vector<std::string>& grid, int i, int j) {
  for (int k = 0; k < 4; k++) {
    const std::vector<std::pair<int, int>> dir = dirs[k];

    if (grid[i + dir[0].first][j + dir[0].second] == 'M' &&
        grid[i + dir[1].first][j + dir[1].second] == 'M' &&
        grid[i + dir[2].first][j + dir[2].second] == 'S' &&
        grid[i + dir[3].first][j + dir[3].second] == 'S') {
      return true;
    }
  }

  return false;
}