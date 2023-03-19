using namespace std;
#include <iostream>
double U(double r)
{
    double a = 1;
    double b = 1;
    double c = pow(r, -2);
    return c * (-a + b * c);
}
double yp(double(*f)(double), double E, double r)
{
    return U(r) - E;
}
double FindRoot(double (*f)(double), double a, double b, double eps, double E)
{
    double c;
    while ((b - a) / 2 > eps)
    {
        c = (a + b) / 2;
        if ((yp(f, E, a) * yp(f, E, c)) > 0)
        {
            a = c;
        }
        else
        {
            b = c;
        }
    }
    return c;
}

double S(double (*f)(double, double), double a, double b, double* A, double* X, double E)
{
    double sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += f((a + b) / 2. + (b - a) * X[i] / 2., E) * A[i];
    }
    sum *= (b - a) / 2.;
    return sum;
}
double f(double r, double E)
{
    double M = 1;
    return 2 * M * sqrt(abs(E - U(r)));
}
void coef(double* x, double* A)
{
    double polynom[10] = { -0.974, -0.865, -0.679, -0.433, -0.149, 0.149, 0.433, 0.679, 0.865, 0.974 };
    double polynom1[10];
    double ans[10];
    for (int i = 0; i < 10; i++)
    {
        polynom1[i] = (polynom[i] * (27720 - 480480 * pow(polynom[i], 2) + 2162160 * pow(polynom[i], 4) - 3500640 * pow(polynom[i], 6) + 1847560 * pow(polynom[i], 8))) / 1024;
    }

    for (int i = 0; i < 10; i++)
    {
        ans[i] = 2 / ((1 - pow(polynom[i], 2)) * pow(polynom[i], 2));
    }
    for (int i = 0; i < 10; i++)
    {
        x[i] = polynom[i];
        A[i] = ans[i];
    }
}
void search(double (*f)(double, double), double &res_a, double &res_b, double* A, double* X, double E,double &E_)
{
    bool N = true;
    double eps = 0.0001;
    double a, b;
    double h = 0.1;
    double res;
    int  i = 0;
    do {
        E_ += i * h;
        i++;
        /*cout << E_ << endl;
        
        cout << h << endl;*/
        a = FindRoot(U, 0, 1.4142, 0.0001, E_);
        b = FindRoot(U, 1.4142, 10, 0.0001, E_);
        res = -S(f, a, b, A, X, E);
        /*cout << a << "  " << b << endl;*/
        if (res < E && abs(res - E) > eps)
        {
            if (h < 0)
            {
                h *= -1;
            }
        }
        else if (res > E && abs(res - E) > eps)
        {
            if (h > 0)
            {
                h *= -1;
            }
            h /= 1.2;
        }
        else
        {
            N = false;
        }
        
    } while (N == true);
    res_a = a;
    res_b = b;
}

int main()
{
    double h_ = 0.1;
    double pi = 3.1415926535;
    double* x = new double[10];
    double* A = new double[10];
    double a, b;
    double a_, b_;
    double eps = 0.00001;
    coef(x, A);

    //double** result = new double*[4];
    //for (int i = 0; i < 4; i++)
    //{
    //    result[i] = new double[1000];
    //}
    //int n = 0;
    //double C;
    double E_min = -0.25;
    double E_step = 0.001;
    double E_max = 0;
    double E;
    double E_ = -0.25;
    int i = 0;
    do {
        E = -0.25 + h_ * (i + 1. / 2.);
        cout << E << endl;
        search(f, a, b, A, x, E, E_);
        cout << a << "   " << b << endl;
        cout << E_ << endl;
        i++;
    } while (i < 5);
}
