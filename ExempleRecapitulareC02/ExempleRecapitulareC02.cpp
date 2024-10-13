#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    int intreg = 10;

    int intreg2 = 10;

    intreg2++;

    cout<< intreg << endl;

    int& rIntreg = intreg;
    rIntreg++;

    cout<< intreg << endl;
    
    return 0;
}
