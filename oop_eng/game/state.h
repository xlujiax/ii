

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




// A state encodes the field and who has the next move.


#ifndef STATE_INCLUDED
#define STATE_INCLUDED   1


#include "move.h"
#include "color.h"

#include <vector>
#include <list>
#include <iostream>


class state
{

public: 
   static const unsigned int width = 7;
   static const unsigned int height = 6;

   color nextplayer;
      // yellow or red. Empty is forbidden.

private: 
   std::vector<color> field;
      // Element [i,j] is stored at position 
      //    width*i + j. 
      // Numbering is as follows: [0][0]: Lower left corner.
      //                          [0][width-1] : Lower right corner.
      //                          [height-1][0]: Upper left corner.
      //                          [height-1][width-1]: Upper right corner. 

   // These are two auxiliary classes. Their purpose is to enable 
   // expressions of form s [i] [j]. We introduce rowref as the 
   // intermediate type of s[i]. Its only purpose is that one can take
   // the [j] of it and obtain a color& . 
   // const_rowref is the same as rowref, but it produces a const color& 
   // when [j] is applied.

   struct rowref 
   {
      std::vector< color > :: iterator it;
      unsigned int len;

      rowref( std::vector< color > :: iterator it, unsigned int len )
         : it(it), len(len)
      {
      }

      color& operator [ ] ( unsigned int );
 
   };

   struct const_rowref 
   {
      std::vector< color > :: const_iterator it;
      unsigned int len;

      const_rowref( std::vector< color > :: const_iterator it, 
                    unsigned int len )
         : it(it), len(len)
      {
      }

      const color& operator [ ] ( unsigned int ) const;

   };


public:
   rowref operator [] ( unsigned int );
   const_rowref operator [ ] ( unsigned int ) const;

 
   state( );  
      // Constructs empty field with yellow as next player.


   bool makemove( move m );
      // Make move m. Return true is the move is possible.
      // Otherwise, return false. In that case the state is not changed. 
  
   std::string islegalmove( move m ) const;
      // Check if move m is legal. Return empty string if the move is legal,
      // and otherwise an error message that explains what is wrong
      // with the move. 

   std::list<move> getlegalmoves( ) const;
      // Returns a list with the legal moves from the present state. 

};


std::ostream& operator << ( std::ostream& , const state& s );

#endif

