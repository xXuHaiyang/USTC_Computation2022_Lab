# include<iostream>
# include<math.h>
# include<windows.h>
# include<vector>
# include<algorithm>
# include<cstdlib>
# include<ctime>
# include<random>
# include<complex>

using namespace std;

# define PI 3.14159265358979323846

double _getf1(double t)
{
	return 0.7*sin(2*PI*2*t)+sin(2*PI*5*t);
}

double _getf2(double t)
{
	return _getf1(t) + 0.3*(rand()%10000/10000.0);
}

vector<complex<double>> getf1(double down, double up, int n)
{
	vector<complex<double>> v;
	double dur;
	dur = (up - down) / n;
	for (int i = 0; i < n; i++)
	{
		v.push_back(complex<double>(_getf1(down + i * dur),0));
	}
	return v;
}

vector<complex<double>> getf2(double down, double up, int n)
{
	vector<complex<double>> v;
	double dur;
	dur = (up - down) / n;
	for (int i = 0; i < n; i++)
	{
		v.push_back(complex<double>(_getf2(down + i * dur),0));
	}
	return v;
}

vector<complex<double>> FFT(vector<complex<double>> &f)
{
	int n = f.size();
	vector<complex<double>> F(n);
	if (n == 1)
	{
		F[0] = f[0];
		return F;
	}
	vector<complex<double>> F_even(n / 2);
	vector<complex<double>> F_odd(n / 2);
	for (int i = 0; i < n / 2; i++)
	{
		F_even[i] = f[2 * i];
		F_odd[i] = f[2 * i + 1];
	}
	vector<complex<double>> F_even_ = FFT(F_even);
	vector<complex<double>> F_odd_ = FFT(F_odd);
	for (int i = 0; i < n / 2; i++)
	{
		F[i] = (F_even_[i] + F_odd_[i] * exp(complex<double>(0, -2 * PI * i / n)))/complex<double>(2,0);
	}
	for (int i = 0; i < n / 2; i++)
	{
		F[i + n / 2] = (F_even_[i] - F_odd_[i] * exp(complex<double>(0, -2 * PI * i / n)))/complex<double>(2,0);
	}
	return F;
}

vector<complex<double>> IFFT(vector<complex<double>> &f)
{
	int n = f.size();
	vector<complex<double>> F(n);
	if (n == 1)
	{
		F[0] = f[0];
		return F;
	}
	vector<complex<double>> F_even(n / 2);
	vector<complex<double>> F_odd(n / 2);
	for (int i = 0; i < n / 2; i++)
	{
		F_even[i] = f[2 * i];
		F_odd[i] = f[2 * i + 1];
	}
	vector<complex<double>> F_even_ = IFFT(F_even);
	vector<complex<double>> F_odd_ = IFFT(F_odd);
	for (int i = 0; i < n / 2; i++)
	{
		F[i] = F_even_[i] + F_odd_[i] * exp(complex<double>(0, 2 * PI * i / n));
	}
	for (int i = 0; i < n / 2; i++)
	{
		F[i + n / 2] = F_even_[i] - F_odd_[i] * exp(complex<double>(0, 2 * PI * i / n));
	}
	return F;
}

vector<double> get_mode(vector<complex<double>> &f)
{
	vector<double> mode;
	int n = f.size();
	for (int i = 0; i < n/2; i++)
	{
		mode.push_back(2*abs(f[i]));
	}
	return mode;
}

void printcomplex(vector<complex<double>> f)
{
	cout.precision(6);
	for (int i = 0; i < f.size(); i++)
	{
		cout << f[i].real() << " -- " << f[i].imag() << endl;
	}
}

void printvector(vector<double> f)
{
	cout.precision(6);
	cout << "[";
	for (int i = 0; i < f.size(); i++)
	{
		cout << f[i] << ",";
	}
	cout << "]" << endl;
}

