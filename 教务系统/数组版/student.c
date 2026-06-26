#include"student.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_STUDENTS 100
struct Student students[MAX_STUDENTS];
int StudentNum = 0;

static void saveToFile() {
    FILE *fp = fopen("student.txt", "w");
    if (fp == NULL) { printf("无法打开文件!\n"); return; }
    for (int i = 0; i < StudentNum; i++) {
        fprintf(fp, "%lld %d %d %s %s %d %d %d %d %d %d %d",
                students[i].Studentid, students[i].Class, students[i].Grade,
                students[i].Name, students[i].Major,
                students[i].score_math, students[i].score_c, students[i].score_linear,
                students[i].score_physics, students[i].score_java, students[i].totalScore,
                students[i].courseCount);
    for (int k = 0; k < students[i].courseCount; k++)
        fprintf(fp, " %lld", students[i].courseIds[k]);
    fprintf(fp, "\n");
    }
    fclose(fp);
}

static void loadFromFile() {
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL) return;
    StudentNum = 0;
    while (fscanf(fp, "%lld %d %d %s %s %d %d %d %d %d %d\n",
              &students[StudentNum].Studentid, &students[StudentNum].Class,
              &students[StudentNum].Grade, students[StudentNum].Name,
              students[StudentNum].Major,
              &students[StudentNum].score_math, &students[StudentNum].score_c,
              &students[StudentNum].score_linear, &students[StudentNum].score_physics,
              &students[StudentNum].score_java, &students[StudentNum].totalScore) == 11) {
                StudentNum++;
            }
    fclose(fp);
}

void Student_init() { loadFromFile(); }

void addStudent(long long Studentid, int Class, int Grade, char Name[], char Major[]) {
    if (StudentNum >= MAX_STUDENTS) { printf("学生已满!\n"); return; }
    students[StudentNum].Studentid = Studentid;
    students[StudentNum].Class = Class;
    students[StudentNum].Grade = Grade;
    strcpy(students[StudentNum].Name, Name);
    strcpy(students[StudentNum].Major, Major);
    students[StudentNum].score_math = 0;
    students[StudentNum].score_c = 0;
    students[StudentNum].score_linear = 0;
    students[StudentNum].score_physics = 0;
    students[StudentNum].score_java = 0;
    students[StudentNum].totalScore = 0;
    students[StudentNum].courseCount = 0;
    StudentNum++;
    saveToFile();
}

void listAllStudent() {
    if (StudentNum == 0) { printf("目前无学生数据存入\n"); return; }
    printf("%-13s %-4s %-4s %-10s %-10s %-6s %-6s %-6s %-6s %-6s %-6s\n",
           "学号","班级","年级","姓名","专业","高数","C语言","线代","大物","Java","总分");
    for (int i = 0; i < StudentNum; i++) {
        printf("%-13lld %-4d %-4d %-10s %-10s %-6d %-6d %-6d %-6d %-6d %-6d\n",
               students[i].Studentid, students[i].Class, students[i].Grade,
               students[i].Name, students[i].Major,
               students[i].score_math, students[i].score_c, students[i].score_linear,
               students[i].score_physics, students[i].score_java, students[i].totalScore);
    }
}

void Student_idSearch(long long id) {
    if (StudentNum == 0) { printf("目前无学生数据存入\n"); return; }
    for (int i = 0; i < StudentNum; i++) {
        if (students[i].Studentid == id) {
            printf("学号: %lld  班级: %d  年级: %d  姓名: %s  专业: %s\n",
                   students[i].Studentid, students[i].Class, students[i].Grade,
                   students[i].Name, students[i].Major);
            printf("高数: %d  C语言: %d  线代: %d  大物: %d  Java: %d\n",
                   students[i].score_math, students[i].score_c, students[i].score_linear,
                   students[i].score_physics, students[i].score_java);
            printf("总分: %d\n", students[i].totalScore);
            return;
        }
    }
    printf("未找到学号为 %lld 的学生\n", id);
}

