
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



#include <iostream>


#ifndef COLOR_INCLUDED
#define COLOR_INCLUDED  1


// A color is either yellow, red or empty.


class color
{
   int c;
      // -1 : yellow.
      //  0 : empty.
      //  1 : red.

   color( int col )
      : c(col)
   {
   }

public: 
   static color yellow( ) { return -1; }
   static color red( ) { return 1; }
   static color empty( ) { return 0; }

   // - returns the opposite color.

   color operator - ( ) const 
   {
      return color( -c );
   }


   bool operator == ( color col ) const
   {
      return c == col.c;
   }

   bool operator != ( color col ) const
   {
      return c != col.c;
   }


   friend std::ostream& operator << ( std::ostream&, color ); 
};



inline std::ostream& operator << ( std::ostream& stream, color c )
{
   switch( c. c )
   {
   case -1:
      stream << "yellow"; return stream; 
   case 0:
      stream << "empty "; return stream; 
   case 1:
      stream << "red   "; return stream; 
   }
   std::cerr << "unknown color"; exit(0); 
}


#endif
 

