#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;


// структура для представления точек
struct Tochechka
{
    double y, x;
    Tochechka(double x = 0, double y = 0) : x(x), y(y) {}
};


// функция для нахождения расстояния между точками
double Evclidic(const Tochechka &a, const Tochechka &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


// Функция для вычисления длины маршрута
double Way_Length(const vector<int> &way, const vector<Tochechka> &points)
{
    int i = 0, len = way.size() - 1, backk = way.back(), frontt = way.front();
    double length = 0.0;

    for (i; i < len; ++i)
    {
        length += Evclidic(points[way[i]], points[way[i + 1]]);
    }

    return length + Evclidic(points[backk], points[frontt]); // считаем цикл, поэтому замыкаем цепочку
}


// 2-opt
void Opt2(vector<int> &way, const vector<Tochechka> &points, int n)
{
    bool fl = true;
    int i, j, N1 = n - 2, N2 = N1 + 1, i1, j1;
    while (fl)
    {
        double len = Way_Length(way, points);
        fl = false;
        for (i = 1; i < N1; i++)
        {
            for (j = i + 1; j < N2; j++)
            {
                i1 = i;
                j1 = j;
                while (i1 < j1)
                {
                    swap(way[i1++], way[j1--]);
                }

                double newlen = Way_Length(way, points);

                if (newlen < len)
                {
                    len = newlen;
                    fl = true;
                }
                else
                {
                    i1 = i;
                    j1 = j;
                    while (i1 < j1)
                    {
                        swap(way[i1++], way[j1--]);
                    }
                }
            }
        }
    }
}


// 3-opt
void Opt3(vector<int>& way, const vector<Tochechka>& points, int n)
{
    bool fl = true;
    int i, j, k, N1 = n - 2, N2 = n - 1;

    while (fl)
    {
        double len = Way_Length(way, points);
        fl = false;
        for (i = 1; i < N1; ++i)
        {
            for (j = i + 1; j < N2; ++j)
            {
                for (k = j + 1; k < n; ++k)
                {
                    reverse(way.begin() + i, way.begin() + j + 1);
                    reverse(way.begin() + j + 1, way.begin() + k + 1);

                    double newlen = Way_Length(way, points);
                    if (newlen < len)
                    {
                        fl = true;
                        len = newlen;
                    }
                    else
                    {
                        reverse(way.begin() + i, way.begin() + j + 1);
                        reverse(way.begin() + j + 1, way.begin() + k + 1);
                    }
                }
            }
        }
    }
}


int main()
{
    // Считываем данные
    int n, i = 0;
    cin >> n;

    vector<Tochechka> points(n);
    for (i; i < n; ++i)
    {
        cin >> points[i].x >> points[i].y;
    }

    // Инициализируем начальный путь 012345...
    vector<int> way(n + 1);
    for (i = 0; i < n; ++i)
    {
        way[i] = i;
    }
    way[n] = 0;

    // Применяем 2-opt и 3-opt улучшения
    Opt2(way, points, n + 1);
    Opt3(way, points, n + 1);

    // Выводим длину пути и сам путь
    double Answer = Way_Length(way, points);

    cout << Answer << " 1" << endl;

    for (i = 0; i < n + 1; ++i)
    {
        cout << way[i] << " ";
    }
    cout << endl;

    return 0;
}