void Student_nameSearch(char name[]) {
    if (StudentNum == 0) { printf("目前无学生数据存入\n"); return; }
    int found = 0;
    for (int i = 0; i < StudentNum; i++) {
        if (strcmp(students[i].Name, name) == 0) {
            printf("学号: %lld  班级: %d  年级: %d  姓名: %s  专业: %s\n",
                   students[i].Studentid, students[i].Class, students[i].Grade,
                   students[i].Name, students[i].Major);
            printf("高数: %d  C语言: %d  线代: %d  大物: %d  Java: %d  总分: %d\n",
                   students[i].score_math, students[i].score_c, students[i].score_linear,
                   students[i].score_physics, students[i].score_java, students[i].totalScore);
            found = 1;
        }
    }
    if (!found) printf("未找到名字为 %s 的学生\n", name);
}

void editStudent(long long id) {
    if (StudentNum == 0) { printf("目前无学生数据存入\n"); return; }
    for (int i = 0; i < StudentNum; i++) {
        if (students[i].Studentid == id) {
            int newClass, newGrade;
            char newName[20], newMajor[50];
            printf("请输入新的班级: "); scanf("%d", &newClass);
            printf("请输入新的年级: "); scanf("%d", &newGrade);
            printf("请输入新的姓名: "); scanf("%s", newName);
            printf("请输入新的专业: "); scanf("%s", newMajor);
            students[i].Class = newClass; students[i].Grade = newGrade;
            strcpy(students[i].Name, newName); strcpy(students[i].Major, newMajor);
            saveToFile(); printf("修改成功!\n"); return;
        }
    }
    printf("未找到学号为 %lld 的学生\n", id);
}

void deleteStudent(long long id) {
    if (StudentNum == 0) { printf("目前无学生数据存入\n"); return; }
    int found = 0;
    for (int i = 0; i < StudentNum; i++) {
        if (students[i].Studentid == id) {
            for (int j = i; j < StudentNum - 1; j++) students[j] = students[j + 1];
            StudentNum--; saveToFile(); printf("删除成功!\n"); found = 1; break;
        }
    }
    if (!found) printf("未找到学号为 %lld 的学生\n", id);
}

int Student_hasData() { return StudentNum > 0; }

void scoreInput(long long id) {
    if (StudentNum == 0) { printf("目前无学生数据存入\n"); return; }
    for (int i = 0; i < StudentNum; i++) {
        if (students[i].Studentid == id) {
            printf("请输入 %s 的成绩:\n", students[i].Name);
            printf("高数: "); scanf("%d", &students[i].score_math);
            printf("C语言: "); scanf("%d", &students[i].score_c);
            printf("线代: "); scanf("%d", &students[i].score_linear);
            printf("大物: "); scanf("%d", &students[i].score_physics);
            printf("Java: "); scanf("%d", &students[i].score_java);
            students[i].totalScore = students[i].score_math + students[i].score_c
                                   + students[i].score_linear + students[i].score_physics
                                   + students[i].score_java;
            saveToFile();
            printf("成绩录入成功! 总分: %d\n", students[i].totalScore);
            return;
        }
    }
    printf("未找到学号为 %lld 的学生\n", id);
}

void scoreShow(long long id) {
    if (StudentNum == 0) { printf("目前无学生数据存入\n"); return; }
    for (int i = 0; i < StudentNum; i++) {
        if (students[i].Studentid == id) {
            printf("\n======== %s 的成绩单 ========\n", students[i].Name);
            printf("高数: %d\n", students[i].score_math);
            printf("C语言: %d\n", students[i].score_c);
            printf("线代: %d\n", students[i].score_linear);
            printf("大物: %d\n", students[i].score_physics);
            printf("Java: %d\n", students[i].score_java);
            printf("总分: %d\n", students[i].totalScore);
            return;
        }
    }
    printf("未找到学号为 %lld 的学生\n", id);
}

