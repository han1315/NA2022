#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>

using namespace Eigen;
using namespace Eigen::internal;
using namespace Eigen::Architecture;
using namespace std;

class Spline
{
public:
    vector<double> X;
    vector<double> U;
    vector<double> L;

    void InputX(double a, double b, int n)
    {
        X.push_back(a);
        double h = (abs(a) + abs(b)) * 1.0 / (double(n) - 1.0);
        double temp = a;
        for (int i = 0; i < n - 2; i++)
        {
            temp = temp + h;
            X.push_back(temp);
        }
        X.push_back(b);
        X.insert(X.begin(), X[0]);
        X.push_back(X[X.size() - 1]);
    }

    void OutputX()
    {
        for (int i = 0; i < X.size(); i++)
        {
            cout << X[i] << endl;
        }
    }

    double f(double x)
    {
        return 1.0 / (1.0 + 25.0 * pow(x, 2));
    }

    double fd(double x)
    {
        return -50.0 * x / pow(1.0 + 25.0 * pow(x, 2), 2);
    }

    void Complete()
    {
        int n = X.size() - 2;

        for (int i = 2; i < n; i++)
        {
            U.push_back((X[i] - X[i - 1]) / (X[i + 1] - X[i - 1]));
            L.push_back((X[i + 1] - X[i]) / (X[i + 1] - X[i - 1]));
        }
        
        MatrixXd A(n, n);
        A.setZero();
        A(0, 0) = 1.0;
        A(n - 1, n - 1) = 1.0;
        for (int i = 1; i < n - 1; i++)
        {
            A(i, i) = 2.0;
        }
        for (int i = 1; i < n - 1; i++)
        {
            A(i, i - 1) = L[i - 1];
            A(i, i + 1) = U[i - 1];
        }

        MatrixXd T(X.size(), 4);
        T.setZero();
        for (int i = 0; i < X.size(); i++)
        {
            T(i, 0) = X[i];
        }
        for (int i = 0; i < X.size(); i++)
        {
            T(i, 1) = f(X[i]);
        }
        for (int i = 1; i < X.size(); i++)
        {
            if (T(i - 1, 0) == T(i, 0))
            {
                T(i, 2) = fd(X[i]);
            }
            else
            {
                T(i, 2) = ((T(i, 1) - T(i - 1, 1)) / (T(i, 0) - T(i - 1, 0)));
            }
        }
        for (int i = 2; i < X.size(); i++)
        {
            T(i, 3) = ((T(i, 2) - T(i - 1, 2)) / (T(i, 0) - T(i - 2, 0)));
        }

        MatrixXd B(X.size() - 2, 1);
        B(0, 0) = T(1, 2);
        B(X.size() - 3, 0) = T(X.size()-1, 2);
        for (int i = 1; i < X.size() - 3; i++)
        {
            B(i, 0) = 3.0 * L[i - 1] * T(i + 1, 2) + 3.0 * U[i - 1] * T(i + 2, 2);
        }

        MatrixXd M = A.inverse() * B;

        for (int i = 0; i < n - 1; i++)
        {     
            cout << noshowpos << f(X[i + 1]);	  
	    cout << showpos << T(i + 2, 2) - (2.0 * M(i, 0) + M(i + 1, 0)) * (X[i + 2] - X[i + 1]) / 6.0;
	    cout << "*(x" << -X[i + 1] << ")" << M(i, 0)/2.0 <<"*(x"<< -X[i + 1] <<")^2";
	    cout << (M(i + 1, 0) - M(i, 0)) / (6.0 * (X[i + 1] - X[i])) << "*(x" << -X[i + 1] << ")^3" << endl;
        }
    }

    void Natural()
    {
        int n = X.size() - 2;

        for (int i = 2; i < n; i++)
        {
            U.push_back((X[i] - X[i - 1]) / (X[i + 1] - X[i - 1]));
            L.push_back((X[i + 1] - X[i]) / (X[i + 1] - X[i - 1]));
        }

        MatrixXd A(n, n);
        A.setZero();
        A(0, 0) = 1.0;
        A(n - 1, n - 1) = 1.0;
        for (int i = 1; i < n - 1; i++)
        {
            A(i, i) = 2.0;
        }
        for (int i = 1; i < n - 1; i++)
        {
            A(i, i - 1) = U[i - 1];
            A(i, i + 1) = L[i - 1];
        }

        MatrixXd T(X.size(), 4);
        T.setZero();
        for (int i = 0; i < X.size(); i++)
        {
            T(i, 0) = X[i];
        }
        for (int i = 0; i < X.size(); i++)
        {
            T(i, 1) = f(X[i]);
        }
        for (int i = 1; i < X.size(); i++)
        {
            if (T(i - 1, 0) == T(i, 0))
            {
                T(i, 2) = fd(X[i]);
            }
            else
            {
                T(i, 2) = ((T(i, 1) - T(i - 1, 1)) / (T(i, 0) - T(i - 1, 0)));
            }
        }
        for (int i = 2; i < X.size(); i++)
        {
            T(i, 3) = ((T(i, 2) - T(i - 1, 2)) / (T(i, 0) - T(i - 2, 0)));
        }

        MatrixXd B(X.size() - 2, 1);
        B.setZero();
        for (int i = 1; i < X.size() - 3; i++)
        {
            B(i, 0) = 6.0 * T(i + 1, 3);
        }

        MatrixXd M = A.inverse() * B;

        for (int i = 0; i < n - 1; i++)
        {
	    cout << noshowpos << f(X[i + 1]);	  
	    cout << showpos << T(i + 2, 2) - (2.0 * M(i, 0) + M(i + 1, 0)) * (X[i + 2] - X[i + 1]) / 6.0;
	    cout << "*(x" << -X[i + 1] << ")" << M(i, 0)/2.0 <<"*(x"<< -X[i + 1] <<")^2";
	    cout << (M(i + 1, 0) - M(i, 0)) / (6.0 * (X[i + 1] - X[i])) << "*(x" << -X[i + 1] << ")^3" << endl;
        }
    }

