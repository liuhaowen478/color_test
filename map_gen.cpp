#include <fstream>
#include <random>
#include <set>
#include <iostream>

const int m = 60;
const int n = 60;
const int count = 15;

std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_int_distribution<int> prob_dist(0, 99);
std::uniform_int_distribution<int> loc_dist(0, 59);

int main() {
    for (int i = 0; i != 10; i++) {
        std::ofstream ofile("gmap" + std::to_string(i) + ".in");
        // Empty map
        std::vector<std::vector<int>> map;
        for (int j = 0; j != m; j++) {
            map.push_back(std::vector<int>());
            for (int k = 0; k != n; k++) {
                map[j].push_back(-1);
            }
        }
        std::set<std::pair<int, int>> hot_spots;
        std::set<std::pair<int, int>> to_add;
        // Starting points for country
        for (int k = 0; k != count; k++) {
            int x = loc_dist(rd);
            int y = loc_dist(rd);
            while (hot_spots.find(std::make_pair(x, y)) != hot_spots.end()) {
                x = loc_dist(rd);
                y = loc_dist(rd);
            }
            hot_spots.insert(std::make_pair(x, y));
            map[x][y] = k;
        }
        int empty_count = m * n - count;
        // Start spreading the map
        while (empty_count > 0) {
            for (auto p : hot_spots) {
                bool dir_avail = false;
                if (p.first - 1 >= 0) {
                    if (map[p.first - 1][p.second] == -1) {
                        dir_avail = true;
                        int prob = prob_dist(rd);
                        if (prob < 50) {
                            map[p.first - 1][p.second] = map[p.first][p.second];
                            to_add.insert(std::make_pair(p.first - 1, p.second));
                            empty_count--;
                        }
                    }
                }
                if (p.first + 1 < m) {
                    if (map[p.first + 1][p.second] == -1) {
                        dir_avail = true;
                        int prob = prob_dist(rd);
                        if (prob < 50) {
                            map[p.first + 1][p.second] = map[p.first][p.second];
                            to_add.insert(std::make_pair(p.first + 1, p.second));
                            empty_count--;
                        }
                    }
                }
                if (p.second - 1 >= 0) {
                    if (map[p.first][p.second - 1] == -1) {
                        dir_avail = true;
                        int prob = prob_dist(rd);
                        if (prob < 50) {
                            map[p.first][p.second - 1] = map[p.first][p.second];
                            to_add.insert(std::make_pair(p.first, p.second - 1));
                            empty_count--;
                        }
                    }
                }
                if (p.second + 1 < n) {
                    if (map[p.first][p.second + 1] == -1) {
                        dir_avail = true;
                        int prob = prob_dist(rd);
                        if (prob < 50) {
                            map[p.first][p.second + 1] = map[p.first][p.second];
                            to_add.insert(std::make_pair(p.first, p.second + 1));
                            empty_count--;
                        }
                    }
                }
                if (!dir_avail) {
                    hot_spots.erase(p);
                }
            }
            std::cout << empty_count << std::endl;
            for (auto p : to_add) {
                hot_spots.insert(p);
            }
            to_add.clear();
        }

        // Write to file
        ofile << count << " " << m << " " << n << std::endl;
        for (int k = 0; k != n; k++) {
            for (auto val : map[k]) {
                ofile << (char)(val + 'A');
            }
            ofile << std::endl;
        }
    }
}
