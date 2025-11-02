// inclusion de la librairie iostream pour les entrées/sorties
#include <iostream>

// pour compiler mettez-vous dans le répertoire où se trouve le fichier et faites
//   $ g++ main1.cpp -o main1
//   $
// main1 est l'exécutable correspondant à la compilation de votre programme main1.cpp

// pour exécuter
//   $ ./main1
//   Hello World !
//   $

// $ est ce qui apparaît dans votre terminal en début des lignes de commandes
// on appelle cela le prompt
// ce n'est peut être par un simple $ chez vous

// fonction à définir comme point d'entrée de votre programme
int main()
{

    // remarquez que le corps de la fonction est
    // une liste d'instructions séparées par des ;
    // le tout est entre {}
    // { code } est la définition d'un bloc de code

    std::cout << "Hello World !" << std::endl;

    // la fonction main retourne obligatoirement un int
    // 0 pour dire que tout s'est bien passé 
    return 0;
}
