#include <fstream>
#include <iostream>
#include <sstream>

int parse(const std::string& str);

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Missing input argument" << '\n';
    return 1;
  }

  char* filename = argv[1];

  std::ifstream input(filename);

  if (!input.is_open()) {
    std::cerr << "Error opening file" << '\n';
    return 1;
  }

  std::ostringstream buf;
  buf << input.rdbuf();

  std::string str = buf.str();

  int total = parse(str);

  std::cout << "Total: " << total << '\n';
}

enum State {
  Do,
  Dont,
};

int parse(const std::string& str) {
  State state = State::Do;

  const std::string pattern = "mul(";

  const std::string doPattern = "do()";

  const std::string dontPattern = "don't()";

  int n = str.size();

  int i = 0;

  long long res = 0;
  while (i < n) {
    if (str.substr(i, 4) == pattern) {
      i += 4;

      int val1 = 0;

      while (i < n && isdigit(str[i]) && val1 < 1000) {
        val1 *= 10;
        val1 += (str[i] - '0');
        i++;
      }

      if (val1 >= 1000 || i >= n || str[i] != ',') {
        continue;
      }

      i++;

      int val2 = 0;

      while (i < n && isdigit(str[i]) && val2 < 1000) {
        val2 *= 10;
        val2 += (str[i] - '0');
        i++;
      }

      if (val2 >= 1000 || i >= n || str[i] != ')') {
        continue;
      }

      i++;

      if (state == State::Do) {
        res += (val1 * val2);
      }

    } else if (str.substr(i, 4) == doPattern) {
      state = State::Do;
      i += 4;
    } else if (str.substr(i, 7) == dontPattern) {
      state = State::Dont;
      i += 7;
    } else {
      i++;
    }
  }
  return res;
}
