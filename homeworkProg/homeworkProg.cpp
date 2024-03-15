#include <iostream>
#include <string>

// Функция для выполнения поразрядного сложения чисел
std::string add(std::string num1, std::string num2) {
    int carry = 0;
    std::string result = "";

    // Добавляем ведущие нули к строкам, чтобы их длины совпадали
    while (num1.size() < num2.size()) {
        num1 = "0" + num1;
    }

    while (num2.size() < num1.size()) {
        num2 = "0" + num2;
    }

    // Проходим по числам справа налево и складываем цифры
    for (int i = num1.size() - 1; i >= 0; i--) {
        int digit1 = num1[i] - '0';
        int digit2 = num2[i] - '0';

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        sum = sum % 10;

        result = std::to_string(sum) + result;
    }

    // Если остался остаток, добавляем его к результату
    if (carry != 0) {
        result = std::to_string(carry) + result;
    }

    return result;
}

// Функция для выполнения поразрядного вычитания чисел
std::string subtract(std::string num1, std::string num2) {
    int borrow = 0;
    std::string result = "";

    // Добавляем ведущие нули к строкам, чтобы их длины совпадали
    while (num1.size() < num2.size()) {
        num1 = "0" + num1;
    }

    while (num2.size() < num1.size()) {
        num2 = "0" + num2;
    }

    // Проходим по числам справа налево и вычитаем цифры
    for (int i = num1.size() - 1; i >= 0; i--) {
        int digit1 = num1[i] - '0';
        int digit2 = num2[i] - '0';

        int diff = digit1 - digit2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }

        result = std::to_string(diff) + result;
    }

    return result;
}


// Функция для выполнения поразрядного умножения чисел
std::string multiply(std::string num1, std::string num2) {
    std::string result = "0";

    // Проходим по второму числу справа налево и умножаем каждую цифру на первое число
    for (int i = num2.size() - 1; i >= 0; i--) {
        int digit = num2[i] - '0';
        std::string partialProduct = "";
        int carry = 0;

        // Умножаем каждую цифру первого числа на текущую цифру второго числа
        // и складываем результаты
        for (int j = num1.size() - 1; j >= 0; j--) {
            int multiplicand = num1[j] - '0';
            int product = multiplicand * digit + carry;
            carry = product / 10;
            product = product % 10;

            partialProduct = std::to_string(product) + partialProduct;
        }

        if (carry != 0) {
            partialProduct = std::to_string(carry) + partialProduct;
        }

        // Добавляем ведущие нули к результату умножения
        for (int k = 0; k < num2.size() - 1 - i; k++) {
            partialProduct += "0";
        }

        result = add(result, partialProduct);
    }

    return result;
}


// Функция для выполнения поразрядного деления чисел
std::string divide(std::string num1, std::string num2) {
    std::string quotient = "";
    std::string remainder = num1;

    // Пока остаток больше или равен делителю, выполняем деление
    while (remainder >= num2) {
        int divisor = std::stoi(num2);
        int i = 0;

        // Вычитаем делитель из остатка до тех пор, пока это возможно
        while (std::stoi(remainder) >= divisor) {
            remainder = subtract(remainder, num2);
            i++;
        }

        quotient += std::to_string(i);
    }

    return quotient;
}


int main() {

    setlocale(LC_ALL, "ru");

    std::string num1 = "1234";
    std::string num2 = "617";

    std::cout << "Сложение: " << add(num1, num2) << std::endl;
    std::cout << "Вычитание: " << subtract(num1, num2) << std::endl;
    std::cout << "Умножение: " << multiply(num1, num2) << std::endl;
    std::cout << "Деление: " << divide(num1, num2) << std::endl;

    return 0;
}