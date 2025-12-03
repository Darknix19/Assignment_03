#include <stdio.h>

double calculateRepayment(double loan, double interestRate, int years, double installment, double extraPayment, int year) {
    if (loan <= 0 || years == 0) return 0;
    loan = loan * (1 + interestRate);
    double payment = installment + extraPayment;
    if (payment > loan) payment = loan;
    double remaining = loan - payment;
    printf("Year %d: Remaining loan = %.2f\n", year, remaining);
    return payment + calculateRepayment(remaining, interestRate, years - 1, installment, extraPayment, year + 1);
}

int main() {
    double total = calculateRepayment(100000, 0.05, 3, 30000, 0, 1);
    printf("Total repayment = %.2f\n", total);
    return 0;
}

/*
Each call carries forward the updated loan balance and remaining years

The base case ensures repayment stops when loan is cleared or years expire

The recursive case naturally models the yearly cycle of interest and payment*/
