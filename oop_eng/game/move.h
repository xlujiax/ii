

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




#ifndef MOVE_INCLUDED 
#define MOVE_INCLUDED 1

#include <iostream>


struct move
{
   unsigned int column;

   move( unsigned int x )
      : column(x)
   {
   }


   // Read a move. The keyword 'static' means that the method can be
   // called without an actual move.

   static move read( std::istream& stream )
   {
      unsigned int x;
      stream >> x;
      return move(x);
   }

};


inline std::ostream& operator << ( std::ostream& stream, move m )
{
   stream << "insert in column " << m. column;
   return stream;
}
 

#endif


