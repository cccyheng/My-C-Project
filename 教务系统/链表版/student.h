#ifndef STUDENT_H
#define STUDENT_H
struct Student {
    long long Studentid;
    int Class;
    int Grade;
    char Name[20];
    char Major[50];
    int score_math;
    int score_c;
    int score_linear;
    int score_physics;
    int score_java;
    int totalScore;
    int courseCount;
    long long courseIds[10];
};
struct StudentNode {
    struct Student data;
    struct StudentNode *next;
};
void addStudent(long long Studentid, int Class, int Grade, char Name[], char Major[]);
void listAllStudent();
void Student_idSearch(long long id);
void Student_nameSearch(char name[]);
void editStudent(long long id);
void deleteStudent(long long id);
void Student_init();
void Student_free();
int Student_hasData();
void scoreInput(long long id);
void scoreShow(long long id);
void enrollCourse(long long sid, long long cid);
void showCourseStudents(long long cid);
void showStudentCourses(long long id);
void rankByTotal();
void rankBySubject(int subject);
#endif
