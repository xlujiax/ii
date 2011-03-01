

#include <iostream>


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


int main( unsigned int argc, char * args [] )
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
}


