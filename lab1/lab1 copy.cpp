# include<iostream>
# include<math.h>
#include <windows.h>

# define epsilon 1e-5
# define delta 1e-12

double f1(double x)
{
    return (pow(x-1,3)-pow(x,2)+x);
}

double f2(double x)
{
    return (pow(sin(x),3)+pow(cos(x),3));
}

int count1 = 1;
int count2 = 1;

double erfen(double (*f)(double), double x1, double x2, FILE *fp)
{
    double x_ = 0.5*(x1+x2);
    double temp = f(x_);
    while(abs(temp) >= epsilon)
    {
        printf("iteration %d : f(%.12f) = %.12f\n", count1, x_, temp);
        fprintf(fp, "%d,%.6f\n", count1, abs(temp));
        count1 ++;
        if(f(x1)*temp<0)
            return erfen(f,x1,x_,fp);
        else
            return erfen(f,x_,x2,fp);
    }
    if(abs(temp) < epsilon)
    {
        printf("iteration %d : f(%.12f) = %.12f\n", count1, x_, temp);
        fprintf(fp, "%d,%.6f\n", count1, abs(temp));
        printf("End, x = %.12f\n",x_);
        return x_;
    }
}

double newton(double (*f)(double), double x0, FILE *fp)
{
    double f_ = (f(x0+delta)-f(x0))/delta;
    double x_new = x0 - f(x0)/f_;
    double temp = f(x_new);
    while(abs(temp) >= epsilon)
    {
        printf("iteration %d : f(%.12f) = %.12f\n", count2, x_new, temp);
        fprintf(fp, "%d,%.6f\n", count2, abs(temp));
        count2 ++;
        return newton(f,x_new,fp);
    }
    if(abs(temp) < epsilon)
    {
        printf("iteration %d : f(%.12f) = %.12f\n", count2, x_new, temp);
        fprintf(fp, "%d,%.6f\n", count2, abs(temp));
        printf("End, x = %.12f\n",x_new);
        return x_new;
    }
}





int main()
{
   printf("\nBelow: f(x) = (x-1)^3-x^2+x,  Bisection\n");
   count1 = 1;
   FILE *fp1;
   fp1 = fopen("./lab1/data/B_1.csv","w");
   erfen(f1,2,3,fp1);


   printf("\nBelow: f(x) = (sin(x))^3+(cos(x))^3,  Bisection\n");
   count1 = 1;
   FILE *fp2;
   fp2 = fopen("./lab1/data/B_2.csv","w");
   erfen(f2,2,3,fp2);


   printf("\nBelow: f(x) = (x-1)^3-x^2+x, \nNewton, Origin = 2.20000000000\n");
   count2 = 1;
   FILE *fp3;
   fp3 = fopen("./lab1/data/N_11.csv","w");
   newton(f1,2.2,fp3);


   printf("\nBelow: f(x) = (x-1)^3-x^2+x, \nNewton, Origin = 2.50000000000\n");
   count2 = 1;
   FILE *fp4;
   fp4 = fopen("./lab1/data/N_12.csv","w");
   newton(f1,2.5,fp4);


   printf("\nBelow: f(x) = (x-1)^3-x^2+x, \nNewton, Origin = 2.80000000000\n");
   count2 = 1;
   FILE *fp5;
   fp5 = fopen("./lab1/data/N_13.csv","w");
   newton(f1,2.8,fp5);


   printf("\nBelow: f(x) = (sin(x))^3+(cos(x))^3,  \nNewton, Origin = 2.20000000000\n");
   count2 = 1;
   FILE *fp6;
   fp6 = fopen("./lab1/data/N_21.csv","w");
   newton(f2,2.2,fp6);


   printf("\nBelow: f(x) = (sin(x))^3+(cos(x))^3,  \nNewton, Origin = 2.50000000000\n");
   count2 = 1;
   FILE *fp7;
   fp7 = fopen("./lab1/data/N_22.csv","w");
   newton(f2,2.5,fp7);


   printf("\nBelow: f(x) = (sin(x))^3+(cos(x))^3,  \nNewton, Origin = 2.80000000000\n");
   count2 = 1;
   FILE *fp8;
   fp8 = fopen("./lab1/data/N_23.csv","w");
   newton(f2,2.8,fp8);


}
