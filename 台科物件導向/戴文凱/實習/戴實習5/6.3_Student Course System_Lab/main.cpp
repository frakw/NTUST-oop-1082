#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
char week[5] = {'M','T','W','R','F'};
class Course;
class Time;
class Time {
public:
    char day;
    int time;
};
class Course {
public:
    string name;
    vector<Time> time;
    void print() {
        cout << name;
        for (int i = 0;i < 5;i++) {//�ץ����~: ��:ComputerGraphics T10 R1 R9 | ��:ComputerGraphics R1 R9 T10
            for (int j = 1;j < 11;j++) {
                for (int k = 0;k < time.size();k++) {
                    if (time[k].day == week[i] && time[k].time == j) {
                        cout << ' ' << time[k].day << time[k].time;
                    }
                }
            }
        }
        /*��Ӫ����~
        for (int i = 0;i < time.size();i++) {
            cout << ' ' << time[i].day << time[i].time;
        }
        */
        cout << endl;
    }
};

class student {
public:
    string name;
    vector<Course> course;
    void print() {
        for (int i = 0;i < 5;i++) {
            cout << week[i]<<":";
            for (int x = 1;x < 11;x++) {
                for (int j = 0;j < course.size();j++) {
                    for (int k = 0;k < course[j].time.size();k++) {
                        if (course[j].time[k].time == x && course[j].time[k].day==week[i]) {
                            cout << ' ' << x << ':' << course[j].name;
                        }
                    }
                }
            }
            cout << endl;
        }
    }
private:
};
int find_student_pos(vector<student>, string);
int main() {
    string input;//���r��
    vector<student> all_data;//�Ҧ��ǥ͸��
    while (getline(cin, input)) {
        stringstream in(input);
        string command;//���O
        student data;//push_back�P�Ȧs��ƥ�
        int index;
        in >> command;
        if (command == "AddStudent") {
            in >> data.name;
            for (int i = 0;i < all_data.size();i++) {//�ˬd���L����
                if (all_data[i].name == data.name) {
                    cout << "The student's name is duplicate." << endl;
                    goto loop_end;
                }
            }
            all_data.push_back(data);
        }
        else if (command == "AddCourse") {
            Course course;//�Ψ�push_back
            Time time;//�Ψ�push_back
            string others;//�s�ҵ{�ɶ����r��A�g�B�z��s�Jvector: W1 W2 W3
            in >> data.name >> course.name;
            if ((index = find_student_pos(all_data, data.name)) == -1) {//�ˬd�ǥͬO�_�s�b
                goto loop_end;
            }
            getline(in, others);
            for (int i = 0;i < others.length();i++) {//�R�ť�
                if (others[i] == ' ') {
                    others.erase(others.begin()+i);
                    i--;//�R���ťի�A����++�A��--��P�A�d�b��a�N�n
                }
            }
            stringstream in2(others);
            while(in2>>time.day){//�Ĭ�Ұ��ˬd
                in2 >> time.time;
                for (int j = 0;j < all_data[index].course.size();j++) {
                    for (int k = 0;k < all_data[index].course[j].time.size();k++) {
                        if (all_data[index].course[j].time[k].day == time.day && all_data[index].course[j].time[k].time == time.time) {
                            cout << "Course conflict." << endl;
                            goto loop_end;
                        }
                    }
                }
                course.time.push_back(time);
            }
            
            all_data[index].course.push_back(course);
        }
        else if (command == "DelStudent") {
            in >> data.name;
            if ((index = find_student_pos(all_data, data.name)) == -1) {//�ˬd�ǥͬO�_�s�b
                goto loop_end;
            }
            all_data.erase(all_data.begin()+index);
        }
        else if (command == "DelCourse") {
            in >> data.name;
            string course_name;
            if ((index = find_student_pos(all_data, data.name)) == -1) {//�ˬd�ǥͬO�_�s�b
                goto loop_end;
            }
            in >> course_name;
            int index2=-1;//�s�Ұ󪺽s��
            for (int i = 0;i < all_data[index].course.size();i++) {//�ˬd�Ұ�s���s�b
                if (course_name == all_data[index].course[i].name) {
                    index2 = i;
                }
            }
            if (index2 == -1) {
                cout << "The course does not exist." << endl;
                continue;
            }
            all_data[index].course.erase(all_data[index].course.begin()+index2);
        }
        else if (command == "Print") {
            in >> data.name;
            string temp;//�s�ҵ{�W�r
            if (data.name == "StudentList") {
                if (all_data.size() == 0) {
                    cout << "The Students list is empty." << endl;
                    continue;
                }
                for (int i = 0;i < all_data.size();i++) {
                    cout << all_data[i].name<<endl;
                }
                continue;
            }
            int index = -1;//�s�ǥͪ��s��
            for (int i = 0;i < all_data.size();i++) {//�ˬd�ǥͦs���s�b
                if (all_data[i].name == data.name) {
                    index = i;
                }
            }
            if (index == -1) {
                cout << "The student's name does not exist." << endl;
                continue;
            }
            else if (in >> temp) {//�p�G�����w�C�L���ӽҵ{:Print Mike English
                int i;
                for (i = 0;i < all_data[index].course.size();i++) {//�ˬd�ҵ{�s���s�b
                    if (temp== all_data[index].course[i].name) {
                        all_data[index].course[i].print();
                        break;
                    }
                }
                if (i == all_data[index].course.size()) {
                    cout << "The course does not exist." << endl;
                }
            }
            else {//�S�����w�C�L���ӽҵ{�A�L�X�Ҫ�:Print English
                all_data[index].print();
            }
        }
    loop_end:;
    }
    return 0;
}

int find_student_pos(vector<student> all_data, string name) {
    int index = -1;
    for (int i = 0;i < all_data.size();i++) {
        if (name == all_data[i].name) {
            index = i;
        }
    }
    if (index == -1) {
        cout << "The student's name does not exist." << endl;
    }
    return index;
}


int find_course_pos(student x, string course_name) {
    int index = -1;
    for (int i = 0;i < x.course.size();i++) {
        if (course_name == x.course[i].name) {
            index = i;
        }
    }
    if (index == -1) {
        cout << "The student's name does not exist." << endl;
    }
    return index;
}