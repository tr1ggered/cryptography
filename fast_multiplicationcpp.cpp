#include <iostream>
#include <random>
using namespace std;

// Функция для проверки простоты числа
bool isPrime(int number) {
    if (number <= 1) return false;
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) return false;
    }
    return true;
}

// Функция генерации случайного числа в заданном диапазоне
int generateRandomNumber(int min, int max) {
    random_device rd; // Источник энтропии
    mt19937 gen(rd()); // Генератор случайных чисел
    uniform_int_distribution<> dist(min, max); // Равномерное распределение
    return dist(gen);
}

// Функция для генерации простого числа
int generatePrime(int min, int max) {
    int candidate;
    do {
        candidate = generateRandomNumber(min, max);
    } while (!isPrime(candidate)); // Повторяем, пока не найдём простое число
    return candidate;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int min = 100, max = 1000; // Диапазон генерации

    cout << "Генерация простого числа в диапазоне от " << min << " до " << max << "..." << endl;
    int primeNumber = generatePrime(min, max);
    cout << "Сгенерировано простое число: " << primeNumber << endl;

    return 0;
}
