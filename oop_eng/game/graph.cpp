
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



#include "graph.h"


graph::unexplored::unexplored::unexplored( const state& s, unsigned int index )
{
   ( this -> index ) = index;
   
   unsigned int level = 0;
   for( unsigned int i = 0; i < s. height; ++ i )
      for( unsigned int j = 0; j < s. width; ++ j )
      {
         if( s[i][j] != color::empty( ))
            ++ level;
      }

   unsigned int p = points( s, color::yellow( )) +
                    points( s, color::red( ));

   ( this -> urgency ) = ( s. height * s. width - level ) * 100 + p / 10; 
      // This means that we search breadth first, but give some priority
      // to states that have many points, because in such states, one of
      // the players almost has a sequence. I don't know if this is 
      // a good strategy at all. 
}

 
unsigned int graph::findorinsert( const state& s )
{
   shared_state ss = s; 
      // First we make a shared state.

   ordered_state os = ss; 
      // Then an ordered state. That is a shared state and a
      // hash value.

   std::map< ordered_state, unsigned int > :: const_iterator 
      p = knownstates. find( os );

   if( p != knownstates. end( )) 
   {
      return p -> second;   // State was already known. 
   }
   else
   {
      unsigned int ind = gr. size( );
         // We insert at the end of gr, so this will be the index.

      knownstates. insert( 
         std::pair< ordered_state, unsigned int > :: pair( ss, ind ));

      gr. push_back( node::node( ss, valuate(s)) ); 
      todo. push( unexplored::unexplored( s, ind ));

      return ind; 
   }
}


// Compute valuation in state k, from the view point of the player
// who has the next move.

void graph::computevaluation( unsigned int k )
{
   // std::cout << "computing valuation " << k << "\n";

   ASSERT( k < gr. size( ));
   if( ! gr [k]. visited )
   {
      gr [k]. visited = true;    // It is visited now. 
                                 // If the game would be circular, there
                                 // would be a problem. 

      // If there are no children, then we do nothing. This
      // means that we keep the state returned by valuate( ). 

      if( gr [k]. m. size( ))
      {
         // There are children, and we recursively calculate their
         // valuations.

         for( std::list< std::pair< move, unsigned int > > :: iterator
                 p = gr [k]. m. begin( );
                 p != gr [k]. m. end( );
                 ++ p )
         {
            computevaluation( p -> second );
         } 

         // Now we compute the valuation of k.
         // We first compute the worst valuation, because the valuations
         // of the children are from the other player's perspective. 
   
         valuation worst; 
         unsigned int cnt = 0; 

         for( std::list< std::pair< move, unsigned int > > :: iterator
                 p = gr [k]. m. begin( );
                 p != gr [k]. m. end( );
                 ++ p )
         {
            valuation w = gr [ p -> second ]. v;
       
            if( cnt == 0 || w < worst )
               worst = w;
 
            ++ cnt; 
         }

         valuation best = ( - worst ). postponement( );  
         gr [k]. v = best;
      }
   }
}

 
graph::graph( const state& s )
{
   findorinsert(s);
      // It will be an insert of course. 
}


bool graph::expand( )
{
   if( todo. size( ))
   {
      unsigned int ind = todo. top( ). index;
      // std::cout << "expanding " << ind << "\n";
   
      todo. pop( );
  
      ASSERT( gr [ ind ]. m. size( ) == 0 );

      if( gr [ ind ]. v. game_over( ))
      {
         // This means that the valuation tells that there is a winner
         // or a loser. In that case, there is nothing left to do.

         return true;
            // We still return true, because we still processed a state,
            // even when it was trivial. 
      }

      std::list< move > m = gr [ ind ]. s. getstate( ). getlegalmoves( );
      if( m. size( ) == 0 )
      {
         // If there are no legal moves, then the game is a draw.
         // We could set the valuation to zero, but we leave it as it is.

         return true;
      }

      
      // We go through the moves, and add (if necessary), the
      // states that they result in.

      for( std::list< move > :: const_iterator
              p = m. begin( );
              p != m. end( );
              ++ p )
      {
         state s = gr [ ind ]. s. getstate( );
         s. makemove( *p );
         unsigned int i = findorinsert(s);
         gr [ ind ]. m. push_back( 
                std::pair< move, unsigned int > :: pair( *p, i ));
      }
   
      return true;
   }
   else
      return false;
}


unsigned int graph::top( ) const
{
   return 0;
      // In our implementation, the top is always state 0. 
}


void graph::computevaluations( )
{
   for( std::vector< node > :: iterator
           p = gr. begin( );
           p != gr. end( );
           ++ p )
   {
      p -> visited = false;
   }

   // We assume that all states without children have a correct valuation.
   // This should be the case, because computevaluations is the only
   // method that can change valuations. But computevaluations changes
   // only valuations of states when they have children. 

   computevaluation( top( ));
}
   

std::pair< std::list< move > , valuation >
graph::getbestmoves( unsigned int i ) const
{
   ASSERT( i < gr. size( ));

   valuation worst;
      // All reachable states have the valuation of the other player.
      // Therefore, we first look for the worst move.

   std::list< move > movelist;

   for( std::list< std::pair< move, unsigned int > > :: const_iterator
           p = gr [i]. m. begin( );
           p != gr [i]. m. end( );
           ++ p )
   {
      valuation w = gr [ p -> second ]. v;

      if( movelist. size( ) && w < worst )
         movelist. clear( );
    
      if( movelist. size( ) == 0 || w == worst ) 
      {
         movelist. push_back( p -> first );
         worst = w;
      }
   }

   worst = ( - worst ). postponement( ); 
   return std::pair< std::list< move > , valuation > :: pair(
                                   movelist, worst );

}


unsigned int graph::nrstates( ) const
{
   return gr. size( );
}


unsigned int graph::nrunexplored( ) const
{
   return todo. size( );
}


std::ostream& operator << ( std::ostream& stream, const graph& g )
{
   std::cout << "State Graph:\n\n";

   for( unsigned int i = 0; i < g. gr. size( ); ++ i ) 
   {
      stream << "state " << i << ":\n";

      stream << g. gr [i]. s << "\n";
      if( g. gr [i]. visited )
         stream << "state was visited\n";
      else
         stream << "state was not visited\n";

      stream << g. gr [i]. v << "\n";

      stream << "move list [ ";
      for( std::list< std::pair< move, unsigned int > > :: const_iterator
              p = g. gr [i]. m. begin( );
              p != g. gr [i]. m. end( );
              ++ p )
      {
         if( p != g. gr [i]. m. begin( ))
            stream << ", ";

         stream << "( " << p -> first << ", " << p-> second << ") ";
      }
      stream << "]\n\n";
   }

#if 1
   stream << "Unexplored: [ ";
   std::priority_queue< graph::unexplored > pq = g. todo;
   unsigned int c = 0;
 
   // This is inefficient, but there seems to be no better way. 
 
   while( pq. size( ))
   {
      if( c > 0 )
         stream << ", "; 
      ++ c;

      stream << pq. top( );
      pq. pop( ); 
   }
   std::cout << " ]\n\n";

#endif
   return stream;
}


std::ostream& operator << ( std::ostream& stream, 
                            const graph::unexplored& u )
{
   stream << "( " << u. index << ", " << u. urgency << " )";
   return stream;
}

 
