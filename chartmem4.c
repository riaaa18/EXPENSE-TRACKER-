#include <stdio.h>
#include <string.h>

void displayPreviousData() {
    FILE *file = fopen("expenses.csv", "r");

    if (file == NULL) {
        printf("No expenses found yet.\n");
        return;
    }

    int week;
    char category[30];
    float amount;

    printf("\n---- Previous Expenses ----\n");
    printf("Week   Category        Amount\n");

    // skip header line (Week,Category,Amount)
    char header[100];
    fgets(header, sizeof(header), file);

    while (fscanf(file, "%d,%[^,],%f\n", &week, category, &amount) == 3) {
        printf("%-6d %-15s %.2f\n", week, category, amount);
    }

    fclose(file);
}

void displayChart() {
    FILE *file = fopen("expenses.csv", "r");

    if (file == NULL) {
        printf("No expenses found yet.\n");
        return;
    }

    float food = 0, transport = 0, entertainment = 0, utilities = 0;

    int week;
    char category[30];
    float amount;

    char header[100];
    fgets(header, sizeof(header), file);

    while (fscanf(file, "%d,%[^,],%f\n", &week, category, &amount) == 3) {
        if (strcmp(category, "Food") == 0) {
            food = food + amount;
        }
        else if (strcmp(category, "Transport") == 0) {
            transport = transport + amount;
        }
        else if (strcmp(category, "Entertainment") == 0) {
            entertainment = entertainment + amount;
        }
        else if (strcmp(category, "Utilities") == 0) {
            utilities = utilities + amount;
        }
    }

    fclose(file);

    printf("\n---- Expense Chart ----\n");

    printf("Food          ");
    for (int i = 0; i < food / 10; i++) {
        printf("*");
    }
    printf(" %.0f\n", food);

    printf("Transport     ");
    for (int i = 0; i < transport / 10; i++) {
        printf("*");
    }
    printf(" %.0f\n", transport);

    printf("Entertainment ");
    for (int i = 0; i < entertainment / 10; i++) {
        printf("*");
    }
    printf(" %.0f\n", entertainment);

    printf("Utilities     ");
    for (int i = 0; i < utilities / 10; i++) {
        printf("*");
    }
    printf(" %.0f\n", utilities);
}
int main() {
    displayPreviousData();
    displayChart();
    return 0;
}