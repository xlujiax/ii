// Maciej Pacut
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// domyślnie bufor na każdą linię ma taką wielkość
// 5 dla pokazania, że algorytm działa poprawnie przy przepełnieniu
// w prawdziwym programie byłaby to większa liczba
#define default_line_len 5

// bufor rośnie dwukrotnie przy przepełnieniu
#define grow_ratio 2

// kolejka specyficzna dla stringów
char** queue;
int queue_begin = 0;
int queue_end = 0;
int queue_sz;

void init_queue()
{
  int i;
  queue = malloc(sizeof(char*)*queue_sz);
  for(i = 0; i < queue_sz; ++i)
    queue[i] = malloc(sizeof(char)*default_line_len); // wskaznik na nic
}

void clean_queue()
{
  int i;
  for(i = 0; i < queue_sz; ++i)
    if(queue[i] != 0)
      free(queue[i]);
  free(queue);
}

// zwraca indeks w ktory mozna wstawic obiekt
int enqueue()
{
  ++queue_end;
  if(queue_end == queue_sz)
    queue_end = 0;

  // przypadek w ktorym nowo wstawainy element zastepuje ostatni element
  if(queue_end == queue_begin)
    {
      dequeue();
    }
  
  return queue_end;
}

// zwraca indeks pierwszego elementu i ustawia nastepny jako pierwszy
int dequeue()
{
  int temp_begin = queue_begin;
  ++queue_begin;
  if(queue_begin == queue_sz)
    queue_begin = 0;

  return temp_begin;
}

int queue_empty()
{
  return queue_begin == queue_end;
}
// koniec implementacji kolejki specyficznej dla stringów

int contains_newline(char* str)
{
  return 0 != strchr(str, '\n');
}

int main(int argc, char *argv[])
{
  switch(argc)
    {
    case 2:
      if(argv[1][1] == 'n')
	sscanf(argv[1], "-n%d", &queue_sz);
      else
	sscanf(argv[1], "-%d", &queue_sz);
      break;
    case 3: sscanf(argv[2], "%d", &queue_sz); break;
    default: printf("sample usage: zad2.e -n6"); return -1;
    }

  if(queue_sz < 1)
    {
      printf("n must be positive\n");
      return -1;
    }
  
  init_queue();

  while(fgets(queue[enqueue()], default_line_len, stdin))
    {
      while(!contains_newline(queue[queue_end]))
	{
	  char* old = queue[queue_end];

	  {
	    int old_sz = strlen(old);
	    int new_sz = grow_ratio * old_sz;
	    queue[queue_end] = malloc(sizeof(char) * new_sz);
	    
	    strcpy(queue[queue_end], old);
	    if(!fgets(queue[queue_end] + old_sz, old_sz, stdin))
	      {
		// przypadek w ktorym nie ma ostatniej pustej linii
		break;
	      }
	  }
	  
	  free(old);
	}
    }

  while(!queue_empty())
    printf("%s", queue[dequeue()]);

  clean_queue();
  return 0;
}
