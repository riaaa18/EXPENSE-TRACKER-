#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct exp
{
    int week;
    double food, transport, entertainment, utility;
    char category[100][100];
    double amount[100];
    int customCount;
    double weekTotal;

} Expense[100];

struct CategoryTotal
{
    char category[100];
    double total;
};

int main()
{
    FILE *fp;
    int week, monthly_salary;
    double weekly_budget;
    char choice;
    double monthlyTotal = 0;
    double remainingSavings = 0;
    double percentage_spent = 0;
    double averageWeeklySpending;

    printf("Enter your monthly salary: ");
    scanf("%d", &monthly_salary);

    if (monthly_salary <= 0)
    {
        printf("Invalid salary input. Please enter a positive number.\n");
        return 1;
    }

    printf("Your monthly salary is: %d\n", monthly_salary);

    weekly_budget = monthly_salary / 4.0;
    printf("Your weekly budget is: %.2lf\n", weekly_budget);

    printf("Enter the number of weeks (1-4): ");
    scanf("%d", &week);

    if (week < 1 || week > 4)
    {
        printf("Invalid number of weeks.\n");
        return 1;
    }

    fp = fopen("expenses.csv", "w");

    if (fp == NULL)
    {
        printf("Error creating file.\n");
        return 1;
    }

    for (int i = 0; i < week; i++)
    {
        printf("\nWeek %d\n", i + 1);

        Expense[i].week = i + 1;

        printf("Food: ");
        scanf("%lf", &Expense[i].food);
        fprintf(fp, "%d,Food,%.2lf\n", Expense[i].week, Expense[i].food);

        printf("Transport: ");
        scanf("%lf", &Expense[i].transport);
        fprintf(fp, "%d,Transport,%.2lf\n", Expense[i].week, Expense[i].transport);

        printf("Entertainment: ");
        scanf("%lf", &Expense[i].entertainment);
        fprintf(fp, "%d,Entertainment,%.2lf\n", Expense[i].week, Expense[i].entertainment);

        printf("Utility: ");
        scanf("%lf", &Expense[i].utility);
        fprintf(fp, "%d,Utility,%.2lf\n", Expense[i].week, Expense[i].utility);

        int j = 0;

        do
        {
            if (j >= 100)
            {
                printf("Maximum custom categories reached.\n");
                break;
            }

            printf("Do you want to add a custom category? (y/n): ");
            scanf(" %c", &choice);

            if (choice == 'y' || choice == 'Y')
            {
                printf("Category: ");
                scanf("%99s", Expense[i].category[j]);

                printf("Amount: ");
                scanf("%lf", &Expense[i].amount[j]);

                fprintf(fp, "%d,%s,%.2lf\n",
                        Expense[i].week,
                        Expense[i].category[j],
                        Expense[i].amount[j]);

                j++;
            }

        } while (choice == 'y' || choice == 'Y');

        Expense[i].customCount = j;
    }

    fclose(fp);

    for (int i = 0; i < week; i++)
    {
        Expense[i].weekTotal =
            Expense[i].food +
            Expense[i].transport +
            Expense[i].entertainment +
            Expense[i].utility;

        for (int j = 0; j < Expense[i].customCount; j++)
        {
            Expense[i].weekTotal += Expense[i].amount[j];
        }

        monthlyTotal += Expense[i].weekTotal;
    }
    averageWeeklySpending = monthlyTotal / week;
    printf("\nMonthly Total: %.2lf\n", monthlyTotal);
    printf("Average Weekly Spending: %.2lf\n", averageWeeklySpending);

    remainingSavings = monthly_salary - monthlyTotal;
    printf("Remaining Savings: %.2lf\n", remainingSavings);

    percentage_spent = (monthlyTotal / monthly_salary) * 100;
    printf("Percentage of Salary Spent: %.2lf%%\n", percentage_spent);

    printf("\n");

    for (int i = 0; i < week; i++)
    {
        printf("Week %d Total: %.2lf\n",
               Expense[i].week,
               Expense[i].weekTotal);
    }

    double highestWeekTotal = Expense[0].weekTotal;
    int highestWeek = Expense[0].week;

    for (int i = 1; i < week; i++)
    {
        if (Expense[i].weekTotal > highestWeekTotal)
        {
            highestWeekTotal = Expense[i].weekTotal;
            highestWeek = Expense[i].week;
        }
    }

    printf("Highest Week Total: %.2lf (Week %d)\n", highestWeekTotal, highestWeek);

    struct CategoryTotal totals[100];
    int totalCategories = 0;
    double highestCategoryTotal;
    char highestCategory[100];

    double foodTotal = 0;
    double transportTotal = 0;
    double entertainmentTotal = 0;
    double utilityTotal = 0;

    for (int i = 0; i < week; i++)
    {
        foodTotal += Expense[i].food;
        transportTotal += Expense[i].transport;
        entertainmentTotal += Expense[i].entertainment;
        utilityTotal += Expense[i].utility;
    }

    for (int i = 0; i < week; i++)
    {
        for (int j = 0; j < Expense[i].customCount; j++)
        {
            int found = 0;
            for (int k = 0; k < totalCategories; k++)
            {
                if (strcmp(totals[k].category, Expense[i].category[j]) == 0)
                {
                    totals[k].total += Expense[i].amount[j];
                    found = 1;
                    break;
                }
            }
            if (!found)
            {

                strcpy(totals[totalCategories].category, Expense[i].category[j]);
                totals[totalCategories].total = Expense[i].amount[j];
                totalCategories++;
            }
        }
    }

    double highestFixedTotal = foodTotal;
    char highestFixedCategory[100] = "Food";

    if (transportTotal > highestFixedTotal)
    {
        highestFixedTotal = transportTotal;
        strcpy(highestFixedCategory, "Transport");
    }
    if (entertainmentTotal > highestFixedTotal)
    {
        highestFixedTotal = entertainmentTotal;
        strcpy(highestFixedCategory, "Entertainment");
    }
    if (utilityTotal > highestFixedTotal)
    {
        highestFixedTotal = utilityTotal;
        strcpy(highestFixedCategory, "Utility");
    }

    if (totalCategories == 0)
    {
        printf("No custom categories were added.\n");
    }
    else
    {
        highestCategoryTotal = totals[0].total;
        strcpy(highestCategory, totals[0].category);

        for (int i = 1; i < totalCategories; i++)
        {
            if (totals[i].total > highestCategoryTotal)
            {
                highestCategoryTotal = totals[i].total;
                strcpy(highestCategory, totals[i].category);
            }
        }
    }

    if (totalCategories == 0)
    {
        printf("\nHighest Spending Category: %s\n", highestFixedCategory);
        printf("Amount: %.2lf\n", highestFixedTotal);
    }
    else
    {
        if (highestFixedTotal > highestCategoryTotal)
        {
            printf("\nHighest Spending Category: %s\n", highestFixedCategory);
            printf("Amount: %.2lf\n", highestFixedTotal);
        }
        else
        {
            printf("\nHighest Spending Category: %s\n", highestCategory);
            printf("Amount: %.2lf\n", highestCategoryTotal);
        }
    }

    printf("\nAll expenses saved successfully to expenses.csv\n");

    return 0;
}