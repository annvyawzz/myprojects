#ifndef CHISLA_H
#define CHISLA_H
#include <QDebug>
#include <cmath>

#pragma once

class NumberProcessor
{
public:
    NumberProcessor(int x = 0, int y = 0) : m_x(x), m_y(y) {}

    void setNumbers(int x, int y) { m_x = x; m_y = y; }
    int getX() const { return m_x; }
    int getY() const { return m_y; }

    int add() const { return m_x + m_y; }
    int subtract() const { return m_x - m_y; }
    int multiply() const { return m_x * m_y; }
    double divide() const {
        if (m_y == 0) {
            qWarning() << "Division by zero!";
            return 0.0;
        }
        return static_cast<double>(m_x) / m_y;
    }

    int gcd() const
    {
        int a = abs(m_x);
        int b = abs(m_y);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    int lcm() const
    {
        if (m_x == 0 || m_y == 0) return 0;
        return abs(m_x * m_y) / gcd();
    }

    bool isEqual() const { return m_x == m_y; }
    int max() const { return (m_x > m_y) ? m_x : m_y; }
    int min() const { return (m_x < m_y) ? m_x : m_y; }

    bool isXArmstrong() const { return isArmstrong(abs(m_x)); }
    bool isYArmstrong() const { return isArmstrong(abs(m_y)); }

    bool isXPrime() const { return isPrime(m_x); }
    bool isYPrime() const { return isPrime(m_y); }

private:
    int m_x;
    int m_y;


    static bool isArmstrong(unsigned int num)
    {
        if (num == 0) return false;
        unsigned int sum = 0;
        unsigned int original = num;
        unsigned int power = countDigits(num);

        while (num != 0) {
            unsigned int digit = num % 10;
            sum += std::pow(digit, power);
            num /= 10;
        }
        return sum == original;
    }

    static unsigned int countDigits(unsigned int num)
    {
        if (num == 0) return 1;
        unsigned int count = 0;
        while (num != 0) {
            num /= 10;
            count++;
        }
        return count;
    }

    static bool isPrime(int num)
    {
        if (num <= 1) return false;
        if (num == 2) return true;
        if (num % 2 == 0) return false;

        for (int i = 3; i * i <= num; i += 2)
        {
            if (num % i == 0) return false;
        }
        return true;
    }
};



#endif // CHISLA_H
