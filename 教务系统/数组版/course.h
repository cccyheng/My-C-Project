#ifndef COURSE_H
#define COURSE_H
struct Course{
    long long Courseid;
    int Credit;
    char CourseName[50];
    int teacherCount;
    long long Teacherids[5];
};
void addCourse(long long Courseid, int Credit, char CourseName[], int teacherCount, long long Teacherids[]);
void listAllCourse();
void Course_idSearch(long long id);
void Course_nameSearch(char name[]);
void editCourse(long long id);
void deleteCourse(long long id);
void Course_init();
#endif

int Course_hasData();
