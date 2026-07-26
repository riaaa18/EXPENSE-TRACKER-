#ifndef EXPENSE_H
#define EXPENSE_H

struct exp
{
    int week;
    double food, transport, entertainment, utility;
    char category[100][100];
    double amount[100];
    int customCount;
    double weekTotal;
};

struct CategoryTotal
{
    char category[100];
    double total;
};

extern struct exp Expense[100];

#endif