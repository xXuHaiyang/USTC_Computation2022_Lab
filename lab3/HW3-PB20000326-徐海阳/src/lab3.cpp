# include<iostream>
# include<math.h>
# include<windows.h>
# include<vector>
# include<algorithm>

using namespace std;

# define nine 0.111111111111
# define eight 0.125
# define seven 0.142857142857
# define six 0.166666666666
# define five 0.2
# define four 0.25
# define three 0.333333333333
# define two 0.5
# define one 1.0

# define delta 1e-5

//创建 h行l列的矩阵，并将初始各值设定为0
vector<vector<double>> creatmatrixA1()
{
	vector<vector<double>> v;
	v.push_back({0,0,0,0,0,0});
    v.push_back({0,nine,eight,seven,six,five});
    v.push_back({0,eight,seven,six,five,four});
    v.push_back({0,seven,six,five,four,three});
    v.push_back({0,six,five,four,three,two});
    v.push_back({0,five,four,three,two,one});
	return v;
}

vector<vector<double>> creatmatrixA2()
{
	vector<vector<double>> v;
	v.push_back({0,0,0,0,0});
    v.push_back({0,4,-1,1,3});
    v.push_back({0,16,-2,-2,5});
    v.push_back({0,16,-3,-1,7});
    v.push_back({0,6,-4,2,9});
	return v;
}

void PrintMatrix(vector<vector<double>> A)
{
    int i,j;
    for(i=1; i<A.size(); i++)//省略dim1和dim2的0元素
    {
        for(j=1; j<A.size(); j++)
        {
            printf(" %.6f ",A[i][j]);
        }
        printf("\n");
    }
}

void PrintVector(vector<double> x)
{
    int i;
    // printf("vector:");
    for( i=1; i< x.size();i++) //省略dim的0元素
    {
        printf("%.6f",x[i]);
        printf("\n");
    }
}

vector<double> Mul(vector<vector<double>> A, vector<double> x)
{
    vector<double> result;
    result.push_back(0);
    int m = A.size()-1;
    int n = A[0].size()-1;
    int i,j,k;
    double ele;
    for(i=1; i<=m; i++)
    {
        ele = 0;
        for(k=1; k<=n; k++)
        {
            ele += A[i][k] * x[k];
        }
        result.push_back(ele);
    }
    return result;
}

vector<double> Norm(vector<double> A)
{
    vector<double> result;
    result.push_back(0);
    double max = 0.0;
    int n = A.size() - 1;
    for(int i=1; i<=n; i++)
    {
        if (A[i] > max) max = A[i];
    }
    for(int i=1; i<=n; i++)
    {
        result.push_back(A[i]/max);
    }
    return result;
}

vector<double> Doolittle(vector<vector<double>> A, vector<double> b)
{
    // A.size() == n+1
    int i,j,k,r;
    int n = A.size()-1;
    double temp;
    // 初始化一个 二维的matrix, 行M,列N,且值自定义为data;
    vector<vector<double>> L(n+1,vector<double>(n+1,0));
    vector<vector<double>> U(n+1,vector<double>(n+1,0));
    
    vector<double> X(n+1, 0);
    vector<double> Y(n+1, 0);

    for(k=1; k<=n; k++)
    {
        for (j=k; j<=n; j++)
        {
            temp = 0;
            for(r=1; r<=k-1; r++)
            {
                temp += L[k][r] * U[r][j];
            }
            U[k][j] = A[k][j] - temp;
        }
        for (i=k+1; i<=n; i++)
        {
            temp = 0;
            for(r=1; r<=k-1; r++)
            {
                temp += L[i][r] * U[r][k];
            }
            L[i][k] = (A[i][k] - temp) / U[k][k];
        }
        for(i=1; i<n; i++)
        {
            L[i][i] = 1;
        }
    }

    for (i=1; i<=n; i++)
    {
        temp = 0;
        for(j=1; j<=i-1; j++)
        {
            temp += L[i][j] * Y[j];
        }
        Y[i] = b[i] - temp;
    }

    for( i=n; i>=1; i--)
    {
        temp = 0;
        for( j = i+1; j<=n; j++)
        {
            temp += U[i][j] * X[j];
        }
        X[i] = (Y[i]-temp) / U[i][i];
    }
    return X;
}

double spe_val(vector<double> x)
{
    double v = *max_element(x.begin(), x.end());
    v = 1/v;
    return v;
}

bool judge(vector<double> xk, vector<double> xk1)
{
    double maxk, maxk1;
    maxk = spe_val(xk);
    maxk1 = spe_val(xk1);
    if (abs(maxk - maxk1) > delta) return true;
    else return false;
}

void Fanmi(vector<vector<double>> A, vector<double> x)
{

    vector<double> y, xk, xk1;
    double val = 1.0;
    xk = x;
    printf("Xk:\n");
    PrintVector(xk);
    y = Norm(x);
    printf("Yk:\n");
    PrintVector(y);
    xk1 = Doolittle(A,y);
    printf("lamda: %.12f\n", val);
    printf("\n");
    int i = 1;
    while(judge(xk, xk1))
    {
        xk = xk1;
        printf("Xk:\n");
        PrintVector(xk);
        y = Norm(xk);
        printf("Yk:\n");
        PrintVector(y);
        xk1 = Doolittle(A,y);
        val = spe_val(xk1);
        printf("lamda: %.12f\n", val);
        printf("\n");
        i++;
    }
    val = spe_val(xk1);
    printf("special_value: %.12f\n", val);
    printf("special_vector: \n");
    PrintVector(xk1);
    printf("iteration cycles: %d\n", i);
    printf("\n\n");
}


int main()
{
    vector<vector<double>> A1, A2;
    A1 = creatmatrixA1();
    A2 = creatmatrixA2();
    vector<double> x1 = {0,1,1,1,1,1};
    vector<double> x2 = {0,1,1,1,1};

    Fanmi(A1, x1);
    Fanmi(A2, x2);
}