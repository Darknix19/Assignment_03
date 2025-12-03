#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "members.dat"

typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];
    char membershipType[10];
    char regDate[11];
    char dob[11];
    char interest[10];
} Student;

// Global dynamic array
Student *students = NULL;
int studentCount = 0;



void loadDatabase(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("No existing database found. Starting fresh.\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    studentCount = size / sizeof(Student);

    students = malloc(size);
    if (!students) {
        printf("Memory allocation failed while loading database.\n");
        fclose(fp);
        exit(1);
    }

    fread(students, sizeof(Student), studentCount, fp);
    fclose(fp);

    printf("Loaded %d records from database.\n", studentCount);
}

void saveDatabase(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error: Could not save database.\n");
        return;
    }

    fwrite(students, sizeof(Student), studentCount, fp);
    fclose(fp);
}



int existsStudent(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == id)
            return 1;
    }
    return 0;
}



void addStudent(Student s, const char *filename) {
    if (existsStudent(s.studentID)) {
        printf("Error: Student ID already exists!\n");
        return;
    }

    students = realloc(students, sizeof(Student) * (studentCount + 1));
    students[studentCount] = s;
    studentCount++;

    saveDatabase(filename);

    printf("Student added successfully.\n");
}



void updateStudent(int studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            printf("Updating student %d\n", studentID);
            printf("Enter new Batch (CS/SE/AI/Cyber): ");
            scanf("%s", students[i].batch);

            printf("Enter new Membership (IEEE/ACM): ");
            scanf("%s", students[i].membershipType);

            saveDatabase(FILENAME);
            printf("Record updated.\n");
            return;
        }
    }
    printf("Student not found.\n");
}



void deleteStudent(int studentID) {
    int found = 0;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            found = 1;

            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }

            studentCount--;
            students = realloc(students, sizeof(Student) * studentCount);
            saveDatabase(FILENAME);

            printf("Student deleted.\n");
            return;
        }
    }
    if (!found) printf("Student not found.\n");
}

void displayAll() {
    if (studentCount == 0) {
        printf("No student records found.\n");
        return;
    }

    printf("\n==== All Student Records ====\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%d | %s | %s | %s | %s | %s | %s\n",
               students[i].studentID,
               students[i].fullName,
               students[i].batch,
               students[i].membershipType,
               students[i].regDate,
               students[i].dob,
               students[i].interest);
    }
}

void batchReport() {
    char batchName[20], interest[10];
    printf("Enter Batch (CS/SE/AI/Cyber): ");
    scanf("%s", batchName);
    printf("Enter Interest (IEEE/ACM/Both): ");
    scanf("%s", interest);

    printf("\n=== Batch-wise Report ===\n");

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].batch, batchName) == 0 &&
            strcmp(students[i].interest, interest) == 0) {
            printf("%d | %s | %s | %s\n",
                   students[i].studentID,
                   students[i].fullName,
                   students[i].membershipType,
                   students[i].interest);
        }
    }
}

int main() {
    loadDatabase(FILENAME);

    int choice;

    while (1) {
        printf("\n====== Membership System ======\n");
        printf("1. Register Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All Students\n");
        printf("5. Batch-wise Report\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Student s;

            printf("Enter Student ID: ");
            scanf("%d", &s.studentID);

            printf("Full Name: ");
            getchar();
            fgets(s.fullName, 100, stdin);
            s.fullName[strcspn(s.fullName, "\n")] = 0;

            printf("Batch (CS/SE/AI/Cyber): ");
            scanf("%s", s.batch);

            printf("Membership Type (IEEE/ACM): ");
            scanf("%s", s.membershipType);

            printf("Registration Date (YYYY-MM-DD): ");
            scanf("%s", s.regDate);

            printf("Date of Birth (YYYY-MM-DD): ");
            scanf("%s", s.dob);

            printf("Interest (IEEE/ACM/Both): ");
            scanf("%s", s.interest);

            addStudent(s, FILENAME);
        }

        else if (choice == 2) {
            int id;
            printf("Enter Student ID to update: ");
            scanf("%d", &id);
            updateStudent(id);
        }

        else if (choice == 3) {
            int id;
            printf("Enter Student ID to delete: ");
            scanf("%d", &id);
            deleteStudent(id);
        }

        else if (choice == 4) {
            displayAll();
        }

        else if (choice == 5) {
            batchReport();
        }

        else if (choice == 6) {
            saveDatabase(FILENAME);
            printf("Exiting... Database saved.\n");
            break;
        }

        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    free(students);
    return 0;
}
