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
    v.push_back({0,7.2,2.3,-4.4,0.5});
    v.push_back({0,1.3,6.3,-3.5,2.8});
    v.push_back({0,5.6,0.9,8.1,-1.3});
    v.push_back({0,1.5,0.4,3.7,5.9});
	return v;
}

void PrintMatrix(vector<vector<double>> A)
{
    int i,j;
    printf("\nA:");
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
    printf("\nx:");
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

void CalL2(vector<double> x1, vector<double> x2)
{
    double L2 = 0, dist;
    int i;
    int n = x1.size()-1;
    for(i=1; i<=n; i++)
    {
        dist = abs(x1[i] - x2[i]);
        L2 += dist * dist;
    }
    printf("\nL2 dist is : %.12f\n", L2);
}

vector<double> GaussCol(vector<vector<double>> A, vector<double> b)
{
    // A.size() == n+1
    int i,j,k;
    int n = A.size()-1;
    double coef;

    //消元得到上三角阵
    for (i=1; i<= n; i++)
    {
        //找列主元
        k = i;
        for(j = i+1; j <= n; j++)
        {
            if(abs(A[k][i]) < abs(A[j][i])) k=j;
        }

        //交换列主元
        for(j = i; j <= n; j++)
        {
            swap(A[k][j],A[i][j]);
        }
        swap(b[i],b[k]);

        //列主元消元
        for(j = i+1; j <= n; j++)
        {
            coef = A[j][i] / A[i][i];
            for(k = 1; k <= n; k++)
            {
                A[j][k] -= coef * A[i][k];
            }
            b[j] -= coef * b[i];
        }
    }
    PrintMatrix(A);

    //计算x[]
    for(i = n; i >= 1; i--)
    {
        for(j = i+1; j <= n; j++)
        {
            b[i] -= A[i][j] * b[j];
        }
        b[i] /= A[i][i]; 
    }
    return b;
}



int main()
{
    vector<vector<double>> A1, A2;
    vector<double> x1, x2;
    A1 = creatmatrixA1();
    A2 = creatmatrixA2();
    vector<double> b1 = {0,1,1,1,1,1};
    vector<double> b2 = {0,15.1,1.8,16.6,36.9};
    vector<double> b1_hat, b2_hat;

    x1 = GaussCol(A1, b1);
    PrintVector(x1);
    b1_hat = Mul(A1, x1);
    CalL2(b1, b1_hat);
    
    x2 = GaussCol(A2, b2);
    PrintVector(x2);
    b2_hat = Mul(A2, x2);
    CalL2(b2, b2_hat);
}


