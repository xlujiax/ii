
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




#ifndef VALUATION_INCLUDED
#define VALUATION_INCLUDED  1


#include "state.h"


class valuation
{
   int val;

   static const int won = 10000;
      // If val >= won, then the game is won.
      // If val <= -won, then the game is lost.



private: 
   explicit valuation( int val ) 
      : val( val ) 
   {
   }


public: 
   // Default is when we know completely nothing.

   valuation( ) :
      val(0)
   { }

 
   // V1 & V2 returns the worse of the two valuations.
 
   valuation operator & ( valuation v ) const
   {
      if( val < v. val )
         return valuation::valuation(val);
      else
         return valuation::valuation(v. val);
   }


   // V1 | V2 returns the better of the two valuations.

   valuation operator | ( valuation v ) const
   {
      if( val < v. val )
         return valuation::valuation( v. val );
      else
         return valuation::valuation( val ); 
   }

   
   // - V : Returns the valuation that you obtain if you change the 
   // player: What is good for one player is bad for the other.

   valuation operator - ( ) const 
   {
      return valuation::valuation( -val );
   }
 

   bool islost( ) const
   {
      return val <= -won; 
   }

   bool iswon( ) const
   {
      return val >= won; 
   }

   bool game_over( ) const
   {
      return iswon( ) || islost( ); 
   }


   bool operator == ( valuation v )
   {
      return val == v. val;
   }

   bool operator < ( valuation v )
   {
      return val < v. val; 
   }

   bool operator > ( valuation v )
   {
      return val > v. val;
   }

   // Loosing is a bit less bitter when it is far in the future.
   // Victory is a bit less sweat when it is far in the future.

   valuation postponement( ) const
   {
      if( val > 0 ) 
         return valuation::valuation( val - 1 );
      if( val < 0 )
         return valuation::valuation( val + 1 );

      return valuation::valuation(0);
   }


   friend valuation valuate( const state& ); 
   friend unsigned int points( const state& , color );

   friend std::ostream& operator << ( std::ostream& stream, 
                                      const valuation& v );    
}; 


unsigned int points( const state& s, color c );
   // Give points to player c, dependent on how many sequences
   // of a given length he has collected.
   //
   // Currently, we give: 
   //    10 points for every sequence of 2.
   //    100 points for every sequence of 3.
   //    ( 5 * won ) points for every sequence of 4.
   //    ( 20 * won ) points for every sequence of 5.
   //    ( 100 * won ) points for a sequence of 6 or more.
   //
   // Sequences of the other color get negative numbers.

valuation valuate( const state& s );  
   // Compute valuation from the perspective of the player who has
   // the next move in s.  
   // (The valuation contains points( currentplayer ) - points( otherplayer );

inline std::ostream& operator << ( std::ostream& stream, const valuation& v )
{
   stream << "valuation( " << v. val << " )";
   return stream;
}


#endif

