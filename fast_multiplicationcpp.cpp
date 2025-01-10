#include <iostream>
#include <limits> // Для работы с максимальными значениями типа
    using namespace std;

    // Функция для проверки простоты числа
    bool isPrime(int number) {
        if (number <= 1) return false;
        for (int i = 2; i * i <= number; ++i) {
            if (number % i == 0) return false;
        }
        return true;
    }

    int main() {
        setlocale(LC_ALL, "Russian");

        int num;

        cout << "Введите число для проверки на простоту: ";

        // Проверяем ввод на корректность
        while (!(cin >> num)) {
            cout << "Ошибка: некорректный ввод. Введите целое число: ";
            cin.clear(); // Сбрасываем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер ввода
        }

        // Проверяем, чтобы число не было слишком большим для int
        if (cin.fail() || num > numeric_limits<int>::max() || num < numeric_limits<int>::min()) {
            cout << "Ошибка: введённое число слишком велико или некорректно." << endl;
            return 1;
        }

        // Проверка числа на простоту
        if (isPrime(num)) {
            cout << "Число " << num << " является простым." << endl;
        }
        else {
            cout << "Число " << num << " не является простым." << endl;
        }

        return 0;
    }
