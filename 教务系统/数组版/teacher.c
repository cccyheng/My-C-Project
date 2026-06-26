#include"teacher.h"
#include <string.h>
#include <stdio.h>
#define MAX_TEACHERS 100
struct Teacher teachers[MAX_TEACHERS];
int TeacherNum = 0;
static void saveToFile() {
    FILE *fp = fopen("teacher.txt", "w");
    if (fp == NULL) {
        printf("无法打开文件!\n");
        return;
    }
    for (int i = 0; i < TeacherNum; i++) {
        fprintf(fp, "%lld %s %s\n",
                teachers[i].Teacherid,
                teachers[i].Name,
                teachers[i].Subject);
    }
    fclose(fp);
}
static void loadFromFile() {
    FILE *fp = fopen("teacher.txt", "r");
    if (fp == NULL) {
        return;
    }
    TeacherNum = 0;
    while (fscanf(fp, "%lld %s %s",
              &teachers[TeacherNum].Teacherid,
              teachers[TeacherNum].Name,
              teachers[TeacherNum].Subject) == 3) {
                TeacherNum++;
}
    fclose(fp);
}
void Teacher_init() {
    loadFromFile();
}
void addTeacher(long long Teacherid, char Name[], char Subject[]) {
    if (TeacherNum >= MAX_TEACHERS) { printf("教师已满!\n"); return; }
    teachers[TeacherNum].Teacherid = Teacherid;
    strcpy(teachers[TeacherNum].Name,Name);
    strcpy(teachers[TeacherNum].Subject,Subject);
    TeacherNum++;
    saveToFile();
}
void listAllTeacher() {
    if(TeacherNum == 0){
        printf("目前无老师数据存入\n");
    }
    else{
        for (int i = 0; i < TeacherNum; i++) {
            printf("%lld %s %s\n",
                teachers[i].Teacherid,
                teachers[i].Name,
                teachers[i].Subject);
        }
    }
}
void Teacher_idSearch(long long id) {
    if (TeacherNum == 0) {
        printf("目前无老师数据存入\n");
        return;
    }
    for (int i = 0; i < TeacherNum; i++) {
        if (teachers[i].Teacherid == id) {
            printf("工号: %lld  姓名: %s  科目: %s\n",
                   teachers[i].Teacherid,
                   teachers[i].Name,
                   teachers[i].Subject);
            return;
        }
    }
    printf("未找到工号为 %lld 的教师\n", id);
}
void Teacher_nameSearch(char name[]){
    if (TeacherNum == 0) {
        printf("目前无老师数据存入\n");
        return;
    }
    int found = 0;
    for (int i = 0; i < TeacherNum; i++) {
        if (strcmp(teachers[i].Name, name) == 0) {
            printf("工号: %lld  姓名: %s  科目: %s\n",
                   teachers[i].Teacherid,
                   teachers[i].Name,
                   teachers[i].Subject);
            found = 1;
        }
    }
    if(!found){
        printf("未找到名字为 %s 的教师\n", name);
    }
}
void editTeacher(long long id) {
    if (TeacherNum == 0) {
        printf("目前无老师数据存入\n");
        return;
    }
    for (int i = 0; i < TeacherNum; i++) {
        if (teachers[i].Teacherid == id) {
            char newName[20], newSubject[50];
            printf("请输入新的姓名: ");
            scanf("%s", newName);
            printf("请输入新的科目: ");
            scanf("%s", newSubject);
            strcpy(teachers[i].Name, newName);
            strcpy(teachers[i].Subject, newSubject);
            saveToFile();
            printf("修改成功!\n");
            return;
        }
    }
    printf("未找到工号为 %lld 的教师\n", id);
}
int Teacher_hasData() {
    return TeacherNum > 0;
}

char* Teacher_getName(long long id) {
    for (int i = 0; i < TeacherNum; i++)
        if (teachers[i].Teacherid == id) return teachers[i].Name;
    return "未知教师";
}

void deleteTeacher(long long id) {
    if (TeacherNum == 0) {
        printf("目前无老师数据存入\n");
        return;
    }
    int found = 0;
    for (int i = 0; i < TeacherNum; i++) {
        if (teachers[i].Teacherid == id) {
            for (int j = i; j < TeacherNum - 1; j++) {
                teachers[j] = teachers[j + 1];
            }
            TeacherNum--;
            saveToFile();
            printf("删除成功!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("未找到工号为 %lld 的教师\n", id);
    }
}