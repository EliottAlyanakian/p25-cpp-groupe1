#include <iostream>

// pour compiler mettez-vous dans le répertoire où se trouve le fichier et faites
//   $ g++ main3.cpp -o main3
// pour exécuter ./main3  bonjour 12 78.90 "Hello World !"

//    $ ./main3  bonjour 12 78.90 "Hello World !"
//    ./main3
//    bonjour
//    12
//    78.90
//    Hello World !
//    ./main3
//    bonjour
//    12
//    78.90
//    Hello World !
//    $

// pour récupérer les arguments passés lors de l'appel de l'exécutable
// l'implémente la fonction main avec ses deux arguments:
//   - argc qui est le nombre de chaînes de caractères séparées par des espaces sur la ligne que vous avez tapée
//     pour mettre des espaces dans une même chaîne de caractère mettez des "" autour
//   - argv qui est le tableau qui contient les chaînes de caractères correspondantes

int main(int argc, char *argv[])
{

    // on parcourt le tableau des arguments et on les affiche

    // avec une boucle while
    // while (condition) { code }
    int i = 0;
    while (i < argc)
    {
        std::cout << argv[i] << std::endl;
        i = i + 1;
    }

    // remarquez les instructions séparées par des ;
    // remarquez les {} autour de la liste d'instructions
    // pour les considérer dans le corps du while

    // avec une boucle for
    // for (initialisation; condition; incrément) { code }
    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    return 0;
}
