#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdio>
using namespace std;
//�D�ػ���:��J�@��r��A���U�Ӧ��n�X�ӼƦr�A���̤j���Ʀr�A�N�r��ѤW�ӤU�ѥ��ӥk�ƦC�Arow�`�Ƭ��̤j���Ʀr�A���U�ӨC�ӼƦr�N���row�ƪ��r��A�ťը��N�����u���X
int main() {
    string input;
    vector<int> number;
    while (getline(cin, input)) {
        int len = 0, temp;
        len = 0;
        while (cin >> temp){
            if (temp > len) {
                len = temp;
            }
            number.push_back(temp);
            if (getchar() == '\n') { break; }
        }
        len++;
        for (int i = 0;i < input.length();i++) {
            if (input[i] == ' ') {
                input[i] = '_';
            }
        }
        int col = ceil((double)input.length() / (double)len);//��row�`��(len)�A�p��col�`�ơA��K����for�j��ϥ�
        for (int i = 0;i < number.size();i++) {//�C�ӼƦr�ҥN���r���X
            for (int j = 0;j < col;j++) {
                if ((j * len + number[i]) < input.length()) {
                    cout << input[j * len + number[i]];
                }
            }
        }
        cout << endl;
        number.clear();
    }
    return 0;
}

/*
Row Transposition
3 0 6 1 2 5 4

int main(void){return 0;}
3 0 4 1 2

Apple
0 1 2 3 4 5 6 7 8 9 10


*/
