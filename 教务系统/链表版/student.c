#include "student.h"
#include "course.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static struct StudentNode *head = NULL;

static void saveToFile() {
    FILE *fp = fopen("student.txt", "w");
    if (fp == NULL) {
        printf("无法打开文件!\n");
        return;
    }
    struct StudentNode *p = head;
    while (p != NULL) {
        fprintf(fp, "%lld %d %d %s %s %d %d %d %d %d %d\n",
                p->data.Studentid,
                p->data.Class,
                p->data.Grade,
                p->data.Name,
                p->data.Major,
                p->data.score_math,
                p->data.score_c,
                p->data.score_linear,
                p->data.score_physics,
                p->data.score_java,
                p->data.totalScore);
        p = p->next;
    }
    fclose(fp);
}

static void loadFromFile() {
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL) {
        return;
    }
    long long id;
    int classNum, grade;
    char name[20], major[50];
    int sm, sc, sl, sp, sj, total, cnt2;
    struct StudentNode *tail = NULL;
    while (fscanf(fp, "%lld %d %d %s %s %d %d %d %d %d %d %d",
                  &id, &classNum, &grade, name, major,
                  &sm, &sc, &sl, &sp, &sj, &total, &cnt2) == 12) {
        struct StudentNode *newNode = malloc(sizeof(*newNode));
        newNode->data.Studentid = id;
        newNode->data.Class = classNum;
        newNode->data.Grade = grade;
        strcpy(newNode->data.Name, name);
        strcpy(newNode->data.Major, major);
        newNode->data.score_math = sm;
        newNode->data.score_c = sc;
        newNode->data.score_linear = sl;
        newNode->data.score_physics = sp;
        newNode->data.score_java = sj;
        newNode->data.totalScore = total;
        newNode->data.courseCount = cnt2;
        for (int k = 0; k < cnt2; k++) fscanf(fp, "%lld", &newNode->data.courseIds[k]);
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    fclose(fp);
}

void Student_init() {
    loadFromFile();
}

void addStudent(long long Studentid, int Class, int Grade, char Name[], char Major[]) {
    struct StudentNode *newNode = malloc(sizeof(*newNode));
    newNode->data.Studentid = Studentid;
    newNode->data.Class = Class;
    newNode->data.Grade = Grade;
    strcpy(newNode->data.Name, Name);
    strcpy(newNode->data.Major, Major);
    newNode->data.score_math = 0;
    newNode->data.score_c = 0;
    newNode->data.score_linear = 0;
    newNode->data.score_physics = 0;
    newNode->data.score_java = 0;
    newNode->data.totalScore = 0;
    newNode->data.courseCount = 0;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        struct StudentNode *p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newNode;
    }
    saveToFile();
}

void listAllStudent() {
    if (head == NULL) {
        printf("目前无学生数据存入\n");
        return;
    }
    printf("%-13s %-4s %-4s %-10s %-10s %-6s %-6s %-6s %-6s %-6s %-6s\n",
           "学号","班级","年级","姓名","专业","高数","C语言","线代","大物","Java","总分");
    struct StudentNode *p = head;
    while (p != NULL) {
        printf("%-11lld %-4d %-4d %-10s %-10s %-6d %-6d %-6d %-6d %-6d %-6d\n",
               p->data.Studentid, p->data.Class, p->data.Grade,
               p->data.Name, p->data.Major,
               p->data.score_math, p->data.score_c, p->data.score_linear,
               p->data.score_physics, p->data.score_java, p->data.totalScore);
        p = p->next;
    }
}

void Student_idSearch(long long id) {
    if (head == NULL) {
        printf("目前无学生数据存入\n");
        return;
    }
    struct StudentNode *p = head;
    while (p != NULL) {
        if (p->data.Studentid == id) {
            printf("学号: %lld  班级: %d  年级: %d  姓名: %s  专业: %s\n",
                   p->data.Studentid, p->data.Class, p->data.Grade,
                   p->data.Name, p->data.Major);
            printf("高数: %d  C语言: %d  线代: %d  大物: %d  Java: %d\n",
                   p->data.score_math, p->data.score_c, p->data.score_linear,
                   p->data.score_physics, p->data.score_java);
            printf("总分: %d\n", p->data.totalScore);
            return;
        }
        p = p->next;
    }
    printf("未找到学号为 %lld 的学生\n", id);
}

