#include <iostream>
#include <cstdlib>
int main(int argc, char *argv[])
{
    if (argc <= 1) //car dans tous les cas ./add sera dedans
    {
        std::cerr << "not enough arguments" << std::endl;
        return -1;
    }
    else
    {
        int i = 1;
        int somme=0;
        while (i < argc)
        {
            somme=std::atoi(argv[i])+somme;
            i = i + 1;
        }
        std::cout << "le résultat est : "<<somme << std::endl;
    }
    
    
    return 0;
}
