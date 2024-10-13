#include <iostream>

using namespace std;

int suma(int a, int b, int c)
{
    return a+b+c;
}

int suma(int a, int b)
{
    return a+b;
}

int main(int argc, char* argv[])
{
    cout << suma(1,2) << endl;
    cout << suma(1,2,3) << endl;
    return 0;
}