

#include <iostream>



struct digit 
{
   char n;
   digit* next;
};



// One has to decide what to do with zero. The most natural representation
// is the empty list. Because then the invariant is that leading
// zeros are always deleted. 
// This makes printing a little bit harder (because 0 should not be 
// printed as empty string), but one should always prefer the most
// natural invariant.


// I have seen may solutions, but the simplest is to use recursion.
// The aim of the task was to have some fun, and to see how
// complicated structures can be built in a natural way if one uses
// the right constructions. 

digit* buildbigint( unsigned int x )
{
   if( x == 0 )
      return 0;
   else
   {
      digit* res = new digit;
      res -> n = ( x % 10 ) + '0';
      res -> next = buildbigint( x / 10 );
      return res; 
   }
}


void printbigint2( const digit* );
   // This is necessary because printbigint uses printbigint2. 

void printbigint( const digit* d )
{
   if( d == 0 )
      std::cout << '0';
   else
      printbigint2( d );
   // The reason for the distinction is the fact that otherwise,
   // nothing would be printed for the number 0.

}

void printbigint2( const digit* d )
{
   if( d != 0 )
   {
      printbigint2( d -> next );
      std::cout << ( d -> n );
   }
}


////////////////////////////////////////////////////////////
// We are now going to prepare for addto


// I really believe that this is the easiest way to do it:
//    Don't be afraid to use recursion!
//    Don't be afraid to use references!


void removeuselesszeroes( digit* & d ) 
{
   if(d)
   {
      removeuselesszeroes( d -> next );
      // If d -> next == 0, and d -> n == '0', then
      // d has become a useless zero by itself, and it has
      // to be removed. 

      if( d -> next == 0 && d -> n == '0' )
      {
         delete d;
         d = 0;
      }
   }
}
   

// The following function makes sure that that number d has 
// at least n positions by adding zeroes if necessary.  
// If d is longerthan n, then the function does nothing.
// This makes the implementation of addition/subtraction/multiplication
// much much easier. 
// Note the use of the reference in the parameter.

void addzeroes( digit* &d, unsigned int n )
{
   if( n > 0 )
   {
      if(d)
         addzeroes( d -> next, n - 1 );
      else
      {
         // This is the easiest way that I could think of:
        
         d = new digit;
         ( d -> n ) = '0'; 
         ( d -> next ) = 0; 
         addzeroes( d -> next, n - 1 );
      }
   }
}


// Returns the length of the representation of d. Non-significant
// zeroes are counted.

unsigned int length( const digit* d )
{
   if(d)
      return length( d -> next ) + 1;
   else
      return 0;
}



// We first compute c1 + k*c2 + carry, where c1,c2 are interpreted
// as ASCII representationsof digits. After that we split the result 
// into a new char and the new carry. 
// This function is designed in such a way that it can be used
// for muliplication, addition (with k = 1), and subtraction (with k = -1)


char adddigits( char c1, int k, char c2, int& carry )
{
   int sum = ( c1 - '0' ) + k * ( c2 - '0' ) + carry;

   carry = 0; 
   if( sum < -1000 ) exit(0);

   if( sum < 0 )
   {
      // I do this, because I am about the outcome of -1 / 7.
      // I think that it would be 0, (with mod -1) but I need -1,
      // (and mod 6)

      sum += 1000;
      carry = -100;
   }
   else
      carry = 0;

   carry += ( sum / 10 );
   sum = sum % 10;
   return sum + '0';
}


void addto2( int& carry, const digit* d1, digit* & d2 );
   // Forward declaration.

// I admit that I forgot in the task to make d2 a reference.
// But was it so hard to find this out by yourself?


void addto( const digit* d1, digit* & d2 )
{
   unsigned int l1 = length( d1 );
   unsigned int l2 = length( d2 );

   unsigned int neededlength;
   if( l1 > l2 )
      neededlength = l1 + 2;
   else
      neededlength = l2 + 2;
         // Of course you can show your smartness and use ? :,  but
         // such code tends to be unreadable.
         // Every extra variable is an opportunity to introduce a name,
         // which you can use for explaining what it is for.
 
   addzeroes( d2, neededlength );

   int carry = 0; 
   addto2( carry, d1, d2 );
   if(carry)
   {
      std::cerr << "number did not fit"; exit(0);
   }

   removeuselesszeroes( d2 );
}
 

void addto2( int& carry, const digit* d1, digit* & d2 )
{
   if(d2)
   {
      if( d1 == 0 )
      {
         d2 -> n = adddigits( '0', 1, d2 -> n, carry );  
         addto2( carry, 0, d2 -> next ); 
      }
      else
      {
         d2 -> n = adddigits( d1 -> n, 1, d2 -> n, carry );
         addto2( carry, d1 -> next, d2 -> next );
      } 
   }
}


// Subtraction has the same structure as addition. 
// If the carry is not zero after the subtraction, this means that
// d1 < d2. In that case you must clean up d2 completely, so that
// the result will be 0.


// I don't think that multiplication is hard.
// First compute the maximal length of the result.
// Then create a chain of zeroes that is big enough to contain
// the result. Then use a double for loop. That's all.
// 
// The result should be a reference.
// multiply( const digit* d1, const digit* d2, digit* & d3 );



int main( unsigned int argc, char * argv [] )
{
   digit* d1 = buildbigint(77);
   digit* d2 = buildbigint(0);

   for( unsigned int k = 0; k < 1000000; ++ k )
   {
      printbigint( d2 ); std::cout << "\n";   
      addto( d1, d2 );
   }
}


