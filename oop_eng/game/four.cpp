
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




#include <sys/time.h> 


#include "valuation.h" 
#include "state.h" 
#include "move.h"
#include "color.h"
#include "shared_state.h"
#include "ordered_state.h"
#include "graph.h"


// Inside the program, there is a variable maxthinkingtime that
// determines how long the program thinks.


int main ( int argc, char * argv [] )
{

#if 0 
   state s;

   s[0][2] = color::red( );
   s[0][3] = color::red( );
   graph g = graph::graph(s); 

   for( unsigned int i = 0; i < 10000; ++ i )
      g. expand( );

   g. computevaluations( );

   std::cout << g << "\n";

   std::list< move > m = g. getbestmoves( g. top( ));
   for( std::list< move > :: const_iterator
           p = m. begin( );
           p != m. end( );
           ++ p )
   {
      std::cout << *p << " ";
   }
   std::cout << "\n";

   return 0; 
#endif 

   std::cout << "\n"; 
   std::cout << "Welcome to CZTERMYNATOR\n\n";
   
   char player = ' ';
      // We simply use 'u' for user, 'c' for computer.
      // In principle, one should make a class from this.
  
   while( player == ' ' )
   {
      std::cout << "who will begin?\n";
      std::cout << "   U)ser\n";
      std::cout << "   C)omputer\n";
      
      std::cout << "\n";
      std::string s;
      std::cin >> s;

      if( s. size( ) && ( s[0] == 'u' || s[0] == 'U' ))
         player = 'u';

      if( s. size( ) && ( s[0] == 'c' || s[0] == 'C' )) 
         player = 'c';
   }

   state s = state::state( );

   while( true )
   {

      if( player == 'u' )
      {
         std::cout << "\n"; 
         std::cout << s << "\n";
         std::cout << "please make a move! (first column has number 0) \n";
         
         move m = move::read( std::cin );
         std::cout << "you chose " << m << "\n";
         std::string err = s. islegalmove(m);
 
         while( err. size( )) 
         { 
            std::cout << err << "!\n";
            std::cout << "please make another move! \n"; 
            m = move::read( std::cin );
            std::cout << "you chose " << m << "\n";
            err = s. islegalmove(m);
         }

         bool b = s. makemove(m);
         ASSERT(b); 

         valuation v = valuate(s);
         if( v. islost( ))
            // Lost for the current player, means
            // won for the previous player, which was the user.
            //
            // When printing the valuation, it has to be inverted,
            // because the player changed. 
         {
            std::cout << s << "\n"; 
            std::cout << "You have won with " << -v << " points\n";
            std::cout << "congratulations!\n\n"; 
              // (This code is probably unreachable) 
            return 0;
         }

         // No legal moves and no winner means that we have a draw.

         if( ! s. getlegalmoves( ). size( ))
         {
            std::cout << s << "\n"; 
            std::cout << "the game is a draw\n";
            return 0;
         }
       
         player = 'c'; 
      }
      else
      {
         std::cout << "\n"; 
         std::cout << s << "\n";
         
         unsigned int maxthinkingtime = 30; 
            // in seconds. 

         unsigned int maxnrstates = 1000000; 

         graph g = graph::graph(s);

         unsigned int starttime = time(0);
         bool e = true; 

         std::cout << "building game graph\n";

         // e becomes false when game graph is complete.

         while( e && 
                time(0) < starttime + maxthinkingtime && 
                g. nrstates( ) < maxnrstates )
         {
            // This probably means that we should do some thinking. 

            e = g. expand( );
         }

         std::cout << "number of explored states ";
         std::cout << g. nrstates( ) << "\n";
         std::cout << "computing valuations\n";
         g. computevaluations( );
         
         std::pair< std::list< move >, valuation > 
            m = g. getbestmoves( g. top( ));

         ASSERT( m. first. size( ));
         {
            // We randomly select a move from the best moves.

            unsigned int nr = rand( ) % m. first. size( );
            ASSERT( nr < m. first. size( ));

            while( nr )
            {
               m. first. pop_front( );
               -- nr;
            }
         }

         std::cout << "my move is " << m. first. front( ) << "\n";
         std::cout << "its valuation is " << m. second << "\n";
            // You may want to hide this from the user, but sometimes
            // it can be also nice to show it.

         bool b = s. makemove( m. first. front( ));
         ASSERT(b);

         valuation v = valuate(s); 
         if( v. islost( ))
         {
            std::cout << s << "\n"; 
            std::cout << "I (CZTERMYNATOR) have won with " << -v;
            std::cout << " points!\n";
            return 0;
         }

         // No winner and no legalmoves means: draw

         if( ! s. getlegalmoves( ). size( ))
         {
            std::cout << s << "\n"; 
            std::cout << "the game is a draw\n";
            return 0;
         }

         player = 'u';
      }
   }
                   
}


