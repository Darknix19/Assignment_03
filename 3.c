#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    double salary;
};

void displayEmployees(struct Employee employees[], int n) {
    printf("\n%-10s %-20s %-20s %-10s\n", "ID", "Name", "Designation", "Salary");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %-20s %-10.2f\n", employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
    }
}

void findHighestSalary(struct Employee employees[], int n) {
    int index = 0;
    for (int i = 1; i < n; i++) {
        if (employees[i].salary > employees[index].salary) {
            index = i;
        }
    }
    printf("\nEmployee with Highest Salary:\n");
    printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
           employees[index].id, employees[index].name, employees[index].designation, employees[index].salary);
}

void searchEmployee(struct Employee employees[], int n, int searchByID, int id, char name[]) {
    int found = 0;
    if (searchByID) {
        for (int i = 0; i < n; i++) {
            if (employees[i].id == id) {
                printf("\nEmployee Found:\nID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
                found = 1;
                break;
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (strcmp(employees[i].name, name) == 0) {
                printf("\nEmployee Found:\nID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
                found = 1;
                break;
            }
        }
    }
    if (!found) {
        printf("\nEmployee not found.\n");
    }
}

void applyBonus(struct Employee employees[], int n, double threshold) {
    for (int i = 0; i < n; i++) {
        if (employees[i].salary < threshold) {
            employees[i].salary *= 1.10; // 10% bonus
        }
    }
}

int main() {
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee employees[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &employees[i].id);
        printf("Name: ");
        scanf("%s", employees[i].name);
        printf("Designation: ");
        scanf("%s", employees[i].designation);
        printf("Salary: ");
        scanf("%lf", &employees[i].salary);
    }

    displayEmployees(employees, n);
    findHighestSalary(employees, n);

    int choice;
    printf("\nSearch by (1) ID or (2) Name: ");
    scanf("%d", &choice);
    if (choice == 1) {
        int id;
        printf("Enter ID to search: ");
        scanf("%d", &id);
        searchEmployee(employees, n, 1, id, "");
    } else {
        char name[50];
        printf("Enter Name to search: ");
        scanf("%s", name);
        searchEmployee(employees, n, 0, 0, name);
    }

    applyBonus(employees, n, 50000);
    printf("\nAfter applying 10%% bonus to employees below 50000:\n");
    displayEmployees(employees, n);

    return 0;
}