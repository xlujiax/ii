#pragma once

struct digit
{
  char n;
  digit* next;
};

class bigunsigned
{
  digit* d;
 public:
  bigunsigned(); // Default constructor constructs number 0.
  bigunsigned( unsigned x ); // Constructs x as big number.
  bigunsigned( const bigunsigned& x ); // Copy constructor.
  ~bigunsigned( );
  void operator = ( const bigunsigned& x );

};

