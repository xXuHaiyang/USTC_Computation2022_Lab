# include<iostream>
# include<math.h>
# include<windows.h>
# include<vector>
# include<algorithm>
# include<cstdlib>
# include<ctime>

using namespace std;

# define delta 1e-12

//创建 h行l列的矩阵，并将初始各值设定为0
vector<vector<double>> creatmatrixA1()
{
	vector<vector<double>> v;
	v.push_back({0,0,0,0,0});
    v.push_back({0,1,2,3,4});
    v.push_back({0,2,5,6,7});
    v.push_back({0,3,6,8,9});
    v.push_back({0,4,7,9,10});
	return v;
}

vector<vector<double>> creatmatrixA2()
{
    double suiji;
	vector<vector<double>> v;
    v.push_back({0,0,0,0,0});
    for (int i = 1; i < 5; i++)
    {
        vector<double> temp;
        temp.push_back(0);
        for (int j = 1; j < 5; j++)
        {
            suiji = rand() % 10000 / 10000.0;
            temp.push_back(suiji);
        }
        v.push_back(temp);
    }
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

vector<double> getdiag(vector<vector<double>> A)
{
    vector<double> diag;
    diag.push_back(0);
    int m = A.size()-1;
    int n = A[0].size()-1;
    int i,j;
    for(i=1; i<=m; i++)
    {
        for(j=1; j<=n; j++)
        {
            if(i==j)
            {
                diag.push_back(A[i][j]);
            }
        }
    }
    return diag;
}

double calnondiagonalsum(vector<vector<double>> A)
{
    double sum = 0;
    int m = A.size()-1;
    int n = A[0].size()-1;
    int i,j;
    for(i=1; i<=m; i++)
    {
        for(j=1; j<=n; j++)
        {
            if(i!=j)
            {
                sum += A[i][j] * A[i][j];
            }
        }
    }
    return sum;
}

vector<double> picknondiagmodemax(vector<vector<double>> A)
{
    vector<double> result;
    double max = 0;
    double maxi, maxj;
    int m = A.size()-1;
    int n = A[0].size()-1;
    int i,j;
    for(i=1; i<=m; i++)
    {
        for(j=1; j<=n; j++)
        {
            if(i!=j)
            {
                if(max < abs(A[i][j]))
                {
                    max = abs(A[i][j]);
                    maxi = i;
                    maxj = j;
                }
            }
        }
    }
    result.push_back(max);
    result.push_back(maxi);
    result.push_back(maxj);
    return result;
}

double cals(vector<vector<double>> A, vector<double> result)
{
    int p = result[1];
    int q = result[2];
    double s;
    s = (A[q][q] - A[p][p])/(2*A[p][q]);
    return s;
}

double calt(double s)
{
    double t1, t2;
    if(s==0)
    {
        return 1;
    }
    else
    {
        t1 = -s - sqrt(s*s + 1);
        t2 = -s + sqrt(s*s + 1);
        if(abs(t1)>abs(t2))
        {
            return t2;
        }
        else
        {
            return t1;
        }
    }
}

vector<double> calcd(double t)
{
    vector<double> result;
    double c, d;
    c = 1/sqrt(1+t*t);
    d = c*t;
    result.push_back(c);
    result.push_back(d);
    return result;
}

int doJacobi(vector<vector<double>> &A, double t, double c, double d, int p, int q)
{
    for (int i = 1; i < A.size(); i++)
    {
        if (i != p && i != q)
        {
            A[i][p] = A[p][i] = (c*A[p][i] - d*A[q][i]);
            A[i][q] = A[q][i] = (c*A[q][i] - d*A[p][i]);
        }
    }
    A[p][p] = A[p][p] - t*A[p][q];
    A[q][q] = A[q][q] + t*A[p][q];
    A[p][q] = A[q][p] = 0;
    return 1;
}

vector<double> Jacobi(vector<vector<double>> A, double limit)
{
    int iteration = 0;
    vector<double> nondiagsum;
    nondiagsum.push_back(0);
    vector<double> diag;
    PrintMatrix(A);
    printf("Begin Jacobi:\n");
    double sum = calnondiagonalsum(A);
    while(sum > limit)
    {
        printf("Iteration %d\n",iteration);
        printf("nondiagonalsum: %.6f\n", sum);
        nondiagsum.push_back(sum);
        vector<double> result = picknondiagmodemax(A);
        double s = cals(A, result);
        double t = calt(s);
        double c = calcd(t)[0];
        double d = calcd(t)[1];
        doJacobi(A, t, c, d, result[1], result[2]);
        printf("After iteration %d:\n",iteration);
        PrintMatrix(A);
        iteration++;
        sum = calnondiagonalsum(A);
    }
    printf("End Jacobi\n");
    printf("This is nondiagsum %.6f\n");
    PrintVector(nondiagsum);
    diag = getdiag(A);
    return diag;
}

vector<vector<double>> lamdaIminusA(vector<vector<double>> A, vector<double> lamda)
{
    // use lamda I minus A
    vector<vector<double>> result;
    result.push_back({0,0,0,0,0});
    int m = A.size()-1;
    int n = A[0].size()-1;
    int i,j;
    for(i=1; i<=m; i++)
    {
        vector<double> row;
        for(j=1; j<=n; j++)
        {
            row.push_back(0);
            if(i==j)
            {
                row.push_back(lamda[i] - A[i][j]);
            }
            else
            {
                row.push_back(-A[i][j]);
            }
        }
        result.push_back(row);
        row.clear();
    }
    return result;
}

double caldet(vector<vector<double>> A)
{
    // calculate the determinant of a non-singular matrix
    int n = A.size()-1;
    if(n==1)
    {
        return A[1][1];
    }
    else
    {
        double det = 0;
        int i,j;
        for(i=1; i<=n; i++)
        {
            vector<vector<double>> B;
            for(j=1; j<=n; j++)
            {
                if(j!=i)
                {
                    vector<double> row;
                    row.push_back(A[j][1]);
                    row.push_back(A[j][2]);
                    B.push_back(row);
                }
            }
            det += pow(-1,i+1)*A[i][1]*caldet(B);
        }
        return det;
    }
}

double check(vector<vector<double>> A, vector<double> lamda)
{
    vector<vector<double>> result = lamdaIminusA(A, lamda);
    double det;
    det = caldet(result);
    return det;
}

int main()
{
    srand(time(NULL));
    vector<vector<double>> A1, A2;
    vector<double> diag1, diag2;
    double check1, check2;
    A1 = creatmatrixA1();
    A2 = creatmatrixA2();
    printf("A1:\n");
    diag1 = Jacobi(A1, delta);
    printf("This is eig value:\n");
    PrintVector(diag1);
    printf("check det(lamda I - A1):\n");
    check1 = check(A1, diag1);
    printf("%.6f\n", check1);
    printf("\n");
    printf("A2:\n");
    diag2 = Jacobi(A2, delta);
    printf("This is eig value:\n");
    PrintVector(diag2);
    printf("check det(lamda I - A2):\n");
    check2 = check(A2, diag2);
    printf("%.6f\n", check2);
}