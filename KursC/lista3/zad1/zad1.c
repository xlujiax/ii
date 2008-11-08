#include <stdio.h>
#include <stdlib.h>

#include "wym.h"

int main(int argc, char *argv[])
{
  Q a = read();
  Q b = read();
  printf("a: "); write(a); printf("\n");
  printf("b: "); write(b); printf("\n");
  printf("a / b: "); write(divide(a, b)); printf("\n");
  printf("a * b: "); write(multiple(a, b)); printf("\n");
  printf("a + b: "); write(plus(a, b)); printf("\n");
  printf("a - b: "); write(minus(a, b)); printf("\n");
  system("PAUSE");	
  return 0;
}
