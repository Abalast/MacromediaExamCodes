// Exams.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

float DoSomethingFunction(float a, float b)
{
    float result;
    if (b > a)
        result = a / b;
    else if (a > b)
        result = b / a;
    else
        result = 1;

    return result;
}

int main()
{
    int sum = 0;
    int x = 5;
    float y = 1.5f;
    std::string part1 = "Hello";
    std::string part2 = "World!";
    float p = x * y;

    std::string input;
    std::string password = "Omnissiah";

    std::cout << "The value of x is " << x <<'\n'
              << "The value of y is " << y << '\n'
              << "Product is " << p << '\n'
              << part1 << " " << part2 << '\n';

    for (int i = 437; i <= 32482; i++)
        sum += i;

    std::cout << "The sum of all integers from 437 to 32482 is " << sum << '\n';

    float s = DoSomethingFunction(0, -1);
    std::cout <<"" << s << '\n';

    std::cout << "The machine spirit ask for the prayers" << '\n';
    std::cin >> input;

    if (input == password)
        std::cout << "Blessed thee. Performing Control Protocol" << '\n';
    else
        std::cout << "Tech-blasphemy. Initiate self-terminate Protocol.";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
