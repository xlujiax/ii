// Maciej Pacut
#include <stdio.h>

char* line;
int offset;

int isfloat(char t)
{
  switch(t)
    {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '0':
    case '.': // !
      return 1;
    default:
      return 0;
  }
}

void skipchar()
{
  ++offset;
}

char readchar()
{
  char t = line[offset];
  //printf("readchar: %c\n",t);
  return t;
}

float readfloat()
{
  float t;
  sscanf(line + offset, "%f", &t);
  //printf("readfloat: %f\n",t);
  return t;
}

void skipfloat()
{
  while(isfloat(readchar()))
    skipchar();
}

float factor();
float term();

float expression()
{
  float t1 = term();
  float t2;
  while(1)
    {
      char ch = readchar();
      switch(ch)
	{
	case '+':
	  skipchar();
	  t2 = term();
	  t1 = t1 + t2;
	  break;
	case '-':
	  skipchar();
	  t2 = term();
	  t1 = t1 - t2;
	  break;
	default: // w tym =
	  return t1;
	}
    }
}

float term()
{
  float f1 = factor();
  float f2;
  while(1)
    {
      char ch = readchar();
      switch(ch)
	{
	case '/':
	  skipchar();
	  f2 = factor();
	  f1 = f1 / f2;
	  break;
	case '*':
	  skipchar();
	  f2 = factor();
	  f1 = f1 * f2;
	  break;
	default:
	  return f1;;
	}
    }
}

float factor()
{
  char ch = readchar();
  if(ch == '(')
    {
      skipchar();
      float e = expression();
      if(readchar() == ')')
	{
	  skipchar();
	  return e;
	}
      else
	{
	  printf("err: mismatch parens\n");
	}
    }
  else if(isfloat(ch))
    {
      float f = readfloat();
      skipfloat();
      return f;
    }
  else if(ch == '-')
    {
      skipchar();
      return -expression();
    }
  else
    printf("err: unexpected character: %c\n", ch);
}

int main()
{
  int sz;
  while(-1 != getline(&line, &sz, stdin))
    {
      offset = 0;
      printf("%s%f\n\n", line, expression());
    }
  return 0;
}
