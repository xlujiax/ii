

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



#ifndef ORDERED_STATE_INCLUDED
#define ORDERED_STATE_INCLUDED  1


#include "shared_state.h"


// For very simple classes, it usually makes no sense to hide the
// structure. This why I used struct here instead of class. 
//
// The only purpose of this class is to avoid that < will look into 
// the states when storing states in an std::map.
// 
// This class combines a state with a hash value. When two ordered_states
// are compared, We first compare the hash values, and only when the 
// hash values are equal, we look into the state. 


struct ordered_state
{
   unsigned int hv; 
   shared_state s;


   static unsigned int hashvalue( color c ); 
   static int compare( color c1, color c2 );    
      // We could also have defined < in class color, but as a general
      // rule one should: Define only those operators their meaning of which
      // is no natural that there will be no doubt what they mean. 


   static int compare( const state& s1, const state& s2 );
   static unsigned int hashvalue( const state& s );
      // People who have programmed in C, tend to have wrong
      // views on the meaning of the word 'static'.
      //
      // A static variable is a variable that belongs to its class,
      // not to the objects of the class. In the programs, there
      // exists only one copy of the static variable. 
      // That means that all instances of the class, share this 
      // same variable. Static variables are potentially dangerous
      // because they can create side effects. Sometimes they are
      // also useful.
      //
      // A static method is a method that does not look at the objects
      // of the class. It can be called without object by using the
      // name of the class. (Like in ordered_state::compare( ))
      // It is allowed that a static method uses the static variables
      // of the class. (Because these also exist without object)


   ordered_state( const state& s );
   ordered_state( const shared_state& s );


   void operator = ( const state& s );
   void operator = ( const shared_state& s ); 
      // We defined these operators, because the hash value needs to 
      // change as well. 
}; 


bool operator < ( const ordered_state& o1, const ordered_state& o2 );
   // std::map needs only <, and I am too lazy to do the others. 

std::ostream& operator << ( std::ostream& , const ordered_state& os );


#endif

