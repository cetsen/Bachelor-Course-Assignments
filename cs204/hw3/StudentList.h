#include <string>
using namespace std;

struct examNode
{
	string courseName;
	int grade;
	examNode * next;

	//default contructor
	examNode::examNode()
	{}

	//constructor
	examNode::examNode(string c, int g, examNode * n)
		:courseName(c), grade(g), next(n)
	{}
};

struct studentNode
{
	string userName;
	examNode * headExamList;
	studentNode * next;
	studentNode * prev;

	//default contructor
	studentNode::studentNode()
	{}

	//constructor
	studentNode::studentNode(string u, examNode * h, studentNode * n, studentNode * p)
		:userName(u), headExamList(h), next(n), prev(p)
	{}
};

class StudentList
{
public:
	StudentList();
	void addExam(string userName, string courseName, int grade);
	void deleteStudent(string userName);
	void printStudent(string userName);
	void printAllAZ();
	void printAllZA();
	void deleteAll();

private:
	studentNode * head;
	studentNode * tail;
};
