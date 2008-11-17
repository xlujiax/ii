// Maciej Pacut
// Lista 5
// zad 1

// to funkcyjna (w sensie braku destrukcyjnych modyfikacji) implementacja jednostornnie po³¹cznych list

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    
    printf("lista 1:\n");
    struct List* lst = lGenerate(5);
    lPrint(lst);
    
    printf("dodanie wartoœci 5 na pocz¹tek listy 1:\n");
    lst = lConcat(lst, 5);
    lPrint(lst);
    
    printf("kopia listy 1:\n");
    struct List* lst2 = lCopy(lst);
    lPrint(lst);
    
    printf("lista 2 powsta³a w wyniku odwrócenia listy 1:\n");
    struct List* rlst = lReverse(lst);
    lPrint(rlst);
    
    printf("lista 3 powsta³a w wyniku z³¹czenia list 1 i 2:\n");
    struct List* two = lAppend(lst, rlst);
    lPrint(two);
    
    printf("dlugoœæ z³¹czonej listy:\n%d\n", lLength(two));
    
    printf("wstawianie do tablicy:\n");
    printf("mamy tablicê:\n");
    struct List* sorted = lEmpty(); // wstawiane s¹ na pocz¹tek, wiêc kolejnoœæ bêdzie odwrotna
    sorted = lConcat(sorted, 9);
    sorted = lConcat(sorted, 7);
    sorted = lConcat(sorted, 5);
    sorted = lConcat(sorted, 3);
    sorted = lConcat(sorted, 1);
    lPrint(sorted);
    printf("wstawiamy 4:\n");
    sorted = lInsertToSorted(sorted, 4);
    lPrint(sorted);
    
    lCleanup(rlst);
    lCleanup(two);
    lCleanup(lst);
    lCleanup(lst2);
  
    system("PAUSE");	
    return 0;
}
