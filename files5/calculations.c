#include "calculations.h"

void calculateWeekTotals(int week, double *monthlyTotal)
{
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

    *monthlyTotal += Expense[i].weekTotal;
}
}