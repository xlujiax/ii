

#ifndef SHARED_STATE_INCLUDED
#define SHARED_STATE_INCLUDED  1


// A shared_state is an instance of a general device that is called
// smart pointer. Smart pointers are pointers that are not just
// pointers, but that take care of the object that they point to.
//
// The version that we use here, counts how often the pointed
// state is used, and deletes the state when the number becomes zero.
// 
// Other smart pointers do agressive sharing (Make sure that
// for every state, there is only one occurrence in the system),
// or no sharing at all. Actually, an aggresively shared state
// would not have been a bad idea in this implementation. 
//
// The natural way to implememt a smart pointer is using templates. 
// Templates are not covered in the course. Therefore, I give here
// the specific instance using state. I explain how the code could
// be changed into a template.


#include "state.h"
#include "assert.h"


class shared_state 
{

   // The state is stored on the heap in a structure called state_rec. 
   // Different shared_states can share the same state_rec 
   // (and therefore, also the state). The counter is used
   // for keeping track of how many shared_states use the
   // state_rec. When the counter goes down to zero, the
   // state_rec is deleted.

   
   struct state_rec 
   {
      state s;
      unsigned int counter; 

      state_rec( const state& s )
         :s(s), counter(1) 
      {
      }
   }; 


   state_rec *ref; 

public: 
   shared_state( const state& s ); 
   shared_state( const shared_state& s );
   void operator = ( const state& s );
   void operator = ( const shared_state& s ); 
   ~shared_state( ); 

   const state& getstate( ) const;
      // Introducing a non-const version of this operator would
      // be very dangerous.
      // If one would give state& getstate( ) to the user,
      // the user could get the state, and modify it.
      // Then all shared_states that share the same state would be modified
      // as well, and object semantics would be lost.
      // (and C++ would degenerate into Java/C#. You wouldn't want
      // that, would you?)

};


std::ostream& operator << ( std::ostream& stream, const shared_state& s );
   // No need for friendship, because we can get at the state through
   // getstate( ); 
 
#endif 


