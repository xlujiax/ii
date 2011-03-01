

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




#include "shared_state.h"


// Constructor: Initialize ref with a new 
// state_rec containing s. The constructor 
// of state_rec initializes the counter to 1.

shared_state::shared_state( const state& s )
   : ref( new state_rec::state_rec(s))
{
}


// Copy constructor. We share the state_rec with our example,
// but increase its counter by 1.


shared_state::shared_state( const shared_state& s )
   : ref( s. ref )
{
   ++ ( ref -> counter );
}


// Assigning a new state to the shared state.
// Simply overwriting ref -> s would be dangerous.
// If different shared_states share the same state_rec, they
// would all be modified. We don't want that because we want
// to program without side effects, and preserve object semantics. 


void shared_state::operator = ( const state& s )
{
   if( ref -> counter == 1 )
   {
      // If we are the only one who uses the state_rec, then
      // overwriting is no problem.

      ref -> s = s;
   }
   else
   {
      -- ( ref -> counter );
         // We know that ref -> counter is not zero, because of the if.

      ref = new state_rec::state_rec(s);
   }
}


// Assigning a shared state to a shared state.

void shared_state::operator = ( const shared_state& s )
{
   state_rec* ref2 = ref;
   
   ref = s. ref;
   ++ ( ref -> counter );

   ASSERT( ref2 -> counter );
   -- ( ref2 -> counter );
   if( ref2 -> counter == 0 )
      delete ref2;

   // You probably wonder: Why not first decrease the counter of ref,
   // then copy s.ref and increase the counter of s. ref?
   // This would fail with assignments of the form s = s, in the case
   // there exists only one reference to s. 

}


shared_state:: ~shared_state( )
{
   ASSERT( ref -> counter );
   -- ( ref -> counter );
   if( ref -> counter == 0 )
   {
      delete ref;
   }
}


const state& shared_state::getstate( ) const 
{
   return ref -> s;
}


std::ostream& operator << ( std::ostream& stream, const shared_state& s )
{
   stream << s. getstate( );
   return stream;
}



