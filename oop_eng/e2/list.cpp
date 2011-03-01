// List data structure implemented by Hans de Nivelle
// modified by Maciej Pacut

#include <iostream>
#include <cstdlib>

struct list
{
  unsigned int val;
  list* next;
};



// Add an element to the front of the list:

void addfront( unsigned int x, list* & l )
// The second parameter is a reference to a pointer to a list.
// The parameter is reference, because addfront needs to modify
// it. I will explain the lecture, why using a function is
// unsafe here.
{
  list* res = new list;

  ( res -> val ) = x;
  // This is alternative notation for (*res). val = x;
  ( res -> next ) = l;
  // (*res). next = l;

  l = res;
}

unsigned int length(const list* lst)
{
  int len = 0;
  while(lst)
  {
    ++len;
    lst = lst->next;
  }
  return len;
}

unsigned int sum(const list* lst)
{
  int s = 0;
  while(lst)
  {
    s += lst->val;
    lst = lst->next;
  }
  return s;
}

// creates copy of list lst by adding elements to the end of the new list
// complexity O(n) is obtained by keeping pointer to last cell of new list
list* makecopy(const list* lst)
{
  if(!lst) return 0;

  // list not empty; creating new list and copying first element of original list into it
  list* new_lst = new list;
  new_lst->val = lst->val;

  // iteration from second element of original list
  lst = lst->next;

  // iteration creates new cells and attaches them to end of new list
  list* last_cell = new_lst;
  while(lst)
  {
    list* new_cell = new list;
    new_cell->val = lst->val;
    last_cell->next = new_cell;
    last_cell = new_cell; // actualize last cell as we attached new cell in line one above
    lst = lst->next;
  }
  
  last_cell->next = 0;
  return new_lst;
}

void print_lst(const list* lst)
{
  while(lst)
  {
    std::cout << lst->val << ' ';
    lst = lst->next;
  }
  std::cout << '\n';
}

void swap_vals(list* const cell1, list* const cell2)
{
  unsigned int temp = cell1->val;
  cell1->val = cell2->val;
  cell2->val = temp;
}

// auxilary procedure for bubblesort
void bubble_one(list* lst)
{
  while(lst && lst->next)
  {
    if(lst->val > lst->next->val)
      swap_vals(lst, lst->next);
    lst = lst->next;
  }
}

void bubblesort(list& x)
{
  unsigned int len = length(&x);
  for(unsigned int i = 0; i < len; ++i)
    bubble_one(&x);
}

void deletelist( list* lst )
{
  while(lst)
  {
    list* temp = lst;
    lst = lst->next;
    delete temp;
  }
}

void manual_test()
{
  
  unsigned int n;
  std::cout << "how many numbers do you want to type: ";
  std::cin >> n;

  list* lst = 0;
  for( unsigned int i = 0; i < n; ++ i )
  {
    std::cout << i << ": ";

    unsigned int v;
    std::cin >> v;
    addfront( v, lst );
  }

  for( list* q = lst; q != 0; q = (*q). next )
  {
    std::cout << (*q). val << " ";
  }
  std::cout << "\n";

  std::cout << "length of list is " << length(lst) << '\n';
  std::cout << "   sum of list is " << sum(lst) << '\n';

  if(length(lst) < 5)
    std::cout << "you need list of at least 5 length to run copy test\n";
  else
  {
    std::cout << "original list:\n";
    print_lst(lst);
    list* new_lst = makecopy(lst);
    std::cout << "copied list:\n";
    print_lst(new_lst);

    std::cout << "let's modify copied list at it's third and fifth argument\n";
    new_lst->next->next->val = 1113;
    new_lst->next->next->next->next->val = 1115;

    print_lst(new_lst);

    std::cout << "original list remains the same\n";
    print_lst(lst);

    std::cout << "let's modify original list at it's fourth element\n";
    lst->next->next->next->val = 2224;
    print_lst(lst);

    std::cout << "copied list remains the same as after it's modifiaction\n";
    print_lst(new_lst);
    deletelist(new_lst);
  }

  std::cout << "(bubble)sorted list:\n";
  bubblesort(*lst);
  print_lst(lst);

  deletelist(lst);

  
}

void top_test(const int iterations)
{
  for(int i = 0; i < iterations; ++i)
  {
    int len = rand() % 10 + 10;
    list* lst = 0;
    for(int j = 0; j < len; ++j)
      addfront(rand() % 20, lst);

    int copies = rand() % 5 + 5;
    for(int j = 0; j < copies; ++j)
    {
      list* copy = makecopy(lst);
      deletelist(copy);
    }
    deletelist(lst);
  }
}

int main( unsigned int argc, char * args [] )
{
  //top_test(10000000);
  manual_test();
}


