
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



#ifndef GRAPH_INCLUDED
#define GRAPH_INCLUDED    1


#include "shared_state.h"
#include "ordered_state.h"
#include "valuation.h"


#include <map>
#include <queue>


// This class represents a game graph. 
// 
// The graph consists of (game) states that are connected by moves.
// A state in the graph is either explored or unexplored.
// A state s is unexplored if the states that are reachable
// from s by a single move, are not yet checked.
// 
// The constructor graph(s) starts with a single state for which
// we want to determine the best move. 
// It builds a singleton graph consisting of s, with s unexplored. 
//
// The function expand( ) selects an unexplored state, computes
// the set of reachable states with their corresponding moves,
// and inserts the states that were not yet present, into the graph. 
// Newly added states are marked as unexplored.
//
// One should continue expanding until some resource limit 
// (time/memory) is exceeded, or the game graph is completely explored.
//
// The function computevaluations assigns valuations to the graph.
// The values of leave nodes (nodes without children) are obtained by
// calling the function valuate. 
// 
// The other nodes receive their valuation from their children.
// The valuation of a state with children is the maximal valuation 
// occurring among the children, seen from the perspective of the player
// who has the next move.
//
// Some more remarks:
//
// There are obvious optimizations possible that we did not implement.
// 
// - If some move is made, one should not throw away the complete graph
//   and start from scratch, but only delete the part that becomes 
//   unreachable. This would involve implementing garbage collection
//   in the graph, and I did not want to do that. 
// 
// - One probably should not compute valuations at the end, but
//   every time when a node is added to the graph.
//   This makes modifications in the tree a bit harder, but the advantage
//   is that, when expanding the tree one can concentrate on those parts
//   that will have effect on deciding the move.
//   If some state is an alternative to a winning move, one does not
//   need to explore it. 
//
// The vector gr[ ] is the main constainer of the graph.
// When a new state is created, we want to be able to check efficiently
// if this state already exists in gr.
// For this purpose, we have an std::map knownstates that maps
// the states to the indices in gr.
// In order to avoid storing a state twice (in gr and knownstates),
// we use a shared_state. 
// In order to avoid comparing states (in knownstates), we store
// them together with a hash value. The map compares first the
// hash values, and only when they are equal, it compares the state.
//
// The unexplored states are stored in a priority_queue. 


class graph
{

   struct node 
   {
      shared_state s; 
      valuation v; 

      bool visited;
         // Used when we compute valuations. It could also be used
         // for garbage collection, if we will implement that some day.  

      std::list< std::pair< move, unsigned int > > m;
         // The list of possible moves, and the states that one
         // reaches through them.

      node( shared_state s, valuation v )
         :s(s), v(v), visited(false) 
      { 
      }
    
   };


   std::vector< node > gr;  

   std::map< ordered_state, unsigned int > knownstates;
      // This data structure maps the known states into their indices in
      // gr.


   struct unexplored
   {
      unsigned int index;
         // This is an index in gr.

      int urgency;
         // One could also make a separate class from this, but at some
         // point one has to stop. A greater urgency means that
         // the state will be earlier explored. 

      bool operator < ( const unexplored& u ) const
      {
         return urgency < u. urgency;
      }


      unexplored( const state& s, unsigned int index );
         // The state is not stored, but it is used to compute the 
         // urgency. 
   };


            
   std::priority_queue< unexplored > todo;
      // These are the states that we have added to the graph, but
      // of which we did not expore the possible moves yet. 
      // We pick the most urgent one, add the possible moves and
      // reachable states to gr and todo.
      // We keep on doing this until our time is finished,
      // (we need to make move), or the complete game is explored.

private: 
   unsigned int findorinsert( const state& s );
      // If state s already exists, then we return its index.
      // If it does not exist, we insert it, and return the index.
      // If s is inserted, then it is also added to todo. 

   void computevaluation( unsigned int k );
      // Recursively compute the valuations that descend from state k. 
      // This function is called by computevaluations( ).

public: 
   graph( const state& s );
      // Construct singleton graph.

   bool expand( );
      // Expand the most urgent state. Return true if an expansion was
      // made. If expand( ) returns false, this means that the game
      // graph is completely explored. 

   unsigned int top( ) const;
      // Returns the index of the top state. (It is always 0 in our
      // current implementation, but you should not count on that) 

   void computevaluations( );
      // Compute the valuations. Valuations are always seen from the 
      // perspective of the player who has the next move. 
    
   std::pair< std::list< move >, valuation >
    getbestmoves( unsigned int i ) const;
      // Returns a pair consisting of a list of best moves from state i, 
      // together with the valuation that these moves have.
      // The valuations are viewed from the perspective of the player 
      // who has the next move in state i. 
 
   unsigned int nrstates( ) const;
      // Number of states in the game graph.

   unsigned int nrunexplored( ) const;
      // Number of unexplored states in the game graph. 

   friend std::ostream& operator << ( std::ostream&, const graph& );  
   friend std::ostream& operator << ( std::ostream&, 
                                      const graph::unexplored& u );
};


std::ostream& operator << ( std::ostream& stream, const graph& g ); 
std::ostream& operator << ( std::ostream& stream, const graph::unexplored& u );


#endif


