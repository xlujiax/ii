// Maciej Pacut
// zad 3

#include <stdio.h>
#include <malloc.h>

#define Empty 0

typedef struct NodeSelf {
  int x;
  struct NodeSelf *left, *right;
} Node;

Node* AttachTo(Node* where, Node* what)
{
  return where->left = what;
}

Node* Leftmost(Node* actual)
{
  if(actual == 0)
    return 0;
  Node* leftmost = Leftmost(actual->left);
  if(leftmost == 0)
    return actual;
  else
    return leftmost;
}

void AttachToLeftmost(Node* leftmost_of, Node* what)
{
  AttachTo(Leftmost(leftmost_of), what);
}

void Destructure(Node* actual)
{
  if(actual == 0)
    return;

  Destructure(actual->left);
  Destructure(actual->right);

  AttachToLeftmost(actual, actual->right);
}

void FixRightsAux(Node* actual, Node* prev)
{
  if(actual == 0)
    return;
  actual->right = prev;
  FixRightsAux(actual->left, actual);
}

void FixRights(Node* top)
{
  FixRightsAux(top, Leftmost(top));
  Leftmost(top)->left = top;
}

Node* N(Node* left, int data, Node* right)
{
  Node* n = malloc(sizeof(Node));
  n->x = data;
  n->left = left;
  n->right = right;
  return n;
}

void Print(Node* actual)
{
  if(actual == 0)
    return;

  printf("%d\n", actual->x);

  Print(actual->left);
}

void do_kolejki(Node* n)
{
  Destructure(n);
  FixRights(n);
}

int main()
{
  Node* n = N(N(N(Empty, 4, Empty), 6, Empty), 3, N(Empty, 9, Empty));
  do_kolejki(n);
  Print(n);
  
  return 0;
}
