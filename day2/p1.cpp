#include <fstream>
#include <iostream>
#include <map>

using namespace std;

map<string, int> colors;
const int max_red = 12;
const int max_green = 13;
const int max_blue = 14;

int main(int argc, char *argv[]) {
  ifstream file("p1.txt");

  int total = 0;

  if (file.is_open()) {
    std::string line;
    std::string in_line;
    std::string set_delim = ";";
    std::string in_delim = ",";
    std::string tmp;
    int valid = 1;
    while (std::getline(file, line)) {
      // cout << line << endl;

      std::string tmp_line = line + ";";
      size_t in_pos = 0;
      size_t pos = 0;
      valid = 1;

      pos = tmp_line.find(":");
      valid = atoi(tmp_line.substr(5, pos - 5).c_str());
      tmp_line.erase(0, pos + 1); // remove :
      while ((pos = tmp_line.find(set_delim)) != string::npos) {
        // cout << tmp_line.substr(0, pos) << endl;

        in_line = tmp_line.substr(0, pos) + ",";
        while ((in_pos = in_line.find(in_delim)) != string::npos) {
          tmp = in_line.substr(0, in_pos);
          // cout << tmp << endl;
          int amt = atoi(tmp.c_str());

          if (tmp.find("green") != string::npos) {
            if (amt > max_green)
              valid = 0;
          } else if (tmp.find("blue") != string::npos) {
            if (amt > max_blue)
              valid = 0;
          } else {
            if (amt > max_red)
              valid = 0;
          }

          in_line.erase(0, in_pos + in_delim.length());
        }
        if (valid == 0) {
          cout << "invalid! " << line << endl;
          break;
        }
        tmp_line.erase(0, pos + set_delim.length());
      }
      total += valid;
    }
    file.close();
    cout << "total: " << total << endl;
  }
  return 0;
}
