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

int overlap(string x, string y, int min_length){
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

    for(int i = 0; i < min_length; i++){
        D[x.size()][i] = INT_MAX / 2;
    }
    vector<int> v = D[x.size()];
    return distance(v.begin(), min_element(v.begin(), v.end()));
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

int main(int argc, char **argv) {
    ofstream myfile ("../output.txt");

    int minLenght = 10;
    vector<string> reads = read_file(argc, argv);
    if (myfile.is_open()) {
        for (string a: reads) {
            for (string b: reads) {
                if (a != b) {
                    myfile << overlap(a, b, minLenght) << " " << a <<  " " << b << "\n";
                }
            }
        }
    } else {
        cout << "Unable to open file";
    }
    myfile.close();
}
