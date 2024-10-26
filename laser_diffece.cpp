#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Beam {
    long long s; // Position parameter
    int type;    // 1 for laser A, -1 for laser B
};

int main() {
    long long L;
    int N, M;
    cin >> L >> N >> M;

    vector<Beam> beams;

    // Read beams from laser A
    for (int i = 0; i < N; ++i) {
        string dir;
        long long C;
        cin >> dir >> C;

        // Skip invalid beams
        if (C <= 0 || C >= L) continue;

        long long s;
        if (dir == "U") {
            s = C; // Beams intersecting the upper side
        } else if (dir == "R") {
            s = L + C; // Beams intersecting the right side
        } else {
            continue; // Invalid direction
        }
        beams.push_back({s, 1}); // Type 1 for laser A
    }

    // Read beams from laser B
    for (int i = 0; i < M; ++i) {
        string dir;
        long long C;
        cin >> dir >> C;

        // Skip invalid beams
        if (C <= 0 || C >= L) continue;

        long long s;
        if (dir == "U") {
            s = C; // Beams intersecting the upper side
        } else if (dir == "L") {
            s = -C; // Beams intersecting the left side
        } else {
            continue; // Invalid direction
        }
        beams.push_back({s, -1}); // Type -1 for laser B
    }

    // Sort beams by s, beams from laser A come before beams from laser B if s is the same
    sort(beams.begin(), beams.end(), [](const Beam &a, const Beam &b) {
        if (a.s != b.s)
            return a.s < b.s;
        return a.type > b.type; // Laser A beams come before laser B beams at the same s
    });

    long long count_A_before = 0;      // Number of laser A beams before current beam
    long long non_intersecting_pairs = 0; // Number of non-intersecting pairs

    for (const auto &beam : beams) {
        if (beam.type == 1) {
            // Beam from laser A
            count_A_before++;
        } else {
            // Beam from laser B
            non_intersecting_pairs += count_A_before;
        }
    }

    long long N_A = count_A_before;                // Total beams from laser A
    long long N_B = beams.size() - count_A_before; // Total beams from laser B

    long long total_pairs = N_A * N_B;                        // Total possible pairs
    long long intersecting_pairs = total_pairs - non_intersecting_pairs; // Pairs that intersect
    long long total_regions = N_A + N_B + intersecting_pairs + 1;

    cout << total_regions << endl;

    return 0;
}
