#include <iostream>
#include <string>
#include <vector>
typedef struct {
	char a, b;
}letter_pair;
using namespace std;
void create_replace_letter(letter_pair*, vector<char>*,char, char,int);//���j�M��i���N�r��
int main() {
	int m, n;
	while (cin >> m >> n) {
		if (!(m || n)) {
			break;
		}
		vector<char> replace[26];//a~z���i���N�r��
		letter_pair* pair = new letter_pair[m];//�ʺA�t�m���Ҧ����r����
		for (int i = 0;i < m;i++) {
			cin >> pair[i].a >> pair[i].b;//OJ���i��cin.get();
		}
		for (char i = 'a';i <= 'z';i++) {//�qa~z��J
			replace[i - 'a'].push_back(i);//��J�ۤv�A����~���Φh�ˬd�ۤv(�j��@�����)
			create_replace_letter(pair, replace,i,i,m);//���j�M��i���N�r��
		}
		delete[] pair;//����
		for (int i = 0;i < n;i++) {
			string a, b;
			cin >> a >> b;
			if (a.length() != b.length()) {//�������A����no�A�M��U�@��
				cout << "no" << endl;
				continue;
			}
			int same_count = 0;//���\½Ķ���ƶq
			for (int j = 0;j < b.length();j++) {
				for (int k = 0;k < replace[a[j] - 'a'].size();k++) {//�qa���ĴX�Ӥ�����X��Ӧr����vector�A�M��]�L���vector
					if (b[j] == replace[a[j] - 'a'][k] ){//�p�G���\½Ķ
						same_count++;
						break;
					}
				}
			}
			cout << ((same_count == b.length())?"yes":"no") << endl;
		}
	}
    return 0;
}

void create_replace_letter(letter_pair* pair,vector<char>* replace,char main_letter,char letter,int m) {//main letter �O�����j�D�n�x�s���r���Aletter�t�d����
	for (int i = 0;i < m;i++){
		if (pair[i].a == letter) {
			int j;
			for (j = 0;j < replace[main_letter - 'a'].size();j++) {//�z�ﱼ�w���Ʀr��
				if (replace[main_letter - 'a'][j] == pair[i].b) {
					break;
				}
			}
			if (j == replace[main_letter - 'a'].size()) {
				replace[main_letter - 'a'].push_back(pair[i].b);//�[�J�s�i���N�r��
				create_replace_letter(pair, replace, main_letter, pair[i].b, m);//�s�i���N�r�����j
			}
		}
	}
}