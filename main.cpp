#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int s(char a, char b) {
    if (a == '-' || b == '-'){
        return 8;
    }
    if (a == b){
        return 0;
    }
    if ((a == 'A' && b != 'G') || (a == 'C' && b != 'T') || (a == 'G' && b != 'A') || (a == 'T' && b != 'C')) {
        return 4;
    }
    return 2;

}

void debug(vector<vector<int>> vec){
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            cout << vec[i][j] << " ";
        }
        cout << "\n";
    }
}

int overlap(string x, string y){
    vector<vector<int>> D ((x.size() + 1), vector<int> (y.size() + 1) );



    for (int i = 1; i < (x.size() + 1); i++){
        for(int j = 1; j < (y.size() + 1); j++) {
            D[0][j] = INT_MAX / 2;
            int a = D[i-1][j] + s(x[i-1], '-');
            int b = D[i][j-1] + s('-', y[j-1]);
            int c = D[i-1][j-1] + s(x[i-1], y[j-1]);

            D[i][j] = min(min(a,b), c);
            //cout << D[i][j] + s(x[i-1], '-') << endl;
            //cout << x[i] << endl;
        }
    }

    for(int i = 0; i < 5; i++){
        D[x.size()][i] = INT_MAX / 2;
    }
    debug(D);
    vector<int> v = D[x.size()];
    return distance(v.begin(), min_element(v.begin(), v.end()));
}

/*int main() {
    string x = "CTCGGCCCTAGG";
    string y = "GGCTCTAGGCCC";
    cout << overlap(x,y);
    cout << "Hello, World!" << endl;
    return 0;
} */

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
                cout << id << " : " << DNA_sequence << endl;
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

    if(!id.empty())
        std::cout << id << " : " << DNA_sequence << std::endl;
    return reads;
}

int main(int argc, char **argv) {
    vector<string> reads = read_file(argc, argv);


}
