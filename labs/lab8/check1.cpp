#include <iostream>

int Origin(int x, int y)
{
    int c = 0;
    if(x == 0 && y ==0)
    {
        return 1;
    }
    if(x > 0)
    {
        c+=Origin(x-1, y);
    }
    if(y > 0)
    {
        c+=Origin(x, y-1);
    }
    return c;
}

int main()
{
    std::cout << Origin(0, 0) << std::endl;
    std::cout << Origin(2, 1) << std::endl;
    std::cout << Origin(2,2) << std::endl;
}