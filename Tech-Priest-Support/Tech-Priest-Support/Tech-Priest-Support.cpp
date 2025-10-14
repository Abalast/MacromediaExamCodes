// Tech-Priest-Support.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstdlib>

int main()
{
    std::string input;
    std::string passwort = "Omnissiah";
    int attempts = 0;
    int maxAttempts = 3;

    std::cout << "Blessed is the Omnissiah!\n";

    while (attempts < maxAttempts)
    {
        std::cout << "Enter prayer to access holy system\n";
        std::cin >> input;

        if (input == passwort)
        {
            std::cout << "You are blessed. Access Granted.\n";
            return 0;
        }
        
        attempts++;

        if (attempts < maxAttempts)
            std::cout << "Access Denied. " << maxAttempts - attempts << " chances until machine spirits declares you as a Heretek.\n";
        else
            break;
    }

    std::cout << "Access Denied! Tech-blasphemy will not be tolerated, Heretek!\n";
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
