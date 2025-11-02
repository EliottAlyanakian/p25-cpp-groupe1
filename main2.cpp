#include <iostream>

// pour compiler mettez-vous dans le répertoire où se trouve le fichier et faites
//   $ g++ main2.cpp -o main2
// pour exécuter
//   $ ./main2
//   Résultat -33
//   $

// définition d'une fonction
// type de retour: int
// nom de la fonction: add
// liste des arguments: (int a, int b, int c)

int add(int a, int b)
{
    // le corps de la fonction
    return a + b;
}

int main()
{

    // appel de la fonction
    // c++ vérifie que le type de retour et les types des arguments
    // sont corrects vis à vis de la définition
    int res = add(12, -45);

    std::cout << "Résultat " << res << std::endl;

    return 0;
}
