#include <stdio.h>
#include "expense.h"
#include "input.h"
#include "file.h"
#include "calculations.h"
#include "display.h"

int main()
{

    int week, monthly_salary;
    int highestWeek;

    double monthlyTotal = 0;
    double remainingSavings = 0;
    double percentage_spent = 0;
    double highestWeekTotal = 0;
    double highestCategoryTotal = 0;


    char highestCategory[100];

    getSalary(&monthly_salary);

    getWeeks(&week);

    getExpenses(week);
    saveExpenses(week);

    calculateWeekTotals(week, &monthlyTotal);

    

    remainingSavings = calculateRemainingSavings(monthly_salary, monthlyTotal);

    percentage_spent = calculatePercentageSpent(monthlyTotal,
                                                monthly_salary);


    displayMonthlySummary(monthlyTotal,
                          monthlyTotal / week,
                          remainingSavings,
                          percentage_spent);


    displayWeekTotals(week);


    findHighestWeek(week, &highestWeekTotal, &highestWeek);
    displayHighestWeek(highestWeekTotal, highestWeek);


    findHighestCategory(week, highestCategory, &highestCategoryTotal);

    displayHighestCategory(highestCategory, highestCategoryTotal);

    displaySuccessMessage();

    return 0;
}