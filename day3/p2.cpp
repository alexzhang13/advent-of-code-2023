#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

pair<int, int> parent[141 * 141];

void make_set(int k, int v) {
  parent[k].first = k;
  parent[k].second = v;
}

int find_set(int v) {
  if (v == parent[v].first) {
    return v;
  }
  return find_set(parent[v].first);
}

// rule: parent[a] is set to b
void union_sets(int a, int b) {
  a = find_set(a);
  b = find_set(b);
  if (a != b) {
    parent[a].first = b;
  }
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

    vector<int> gears;

    int round = 0;
    int total = 0;
    int accum = 0;
    int idx = 0;
    bool prev = false;
    while (getline(file, line)) {
      round++;
      prev = false;
      for (int i = 0; i < n; i++) {
        idx = round * n + i;
        if (line[i] == '*') {
          gears.push_back(idx);
          prev = false;
        } else if (isdigit(line[i])) {
          if (prev) {
            accum = accum * 10 + line[i] - '0';
            make_set(idx, accum);
            union_sets(idx - 1, idx);
          } else {
            accum = line[i] - '0';
            make_set(idx, accum);
            prev = true;
          }
          prev = true;
        } else {
          prev = false;
        }
      }
    }

    int tmp;
    for (auto gear : gears) {
      cout << "idx: (" << gear / n << "," << gear % n << ")" << endl;
      std::map<int, int> ratios;
      int par = 0;
      bool upper = (gear >= 2 * n);
      bool left = (gear % n > 0);
      bool right = (gear % n != (n));
      bool lower = (gear < n * (n));

      cout << upper << " " << lower << " " << right << " " << left << " "
           << endl;

      if (upper) {
        par = find_set(gear - n);
        ratios[par] = parent[par].second;
      }
      if (left) {
        par = find_set(gear - 1);
        ratios[par] = parent[par].second;
      }
      if (right) {
        par = find_set(gear + 1);
        ratios[par] = parent[par].second;
      }
      if (lower) {
        par = find_set(gear + n);
        ratios[par] = parent[par].second;
      }
      if (upper && left) {
        par = find_set(gear - n - 1);
        ratios[par] = parent[par].second;
      }
      if (lower && left) {
        par = find_set(gear + n - 1);
        ratios[par] = parent[par].second;
      }
      if (upper && right) {
        par = find_set(gear - n + 1);
        ratios[par] = parent[par].second;
      }
      if (lower && right) {
        par = find_set(gear + n + 1);
        ratios[par] = parent[par].second;
      }

      ratios.erase(0);
      cout << "gear size: " << ratios.size() << endl;

      tmp = 1;
      for (auto r : ratios) {
        cout << "(" << r.first / n << "," << r.first % n << ")"
             << " " << r.second << endl;
        if (ratios.size() == 2) {
          tmp *= r.second;
        }
      }
      if (tmp > 1)
        total += tmp;
    }

    // for (int i = 1; i <= n; i++) {
    //   for (int j = 0; j < n; j++) {
    //     idx = i * n + j;
    //     if (parent[idx].first != 0) {
    //       cout << parent[find_set(idx)].second << " ";
    //     } else if (std::find(gears.begin(), gears.end(), idx) != gears.end())
    //     {
    //       cout << "* ";
    //     } else {
    //       cout << ". ";
    //     }
    //   }
    //   cout << endl;
    // }
    cout << "total: " << total << endl;
    file.close();
  }
  return 0;
}
