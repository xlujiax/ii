

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




#include "state.h"
#include "assert.h"


color& state::rowref::operator [] ( unsigned int i )
{
   ASSERT( i < len );
   return it [i];
}


const color& state::const_rowref::operator [] ( unsigned int i ) const
{
   ASSERT( i < len );
   return it [i];
}


state::rowref state::operator [ ] ( unsigned int i ) 
{
   ASSERT( i < height );
   return rowref::rowref( field. begin( ) + i * width, width );
}


state::const_rowref state::operator [ ] ( unsigned int i ) const
{
   ASSERT( i < height );
   return const_rowref::const_rowref( field. begin( ) + i * width, width );
}


state::state( ) 
   : nextplayer( color::yellow( )),
     field( std::vector< color > :: vector( width * height, color::empty( )))
{
}


bool state::makemove( move m )
{
   if( m. column < width && 
       (*this)[ height - 1 ] [ m. column ] == color::empty( ))
   {
      unsigned int h = 0;
      while(  (*this) [h] [ m. column ] != color:: empty( ))
         ++ h;
            // Because of the if above, we are guaranteed to 
            // stay within the field. 

      (*this) [h] [ m. column ] = nextplayer;
      nextplayer = - nextplayer;
         // Now it is the other player's turn.

      return true;
   }
   else
     return false;
}


std::string state::islegalmove( move m ) const
{
   if( m. column >= width )
      return "column is out of range";
   if( (*this) [ height - 1 ] [ m. column ] != color::empty( ))
      return "column is already full";
   return "";
}


std::list< move > state::getlegalmoves( ) const
{
   std::list< move > result;
   for( unsigned int c = 0; c < width; ++ c )
   {
      if( (*this) [ height - 1 ][c] == color::empty( ))
         result. push_back(c);
   }

   return result;
}
 

std::ostream& operator << ( std::ostream& stream, const state& s )
{

   stream << " ---------------------------------------------" <<
             "-------------------\n";
 
   unsigned int i = s. height; 
   while( i != 0 )
   {
      -- i;
      stream << " | ";
      for( unsigned int j = 0; j < s. width; ++ j )
      {
         stream << s[i][j] << " | ";
      }
      stream << "\n";
      stream << " ------------------------------------------" << 
                "----------------------\n";
   }
   stream << "nextplayer is " << s. nextplayer << "\n";
   return stream;
}

 
