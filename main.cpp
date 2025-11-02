#include <iostream> //io stream=fichier de c++ et donne tous les fonctionnalités d'entrée et  sortie
#include <limits>


int marino(int a, int b, int c)
{
    return a+b+c;
}

int main(int argc, char *argv [])
{
    std::cout <<marino(10,10,10)<<std::endl;//renvoie b
    return 0; //renvoie tjrs un entier
}
