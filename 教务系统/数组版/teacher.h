#ifndef TEACHER_H
#define TEACHER_H
struct Teacher{
    long long Teacherid;
    char Name[20];
    char Subject[50];
};
void addTeacher(long long Teacherid,char Name[],char Subject[]);
void listAllTeacher();
void Teacher_idSearch(long long id);
void Teacher_nameSearch(char name[]);
void editTeacher(long long id);
void deleteTeacher(long long id);
void Teacher_init();
char* Teacher_getName(long long id);
#endif

int Teacher_hasData();
