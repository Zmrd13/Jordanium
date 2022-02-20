#include <iostream>
#include <string>

using namespace std;

#define M 4//уравнений
#define n 3// переменные

class simpleFrac {
public:
    int c;
    int z;
    int res;
    simpleFrac(int c, int z) : c(c), z(z) {
        if (z == 0) {
            exit('2');
        }
        if (ceil((float) c / (float) z) == (float) c / (float) z) {
            res = ceil((float) c / (float) z);
        }
    };

    explicit simpleFrac(int c) : c(c), z(1) {

        if (ceil((float) c / (float) z) == (float) c / (float) z) {
            res = ceil((float) c / (float) z);
        }
    };

    string show() {
        if (ceil((float) c / (float) z) == (float) c / (float) z) {
            res = ceil((float) c / z);
            return to_string(res);
        } else {
            return to_string(c) + "/" + to_string(z);
        }
    }

    void div(int d) {
        z *= d;
    }

    void mult(int d) {
        c *= d;
    }

    void div(simpleFrac d) {
        z *= d.c;
        c *= d.z;
    }

    void mult(simpleFrac d) {
        c *= d.c;
        z *= d.z;
    }

    void plus(simpleFrac d) {
        if (z == d.z) {
            c += d.c;
        } else {
            int temp[2];
            temp[0] = d.z;
            temp[1] = z;
            z = d.z = d.z * z;
            c *= temp[0];
            d.c *= temp[1];
            c += d.c;
        }
    }

    void minus(simpleFrac d) {
        if (z == d.z) {
            c -= d.c;
        } else {
            int temp[2];
            temp[0] = d.z;
            temp[1] = z;
            z = d.z = d.z * z;
            c *= temp[0];
            d.c *= temp[1];
            c -= d.c;
        }
    }
   static void conv(simpleFrac &t) {
        int a = t.c;
        int b = t.z;
        if (a < 0)
            a *= -1;
        if (b < 0)
            b *= -1;
        if (b == 0 || a == 0) {
            return;
        }
        while (a - b != 0) {
            if (a > b)
                a -= b;
            else
                b -= a;
        }

        t.c /= a;
        t.z /= b;
        if (t.c < 0 && t.z < 0) {
            t.c /= -1;
            t.z /= -1;
        }
        if (t.c > 0 && t.z < 0) {
            t.c /= -1;
            t.z /= -1;
        }
    };
};

//void conv(simpleFrac &t) {
//    int a = t.c;
//    int b = t.z;
//    if (a < 0)
//        a *= -1;
//    if (b < 0)
//        b *= -1;
//    if (b == 0 || a == 0) {
//        return;
//    }
//    while (a - b != 0) {
//        if (a > b)
//            a -= b;
//        else
//            b -= a;
//    }
//
//    t.c /= a;
//    t.z /= b;
//    if (t.c < 0 && t.z < 0) {
//        // cout<<"asd";
//        t.c /= -1;
//        t.z /= -1;
//    }
//    if (t.c > 0 && t.z < 0) {
//        // cout<<"asd";
//        t.c /= -1;
//        t.z /= -1;
//    }
//};

int PerformOperation(simpleFrac a[][M]) {
    int i, j, k = 0, c, flag = 0, m = 0;
    simpleFrac pro(1);
    for (i = 0; i < n; i++) {
        if (a[i][i].c == 0) {
            c = 1;
            while ((i + c) < n && a[i + c][i].c == 0)
                c++;
            if ((i + c) == n) {
                flag = 1;
                break;
            }
            for (j = i, k = 0; k <= n; k++)
                swap(a[j][k], a[j + c][k]);
        }
        for (j = 0; j < n; j++) {
            if (i != j) {
                simpleFrac h = a[j][i];
                h.div(a[i][i]);
                pro = h;
                for (k = 0; k <= n; k++) {
                    h = a[i][k];
                    h.mult(pro);
                    a[j][k].minus(h);
                    //                    a[j][k] = a[j][k] - (a[i][k]) * pro;
                }
            }
        }
    }
    return flag;
}

void PrintResult(simpleFrac a[][M], int flag) {
    cout << "Result is : ";
    if (flag == 2)
        cout << "Infinite Solutions Exists" << endl;
    else if (flag == 3)
        cout << "No Solution Exists" << endl;
    else {
        for (int i = 0; i < n; i++) {
            simpleFrac t = a[i][n];
            t.div(a[i][i]);
            simpleFrac::conv(t);
            cout << t.show() << " ";
        }
    }
}

void PrintMatrix(simpleFrac a[][M]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            simpleFrac::conv(a[i][j]);
            cout << a[i][j].show() << " ";
        }
        cout << endl;
    }
}

int main() {

    simpleFrac a[n][M] = {{simpleFrac(3), simpleFrac(2), simpleFrac(-5), simpleFrac(-1)},
                         {simpleFrac(2), simpleFrac(-1), simpleFrac(3), simpleFrac(13)},
                         {simpleFrac(1), simpleFrac(2), simpleFrac(-1), simpleFrac(9)}};
    int flag = 0;
    flag = PerformOperation(a);
    PrintMatrix(a);
    PrintResult(a, flag);


    return 0;
}
