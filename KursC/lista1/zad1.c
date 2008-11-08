// Maciej Pacut 221082
// parametry : 2
// mozliwe: utf iso cp

#include <stdio.h>
#include <stdlib.h>

typedef int (*fun_int_to_int)(int);


int cp_to_utf(int a)
{
     switch(a)
     {
     case 165: return 260 + 256*260; // kodowanie w unicode za pomoc¹ przesuniecia o 8 bitow
     case 198: return 262 + 256*260; // b³êdne wartoœci, brak³o czasu do wpisania poprawnych
     case 202: return 280 + 256*260;
     case 163: return 321 + 256*260;
     case 209: return 323 + 256*260;
     case 211: return 211 + 256*260;
     case 140: return 346 + 256*260;
     case 143: return 377 + 256*260;
     case 175: return 379 + 256*260;
     case 185: return 261 + 256*260;
     case 230: return 263 + 256*260;
     case 234: return 281 + 256*260;
     case 179: return 322 + 256*260;
     case 241: return 324 + 256*260;
     case 243: return 243 + 256*260;
     case 156: return 347 + 256*260;
     case 159: return 378 + 256*260;
     case 191: return 380 + 256*260;
     default: return a;
     }     
}
int cp_to_iso(int a)
{
     switch(a)
     { 	  	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 		 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	
     case 165: return 161;
     case 198: return 198;
     case 202: return 202;
     case 163: return 163;
     case 209: return 209;
     case 211: return 211;
     case 140: return 166;
     case 143: return 172;
     case 175: return 175;
     case 185: return 177;
     case 230: return 230;
     case 234: return 234;
     case 179: return 179;
     case 241: return 241;
     case 243: return 243;
     case 156: return 182;
     case 159: return 188;
     case 191: return 191;
     default: return a;
     }     
}
int utf_to_cp(int a)
{
     switch(a)
     { 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	
     case 123 + 256*260: return 165; // kodowanie w unicode za pomoc¹ przesuniecia o 8 bitow
     case 262 + 256*260: return 198; // b³êdne wartoœci, brak³o czasu do wpisania poprawnych
     case 280 + 256*260: return 202;
     case 321 + 256*260: return 163;
     case 323 + 256*260: return 209;
     case 211 + 256*260: return 211;
     case 346 + 256*260: return 140;
     case 377 + 256*260: return 143;
     case 379 + 256*260: return 175;
     case 261 + 256*260: return 185;
     case 263 + 256*260: return 230;
     case 281 + 256*260: return 234;
     case 322 + 256*260: return 179;
     case 324 + 256*260: return 241;
     case 243 + 256*260: return 243;
     case 347 + 256*260: return 156;
     case 378 + 256*260: return 159;
     case 380 + 256*260: return 191;
     default: return a;
     }     
}
int utf_to_iso(int a)
{
     switch(a)
     {
     case 123 + 256*260: return 161; // kodowanie w unicode za pomoc¹ przesuniecia o 8 bitow
     case 262 + 256*260: return 198; // b³êdne wartoœci, brak³o czasu do wpisania poprawnych
     case 280 + 256*260: return 202;
     case 321 + 256*260: return 163;
     case 323 + 256*260: return 209;
     case 211 + 256*260: return 211;
     case 346 + 256*260: return 166;
     case 377 + 256*260: return 172;
     case 379 + 256*260: return 175;
     case 261 + 256*260: return 177;
     case 263 + 256*260: return 230;
     case 281 + 256*260: return 234;
     case 322 + 256*260: return 179;
     case 324 + 256*260: return 241;
     case 243 + 256*260: return 243;
     case 347 + 256*260: return 182;
     case 378 + 256*260: return 188;
     case 380 + 256*260: return 191;
     default: return a;
     }     
}
int iso_to_utf(int a)
{
     switch(a)
     {
     case 161: return 123 + 256*260; // kodowanie w unicode za pomoc¹ przesuniecia o 8 bitow
     case 198: return 262 + 256*260; // b³êdne wartoœci, brak³o czasu do wpisania poprawnych
     case 202: return 280 + 256*260;
     case 163: return 321 + 256*260;
     case 209: return 323 + 256*260;
     case 211: return 211 + 256*260;
     case 166: return 346 + 256*260;
     case 172: return 377 + 256*260;
     case 175: return 379 + 256*260;
     case 177: return 261 + 256*260;
     case 230: return 263 + 256*260;
     case 234: return 281 + 256*260;
     case 179: return 322 + 256*260;
     case 241: return 324 + 256*260;
     case 243: return 243 + 256*260;
     case 182: return 347 + 256*260;
     case 188: return 378 + 256*260;
     case 191: return 380 + 256*260;
     default: return a;
     }     
}
int iso_to_cp(int a)
{
     switch(a)
     {
     case 161: return 165;
     case 198: return 198;
     case 202: return 202;
     case 163: return 163;
     case 209: return 209;
     case 211: return 211;
     case 166: return 140;
     case 172: return 143;
     case 175: return 175;
     case 177: return 185;
     case 230: return 230;
     case 234: return 234;
     case 179: return 179;
     case 241: return 241;
     case 243: return 243;
     case 182: return 156;
     case 188: return 159;
     case 191: return 191;
     default: return a;
     }     
}

fun_int_to_int choose_encoding(char* from, char* to)
{
     if(0 == strcmp(from, "cp"))
     {
             if(0 == strcmp(to, "iso"))
                   return cp_to_iso;
             if(0 == strcmp(to, "utf"))
                   return cp_to_utf; 
     }
     if(0 == strcmp(from, "iso"))
     {
             if(0 == strcmp(to, "utf"))
                   return iso_to_utf;
             if(0 == strcmp(to, "cp"))
                   return iso_to_cp;
     }
     if(0 == strcmp(from, "utf"))
     {
             if(0 == strcmp(to, "iso"))
                   return utf_to_iso;
             if(0 == strcmp(to, "cp"))
                   return utf_to_cp;
     }
     printf("unsupported encoding\n");
}

void print_supporting_unicode(int a)
{
     if((int)((char)(a)) == a)
     {
      putchar(a);
     }
     else
     {
     /*
          jesli nie miesci sie w incie
          to jest to unicode
          i trzeba dwa razy wywolac putchar
     */
         putchar((char)a);
         putchar(a / 256);
     }
}

int main(int argc, char *argv[])
{
    int actual;
    char* from;
    char* to;
    if(argc != 3)
    {
            printf("default arguments: from utf to iso\n");
            from = "utf";
            to = "iso";
    }
    else
    {
        from = argv[1];
        to = argv[2];
    }
    fun_int_to_int encoding = choose_encoding(from, to);
    while(EOF != (actual = getchar()))
    {
     int en = encoding(actual);
     print_supporting_unicode(en);
    }
  
  return 0;
}
