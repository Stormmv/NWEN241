#include <iostream>
using namespace std;
namespace Complex
{
    class complex
    {
    private:
        int a, b;

    public:
        complex()
        {
            a = 1;
            b = 1;
        }
        complex(int x, int y)
        {
            a = x;
            b = y;
        }
        int geta()
        {
            return a;
        }
        int getb()
        {
            return b;
        }
    };
}

int main()
{
    Complex::complex c1;
    Complex::complex c2(5, 10);
    cout << "Complex number 1: " << c1.geta() << " + " << c1.getb() << "i" << endl;
    cout << "Complex number 2: " << c2.geta() << " + " << c2.getb() << "i" << endl;
    return 0;
}
