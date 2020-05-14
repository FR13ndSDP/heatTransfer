#include <iostream>
using namespace std;

class XY
{
private:
    int x;
public:
    XY(int i)
    {
        x = 1;
    }

    XY()
    {
        
    }
    int change()
    {
        cout << x;
        x=5;
    }
    int cchange()
    {
        change();
        x=x+1;
    }
    void print()
    {
        cout << x;
    }
};

int main()
{
    XY a;
    a.change();
    a.print();
    return 0;
}