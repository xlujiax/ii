

// This file is part of a connect four implementation called
// CZTERMYNATOR.
//
// CZTERMYNATOR is free software: You can distribute it and/or modify
// it under the terms of the GNU General Public License, Version 3,
// as published by the Free Software Foundation.
//
// CZTERMYNATOR is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// Version 3 along with CZTERMYNATOR. It not, see
// < http://www.gnu.org/licenses/ >


#include "ordered_state.h"


inline unsigned int ordered_state::hashvalue( color c )
{
   if( c == color::yellow( ))
      return 0;
   if( c == color::red( ))
      return 1;
   return 2;
}


int ordered_state::compare( color c1, color c2 )
{
   unsigned int h1 = hashvalue(c1); 
   unsigned int h2 = hashvalue(c2);

   // Be careful, because code with thisf form does not work in general.
   // It can happen that different objects have the same hashvalue.
   // However, with colors this cannot happen.

   if( h1 < h2 ) 
      return -1;
   if( h1 > h2 )
      return 1;
   return 0; 
}


// We look for the first difference, in some inessential order:

int ordered_state::compare( const state& s1, const state& s2 )
{
   int c = compare( s1. nextplayer, s2. nextplayer );
   if(c)
      return c;

   for( unsigned int i = 0; i < s1. height; ++ i )
      for( unsigned int j = 0; j < s1. width; ++ j )
      {
         c = compare( s1 [i] [j], s2 [i] [j] ); 
         if(c)
            return c;
      }

   return 0;
}


// Desiging a good hash function requires deep knowledge of algebraic
// number theory, which I don't have. At least I understand that 3 is a 
// prime number and that that is probably good. 

unsigned int ordered_state::hashvalue( const state& s )
{
   unsigned int hv = hashvalue( s. nextplayer ); 

   for( unsigned int i = 0; i < s. height; ++ i )
      for( unsigned int j = 0; j < s. width; ++ j ) 
         hv = 3 * hv + hashvalue( s[i][j] );

   return hv;
}


// Remember the scoping rules in initializers:

ordered_state::ordered_state( const state& s )
   : hv( hashvalue(s)),
     s( shared_state::shared_state(s))
{
}


ordered_state::ordered_state( const shared_state&s )
   : hv( hashvalue( s. getstate( ))),
     s(s)
{
}


void ordered_state::operator = ( const state& s )
{
   ( this -> hv ) = hashvalue(s);
   ( this -> s ) = s;
}


void ordered_state::operator = ( const shared_state& s )
{
   ( this -> hv ) = hashvalue( s. getstate( ));
   ( this -> s ) = s;
}


bool operator < ( const ordered_state& o1, const ordered_state& o2 )
{
   if( o1. hv < o2. hv )
      return true;
   if( o1. hv > o2. hv )
      return false;

   return ordered_state::compare( 
                     o1. s. getstate( ), 
                     o2. s. getstate( )) == -1;
}


std::ostream& operator << ( std::ostream& stream,
                            const ordered_state& os )
{
   stream << os. s << "[ hv = " << os. hv << " ]\n";
   return stream;
}


