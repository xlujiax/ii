#pragma once

#include "bigint.h"

class bigunsigned
{
  digit* d;
 public:
  bigunsigned(); // Default constructor constructs number 0.
  bigunsigned( unsigned x ); // Constructs x as big number.
  bigunsigned( const bigunsigned& x ); // Copy constructor.
  ~bigunsigned( );
  bigunsigned& operator = ( const bigunsigned& x );

  bigunsigned operator+(const bigunsigned& x) const;
  bigunsigned operator-(const bigunsigned& x) const;
  bigunsigned operator*(const bigunsigned& x) const;

  bigunsigned& operator++(); //prefix
  bigunsigned& operator--(); //prefix
  bigunsigned operator++(int unused); //postfix
  bigunsigned operator--(int unused); //postfix

  friend bool operator == ( const bigunsigned& d1, const bigunsigned& d2 );
  friend bool operator != ( const bigunsigned& d1, const bigunsigned& d2 );
  friend bool operator < ( const bigunsigned& d1, const bigunsigned& d2 );
  friend bool operator > ( const bigunsigned& d1, const bigunsigned& d2 );
  friend bool operator <= ( const bigunsigned& d1, const bigunsigned& d2 );
  friend bool operator >= ( const bigunsigned& d1, const bigunsigned& d2 );
 
  friend std::ostream& operator << ( std::ostream& , const bigunsigned & );
};