void Student_nameSearch(char name[]) {
    if (head == NULL) {
        printf("目前无学生数据存入\n");
        return;
    }
    int found = 0;
    struct StudentNode *p = head;
    while (p != NULL) {
        if (strcmp(p->data.Name, name) == 0) {
            printf("学号: %lld  班级: %d  年级: %d  姓名: %s  专业: %s\n",
                   p->data.Studentid, p->data.Class, p->data.Grade,
                   p->data.Name, p->data.Major);
            printf("高数: %d  C语言: %d  线代: %d  大物: %d  Java: %d  总分: %d\n",
                   p->data.score_math, p->data.score_c, p->data.score_linear,
                   p->data.score_physics, p->data.score_java, p->data.totalScore);
            found = 1;
        }
        p = p->next;
    }
    if (!found) {
        printf("未找到名字为 %s 的学生\n", name);
    }
}

void editStudent(long long id) {
    if (head == NULL) {
        printf("目前无学生数据存入\n");
        return;
    }
    struct StudentNode *p = head;
    while (p != NULL) {
        if (p->data.Studentid == id) {
            int newClass, newGrade;
            char newName[20], newMajor[50];
            printf("请输入新的班级: ");
            scanf("%d", &newClass);
            printf("请输入新的年级: ");
            scanf("%d", &newGrade);
            printf("请输入新的姓名: ");
            scanf("%s", newName);
            printf("请输入新的专业: ");
            scanf("%s", newMajor);
            p->data.Class = newClass;
            p->data.Grade = newGrade;
            strcpy(p->data.Name, newName);
            strcpy(p->data.Major, newMajor);
            saveToFile();
            printf("修改成功!\n");
            return;
        }
        p = p->next;
    }
    printf("未找到学号为 %lld 的学生\n", id);
}

void deleteStudent(long long id) {
    if (head == NULL) {
        printf("目前无学生数据存入\n");
        return;
    }
    struct StudentNode *p = head;
    if (p->data.Studentid == id) {
        head = head->next;
        free(p);
        saveToFile();
        printf("删除成功!\n");
        return;
    }
    while (p->next != NULL) {
        if (p->next->data.Studentid == id) {
            struct StudentNode *temp = p->next;
            p->next = p->next->next;
            free(temp);
            saveToFile();
            printf("删除成功!\n");
            return;
        }
        p = p->next;
    }
    printf("未找到学号为 %lld 的学生\n", id);
}

int Student_hasData() {
    return head != NULL;
}

void scoreInput(long long id) {
    if (head == NULL) {
        printf("目前无学生数据存入\n");
        return;
    }
    struct StudentNode *p = head;
    while (p != NULL) {
        if (p->data.Studentid == id) {
            printf("请输入 %s 的成绩:\n", p->data.Name);
            printf("高数: "); scanf("%d", &p->data.score_math);
            printf("C语言: "); scanf("%d", &p->data.score_c);
            printf("线代: "); scanf("%d", &p->data.score_linear);
            printf("大物: "); scanf("%d", &p->data.score_physics);
            printf("Java: "); scanf("%d", &p->data.score_java);
            p->data.totalScore = p->data.score_math + p->data.score_c
                               + p->data.score_linear + p->data.score_physics
                               + p->data.score_java;
            saveToFile();
            printf("成绩录入成功! 总分: %d\n", p->data.totalScore);
            return;
        }
        p = p->next;
    }
    printf("未找到学号为 %lld 的学生\n", id);
}

void scoreShow(long long id) {
    if (head == NULL) {
        printf("目前无学生数据存入\n");
        return;
    }
    struct StudentNode *p = head;
    while (p != NULL) {
        if (p->data.Studentid == id) {
            printf("\n======== %s 的成绩单 ========\n", p->data.Name);
            printf("高数: %d\n", p->data.score_math);
            printf("C语言: %d\n", p->data.score_c);
            printf("线代: %d\n", p->data.score_linear);
            printf("大物: %d\n", p->data.score_physics);
            printf("Java: %d\n", p->data.score_java);
            printf("总分: %d\n", p->data.totalScore);
            return;
        }
        p = p->next;
    }
    printf("未找到学号为 %lld 的学生\n", id);
}

