#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

// Утилита для деления числа на части
vector<long long> splitNumber(long long num, int parts, int base) {
    vector<long long> result(parts, 0);
    for (int i = 0; i < parts; ++i) {
        result[i] = num % base;
        num /= base;
    }
    return result;
}

// Метод Карацубы
long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10) {
        return x * y;
    }

    int numDigits = max((int)log10(x) + 1, (int)log10(y) + 1);
    int half = numDigits / 2;

    long long base = pow(10, half);
    long long a = x / base;
    long long b = x % base;
    long long c = y / base;
    long long d = y % base;

    long long ac = karatsuba(a, c);
    long long bd = karatsuba(b, d);
    long long ad_plus_bc = karatsuba(a + b, c + d) - ac - bd;

    return ac * pow(10, 2 * half) + ad_plus_bc * base + bd;
}

// Метод Туума-Кука
long long toomCook(long long x, long long y) {
    // Разделение числа на 3 части
    int base = 1000; // Используем базу 10^k, где k = 3 (можно настроить)
    vector<long long> xParts = splitNumber(x, 3, base);
    vector<long long> yParts = splitNumber(y, 3, base);

    // Подсчёт значений полинома в точках
    long long p0 = xParts[0] * yParts[0];
    long long p1 = (xParts[0] + xParts[1] + xParts[2]) * (yParts[0] + yParts[1] + yParts[2]);
    long long p2 = (xParts[0] - xParts[1] + xParts[2]) * (yParts[0] - yParts[1] + yParts[2]);
    long long p3 = (xParts[0] + 2 * xParts[1] + 4 * xParts[2]) * (yParts[0] + 2 * yParts[1] + 4 * yParts[2]);
    long long p4 = (xParts[0] - 2 * xParts[1] + 4 * xParts[2]) * (yParts[0] - 2 * yParts[1] + 4 * yParts[2]);

    // Интерполяция
    long long r0 = p0;
    long long r4 = p4;
    long long r3 = (p3 - p1) / 2;
    long long r1 = (p1 - p2) / 2;
    long long r2 = (p2 - p0 - p4) / 2;

    // Объединение результата
    return r0 + r1 * base + r2 * pow(base, 2) + r3 * pow(base, 3) + r4 * pow(base, 4);
}

// Метод Шёнхаге-Штрассена
long long schoenhageStrassen(long long x, long long y) {
    // Реализация метода Шёнхаге-Штрассена требует работы с числами как с полиномами и FFT.
    // Здесь представлена упрощённая версия для демонстрации принципа работы.

    vector<int> xDigits, yDigits;
    while (x > 0) {
        xDigits.push_back(x % 10);
        x /= 10;
    }
    while (y > 0) {
        yDigits.push_back(y % 10);
        y /= 10;
    }

    reverse(xDigits.begin(), xDigits.end());
    reverse(yDigits.begin(), yDigits.end());

    int n = max(xDigits.size(), yDigits.size());
    xDigits.resize(n, 0);
    yDigits.resize(n, 0);

    vector<int> result(2 * n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i + j] += xDigits[i] * yDigits[j];
        }
    }

    for (int i = 0; i < result.size() - 1; ++i) {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    long long finalResult = 0;
    for (int i = result.size() - 1; i >= 0; --i) {
        finalResult = finalResult * 10 + result[i];
    }

    return finalResult;
}

// Простое умножение для сравнения
long long simpleMultiplication(long long x, long long y) {
    return x * y;
}

// Тестирование всех методов
int main() {
    setlocale(LC_ALL, "Russian");
    long long x = 123456789;
    long long y = 987654321;

    cout << "Умножение методом простого умножения:\n";
    cout << x << " * " << y << " = " << simpleMultiplication(x, y) << endl;

    cout << "Умножение методом Карацубы:\n";
    cout << x << " * " << y << " = " << karatsuba(x, y) << endl;

    cout << "Умножение методом Туума-Кука:\n";
    cout << x << " * " << y << " = " << toomCook(x, y) << endl;

    cout << "Умножение методом Шёнхаге-Штрассена:\n";
    cout << x << " * " << y << " = " << schoenhageStrassen(x, y) << endl;

    return 0;
}
