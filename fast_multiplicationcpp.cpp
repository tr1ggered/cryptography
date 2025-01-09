#include <iostream>
#include <limits> // Для работы с максимальными значениями типа
#include <cmath>  // Для функции sqrt
    using namespace std;

    // Функция быстрого возведения в квадрат с проверкой
    bool safeSquare(int number, int& result) {
        if (number > 0 && number > sqrt(numeric_limits<int>::max())) {
            // Если число слишком большое, чтобы результат помещался в int
            return false;
        }
        if (number < 0 && number < -sqrt(numeric_limits<int>::max())) {
            // Если отрицательное число слишком большое по модулю
            return false;
        }
        result = number * number; // Вычисление квадрата
        return true;
    }

    int main() {
        setlocale(LC_ALL, "Russian");
        int num;

        cout << "Введите число: ";
        while (!(cin >> num)) { // Проверка на некорректный ввод
            cout << "Ошибка: некорректный ввод. Введите целое число: ";
            cin.clear(); // Сбрасываем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер ввода
        }

        int result;
        if (safeSquare(num, result)) {
            cout << "Квадрат числа " << num << " равен " << result << endl;
        }
        else {
            cout << "Ошибка: квадрат числа " << num << " слишком большой для хранения в типе int." << endl;
        }

        return 0;
    }
