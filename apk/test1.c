int foo(void)
{
  return 42;
}

int bar(int power_level)
{
  if (power_level > 9000)
    return foo() + bar(foo());
  else
    return 0;
}

int main(void)
{
  int (*f)(void);
  f = foo;
  bar(f());
}
