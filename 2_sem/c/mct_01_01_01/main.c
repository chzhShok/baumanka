#include <math.h>
#include <stdio.h>

#define OK 0
#define ERR_IO 1

double series(double x, double eps)
{
    double s = 0;
    double a = pow(x, 5) / 6;
    int i = 2;

    printf("Table:\n");
    printf("i    | ai         | si\n");
    printf("-----------------------------\n");
    while (fabs(a) >= eps)
    {
        printf("%-4d | %-10.2lf | ", i, a);
        s += a;
        printf("%-10.2lf\n", s);
        i++;
        a = (-x * x * a) / (i + 2);
    }

    return s;
}

int main(void)
{
    double x, eps;

    printf("Input x: ");
    if (scanf("%lf", &x) != 1)
    {
        printf("I/O error");
        return ERR_IO;
    }

    printf("Input eps: ");
    if (scanf("%lf", &eps) != 1)
    {
        printf("I/O error");
        return ERR_IO;
    }

    double s = series(x, eps);

    double f = sin(x) * x;

    printf("f(x): %-.2lf\n", f);
    printf("s(x): %-.2g\n", s);

    return OK;
}