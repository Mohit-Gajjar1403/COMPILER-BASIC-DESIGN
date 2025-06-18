#include <bits/stdc++.h>
using namespace std;

// Global position variable to keep track of parsing progress
int pos = 0;
string input;

// Skip any whitespace characters to ensure clean parsing
void skipw()
{
    while (pos < input.size() && isspace(input[pos]))
        pos++;
}

// Parse and return the next full number (multi-digit allowed)
int getnum()
{
    skipw(); // Skip any spaces before a number
    int num = 0;
    while (pos < input.size() && isdigit(input[pos]))
    {
        num = num * 10 + (input[pos] - '0'); // Convert char to int
        pos++;
    }
    return num;
}

// Forward declarations to handle recursion
int expression(); // handles + and -
int term();       // handles * and /
int factor();     // handles numbers and brackets

// Handle brackets or direct numbers
int factor()
{
    skipw();
    if (input[pos] == '(')
    {
        pos++; // Skip '('
        skipw();
        int result = expression(); // Evaluate the inner expression
        skipw();
        if (input[pos] == ')') // Expect closing bracket
            pos++;
        return result;
    }
    else
        return getnum(); // If not bracketed, return the number
}

// Handle * and / operations
int term()
{
    int result = factor(); // Start with the first factor

    while (true)
    {
        if (input.size() <= pos)
            break;

        char op = input[pos];
        if (op == '*' || op == '/')
        {
            pos++; // Move to the next factor
            int nextterm = factor();

            if (op == '*')
                result *= nextterm;
            else
            {
                if (nextterm == 0)
                {
                    cout << "Error : Division by 0" << endl;
                    exit(1); // Exit on divide-by-zero
                }
                result /= nextterm;
            }
        }
        else
        {
            break; // No more * or /, so return
        }
    }

    return result;
}

// Handle + and - operations by combining terms
int expression()
{
    int result = term(); // Get the first term

    while (true)
    {
        skipw();
        if (pos >= input.size())
            break;

        char op = input[pos];
        if (op == '+' || op == '-')
        {
            pos++; // Move to next term
            int nextterm = term();

            // Add or subtract based on the operator
            result = op == '+' ? result + nextterm : result - nextterm;
        }
        else
            break;
    }

    return result;
}

int main()
{
    cout << "Enter an Arithematic Expression :" << endl;
    getline(cin, input); // Take entire line as input

    int result = expression(); // Start parsing and evaluating
    skipw();

    // Final check to make sure the expression is fully consumed
    if (pos != input.size())
        cout << "Not a Valid Expression use (digits , ( , ), + , - , * , / )" << endl;
    else
        cout << "\n\nResult of Expression : " << result << endl;

    return 0;
}
