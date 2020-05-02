#include <iostream>
#include <string>
#include <vector>


#define version1
//#define version2


typedef struct {
	char a, b;
#ifdef version2
	bool has_go = false;
#endif // version2
}letter_pair;
using namespace std;
#ifdef version1
void create_replace_letter(letter_pair*, vector<char>*, char, char, int);//���j�M��i���N�r��
#endif // version1
#ifdef version2
bool check_char_link(letter_pair check_data, letter_pair* pair, int m);
#endif // version2
int main() {
	int m, n;
	while (cin >> m >> n) {
		if (!(m || n)) {
			break;
		}
		letter_pair* pair = new letter_pair[m];//�ʺA�t�m���Ҧ����r����
		for (int i = 0;i < m;i++) {
			cin >> pair[i].a >> pair[i].b;//OJ���i��cin.get();
		}
#ifdef version1
		vector<char> replace[26];//a~z���i���N�r��
		for (char i = 'a';i <= 'z';i++) {//�qa~z��J
			replace[i - 'a'].push_back(i);//��J�ۤv�A����~���Φh�ˬd�ۤv(�j��@�����)
			create_replace_letter(pair, replace, i, i, m);//���j�M��i���N�r��
		}
#endif // version1
		for (int i = 0;i < n;i++) {
			string a, b;
			cin >> a >> b;
			if (a.length() != b.length()) {//�������A����no�A�M��U�@��
				cout << "no" << endl;
				continue;
			}
			int same_letter_count = 0;//���\½Ķ���ƶq
#ifdef version1
			for (int j = 0;j < b.length();j++) {
				for (auto k : replace[a[j] - 'a']) {//�qa���ĴX�Ӥ�����X��Ӧr����vector�A�M��]�L���vector
					if (b[j] == k) {//�p�G���\½Ķ
						same_letter_count++;
						break;
					}
				}
			}
			cout << ((same_letter_count == b.length()) ? "yes" : "no") << endl;
#endif // version1
#ifdef version2
			for (int j = 0;j < b.length();j++) {
				letter_pair new_pair;
				new_pair.a = a[j]; new_pair.b = b[j];
				for (int i = 0;i < m;i++) {
					pair[i].has_go = false;
				}
				if (!check_char_link(new_pair, pair, m)) {
					cout << "no" << endl;
					goto next_test;
				}
			}
			cout << "yes" << endl;	
		next_test:;		
#endif // version2		
		}
		delete[] pair;
	}
	return 0;
}
#ifdef version1
void create_replace_letter(letter_pair* pair, vector<char>* replace, char main_letter, char letter, int m) {//main letter �O�����j�D�n�x�s���r���Aletter�t�d����
	for (int i = 0;i < m;i++) {
		if (pair[i].a == letter) {
			for (auto j : replace[main_letter - 'a']) {//�z�ﱼ�w���Ʀr��
				if (j == pair[i].b) {
					goto do_next;
				}
			}
			replace[main_letter - 'a'].push_back(pair[i].b);//�[�J�s�i���N�r��
			create_replace_letter(pair, replace, main_letter, pair[i].b, m);//�s�i���N�r�����j
		}
	do_next:;
	}
}
#endif // version1
#ifdef version2
bool check_char_link(letter_pair check_data,letter_pair* pair,int m)//�������j����  check_data��2�ӭn�˴����r��
{
	if (check_data.a == check_data.b) return true;
	for (int i = 0; i < m; i++)
	{
		if (!pair[i].has_go && pair[i].b == check_data.b )
		{
			pair[i].has_go = true;
			letter_pair tmp = check_data;
			tmp.b = pair[i].a;
			if (pair[i].a == check_data.a || check_char_link(tmp, pair, m)) {
				return true;
			}
		}
	}
	return false;
}
#endif // version2