void rankByTotal() {
    if (StudentNum == 0) { printf("目前无学生数据存入\n"); return; }
    struct Student *arr = malloc(sizeof(*arr) * StudentNum);
    for (int i = 0; i < StudentNum; i++) arr[i] = students[i];
    for (int i = 0; i < StudentNum - 1; i++) {
        for (int j = 0; j < StudentNum - 1 - i; j++) {
            if (arr[j].totalScore < arr[j+1].totalScore) {
                struct Student t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t;
            }
        }
    }
    printf("\n======== 总分排名 ========\n");
    printf("%-6s %-13s %-10s %-6s\n", "排名", "学号", "姓名", "总分");
    for (int i = 0; i < StudentNum; i++)
        printf("%-6d %-13lld %-10s %-6d\n", i+1, arr[i].Studentid, arr[i].Name, arr[i].totalScore);
    free(arr);
}

void rankBySubject(int subject) {
    if (StudentNum == 0) { printf("目前无学生数据存入\n"); return; }
    if (subject < 1 || subject > 5) { printf("科目选择错误!\n"); return; }
    char *subNames[] = {"", "高数", "C语言", "线代", "大物", "Java"};
    char *subName = subNames[subject];
    struct Student *arr = malloc(sizeof(*arr) * StudentNum);
    for (int i = 0; i < StudentNum; i++) arr[i] = students[i];
    for (int i = 0; i < StudentNum - 1; i++) {
        for (int j = 0; j < StudentNum - 1 - i; j++) {
            int a, b;
            if (subject == 1) { a = arr[j].score_math; b = arr[j+1].score_math; }
            else if (subject == 2) { a = arr[j].score_c; b = arr[j+1].score_c; }
            else if (subject == 3) { a = arr[j].score_linear; b = arr[j+1].score_linear; }
            else if (subject == 4) { a = arr[j].score_physics; b = arr[j+1].score_physics; }
            else { a = arr[j].score_java; b = arr[j+1].score_java; }
            if (a < b) { struct Student t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t; }
        }
    }
    printf("\n======== %s排名 ========\n", subName);
    printf("%-6s %-13s %-10s %-6s\n", "排名", "学号", "姓名", subName);
    for (int i = 0; i < StudentNum; i++) {
        int score;
        if (subject == 1) score = arr[i].score_math;
        else if (subject == 2) score = arr[i].score_c;
        else if (subject == 3) score = arr[i].score_linear;
        else if (subject == 4) score = arr[i].score_physics;
        else score = arr[i].score_java;
        printf("%-6d %-13lld %-10s %-6d\n", i+1, arr[i].Studentid, arr[i].Name, score);
    }
    free(arr);
}

void enrollCourse(long long sid, long long cid) {
    struct Student *s = NULL;
    int n = 0;
    for (int i = 0; i < StudentNum; i++) {
        if (students[i].Studentid == sid) { s = &students[i]; n = StudentNum; break; }
    }
    if (s == NULL) { printf("未找到该学生!\n"); return; }
    if (s->courseCount >= 10) { printf("已选课程已满!\n"); return; }
    for (int i = 0; i < s->courseCount; i++)
        if (s->courseIds[i] == cid) { printf("该课程已选!\n"); return; }
    s->courseIds[s->courseCount++] = cid;
    saveToFile();
    printf("选课成功!\n");
}

void showStudentCourses(long long id) {
    for (int i = 0; i < StudentNum; i++) {
        if (students[i].Studentid == id) {
            printf("学生 %s(%lld) 已选课程:\n", students[i].Name, students[i].Studentid);
            for (int j = 0; j < students[i].courseCount; j++)
                printf("  %lld %s\n", students[i].courseIds[j], Course_getName(students[i].courseIds[j]));
            printf("\n"); return;
        }
    }
    printf("未找到该学生!\n");
}

void showCourseStudents(long long cid) {
    printf("选了课程 %lld 的学生:\n", cid);
    int found = 0;
    for (int i = 0; i < StudentNum; i++) {
        for (int j = 0; j < students[i].courseCount; j++) {
            if (students[i].courseIds[j] == cid) {
                printf("  %lld %s\n", students[i].Studentid, students[i].Name);
                found = 1; break;
            }
        }
    }
    if (!found) printf("  暂无学生选这门课\n");
}
