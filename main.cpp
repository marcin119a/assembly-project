#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#define INT_MAX 2147483647
using namespace std;


int s(char a, char b) {
    if (a == b){
        return 0;
    }
    if (a != b) {
        return 1;
    }
    return 0;
}


vector<float> overlap(string x, string y, int min_length){
    vector<vector<int>> D ((x.size() + 1), vector<int> (y.size() + 1) );
    vector<int> sx(x.size() + 1);
    vector<int> sy(y.size() + 1) ;

    for (int i = 1; i < (x.size() + 1); i++){
        int p = 1;
        while (p <= i ) {
            sx[x.size() - (i-p)] = sx[x.size() - (i-p)] + s(x[i-1], y[p-1]);
            sy[y.size() - (i-p)] = sy[y.size() - (i-p)] + s(x[p-1], y[i-1]);
            p += 1;
        }
    }

    for(int i = 0; i < min_length; i++){ //horizontal
        sx[i] = INT_MAX / 2;
    }
    for(int j = 0; j < min_length; j++){ //vertical
        sy[j] = INT_MAX / 2;
    }


    int a = distance(sx.begin(), min_element(sx.begin(), sx.end()));
    int b = distance(sy.begin(), min_element(sy.begin(), sy.end()));


    vector<float> r = {float(sx[a])/ a, float(sy[b]) / b, float(a), float(b)};

    return r;
}


vector<string> read_file(int argc, char **argv){
    if (argc < 2) {
        std::cerr << " Wrong format: " << argv[0] << " [infile] " << std::endl;
    }

    ifstream input(argv[1]);
    if (!input.good()) {
        std::cerr << "Error opening: " << argv[1] << " . You have failed." << std::endl;
    }
    string line, id, DNA_sequence;
    vector<string> reads;

    int i = 0;
    while (getline(input, line)) {
        if(line.empty())
            continue;

        if (line[0] == '>') {
            if(!id.empty()) {
                reads.push_back(DNA_sequence);
            }
            id = line.substr(1);
            DNA_sequence.clear();
        }
        else {
            DNA_sequence += line;
        }
        i += 1;
    }


    return reads;
}

#define OLEN_AB 2
#define OLEN_BA 3
pair<vector<string>, int> pick_maximal_overlap(vector<string> reads, int k){
    string reada = "";
    string readb = "";
    int best_olen = 0;
    if (reads.size() == 1){ return {{"", ""}, 0};}

    for (string a: reads) {
        for (string b: reads){
            if (a < b){
                vector<float> v = overlap(a, b, k);
                if (v[OLEN_AB] > best_olen){ //
                    best_olen = v[OLEN_AB];
                    reada = a;
                    readb = b;
                }
                if (v[OLEN_BA] > best_olen) {
                    best_olen = v[OLEN_BA];
                    reada = b;
                    readb = a;
                }
            }
        }
    }
    vector<string> read = {reada, readb};
    pair<vector<string>, int> r = {read, best_olen};
    return r;
}



void save(int argc, char **argv,  int k){
    ofstream myfile (argv[2]);

    vector<string> reads = read_file(argc, argv);
    if (myfile.is_open()) {
        for (string a: reads) {
            for (string b: reads) {
                if (a < b) {
                    vector<float> v = overlap(a, b, k);
                    myfile << v[0] << ";" << v[1] << ";" << v[2] << ";" << v[3] << ";" << a <<  ";" << b << ";" << "\n";
                }
            }
        }
    } else {
        cout << "Unable to open file";
    }
    myfile.close();
}

int main(int argc, char **argv) {
    vector<string> reads = read_file(argc, argv);
    int k = atoi(argv[3]);
    save(argc, argv, k);

}
