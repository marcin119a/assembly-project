#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int s(char a, char b) {
    if (a == b){
        return 0;
    }
    if (a != b) {
        return 1;
    }

}

void debug(vector<vector<int>> vec){
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            cout << vec[i][j] << " ";
        }
    }
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
    for (string a: reads) { // tu jest jakiś problem ?
        for (string b: reads){
            if (a < b){
                vector<float> v = overlap(a, b, k);
                cout << v[2] << "---" << v[3] << " ... ";
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

vector<string> greedy_scs(vector<string> reads, int k){
    pair<vector<string>, int> r = pick_maximal_overlap(reads, k);
    string reada = r.first[0];
    string readb = r.first[1];
    int olen = r.second;
    cout << olen;

    while (olen > 0){
        remove(reads.begin(),reads.end(),reada);
        remove(reads.begin(),reads.end(),readb);
        string outr = readb.substr(olen, readb.size());
        cout << " " << reada + outr;

        reads.push_back(reada + outr);

        r = pick_maximal_overlap(reads, k);
        reada = r.first[0];
        readb = r.first[1];
        olen = r.second;
    }
    return reads;
}

int main(int argc, char **argv) {
    vector<string> reads = {"CTCGGCCCTAGG", "GGCTCTAGGCCC"};
    int k = 5;
    //vector<float> r = overlap("CTCGGCCCTAGG", "GGCTCTAGGCCC", k);
    //cout << r[2] << " ";
    //cout << r[3];
    vector<string> rrrr = greedy_scs(reads, k);
    std::cout << rrrr[0];
    //save("../ouputs.txt", argc, argv);
    //vector<float> v = overlap("ACTG", "ACCT", 1);
    //cout << v[0] << " " << v[1]  << " " << v[2] << v[3];
}
