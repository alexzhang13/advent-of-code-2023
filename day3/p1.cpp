#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void parse_symbols(vector<int> &mark_tokens, string &line, int n, int round) {
  for (int i = 0; i < n; i++) {
    if (!isdigit(line[i]) && line[i] != '.') {
      mark_tokens[i] = round;
    }
  }
}
void parse_nums(vector<int> &mark_unused, string &line, int n) {
  bool prev = false;
  for (int i = 0; i < n; i++) {
    if (!isdigit(line[i]) && line[i] != '.') {
      prev = false;
    } else if (line[i] != '.') {
      if (prev) {
        mark_unused[i] = mark_unused[i - 1] * 10 + line[i] - '0';
      } else {
        mark_unused[i] = line[i] - '0';
        prev = true;
      }
    } else {
      prev = false;
    }
  }
}

int extract(vector<int> &mark_unused, vector<int> &mark_tokens, int i, int n) {
  int amt = mark_unused[i] / 10;
  int digits = 0;
  int total = 0;

  // clear earlier stuff
  while (amt > 0) {
    digits++;
    amt /= 10;
    mark_unused[i - digits] = 0;
  }

  // clear later
  int j = i;
  while (mark_unused[j] > 0 && j < n) {
    total = mark_unused[j];
    mark_unused[j] = 0;
    j++;
  }

  cout << i << " " << total << endl;
  return total;
}

int solve(vector<int> &mark_unused, vector<int> &mark_tokens, int n,
          int round) {
  int total = 0;
  for (int i = 0; i < n; i++) {
    if (mark_tokens[i] == round || mark_tokens[i] == (round - 1)) {
      if (i > 0 && mark_unused[i - 1] != 0) {
        total += extract(mark_unused, mark_tokens, i - 1, n);
      }
      if (mark_unused[i] != 0) {
        total += extract(mark_unused, mark_tokens, i, n);
      }
      if (i < n - 1 && mark_unused[i + 1] != 0) {
        total += extract(mark_unused, mark_tokens, i + 1, n);
      }
    }
  }
  return total;
}

void clear(vector<int> &mark) {
  for (size_t i = 0; i < mark.size(); i++)
    mark[i] = 0;
}

int main(int argc, char *argv[]) {

  ifstream file("p1.txt");

  if (file.is_open()) {
    std::string line;

    if (file.good()) {
      getline(file, line); // first line
      file.clear();
      file.seekg(0);
    }

    int n = line.size();
    cout << "line size: " << n << endl;

    vector<int> mark_tokens(n); // unused special token
    vector<int> mark_unused(n); // unused numbers from previous line

    int round = 2;
    int total = 0;
    while (getline(file, line)) {
      cout << line << endl;
      parse_symbols(mark_tokens, line, n, round);
      total += solve(mark_unused, mark_tokens, n, round);
      clear(mark_unused);

      parse_nums(mark_unused, line, n);
      total += solve(mark_unused, mark_tokens, n, round);

      cout << "round " << round << ". leftover unused: ";
      for (int i = 0; i < n; i++)
        cout << mark_unused[i] << " ";
      cout << ". current total: " << total;
      cout << endl;
      round++;
    }
    cout << "total: " << total << endl;
    file.close();
  }
  return 0;
}
