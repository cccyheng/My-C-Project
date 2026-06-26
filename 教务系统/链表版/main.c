#include <stdio.h>
#include "teacher.h"
#include "student.h"
#include "course.h"

int main() {
    Teacher_init();
    Student_init();
    Course_init();
    int choice;

    while (1) {
        printf("\n===== 学校信息管理系统(链表版) =====\n");
        printf("1. 教师管理\n");
        printf("2. 学生管理\n");
        printf("3. 课程管理\n");
        printf("4. 退出\n");
        printf("请选择: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int subChoice;
            while (1) {
                printf("\n===== 教师管理 =====\n");
                printf("1. 添加教师\n");
                printf("2. 列出所有教师\n");
                printf("3. 按工号查找\n");
                printf("4. 按姓名查找\n");
                printf("5. 修改教师\n");
                printf("6. 删除教师\n");
                printf("7. 返回主菜单\n");
                printf("请选择: ");
                scanf("%d", &subChoice);

                if (subChoice == 1) {
                    long long id;
                    char name[20], subject[50];
                    printf("请输入工号: ");
                    scanf("%lld", &id);
                    printf("请输入姓名: ");
                    scanf("%s", name);
                    printf("请输入科目: ");
                    scanf("%s", subject);
                    addTeacher(id, name, subject);
                    printf("添加成功!\n");
                } else if (subChoice == 2) {
                    listAllTeacher();
                } else if (subChoice == 3) {
                    if (!Teacher_hasData()) { printf("目前无老师数据存入\n"); continue; }
                    long long id;
                    printf("请输入工号: ");
                    scanf("%lld", &id);
                    Teacher_idSearch(id);
                } else if (subChoice == 4) {
                    if (!Teacher_hasData()) { printf("目前无老师数据存入\n"); continue; }
                    char name[20];
                    printf("请输入姓名: ");
                    scanf("%s", name);
                    Teacher_nameSearch(name);
                } else if (subChoice == 5) {
                    if (!Teacher_hasData()) { printf("目前无老师数据存入\n"); continue; }
                    long long id;
                    printf("请输入要修改的工号: ");
                    scanf("%lld", &id);
                    editTeacher(id);
                } else if (subChoice == 6) {
                    if (!Teacher_hasData()) { printf("目前无老师数据存入\n"); continue; }
                    long long id;
                    printf("请输入要删除的工号: ");
                    scanf("%lld", &id);
                    deleteTeacher(id);
                } else if (subChoice == 7) {
                    break;
                } else {
                    printf("输入错误, 请重新选择\n");
                }
            }
        } else if (choice == 2) {
            int subChoice;
            while (1) {
                printf("\n===== 学生管理 =====\n");
                printf("1. 添加学生\n");
                printf("2. 列出所有学生\n");
                printf("3. 按学号查找\n");
                printf("4. 按姓名查找\n");
                printf("5. 修改学生\n");
                printf("6. 删除学生\n");
                printf("7. 成绩录入\n");
                printf("8. 查看成绩\n");
                printf("9. 总分排名\n");
                printf("10. 单科排名\n");
                printf("11. 学生选课\n");
                printf("12. 查看选课\n");
                printf("13. 返回主菜单\n");
                printf("请选择: ");
                scanf("%d", &subChoice);

                if (subChoice == 1) {
                    long long id; int classNum, grade;
                    char name[20], major[50];
                    printf("请输入学号: ");
                    scanf("%lld", &id);
                    printf("请输入班级: ");
                    scanf("%d", &classNum);
                    printf("请输入年级: ");
                    scanf("%d", &grade);
                    printf("请输入姓名: ");
                    scanf("%s", name);
                    printf("请输入专业: ");
                    scanf("%s", major);
                    addStudent(id, classNum, grade, name, major);
                    printf("添加成功!\n");
                } else if (subChoice == 2) {
                    listAllStudent();
                } else if (subChoice == 3) {
                    if (!Student_hasData()) { printf("目前无学生数据存入\n"); continue; }
                    long long id;
                    printf("请输入学号: ");
                    scanf("%lld", &id);
                    Student_idSearch(id);
                } else if (subChoice == 4) {
                    if (!Student_hasData()) { printf("目前无学生数据存入\n"); continue; }
                    char name[20];
                    printf("请输入姓名: ");
                    scanf("%s", name);
                    Student_nameSearch(name);
                } else if (subChoice == 5) {
                    if (!Student_hasData()) { printf("目前无学生数据存入\n"); continue; }
                    long long id;
                    printf("请输入要修改的学号: ");
                    scanf("%lld", &id);
                    editStudent(id);
                } else if (subChoice == 6) {
                    if (!Student_hasData()) { printf("目前无学生数据存入\n"); continue; }
                    long long id;
                    printf("请输入要删除的学号: ");
                    scanf("%lld", &id);
                    deleteStudent(id);
                } else if (subChoice == 7) {
                    if (!Student_hasData()) { printf("目前无学生数据存入\n"); continue; }
                    long long id;
                    printf("请输入要录入成绩的学号: ");
                    scanf("%lld", &id);
                    scoreInput(id);
                } else if (subChoice == 8) {
                    if (!Student_hasData()) { printf("目前无学生数据存入\n"); continue; }
                    long long id;
                    printf("请输入要查看成绩的学号: ");
                    scanf("%lld", &id);
                    scoreShow(id);
                } else if (subChoice == 9) {
                    if (!Student_hasData()) { printf("目前无学生数据存入\n"); continue; }
                    rankByTotal();
                } else if (subChoice == 10) {
                    if (!Student_hasData()) { printf("目前无学生数据存入\n"); continue; }
                    int sub;
                    printf("选择科目(1-高数 2-C语言 3-线代 4-大物 5-Java): ");
                    scanf("%d", &sub);
                    rankBySubject(sub);
                } else if (subChoice == 11) {
                    if (!Student_hasData()) { printf("目前无学生数据存入\n"); continue; }
                    long long sid, cid;
                    printf("请输入学生学号: "); scanf("%lld", &sid);
                    printf("请输入课程代码: "); scanf("%lld", &cid);
                    enrollCourse(sid, cid);
                } else if (subChoice == 12) {
                    if (!Student_hasData()) { printf("目前无学生数据存入\n"); continue; }
                    long long sid;
                    printf("请输入学生学号: "); scanf("%lld", &sid);
                    showStudentCourses(sid);
                } else if (subChoice == 13) {
                    break;
                } else {
                    printf("输入错误, 请重新选择\n");
                }
            }
        } else if (choice == 3) {
            int subChoice;
            while (1) {
                printf("\n===== 课程管理 =====\n");
                printf("1. 添加课程\n");
                printf("2. 列出所有课程\n");
                printf("3. 按课程代码查找\n");
                printf("4. 按课程名称查找\n");
                printf("5. 修改课程\n");
                printf("6. 删除课程\n");
                printf("7. 查看选课学生\n");
                printf("8. 科目成绩排名\n");
                printf("9. 返回主菜单\n");
                printf("请选择: ");
                scanf("%d", &subChoice);

                if (subChoice == 1) {
                    long long id; int credit, n;
                    char name[50];
                    long long tids[5];
                    printf("请输入课程代码: ");
                    scanf("%lld", &id);
                    printf("请输入学分: ");
                    scanf("%d", &credit);
                    printf("请输入课程名称: ");
                    scanf("%s", name);
                    printf("请输入授课教师人数: ");
                    scanf("%d", &n);
                    for (int j = 0; j < n; j++) {
                        printf("请输入第%d位教师工号: ", j+1);
                        scanf("%lld", &tids[j]);
                    }
                    addCourse(id, credit, name, n, tids);
                    printf("添加成功!\n");
                } else if (subChoice == 2) {
                    listAllCourse();
                } else if (subChoice == 3) {
                    if (!Course_hasData()) { printf("目前无课程数据存入\n"); continue; }
                    long long id;
                    printf("请输入课程代码: ");
                    scanf("%lld", &id);
                    Course_idSearch(id);
                } else if (subChoice == 4) {
                    if (!Course_hasData()) { printf("目前无课程数据存入\n"); continue; }
                    char name[50];
                    printf("请输入课程名称: ");
                    scanf("%s", name);
                    Course_nameSearch(name);
                } else if (subChoice == 5) {
                    if (!Course_hasData()) { printf("目前无课程数据存入\n"); continue; }
                    long long id;
                    printf("请输入要修改的课程代码: ");
                    scanf("%lld", &id);
                    editCourse(id);
                } else if (subChoice == 6) {
                    if (!Course_hasData()) { printf("目前无课程数据存入\n"); continue; }
                    long long id;
                    printf("请输入要删除的课程代码: ");
                    scanf("%lld", &id);
                    deleteCourse(id);
                } else if (subChoice == 7) {
                    if (!Course_hasData()) { printf("目前无课程数据存入\n"); continue; }
                    long long cid;
                    printf("请输入课程代码: "); scanf("%lld", &cid);
                    showCourseStudents(cid);
                } else if (subChoice == 8) {
                    if (!Student_hasData()) { printf("目前无学生数据存入\n"); continue; }
                    int sub;
                    printf("选择科目(1-高数 2-C语言 3-线代 4-大物 5-Java): ");
                    scanf("%d", &sub);
                    rankBySubject(sub);
                } else if (subChoice == 9) {
                    break;
                } else {
                    printf("输入错误, 请重新选择\n");
                }
            }
        } else if (choice == 4) {
            Teacher_free();
                Student_free();
                Course_free();
                printf("感谢使用, 再见!\n");
                break;
        } else {
            printf("输入错误, 请重新选择(1-4)\n");
        }
    }
    return 0;
}
                                                                                                                                                                                                                                                                                                           