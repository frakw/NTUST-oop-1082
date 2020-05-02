#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
class student {
public:
    string id;
    bool deny=false;
    string symptom;
    string travel;
    void print() {
        cout << id << '\t' << symptom << '\t' << travel << '\t' << (deny ? "Denied" : "Allowed") << endl;
    }
};
int main() {
    string input;
    vector<student> all_data;
    const string deny_symptom[5] = { "Fever","Dry cough","Fatigue","Shortness of breath","Chills" };
    const string deny_travel[9] = { "China" ,"USA" ,"Italy" ,"Spain" ,"Germany" ,"Iran" ,"France" ,"UK" ,"Switzerland" };
    
    while (getline(cin, input)) {
        if (input == "List") {
            for (int i = 0;i < all_data.size();i++) {
                all_data[i].print();
            }
            continue;
        }
        stringstream in(input);
        student data;
        string process,trash;
        string temp;
        char space;
        int travel_pos=0;
        in >> trash >> data.id;
        getline(in, process);
        for (int i = 0;i < process.length();i++) {//��X�̫�@�Ӫťժ���m
            if (process[i] == ' ') {
                travel_pos = i+1;
            }
        }
        for (int i = 1;i < travel_pos-1;i++) {//�̫�@�Ӫťիe�N�O�g���A��Jdata
            data.symptom.push_back(process[i]);
        }
        for (int i = travel_pos;i < process.length();i++) {//�̫�@�Ӫťի�N�O�ȹC�v�A��Jdata
            data.travel.push_back(process[i]);
        }
        for (int i = 0;i < 5;i++) {//�ˬd�g��
            if (data.symptom == deny_symptom[i]) {
                data.deny = true;
            }
        }
        for (int i = 0;i < 9;i++) {//�ˬd�ȹC�v
            if (data.travel == deny_travel[i]) {
                data.deny = true;
            }
        }
        all_data.push_back(data);//��Jall_data
        cout << data.id << " Access " << (data.deny ? "denied." : "allowed.") << endl;
        input.clear();
    }
    return 0;
}