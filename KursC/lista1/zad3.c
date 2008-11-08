// Maciej Pacut
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* pattern;
int npattern;
char line[100];
int nline;

int hits = 0;
int loses = 0;

unsigned long long fingerprint(char* str, int from, int to)
{
  unsigned long long sum = 0;
  int i;
  for(i = from; i < to; ++i)
    sum += str[i];
  return sum;
}

int strings_eql(char* a, int sa, int ea, char* b, int sb, int eb)
{
  for(; sa < ea && sb < eb; sa++, sb++)
    {
      if(a[sa] != b[sb])
	return 0;
    }
  return 1;
}

int contains_pattern(char* pattern, int npattern, char* line, int nline)
{
  unsigned long long fline;
  unsigned long long fpattern = fingerprint(pattern, 0, npattern);
  int i;
  for(i = 0; i < nline - npattern; ++i)
    {
      fline = fingerprint(line, i, i + npattern);
      if(fline == fpattern)
	{
	  if(strings_eql(pattern, 0, npattern, line, i, i + npattern))
	    {
	      hits++;
	      return 1;
	    }
	  else
	    loses++;
	}
      fline += line[i + npattern];
      fline -= line[i];
    }
  return 0;
}

int main(int argc, char* argv[])
{
  if(argc == 2)
    pattern = argv[1];
  else
    {
      printf("usage: zad3.e pattern\n");
      return 0;
    }
  npattern = strlen(pattern);
  while(fgets(line, 100, stdin))
    {
      nline = strlen(line);
      if(contains_pattern(pattern, npattern, line, nline))
	printf("%s", line);
    }
  fprintf(stderr, "hits: %d\nloses: %d\nperc: %f\n", hits, loses, 100.0f * ((float)hits) / ((float)(hits + loses)));
  return 0;
}
