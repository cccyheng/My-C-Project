#include "teacher.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static struct TeacherNode *head = NULL;

static void saveToFile() {
    FILE *fp = fopen("teacher.txt", "w");
    if (fp == NULL) {
        printf("无法打开文件!\n");
        return;
    }
    struct TeacherNode *p = head;
    while (p != NULL) {
        fprintf(fp, "%lld %s %s\n",
                p->data.Teacherid,
                p->data.Name,
                p->data.Subject);
        p = p->next;
    }
    fclose(fp);
}

static void loadFromFile() {
    FILE *fp = fopen("teacher.txt", "r");
    if (fp == NULL) {
        return;
    }
    long long id;
    char name[20], subject[50];
    struct TeacherNode *tail = NULL;
    while (fscanf(fp, "%lld %s %s", &id, name, subject) == 3) {
        struct TeacherNode *newNode = malloc(sizeof(*newNode));
        newNode->data.Teacherid = id;
        strcpy(newNode->data.Name, name);
        strcpy(newNode->data.Subject, subject);
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

void Teacher_init() {
    loadFromFile();
}

void addTeacher(long long Teacherid, char Name[], char Subject[]) {
    struct TeacherNode *newNode = malloc(sizeof(*newNode));
    newNode->data.Teacherid = Teacherid;
    strcpy(newNode->data.Name, Name);
    strcpy(newNode->data.Subject, Subject);
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        struct TeacherNode *p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newNode;
    }
    saveToFile();
}

void listAllTeacher() {
    if (head == NULL) {
        printf("目前无老师数据存入\n");
        return;
    }
    struct TeacherNode *p = head;
    while (p != NULL) {
        printf("%lld %s %s\n",
               p->data.Teacherid,
               p->data.Name,
               p->data.Subject);
        p = p->next;
    }
}

void Teacher_idSearch(long long id) {
    if (head == NULL) {
        printf("目前无老师数据存入\n");
        return;
    }
    struct TeacherNode *p = head;
    while (p != NULL) {
        if (p->data.Teacherid == id) {
            printf("工号: %lld  姓名: %s  科目: %s\n",
                   p->data.Teacherid,
                   p->data.Name,
                   p->data.Subject);
            return;
        }
        p = p->next;
    }
    printf("未找到工号为 %lld 的教师\n", id);
}

void Teacher_nameSearch(char name[]) {
    if (head == NULL) {
        printf("目前无老师数据存入\n");
        return;
    }
    int found = 0;
    struct TeacherNode *p = head;
    while (p != NULL) {
        if (strcmp(p->data.Name, name) == 0) {
            printf("工号: %lld  姓名: %s  科目: %s\n",
                   p->data.Teacherid,
                   p->data.Name,
                   p->data.Subject);
            found = 1;
        }
        p = p->next;
    }
    if (!found) {
        printf("未找到名字为 %s 的教师\n", name);
    }
}

void editTeacher(long long id) {
    if (head == NULL) {
        printf("目前无老师数据存入\n");
        return;
    }
    struct TeacherNode *p = head;
    while (p != NULL) {
        if (p->data.Teacherid == id) {
            char newName[20], newSubject[50];
            printf("请输入新的姓名: ");
            scanf("%s", newName);
            printf("请输入新的科目: ");
            scanf("%s", newSubject);
            strcpy(p->data.Name, newName);
            strcpy(p->data.Subject, newSubject);
            saveToFile();
            printf("修改成功!\n");
            return;
        }
        p = p->next;
    }
    printf("未找到工号为 %lld 的教师\n", id);
}

int Teacher_hasData() {
    return head != NULL;
}

void deleteTeacher(long long id) {
    if (head == NULL) {
        printf("目前无老师数据存入\n");
        return;
    }
    struct TeacherNode *p = head;
    if (p->data.Teacherid == id) {
        head = head->next;
        free(p);
        saveToFile();
        printf("删除成功!\n");
        return;
    }
    while (p->next != NULL) {
        if (p->next->data.Teacherid == id) {
            struct TeacherNode *temp = p->next;
            p->next = p->next->next;
            free(temp);
            saveToFile();
            printf("删除成功!\n");
            return;
        }
        p = p->next;
    }
    printf("未找到工号为 %lld 的教师\n", id);
}

char* Teacher_getName(long long id) {
    struct TeacherNode *p = head;
    while (p != NULL) {
        if (p->data.Teacherid == id)
            return p->data.Name;
        p = p->next;
    }
    return "未知教师";
}

void Teacher_free() {
    struct TeacherNode *p = head;
    while (p != NULL) {
        struct TeacherNode *temp = p;
        p = p->next;
        free(temp);
    }
    head = NULL;
}
