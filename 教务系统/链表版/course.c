#include "course.h"
#include "teacher.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static struct CourseNode *head = NULL;

static void saveToFile() {
    FILE *fp = fopen("course.txt", "w");
    if (fp == NULL) { printf("无法打开文件!\n"); return; }
    struct CourseNode *p = head;
    while (p != NULL) {
        fprintf(fp, "%lld %d %s %d", p->data.Courseid, p->data.Credit, p->data.CourseName, p->data.teacherCount);
        for (int j = 0; j < p->data.teacherCount; j++)
            fprintf(fp, " %lld", p->data.Teacherids[j]);
        fprintf(fp, "\n");
        p = p->next;
    }
    fclose(fp);
}

static void loadFromFile() {
    FILE *fp = fopen("course.txt", "r");
    if (fp == NULL) return;
    int cnt, credit; long long cid; char name[50]; long long tids[5];
    struct CourseNode *tail = NULL;
    while (fscanf(fp, "%lld %d %s %d", &cid, &credit, name, &cnt) == 4) {
        for (int j = 0; j < cnt; j++) fscanf(fp, "%lld", &tids[j]);
        struct CourseNode *newNode = malloc(sizeof(*newNode));
        newNode->data.Courseid = cid; newNode->data.Credit = credit;
        strcpy(newNode->data.CourseName, name);
        newNode->data.teacherCount = cnt;
        for (int j = 0; j < cnt; j++) newNode->data.Teacherids[j] = tids[j];
        newNode->next = NULL;
        if (head == NULL) { head = newNode; tail = newNode; }
        else { tail->next = newNode; tail = newNode; }
    }
    fclose(fp);
}
void Course_init() { loadFromFile(); }
void addCourse(long long Courseid, int Credit, char CourseName[], int teacherCount, long long Teacherids[]) {
    struct CourseNode *newNode = malloc(sizeof(*newNode));
    newNode->data.Courseid = Courseid; newNode->data.Credit = Credit;
    strcpy(newNode->data.CourseName, CourseName);
    newNode->data.teacherCount = teacherCount;
    for (int j = 0; j < teacherCount; j++) newNode->data.Teacherids[j] = Teacherids[j];
    newNode->next = NULL;
    if (head == NULL) head = newNode;
    else { struct CourseNode *p = head; while (p->next != NULL) p = p->next; p->next = newNode; }
    saveToFile();
}
void listAllCourse() {
    if (head == NULL) { printf("目前无课程数据存入\n"); return; }
    struct CourseNode *p = head;
    while (p != NULL) {
        printf("%lld %d %s ", p->data.Courseid, p->data.Credit, p->data.CourseName);
        for (int j = 0; j < p->data.teacherCount; j++)
            printf("%s ", Teacher_getName(p->data.Teacherids[j]));
        printf("\n"); p = p->next;
    }
}
void Course_idSearch(long long id) {
    if (head == NULL) { printf("目前无课程数据存入\n"); return; }
    struct CourseNode *p = head;
    while (p != NULL) {
        if (p->data.Courseid == id) {
            printf("课程代码: %lld  学分: %d  课程名: %s  授课教师: ", p->data.Courseid, p->data.Credit, p->data.CourseName);
            for (int j = 0; j < p->data.teacherCount; j++)
                printf("%s(%lld) ", Teacher_getName(p->data.Teacherids[j]), p->data.Teacherids[j]);
            printf("\n"); return;
        }
        p = p->next;
    }
    printf("未找到课程代码为 %lld 的课程\n", id);
}
void Course_nameSearch(char name[]) {
    if (head == NULL) { printf("目前无课程数据存入\n"); return; }
    int found = 0; struct CourseNode *p = head;
    while (p != NULL) {
        if (strcmp(p->data.CourseName, name) == 0) {
            printf("课程代码: %lld  学分: %d  课程名: %s  授课教师: ", p->data.Courseid, p->data.Credit, p->data.CourseName);
            for (int j = 0; j < p->data.teacherCount; j++)
                printf("%s(%lld) ", Teacher_getName(p->data.Teacherids[j]), p->data.Teacherids[j]);
            printf("\n"); found = 1;
        }
        p = p->next;
    }
    if (!found) printf("未找到名称为 %s 的课程\n", name);
}
void editCourse(long long id) {
    if (head == NULL) { printf("目前无课程数据存入\n"); return; }
    struct CourseNode *p = head;
    while (p != NULL) {
        if (p->data.Courseid == id) {
            int newCredit, n; char newName[50]; long long tids[5];
            printf("请输入新的学分: "); scanf("%d", &newCredit);
            printf("请输入新的课程名: "); scanf("%s", newName);
            printf("请输入授课教师人数: "); scanf("%d", &n);
            for (int j = 0; j < n; j++) { printf("请输入第%d位教师工号: ", j+1); scanf("%lld", &tids[j]); }
            p->data.Credit = newCredit; strcpy(p->data.CourseName, newName);
            p->data.teacherCount = n;
            for (int j = 0; j < n; j++) p->data.Teacherids[j] = tids[j];
            saveToFile(); printf("修改成功!\n"); return;
        }
        p = p->next;
    }
    printf("未找到课程代码为 %lld 的课程\n", id);
}

char* Course_getName(long long id) {
    struct CourseNode *p = head;
    while (p) {
        if (p->data.Courseid == id) return p->data.CourseName;
        p = p->next;
    }
    return "未知课程";
}

int Course_hasData() { return head != NULL; }
void deleteCourse(long long id) {
    if (head == NULL) { printf("目前无课程数据存入\n"); return; }
    struct CourseNode *p = head;
    if (p->data.Courseid == id) { head = head->next; free(p); saveToFile(); printf("删除成功!\n"); return; }
    while (p->next != NULL) {
        if (p->next->data.Courseid == id) {
            struct CourseNode *temp = p->next; p->next = p->next->next; free(temp);
            saveToFile(); printf("删除成功!\n"); return;
        }
        p = p->next;
    }
    printf("未找到课程代码为 %lld 的课程\n", id);
}
void Course_free() {
    struct CourseNode *p = head;
    while (p != NULL) { struct CourseNode *temp = p; p = p->next; free(temp); }
    head = NULL;
}
