

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




#include "valuation.h"
#include "assert.h"


// This is an anonymous namespace, which means that the following
// function will be invisible outside of this file.


namespace
{
   // This functions counts how long is the longest sequence of color
   // c starting at point (i,j) in direction (diri,dirj).


   unsigned int count( const state& s, color c, 
                       unsigned int i, unsigned int j,
                       int diri, int dirj )
   {
      unsigned int length = 0;

      while( true )
      {
         // At this point we are certain that (i,j) is in the field.

         if( s[i][j] != c )
            return length;

          ++ length;
        
          // If the step (diri,dirj) brings us out of the field,
          // we quit.
 
          if(  ( i == 0 && diri == -1 ) ||
               ( i == s. height - 1 && diri == 1 ) ||
               ( j == 0 && dirj == -1 ) ||
               ( j == s. width - 1 && dirj == 1 ))
          {
             return length;
          }

          // Otherwise, we make the step (i,j). 

          i += diri;
          j += dirj;
       }
   }           
}




unsigned int points( const state& s, color c ) 
{

   static unsigned int maxseq = 
       ( s. width > s. height ) ? s. width : s. height;
          // Maximal length that a sequence of the same color can have.

   static std::vector< unsigned int > sequences 
      = std::vector< unsigned int > :: vector( maxseq + 1, 0 );

   // Because sequences is static, we have to clean up from
   // previous calls. 

   for( unsigned int i = 0; i <= maxseq; ++ i )
      sequences [i] = 0;
 
   for( unsigned int dir = 0; dir < 4; ++ dir )
   {
      int diri;
      int dirj;

      switch(dir)
      {
      case 0:
         diri = 0; dirj = 1; break; 
      case 1:
         diri = 1; dirj = 1; break; 
      case 2:
         diri = 1; dirj = 0; break; 
      case 3:
         diri = 1; dirj = -1; break;
      }


      for( unsigned int i = 0; i < s. height; ++ i )
         for( unsigned int j = 0; j < s. width; ++ j )
         {
            // std::cout << "checking point " << i << ", " << j;
            // std::cout << " for color " << c << "\n";

            unsigned int len = count( s, c, i, j, diri, dirj );
            if( len >= 2 && 
                count( s, c, i, j, -diri, -dirj ) == 1 )
            {
               ASSERT( len < sequences. size( ));

               // std::cout << diri << ", " << dirj << "\n";
               // std::cout << "found a sequence of length " << len << "\n";

               ++ sequences [ len ];
            }
         } 
   }

   unsigned int val = 
             10 * sequences [2] +
             100 * sequences [3] +
             5 * valuation::won * sequences [4] +
             20 * valuation::won * sequences [5];
   for( unsigned int i = 6; i <= maxseq; ++ i )
      val += 100 * valuation::won * sequences [i]; 

   return val;    
}
     
                 
valuation valuate( const state& s )
{
   return valuation::valuation( points( s, s. nextplayer ) -
                                points( s, -s. nextplayer ));
}


