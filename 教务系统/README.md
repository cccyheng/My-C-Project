# 学校信息管理系统（C语言实训）

## 项目结构
- `数组版/` - 基于数组存储的学校信息管理系统
- `链表版/` - 基于链表存储的学校信息管理系统

## 编译运行
### 数组版
```
cd 数组版
gcc -o school main.c teacher.c student.c course.c
school.exe
```

### 链表版
```
cd 链表版
gcc -o school main.c teacher.c student.c course.c
school.exe
```

## 功能
- 教师管理（增删改查）
- 学生管理（增删改查、成绩录入、排名）
- 课程管理（增删改查、多教师）
- 学生选课
- 数据持久化（文件存储）