    void NotaKnot()
    {
        int n = X.size() - 2;

        for (int i = 2; i < n; i++)
        {
            U.push_back((X[i] - X[i - 1]) / (X[i + 1] - X[i - 1]));
            L.push_back((X[i + 1] - X[i]) / (X[i + 1] - X[i - 1]));
        }
        
        MatrixXd A(n, n);
        A.setZero();
        A(0, 0) = -L[0];
        A(0, 1) = 1;
        A(0, 2) = -U[0];
        A(n - 1, n - 3) = -L[U.size() - 1];
        A(n - 1, n - 2) = 1.0;
        A(n - 1, n - 1) = -U[U.size() - 1];
        for (int i = 1; i < n - 1; i++)
        {
            A(i, i) = 2.0;
        }
        for (int i = 1; i < n - 1; i++)
        {
            A(i, i - 1) = U[i - 1];
            A(i, i + 1) = L[i - 1];
        }

        MatrixXd T(X.size(), 4);
        T.setZero();
        for (int i = 0; i < X.size(); i++)
        {
            T(i, 0) = X[i];
        }
        for (int i = 0; i < X.size(); i++)
        {
            T(i, 1) = f(X[i]);
        }
        for (int i = 1; i < X.size(); i++)
        {
            if (T(i - 1, 0) == T(i, 0))
            {
                T(i, 2) = fd(X[i]);
            }
            else
            {
                T(i, 2) = ((T(i, 1) - T(i - 1, 1)) / (T(i, 0) - T(i - 1, 0)));
            }
        }
        for (int i = 2; i < X.size(); i++)
        {
            T(i, 3) = ((T(i, 2) - T(i - 1, 2)) / (T(i, 0) - T(i - 2, 0)));
        }

        MatrixXd B(X.size() - 2, 1);
        B.setZero();
        for (int i = 1; i < X.size() - 3; i++)
        {
            B(i, 0) = 6.0 * T(i + 1, 3);
        }

        MatrixXd M = A.inverse() * B;

        for (int i = 0; i < n - 1; i++)
        {
            cout << noshowpos << f(X[i + 1]);	  
	    cout << showpos << T(i + 2, 2) - (2.0 * M(i, 0) + M(i + 1, 0)) * (X[i + 2] - X[i + 1]) / 6.0;
	    cout << "*(x" << -X[i + 1] << ")" << M(i, 0)/2.0 <<"*(x"<< -X[i + 1] <<")^2";
	    cout << (M(i + 1, 0) - M(i, 0)) / (6.0 * (X[i + 1] - X[i])) << "*(x" << -X[i + 1] << ")^3" << endl;
        }
    }


};

int main()
{
    Spline A1;
    A1.InputX(-1, 1, 6);
    cout << "Complete Cubic Spline with 6 nodes:" << endl;
    A1.Complete();
    cout << endl;

    Spline A2;
    A2.InputX(-1, 1, 11);
    cout << "Complete Cubic Spline with 11 nodes :" << endl;
    A2.Complete();
    cout << endl;

    Spline A3;
    A3.InputX(-1, 1, 21);
    cout << "Complete Cubic Spline with 21 nodes :" << endl;
    A3.Complete();
    cout << endl;

    Spline A4;
    A4.InputX(-1, 1, 41);
    cout << "Complete Cubic Spline with 41 nodes :" << endl;
    A4.Complete();
    cout << endl;

    Spline A5;
    A5.InputX(-1, 1, 81);
    cout << "Complete Cubic Spline with 81 nodes :" << endl;
    A5.Complete();
    cout << endl;
    
    cout << endl;
    Spline B1;
    B1.InputX(-1, 1, 6);
    cout << "Natural Cubic Spline with 6 nodes:" << endl;
    B1.Natural();
    cout << endl;

    Spline B2;
    B2.InputX(-1, 1, 11);
    cout << "Natural Cubic Spline with 11 nodes :" << endl;
    B2.Natural();
    cout << endl;

    Spline B3;
    B3.InputX(-1, 1, 21);
    cout << "Natural Cubic Spline with 21 nodes :" << endl;
    B3.Natural();
    cout << endl;

    Spline B4;
    B4.InputX(-1, 1, 41);
    cout << "Natural Cubic Spline with 41 nodes :" << endl;
    B4.Natural();
    cout << endl;

    Spline B5;
    B5.InputX(-1, 1, 81);
    cout << "Natural Cubic Spline with 81 nodes :" << endl;
    B5.Natural();
    cout << endl;

    cout << endl;
    Spline C1;
    C1.InputX(-1, 1, 6);
    cout << "Not a Knot Cubic Spline with 6 nodes:" << endl;
    C1.NotaKnot();
    cout << endl;

    Spline C2;
    C2.InputX(-1, 1, 11);
    cout << "Not a Knot Cubic Spline with 11 nodes :" << endl;
    C2.NotaKnot();
    cout << endl;

    Spline C3;
    C3.InputX(-1, 1, 21);
    cout << "Not a Knot Cubic Spline with 21 nodes :" << endl;
    C3.NotaKnot();
    cout << endl;

    Spline C4;
    C4.InputX(-1, 1, 41);
    cout << "Not a Knot Cubic Spline with 41 nodes :" << endl;
    C4.NotaKnot();
    cout << endl;

    Spline C5;
    C5.InputX(-1, 1, 81);
    cout << "Not a Knot Cubic Spline with 81 nodes :" << endl;
    C5.NotaKnot();
    cout << endl;
}

