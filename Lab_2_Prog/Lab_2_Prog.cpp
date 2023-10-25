#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Структура "Студент"
struct Student {
    char firstName[50];
    char lastName[50];
    int age;
    char studentID[20];
    double mathGrade;
    double russianGrade;
    double physicsGrade;
};

// Структура "Оценка"
struct Grade {
    char subject[20];
    double grade;
};

// Структура "Группа"
struct Group {
    char groupName[50];
    int numStudents;
    struct Student students[100];
};

// Функция для создания структуры "Студент"
struct Student createStudent() {
    struct Student student;
    printf("Введите имя студента: ");
    scanf("%s", student.firstName);
    printf("Введите фамилию студента: ");
    scanf("%s", student.lastName);
    printf("Введите возраст студента: ");
    scanf("%d", &student.age);
    printf("Введите номер студенческого билета: ");
    scanf("%s", student.studentID);

    student.mathGrade = -1.0;  // Инициализируем оценки значением -1 (отсутствие оценки)
    student.russianGrade = -1.0;
    student.physicsGrade = -1.0;

    return student;
}

// Функция для создания структуры "Оценка"
struct Grade createGrade() {
    struct Grade grade;
    int subjectChoice;

    do {
        printf("Выберите предмет:\n");
        printf("1. Математика\n");
        printf("2. Русский\n");
        printf("3. Физика\n");
        printf("Введите номер предмета (1-3): ");
        scanf("%d", &subjectChoice);
    } while (subjectChoice < 1 || subjectChoice > 3);

    switch (subjectChoice) {
    case 1:
        strcpy(grade.subject, "Математика");
        break;
    case 2:
        strcpy(grade.subject, "Русский");
        break;
    case 3:
        strcpy(grade.subject, "Физика");
        break;
    default:
        strcpy(grade.subject, "Недопустимый предмет");
        break;
    }

    printf("Введите оценку: ");
    scanf("%lf", &grade.grade);

    return grade;
}


// Функция для добавления оценки студенту в группе
void addGradeToStudent(struct Student* student, struct Grade grade) {
    if (strcmp(grade.subject, "Математика") == 0) {
        student->mathGrade = grade.grade;
    }
    else if (strcmp(grade.subject, "Русский") == 0) {
        student->russianGrade = grade.grade;
    }
    else if (strcmp(grade.subject, "Физика") == 0) {
        student->physicsGrade = grade.grade;
    }
}

// Функция для расчета средней оценки студента
double calculateAverageGrade(struct Student student) {
    double sum = 0.0;
    int numSubjects = 0;

    if (student.mathGrade >= 0.0) {
        sum += student.mathGrade;
        numSubjects++;
    }

    if (student.russianGrade >= 0.0) {
        sum += student.russianGrade;
        numSubjects++;
    }

    if (student.physicsGrade >= 0.0) {
        sum += student.physicsGrade;
        numSubjects++;
    }

    if (numSubjects == 0) {
        return -1.0; // Нет оценок
    }

    return sum / numSubjects;
}

// Функция для вывода информации о студенте в консоль
void printStudent(struct Student student) {
    printf("Имя: %s\n", student.firstName);
    printf("Фамилия: %s\n", student.lastName);
    printf("Возраст: %d\n", student.age);
    printf("Номер студенческого билета: %s\n", student.studentID);
    printf("Оценки:\n");
    if (student.mathGrade >= 0.0) {
        printf("Математика: %.1lf\n", student.mathGrade);
    }
    if (student.russianGrade >= 0.0) {
        printf("Русский: %.1lf\n", student.russianGrade);
    }
    if (student.physicsGrade >= 0.0) {
        printf("Физика: %.1lf\n", student.physicsGrade);
    }
    double average = calculateAverageGrade(student);
    if (average >= 0.0) {
        printf("Средний балл: %.1lf\n", average);
    }
    else {
        printf("Средний балл: Нет данных\n");
    }
}

// Функция для вывода информации о группе в консоль
void printGroup(struct Group group) {
    printf("Название группы: %s\n", group.groupName);
    printf("Количество студентов: %d\n", group.numStudents);
    printf("Список студентов:\n");
    for (int i = 0; i < group.numStudents; i++) {
        printf("Студент %d:\n", i + 1);
        printStudent(group.students[i]);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    struct Group group;
    printf("Введите название группы: ");
    scanf("%s", group.groupName);
    group.numStudents = 0;

    int choice;
    do {
        printf("\nМеню:\n");
        printf("1. Добавить студента\n");
        printf("2. Добавить оценку студенту\n");
        printf("3. Вывести информацию о студенте\n");
        printf("4. Вывести информацию о группе\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: // Добавить студента
            if (group.numStudents < 100) {
                group.students[group.numStudents] = createStudent();
                group.numStudents++;
            }
            else {
                printf("Достигнуто максимальное количество студентов в группе.\n");
            }
            break;

        case 2: // Добавить оценку студенту
            if (group.numStudents > 0) {
                printf("Введите номер студенческого билета студента: ");
                char studentID[20];
                scanf("%s", studentID);
                int found = 0;
                for (int i = 0; i < group.numStudents; i++) {
                    if (strcmp(group.students[i].studentID, studentID) == 0) {
                        struct Grade grade = createGrade();
                        addGradeToStudent(&group.students[i], grade);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Студент с таким номером студенческого билета не найден.\n");
                }
            }
            else {
                printf("В группе нет студентов.\n");
            }
            break;

        case 3: // Вывести информацию о студенте
            if (group.numStudents > 0) {
                printf("Введите номер студента (1-%d): ", group.numStudents);
                int studentNum;
                scanf("%d", &studentNum);
                if (studentNum >= 1 && studentNum <= group.numStudents) {
                    printf("Информация о студенте %d:\n", studentNum);
                    printStudent(group.students[studentNum - 1]);
                }
                else {
                    printf("Неправильный номер студента.\n");
                }
            }
            else {
                printf("В группе нет студентов.\n");
            }
            break;

        case 4: // Вывести информацию о группе
            if (group.numStudents > 0) {
                printf("Информация о группе:\n");
                printGroup(group);
            }
            else {
                printf("В группе нет студентов.\n");
            }
            break;

        case 0: // Выход
            break;

        default:
            printf("Неправильный выбор. Попробуйте снова.\n");
            break;
        }
    } while (choice != 0);

    return 0;
}