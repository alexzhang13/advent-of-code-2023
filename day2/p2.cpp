#include <fstream>
#include <iostream>
#include <map>

using namespace std;

map<string, int> colors;

int main(int argc, char *argv[]) {
  ifstream file("p1.txt");

  int total = 0;

  if (file.is_open()) {
    std::string line;
    std::string in_line;
    std::string set_delim = ";";
    std::string in_delim = ",";
    std::string tmp;
    while (std::getline(file, line)) {
      // cout << line << endl;

      std::string tmp_line = line + ";";
      size_t in_pos = 0;
      size_t pos = 0;
      int max_red = 0;
      int max_green = 0;
      int max_blue = 0;

      pos = tmp_line.find(":");
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
              max_green = amt;
          } else if (tmp.find("blue") != string::npos) {
            if (amt > max_blue)
              max_blue = amt;
          } else {
            if (amt > max_red)
              max_red = amt;
          }

          in_line.erase(0, in_pos + in_delim.length());
        }
        tmp_line.erase(0, pos + set_delim.length());
      }
      cout << line << endl;
      cout << "mred: " << max_red << "; m_green: " << max_green
           << "; m_blue: " << max_blue << endl;
      total += max_green * max_blue * max_red;
    }
    file.close();
    cout << "total: " << total << endl;
  }
  return 0;
}
