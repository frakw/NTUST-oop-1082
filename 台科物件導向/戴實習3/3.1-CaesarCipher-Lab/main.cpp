#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdio>
using namespace std;

int main() {
    string input;
    int len;
    long long int num;
    while (getline(cin,input)) {
        cin >> num;
        cin.ignore();
        num = num % 26;
        for (int i = 0;i < input.length();i++) {
            int temp;//����|��char����A����int�s
            if (isupper(input[i])) {
                temp = input[i];
                temp += num;
                if (temp < 'A') {
                    temp += 26;
                }
                else if (temp > 'Z') {
                    temp -= 26;
                }
                input[i] = temp;//��^��
            }
            else if (islower(input[i])) {
                temp = input[i];
                temp += num;
                if (temp < 'a') {
                    temp += 26;
                }
                else if (temp > 'z') {
                    temp -= 26;
                }
                input[i] = temp;
            }
        }
        cout << input << endl;
    }
    return 0;
}