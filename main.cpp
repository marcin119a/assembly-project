#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#define DYN_MAX 2.0f
#define INT_MAX 2147483647
using namespace std;


int s(char a, char b) {
    if (a == b){
        return 0;
    }
    if (a == 'A' & (b == 'C' ||  b == 'T')) {
        return 4;
    }
    if (a == 'A' & (b == 'G')) {
        return 2;
    }
    if (a == 'C' & (b == 'A' ||  b == 'G')) {
        return 4;
    }
    if (a == 'C' & (b == 'T')) {
        return 2;
    }
    if (a == 'G' & (b == 'C' ||  b == 'T')) {
        return 4;
    }
    if (a == 'G' & (b == 'A')) {
        return 2;
    }
    if (a == 'T' & (b == 'A' ||  b == 'G')) {
        return 4;
    }
    if (a == 'T' & (b == 'C')) {
        return 2;
    }


    return 0;
}

/*
memory O(k)
complexity O(k^2)
*/
vector<float> overlap(string x, string y, int min_length){
    vector<int> sx(x.size() + 1);
    vector<int> sy(y.size() + 1);
    vector<float> sxf(x.size() + 1);
    vector<float> syf(y.size() + 1);

    for (int i = 1; i < (x.size() + 1); i++){
        int p = 1;
        while (p <= i ) {
            sx[x.size() - (i-p)] = sx[x.size() - (i-p)] + s(x[i-1], y[p-1]);
            sy[y.size() - (i-p)] = sy[y.size() - (i-p)] + s(x[p-1], y[i-1]);
            p += 1;
        }
    }

    for(int i = 0; i < (x.size() + 1); i++){ //horizontal
        if (i < min_length) {
            sxf[i] = DYN_MAX;
            sx[i] = INT_MAX/2;
        } else {
            sxf[i] = float(sx[i]) / (i+1);
        }
    }
    for(int j = 0; j < (y.size() + 1); j++){ //vertical
        if (j < min_length) {
            syf[j] = DYN_MAX;
            sy[j] = INT_MAX/2;
        } else {
            syf[j] = float(sy[j]) / (j+1);
        }
    }

    //argmin
    int a = distance(begin(sx), min_element(rbegin(sx), rend(sx)).base()) - 1;
    int b = distance(begin(sy), min_element(rbegin(sy), rend(sy)).base()) - 1 ;


    vector<float> r = {float(sx[a]), float(sy[b]), float(a), float(b)};

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
                    myfile << a << ";" << "1" << ";" << b << ";" <<  "-1" << ";" <<  v[2] << ";" << v[0] << "\n";
                    myfile << b << ";" << "1" << ";" << a << ";" <<  "-1" << ";" << v[3] << ";" << v[1] << "\n";
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