vector<complex<double>> lowfreqfilter(vector<complex<double>> x, double rate)
{
	vector<complex<double>> y;
	for (int i = 0; i < x.size(); i++)
	{
		if (i < rate * x.size())
		{
			y.push_back(x[i]);
		}
		else
		{
			y.push_back(complex<double>(0, 0));
		}
	}
	return y;
}

void require1(vector<complex<double>> (*f_)(double, double, int), int n)
{
	cout.precision(6);
	vector<complex<double>> f = f_(0,1,n);
	vector<complex<double>> g = FFT(f);
	cout << "F = real -- imag" << endl;
	printcomplex(g);
}

void require2(vector<complex<double>> (*f_)(double, double, int), int n)
{
	cout.precision(6);
	vector<complex<double>> f = f_(0,1,n);
	vector<complex<double>> g = FFT(f);
	vector<double> modeg = get_mode(g);
	cout << "f = [";
	for (int i = 0; i < modeg.size(); i++)
	{
		cout << i << ",";
	}
	cout << "]" << endl;
	cout << "mode = [";
	for (int i = 0; i < modeg.size(); i++)
	{
		cout << modeg[i] << ",";
	}
	cout << "]" << endl;
}

void require3(int n)
{
	cout.precision(6);
	vector<complex<double>> f = getf1(0, 1, n);
	vector<complex<double>> g = FFT(f);
	vector<complex<double>> f_ = IFFT(g);
	cout << "x = [";
	for (int i = 0; i < n; i++)
	{
		cout << 1.0/n*i << ",";
	}
	cout << "]" << endl;
	cout << "f = [";
	for (int i = 0; i < f.size(); i++)
	{
		cout << f[i].real() << ",";
	}
	cout << "]" << endl;
	cout << "f_ = [";
	for (int i = 0; i < f_.size(); i++)
	{
		cout << f_[i].real() << ",";
	}
	cout << "]" << endl;
}

void require4(int n)
{
	cout.precision(6);
	vector<complex<double>> f = getf2(0, 1, n);
	vector<complex<double>> g = FFT(f);
	vector<complex<double>> g_25 = lowfreqfilter(g, 0.25);
	vector<complex<double>> f_ = IFFT(g_25);
	cout << "x = [";
	for (int i = 0; i < n; i++)
	{
		cout << 1.0 / n * i << ",";
	}
	cout << "]" << endl;
	cout << "f = [";
	for (int i = 0; i < f.size(); i++)
	{
		cout << f[i].real() << ",";
	}
	cout << "]" << endl;
	cout << "f_ = [";
	for (int i = 0; i < f_.size(); i++)
	{
		cout << f_[i].real() << ",";
	}
	cout << "]" << endl;
}

int main()
{
	srand(time(NULL));
	int n1 = pow(2, 4), n2 = pow(2, 7);
	cout << "require1: " << endl;
	cout << "f: f1; n: " << n1 << endl;
	require1(getf1, n1);
	cout << "f: f2; n: " << n1 << endl;
	require1(getf2, n1);
	cout << "f: f1; n: " << n2 << endl;
	require1(getf1, n2);
	cout << "f: f2; n: " << n2 << endl;
	require1(getf2, n2);
	cout << "require2: " << endl;
	cout << "f: f1; n: " << n1 << endl;
	require2(getf1, n1);
	cout << "f: f2; n: " << n1 << endl;
	require2(getf2, n1);
	cout << "f: f1; n: " << n2 << endl;
	require2(getf1, n2);
	cout << "f: f2; n: " << n2 << endl;
	require2(getf2, n2);
	cout << "require3: " << endl;
	cout << "n: " << n1 << endl;
	require3(n1);
	cout << "n: " << n2 << endl;
	require3(n2);
	cout << "require4: " << endl;
	cout << "n: " << n1 << endl;
	require4(n1);
	cout << "n: " << n2 << endl;
	require4(n2);
	return 0;
}