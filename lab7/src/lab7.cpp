# include<iostream>
# include<math.h>
# include<windows.h>
# include<vector>
# include<algorithm>
# include<cstdlib>
# include<ctime>
# include<random>
# include<complex>
# include<iomanip>

using namespace std;

# define PI 3.14159265358979323846
# define episilon 1e-6

double sumup(double (*f) (double), int k, double *h, double a, double b)
{
	double result = 0;
	for(int i=1; i<=pow(2, k-2); i++)
	{
		result += f(a + (2*i-1)*h[k]);
	}
	return h[k-1] * result;
}

double initial(double h, double(*f)(double), double a, double b)
{
	double R = 0;
	int n = int((b - a) / h);
	if(n==1)
	{
		R = h / 2.0 * (f(a) + f(b));
	}
	if(n==2)
	{
		R = h / 3.0 * (f(a) + 4.0 * f(a + h) + f(b));
	}
	return R;
}

double nRomberg(double a, double b, double lim, double(*f)(double), double(*Romberg)(double,double,double,double(*f)(double),int,int), int n, int flag)
{
	double dur = (b-a) / n ; 
	if(n==2)
	{
		return Romberg(a,a+dur,lim,f,1,flag) + Romberg(a+dur,b,lim,f,1,flag);
	}
	else
	{
		return nRomberg(a,a+dur,lim/2.0,f,Romberg,n/2,flag) + nRomberg(a+dur,b,lim/2.0,f,Romberg,n/2,flag);
	}
}


double Romberg(double a, double b, double lim, double(*f)(double), int n, int flag)
{
	double R[50][50];
	memset(R, 0.0, sizeof(R));
	double h0 = (b - a) / n;
	double h[50];
	for (int i = 1; i < 50; i++)
	{
		h[i] = h0 / pow(2, i-1);
	}
	R[1][1] = initial(h0, f, a, b);
	for(int i=2; ;i++)
	{
		if(n==1)
			R[i][1] = (R[i-1][1] + sumup(f, i, h, a, b))/2.0;
		else
			return nRomberg(a,b,lim,f,Romberg,n,flag);
		for(int j=2; j<=i; j++)
		{
			R[i][j] = (pow(4, j-1) * R[i][j-1] - R[i-1][j-1]) / (pow(4, j-1) - 1);
		}
		if(abs(R[i][i] - R[i-1][i-1]) < lim)
		{
			if(flag == 1)
			{
				for (int k = 1; k <= i; k++)
				{
					for (int j = 1; j <= i; j++)
					{
						cout << setw(7) << R[k][j] << " ";
					}
					cout << endl;
				}
			}
			return R[i][i];
		}
	}
}

double f1(double x)
{
	return log(x);
}

double f2(double x)
{
	return pow((2-pow(sin(x), 2)), 0.5);
}

int main()
{
	double a1 = 1, b1 = 2;
	double a2 = -PI/6, b2 = 3*PI/4;
	double lim = episilon;
	double result;
	int n1 = 1, n2 = 4;
	result = Romberg(a1, b1, lim, f1, n1, 1);
	cout << "The result of Romberg's method is " << result << endl;
	result = Romberg(a2, b2, lim, f2, n1, 1);
	cout << "The result of Romberg's method is " << result << endl;
	result = Romberg(a1, b1, lim, f1, n2, 1);
	cout << "The result of Romberg's method is " << result << endl;
	result = Romberg(a2, b2, lim, f2, n2, 1);
	cout << "The result of Romberg's method is " << result << endl;
	cout << "result of n = 1,2,4,8,16,32,64: " << endl;
	cout << Romberg(a1, b1, lim, f1, 1, 0) << endl;
	cout << Romberg(a1, b1, lim, f1, 2, 0) << endl;
	cout << Romberg(a1, b1, lim, f1, 4, 0) << endl;
	cout << Romberg(a1, b1, lim, f1, 8, 0) << endl;
	cout << Romberg(a1, b1, lim, f1, 16, 0) << endl;
	cout << Romberg(a1, b1, lim, f1, 32, 0) << endl;
	cout << Romberg(a1, b1, lim, f1, 64, 0) << endl;
	cout << Romberg(a2, b2, lim, f2, 1, 0) << endl;
	cout << Romberg(a2, b2, lim, f2, 2, 0) << endl;
	cout << Romberg(a2, b2, lim, f2, 4, 0) << endl;
	cout << Romberg(a2, b2, lim, f2, 8, 0) << endl;
	cout << Romberg(a2, b2, lim, f2, 16, 0) << endl;
	cout << Romberg(a2, b2, lim, f2, 32, 0) << endl;
	cout << Romberg(a2, b2, lim, f2, 64, 0) << endl;
	return 0;
}

