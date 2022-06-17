# include<iostream>
# include<math.h>
# include<windows.h>
# include<vector>
# include<algorithm>
# include<cstdlib>
# include<ctime>
# include<random>

using namespace std;

vector<double> randomsample(double min, double max, int n)
{
	void printvec(vector<double> v);
	// 0,1,2 ... n
	cout << "randomsample:" << n+1 << endl;
	vector<double> v;
	double suiji;
	for (int i = 0; i <= n; i++)
	{
		suiji = rand() % 10000 / 10000.0 * (max - min) + min;
		v.push_back(suiji);
	}
	sort(v.begin(), v.end());
	printvec(v);
	return v;
}

vector<double> uniformsample(double min, double max, int n)
{
	// 0,1,2 ... n
	void printvec(vector<double> v);
	cout << "uniformsample:" << n+1 << endl;
	vector<double> v;
	double sample;
	double dur;
	dur = (max - min)/n;
	for (int i = 0; i <= n; i++)
	{
		sample = min + i * dur;
		v.push_back(sample);
	}
	printvec(v);
	return v;
}

double _getf1(double x)
{
	return x/(pow(x,2) + x+ 1);
}

double _getf2(double x)
{
	return (x+sin(x))/(1+exp(-x));
}

double _getf1__(double x)
{
	double fenzi, fenmu;
	fenzi = 2*pow(x,3) - 6 * x -2;
	fenmu = pow((pow(x,2) + x + 1),3);
	return fenzi/fenmu;
}

double _getf2__(double x)
{
	double cos2x = cos(2*x);
	double sin2x = sin(2*x);
	double e_x = exp(-x);
	double m1 = 2*e_x*(1+2*cos2x)/pow((1+e_x),2);
	double m2 = 4*sin2x/(1+e_x);
	double m3 = 2*pow(e_x,2)/pow((1+e_x),3);
	double m4 = e_x/pow((1+e_x),2);
	double m5 = x+sin2x;
	return m1-m2+(m3-m4)*m5;
}

vector<double> getf1(vector<double> x)
{
	// 0,1,2 ... n
	int n = x.size()-1;
	vector<double> fx(n+1);
	for (int i = 0; i < x.size(); i++)
	{
		fx[i] = _getf1(x[i]);
	}
	return fx;
}

vector<double> getf2(vector<double> x)
{
	// 0,1,2 ... n
	int n = x.size()-1;
	vector<double> fx(n+1);
	for (int i = 0; i < x.size(); i++)
	{
		fx[i] = (_getf2(x[i]));
	}
	return fx;
}

vector<double> getf1__(vector<double> x)
{
	vector<double> fx;
	for (int i = 0; i < x.size(); i++)
	{
		fx.push_back(_getf1__(x[i]));
	}
	return fx;
}

vector<double> getf2__(vector<double> x)
{
	vector<double> fx;
	for (int i = 0; i < x.size(); i++)
	{
		fx.push_back(_getf2__(x[i]));
	}
	return fx;
}

vector<double> geth(vector<double> x)
{
	// 0,1,2 ... n-1
	vector<double> h;
	for (int i = 0; i < x.size()-1; i++)
	{
		h.push_back(x[i+1] - x[i]);
	}
	h.push_back(0);
	return h;
}

vector<double> getlambda(vector<double> h)
{
	// 1,2 ... n-1
	vector<double> lambda;
	lambda.push_back(0);
	for (int i = 1; i < h.size(); i++)
	{
		lambda.push_back(h[i] / (h[i] + h[i-1]));
	}
	//lambda.push_back(0);
	return lambda;
}

vector<double> getmu(vector<double> lamda)
{
	// 1,2 ... n-1
	vector<double> mu;
	mu.push_back(0);
	for (int i = 1; i < lamda.size()-1; i++)
	{
		mu.push_back(1-lamda[i]);
	}
	mu.push_back(0);
	return mu;
}

double chafen(double x1, double x2, double x3)
{
	double z1, z2, end;
	z1 = (_getf1(x1) - _getf1(x2)) / (x1 - x2);
	z2 = (_getf1(x2) - _getf1(x3)) / (x2 - x3);
	end = (z1 - z2) / (x1 - x3);
	return end;
}

vector<double> getd(vector<double> x)
{
	//1,2 ... n-1
	vector<double> d;
	d.push_back(0);
	for (int i = 1; i < x.size()-1; i++)
	{
		d.push_back(6 * chafen(x[i-1], x[i], x[i+1]));
	}
	d.push_back(0);
	return d;
}

