@echo off
cd /d "%~dp0"
taskkill /f /im school.exe 2>nul
gcc -fexec-charset=gbk -o school main.c teacher.c student.c course.c
school.exe
pause