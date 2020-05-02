#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

void readInput(string file, vector<vector<char>> &cmap, char &num);
void readOutput(string file, map<char, int> &result, char num);

int main() {
    for (int i = 0; i != 10; i++) {
        vector<vector<char>> cmap;
        char num;
        map<char, int> result;
        readInput("gmap" + to_string(i) + ".in", cmap, num);
        readOutput("gmap" + to_string(i) + ".out", result, num);

        for (size_t x = 0; x != cmap.size(); x++) {
            for (size_t y = 0; y != cmap[0].size(); y++) {
                if (x != 0) {
                    if (cmap[x - 1][y] != cmap[x][y]) {
                        auto col1 = result.find(cmap[x - 1][y]);
                        auto col2 = result.find(cmap[x][y]);
                        if (col1->second == col2->second) {
                            cout << "Invalid color on " << x << ", " << y
                                 << endl
                                 << "File: " << i << endl;
                            return 1;
                        }
                    }
                }
                if (y != 0) {
                    if (cmap[x][y - 1] != cmap[x][y]) {
                        auto col1 = result.find(cmap[x][y - 1]);
                        auto col2 = result.find(cmap[x][y]);
                        if (col1->second == col2->second) {
                            cout << "Invalid color on " << x << ", " << y
                                 << endl
                                 << "File: " << i << endl;
                            return 1;
                        }
                    }
                }
                if (x != cmap.size() - 1) {
                    if (cmap[x + 1][y] != cmap[x][y]) {
                        auto col1 = result.find(cmap[x + 1][y]);
                        auto col2 = result.find(cmap[x][y]);
                        if (col1->second == col2->second) {
                            cout << "Invalid color on " << x << ", " << y
                                 << endl
                                 << "File: " << i << endl;
                            return 1;
                        }
                    }
                }
                if (y != cmap[0].size() - 1) {
                    if (cmap[x][y + 1] != cmap[x][y]) {
                        auto col1 = result.find(cmap[x][y + 1]);
                        auto col2 = result.find(cmap[x][y]);
                        if (col1->second == col2->second) {
                            cout << "Invalid color on " << x << ", " << y
                                 << endl
                                 << "File: " << i << endl;
                            return 1;
                        }
                    }
                }
            }
        }
        cout << "File " << i << " passed the test." << endl;
    }
}

void readInput(string file, vector<vector<char>> &cmap, char &num) {
    ifstream infile(file);
    int m;
    int n;
    int x;
    infile >> x >> m >> n;
    num = x;
    infile.ignore(256, '\n');
    for (int i = 0; i != m; i++) {
        cmap.push_back(vector<char>());
        for (int k = 0; k != n; k++) {
            char c;
            infile.get(c);
            cmap[i].push_back(c);
        }
        infile.ignore(256, '\n');
    }
}

void readOutput(string file, map<char, int> &result, char num) {
    ifstream infile(file);
    for (char i = 0; i != num; i++) {
        int color;
        infile.ignore(256, i + 'A');
        infile >> color;
        infile.ignore(256, '\n');
        result.insert(make_pair(i + 'A', color));
    }
}