vector<double> runafter(vector<double> a, vector<double> b, vector<double> c, vector<double> f)
{
	//a: 1,2,...,n b: 1,2,...,n-1 c: 2,3,...,n f: 1,2,...,n x: 1,2,...,n
	int n = a.size()-1;
	vector<double> u, v, y;
	u.push_back(0);
	v.push_back(0);
	y.push_back(0);
	int i, k;
	for (k=1; k<=n; k++)
	{
		u.push_back(a[k] - c[k] * v[k-1]);
		v.push_back(b[k]/u[k]);
		y.push_back((f[k] - c[k] * y[k-1])/u[k]);
	}
	vector<double> x(n+2);
	x[0] = 0;
	x[n+1] = 0;
	for (i=n; i>=1; i--)
	{
		x[i] = y[i] - v[i] * x[i+1];
	}
	return x;
}

void printvec(vector<double> x)
{
	printf("print size: %d\n", x.size());
	for (int i = 0; i < x.size(); i++)
	{
		cout << x[i] << " ";
	}
	cout << endl;
}

vector<double> cal(char category, vector<double> x, vector<double> fx, vector<double> M, vector<double> h)
{
	vector<double> result;
	if(category == 'C')
	{
		for (int i = 0; i < x.size()-1; i++)
		{
			result.push_back(fx[i]/h[i] - M[i]*h[i]/6);
		}
	}
	else if(category == 'D')
	{
		for (int i = 0; i < x.size()-1; i++)
		{
			result.push_back(fx[i+1]/h[i] - M[i+1]*h[i]/6);
		}
	}
	return result;
}

void ziran(vector<double> x, vector<double> (*f)(vector<double>))
{
	vector<double> fx, lambda, mu, h, d;
	fx = f(x);
	cout << "fx: " << endl;
	printvec(fx);
	h = geth(x);
	lambda = getlambda(h);
	mu = getmu(lambda);
	d = getd(x);
	int n = x.size()-1;
	vector<double> a(n,2);
	lambda[n-1] = 0;
	mu[1] = 0;
	vector<double> M;
	M = runafter(a, lambda, mu, d);
	vector<double> C,D;
	C = cal('C', x, fx, M, h);
	D = cal('D', x, fx, M, h);
	cout << "C: " << endl;
	printvec(C);
	cout << "D: " << endl;
	printvec(D);
	cout << "M: " << endl;
	printvec(M);
}

void yijie(vector<double> x, vector<double> (*f)(vector<double>), double m0, double mn)
{
	vector<double> fx, lambda, mu, h, d;
	fx = f(x);
	cout << "fx: " << endl;
	printvec(fx);
	h = geth(x);
	lambda = getlambda(h);
	mu = getmu(lambda);
	d = getd(x);
	int n = x.size()-1;
	vector<double> a(n+2,2);
	lambda[0] = 1;
	lambda.insert(lambda.begin(), 0);
	mu[n-1] = 1;
	vector<double> M;
	d[0] = 6/h[0]*((fx[1]-fx[0])/h[0] - m0);
	d[n] = 6/h[n-1]*(-(fx[n]-fx[n-1])/h[n-1] + mn);
	d.insert(d.begin(), 0);
	d.insert(d.end(), 0);
	M = runafter(a, lambda, mu, d);
	M.pop_back();
	M.erase(M.begin());
	vector<double> C,D;
	C = cal('C', x, fx, M, h);
	D = cal('D', x, fx, M, h);
	cout << "C: " << endl;
	printvec(C);
	cout << "D: " << endl;
	printvec(D);
	cout << "M: " << endl;
	printvec(M);
}

void uniform1(int n)
{
	vector<double> x;
	x = uniformsample(-2, 2, n);
	cout << "ziran: " << endl;
	ziran(x, getf1);
	cout << "yijie: " << endl;
	yijie(x, getf1, 0, 0);
}

void uniform2(int n)
{
	vector<double> x;
	x = uniformsample(-2, 4, n);
	cout << "ziran: " << endl;
	ziran(x, getf2);
	cout << "yijie: " << endl;
	yijie(x, getf2, 0, 0);
}

void random1(int n)
{
	vector<double> x;
	x = randomsample(-2, 2, n);
	cout << "ziran: " << endl;
	ziran(x, getf1);
	printf("\n");
	cout << "yijie: " << endl;
	yijie(x, getf1, 0, 0);
}

void random2(int n)
{
	vector<double> x;
	x = randomsample(-2, 4, n);
	cout << "ziran: " << endl;
	ziran(x, getf2);
	printf("\n");
	cout << "yijie: " << endl;
	yijie(x, getf2, 0, 0);
}

int main()
{
	cout << "uniform1: " << endl;
	uniform1(20);
	cout << endl;
	cout << "uniform2: " << endl;	
	uniform2(20);
	cout << endl;
	cout << "random1(1): " << endl;
	random1(20);
	cout << endl;
	cout << "random1(2): " << endl;
	random1(20);
	cout << endl;
	cout << "random2(1): " << endl;
	random2(20);
	cout << endl;
	cout << "random2(2): " << endl;
	random2(20);
	return 0;
}




