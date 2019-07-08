#ifndef STUDENT_H
#define STUDENT_H

#endif // STUDENT_H

#include <stdlib.h>
#include <string.h>
#include <fstream>
#include<iostream>
#include <vector>
#include <iterator>
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

typedef unsigned int uint;

class Student{

protected:
    char name[30];
    uint course;
    uint group;
public:
    Student()
    {
		char name[] = "";
        course = 0;
        group = 0;
    }
    Student(char name[30],uint course,uint group)
    {
		
		strncpy_s(this->name, name, sizeof(this->name) - 1);
		this->name[sizeof(this->name) - 1] = 0;

        this->course = course;
        this->group = group;

    }

	string get() const
	{
		
		return "\r"+string(name) + " " + to_string(course) + " " + to_string(group);
	}

	~Student()
	{

	}
};

class QAbstractTableModel
{
private:
    
    string path;
public:
    QAbstractTableModel(string path)
    {
		this->path = path;
    }
    void show()
    {
        string s;
		ifstream f(path, ios::binary);
		while (getline(f, s))
		{
			cout << s << endl;
		}
		f.close();
    }
	void delete_row(int number)
	{
		vector<string> v;
		ifstream f(path, ios::binary);
		int i = 1;
		string s;
		while (getline(f, s))
		{
			if (i != number)
				v.push_back(s);
			i++;
		}
		f.close();
		ofstream file(path, ios::binary);
		copy(v.begin(), v.end(), ostream_iterator<string>(file));
		file.close();
	}
	void insert_row(Student s)
	{
		std::ofstream file;
		file.open(path, std::ios::binary | std::ofstream::out | std::ofstream::in);
		file.seekp(0, std::ios_base::end);
		
		file.write(s.get().c_str(), s.get().size());
	}
	
};
