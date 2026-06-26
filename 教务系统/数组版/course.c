#include"course.h"
#include"teacher.h"
#include <string.h>
#include <stdio.h>
#define MAX_COURSES 100
struct Course courses[MAX_COURSES];
int CourseNum = 0;
static void saveToFile() {
    FILE *fp = fopen("course.txt", "w");
    if (fp == NULL) { printf("无法打开文件!\n"); return; }
    for (int i = 0; i < CourseNum; i++) {
        fprintf(fp, "%lld %d %s %d", courses[i].Courseid, courses[i].Credit, courses[i].CourseName, courses[i].teacherCount);
        for (int j = 0; j < courses[i].teacherCount; j++)
            fprintf(fp, " %lld", courses[i].Teacherids[j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}
static void loadFromFile() {
    FILE *fp = fopen("course.txt", "r");
    if (fp == NULL) return;
    CourseNum = 0;
    while (fscanf(fp, "%lld %d %s %d", &courses[CourseNum].Courseid, &courses[CourseNum].Credit, courses[CourseNum].CourseName, &courses[CourseNum].teacherCount) == 4) {
        for (int j = 0; j < courses[CourseNum].teacherCount; j++)
            fscanf(fp, "%lld", &courses[CourseNum].Teacherids[j]);
        CourseNum++;
    }
    fclose(fp);
}
void Course_init() { loadFromFile(); }
void addCourse(long long Courseid, int Credit, char CourseName[], int teacherCount, long long Teacherids[]) {
    if (CourseNum >= MAX_COURSES) { printf("课程已满!\n"); return; }
    courses[CourseNum].Courseid = Courseid; courses[CourseNum].Credit = Credit;
    strcpy(courses[CourseNum].CourseName, CourseName);
    courses[CourseNum].teacherCount = teacherCount;
    for (int j = 0; j < teacherCount; j++) courses[CourseNum].Teacherids[j] = Teacherids[j];
    CourseNum++; saveToFile();
}
void listAllCourse() {
    if (CourseNum == 0) { printf("目前无课程数据存入\n"); return; }
    for (int i = 0; i < CourseNum; i++) {
        printf("%lld %d %s ", courses[i].Courseid, courses[i].Credit, courses[i].CourseName);
        for (int j = 0; j < courses[i].teacherCount; j++)
            printf("%s ", Teacher_getName(courses[i].Teacherids[j]));
        printf("\n");
    }
}
void Course_idSearch(long long id) {
    if (CourseNum == 0) { printf("目前无课程数据存入\n"); return; }
    for (int i = 0; i < CourseNum; i++) {
        if (courses[i].Courseid == id) {
            printf("课程代码: %lld  学分: %d  课程名: %s  授课教师: ", courses[i].Courseid, courses[i].Credit, courses[i].CourseName);
            for (int j = 0; j < courses[i].teacherCount; j++)
                printf("%s(%lld) ", Teacher_getName(courses[i].Teacherids[j]), courses[i].Teacherids[j]);
            printf("\n"); return;
        }
    }
    printf("未找到课程代码为 %lld 的课程\n", id);
}
void Course_nameSearch(char name[]) {
    if (CourseNum == 0) { printf("目前无课程数据存入\n"); return; }
    int found = 0;
    for (int i = 0; i < CourseNum; i++) {
        if (strcmp(courses[i].CourseName, name) == 0) {
            printf("课程代码: %lld  学分: %d  课程名: %s  授课教师: ", courses[i].Courseid, courses[i].Credit, courses[i].CourseName);
            for (int j = 0; j < courses[i].teacherCount; j++)
                printf("%s(%lld) ", Teacher_getName(courses[i].Teacherids[j]), courses[i].Teacherids[j]);
            printf("\n"); found = 1;
        }
    }
    if (!found) printf("未找到名称为 %s 的课程\n", name);
}
void editCourse(long long id) {
    if (CourseNum == 0) { printf("目前无课程数据存入\n"); return; }
    for (int i = 0; i < CourseNum; i++) {
        if (courses[i].Courseid == id) {
            int newCredit, n; char newName[50]; long long tids[5];
            printf("请输入新的学分: "); scanf("%d", &newCredit);
            printf("请输入新的课程名: "); scanf("%s", newName);
            printf("请输入授课教师人数: "); scanf("%d", &n);
            for (int j = 0; j < n; j++) {
                printf("请输入第%d位教师工号: ", j+1); scanf("%lld", &tids[j]);
            }
            courses[i].Credit = newCredit; strcpy(courses[i].CourseName, newName);
            courses[i].teacherCount = n;
            for (int j = 0; j < n; j++) courses[i].Teacherids[j] = tids[j];
            saveToFile(); printf("修改成功!\n"); return;
        }
    }
    printf("未找到课程代码为 %lld 的课程\n", id);
}

char* Course_getName(long long id) {
    for (int i = 0; i < CourseNum; i++)
        if (courses[i].Courseid == id) return courses[i].CourseName;
    return "未知课程";
}

int Course_hasData() { return CourseNum > 0; }
void deleteCourse(long long id) {
    if (CourseNum == 0) { printf("目前无课程数据存入\n"); return; }
    int found = 0;
    for (int i = 0; i < CourseNum; i++) {
        if (courses[i].Courseid == id) {
            for (int j = i; j < CourseNum - 1; j++) courses[j] = courses[j + 1];
            CourseNum--; saveToFile(); printf("删除成功!\n"); found = 1; break;
        }
    }
    if (!found) printf("未找到课程代码为 %lld 的课程\n", id);
}
