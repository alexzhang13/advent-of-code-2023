#include <fstream>
#include <iostream>

using namespace std;

int main() {
  ifstream file("p1.txt");
  int total = 0;

  string val;
  int ones = 0;
  int tens = 0;

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      ones = 0;
      tens = 0;
      for (int i = 0; i < line.size(); i++) {
        if (isdigit(line[i])) {
          val = line[i];
          ones = atoi(val.c_str());
          break;
        }
      }
      for (int i = line.size() - 1; i >= 0; i--) {
        if (isdigit(line[i])) {
          val = line[i];
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
