// #include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

void convert(string &str, map<string, string> &dc, bool forward) {
  int index = 0;
  map<string, string>::iterator it = dc.begin();

  if (forward) {
    for (index = 0; index != (int)str.size(); index++) {
      it = dc.begin();

      while (it != dc.end()) {
        int len = it->first.size();
        if (len + index > (int)str.size()) { // 4 + 0 satisfies 4-length
          ++it;
          continue;
        }
        if (str.substr(index, len).compare(it->first) == 0) {
          str.replace(index, len, it->second);
          return;
        }
        ++it;
      }
    }
  } else {
    for (index = str.size() - 1; index >= 0; index--) {
      it = dc.begin();

      while (it != dc.end()) {
        int len = it->first.size();
        if (len + index > (int)str.size()) { // 4 + 0 satisfies 4-length
          ++it;
          continue;
        }
        if (str.substr(index, len).compare(it->first) == 0) {
          str.replace(index, len, it->second);
          return;
        }
        ++it;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  ifstream file("p1.txt");
  int total = 0;

  string val;
  int ones = 0;
  int tens = 0;
  std::map<string, string> dc;
  dc["one"] = "1";
  dc["two"] = "2";
  dc["three"] = "3";
  dc["four"] = "4";
  dc["five"] = "5";
  dc["six"] = "6";
  dc["seven"] = "7";
  dc["eight"] = "8";
  dc["nine"] = "9";
  dc["zero"] = "0";

  if (file.is_open()) {
    std::string line;
    std::string line_f;
    std::string line_b;
    while (std::getline(file, line)) {
      ones = 0;
      tens = 0;
      line_f = line;
      line_b = line;
      cout << "original: " << line_f << endl;
      convert(line_f, dc, true);
      cout << line_f << endl;
      convert(line_b, dc, false);
      cout << line_b << endl;

      for (int i = 0; i < line_f.size(); i++) {
        if (isdigit(line_f[i])) {
          val = line_f[i];
          ones = atoi(val.c_str());
          break;
        }
      }
      for (int i = line_b.size() - 1; i >= 0; i--) {
        if (isdigit(line_b[i])) {
          val = line_b[i];
          tens = atoi(val.c_str());
          break;
        }
      }
      cout << 10 * ones + tens << endl;
      total += tens + 10 * ones;
    }
    file.close();
  }

  cout << "total: " << total << endl;
  return 0;
}