void rankByTotal() {
    if (head == NULL) {
        printf("目前无学生数据存入\n");
        return;
    }
    int count = 0;
    struct StudentNode *p = head;
    while (p != NULL) { count++; p = p->next; }

    struct Student *arr = malloc(sizeof(*arr) * count);
    p = head;
    for (int i = 0; i < count; i++) {
        arr[i] = p->data;
        p = p->next;
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (arr[j].totalScore < arr[j+1].totalScore) {
                struct Student t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t;
            }
        }
    }
    printf("\n======== 总分排名 ========\n");
    printf("%-6s %-13s %-10s %-6s\n", "排名", "学号", "姓名", "总分");
    for (int i = 0; i < count; i++) {
        printf("%-6d %-11lld %-10s %-6d\n",
               i+1, arr[i].Studentid, arr[i].Name, arr[i].totalScore);
    }
    free(arr);
}

void rankBySubject(int subject) {
    if (head == NULL) {
        printf("目前无学生数据存入\n");
        return;
    }
    if (subject < 1 || subject > 5) {
        printf("科目选择错误!\n");
        return;
    }
    char *subNames[] = {"", "高数", "C语言", "线代", "大物", "Java"};
    char *subName = subNames[subject];

    int count = 0;
    struct StudentNode *p = head;
    while (p != NULL) { count++; p = p->next; }

    struct Student *arr = malloc(sizeof(*arr) * count);
    p = head;
    for (int i = 0; i < count; i++) {
        arr[i] = p->data;
        p = p->next;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            int a, b;
            if (subject == 1) { a = arr[j].score_math; b = arr[j+1].score_math; }
            else if (subject == 2) { a = arr[j].score_c; b = arr[j+1].score_c; }
            else if (subject == 3) { a = arr[j].score_linear; b = arr[j+1].score_linear; }
            else if (subject == 4) { a = arr[j].score_physics; b = arr[j+1].score_physics; }
            else { a = arr[j].score_java; b = arr[j+1].score_java; }
            if (a < b) {
                struct Student t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t;
            }
        }
    }

    printf("\n======== %s排名 ========\n", subName);
    printf("%-6s %-13s %-10s %-6s\n", "排名", "学号", "姓名", subName);
    for (int i = 0; i < count; i++) {
        int score;
        if (subject == 1) score = arr[i].score_math;
        else if (subject == 2) score = arr[i].score_c;
        else if (subject == 3) score = arr[i].score_linear;
        else if (subject == 4) score = arr[i].score_physics;
        else score = arr[i].score_java;
        printf("%-6d %-11lld %-10s %-6d\n",
               i+1, arr[i].Studentid, arr[i].Name, score);
    }
    free(arr);
}
void Student_free() {
    struct StudentNode *p = head;
    while (p != NULL) {
        struct StudentNode *temp = p;
        p = p->next;
        free(temp);
    }
    head = NULL;
}

void enrollCourse(long long sid, long long cid) {
    struct Student *s = NULL;
    int n = 0;
    struct StudentNode *p = head;
    while (p) { if (p->data.Studentid == sid) { s = &p->data; break; } p = p->next; }
    if (s == NULL) { printf("未找到该学生!\n"); return; }
    if (s->courseCount >= 10) { printf("已选课程已满!\n"); return; }
    for (int i = 0; i < s->courseCount; i++)
        if (s->courseIds[i] == cid) { printf("该课程已选!\n"); return; }
    s->courseIds[s->courseCount++] = cid;
    saveToFile();
    printf("选课成功!\n");
}

void showStudentCourses(long long id) {
    struct StudentNode *p = head;
    while (p) {
        if (p->data.Studentid == id) {
            printf("学生 %s(%lld) 已选课程:\n", p->data.Name, p->data.Studentid);
            for (int j = 0; j < p->data.courseCount; j++)
                printf("  %lld %s\n", p->data.courseIds[j], Course_getName(p->data.courseIds[j]));
            printf("\n"); return;
        }
        p = p->next;
    }
    printf("未找到该学生!\n");
}

void showCourseStudents(long long cid) {
    printf("选了课程 %lld 的学生:\n", cid);
    int found = 0;
    struct StudentNode *p = head;
    while (p) {
        for (int j = 0; j < p->data.courseCount; j++) {
            if (p->data.courseIds[j] == cid) {
                printf("  %lld %s\n", p->data.Studentid, p->data.Name);
                found = 1; break;
            }
        }
        p = p->next;
    }
    if (!found) printf("  暂无学生选这门课\n");
}
                    