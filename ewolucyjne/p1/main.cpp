#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>
using namespace std;

void print_result();

int d = 80;
double theta = 1.0 / 30;

typedef vector<bool> individual;


double uniform_random(double a, double b)
{
  double ret = a + (b - a) * ((double)rand() / (double)RAND_MAX);
  assert(a <= ret);
  assert(ret <= b);
  return ret;
}

bool binary_random(double p)
{
  assert(0.0 <= p);
  assert(p <= 1.0);
  if(uniform_random(0.0, 1.0) < p)
    return 1;
  return 0;
}


vector<double> probabilities;

void init_prob_vector()
{
  probabilities.reserve(d);
  fill_n(back_inserter(probabilities), d, 0.5);
}

individual rand_individual()
{
  individual v;
  v.resize(d);
  for(int i = 0; i < d; ++i)
    v[i] = binary_random(probabilities[i]);
  return v;
}

void print_individual(const individual& i)
{
  cout << "[ ";
  for(int j = 0; j < i.size(); ++j)
    cout << i[j] << ' ';
  cout << "]\n";
}

void cga(double (*F)(const individual&), bool (*terminate)(const individual&, const individual&))
{
  init_prob_vector();

  individual x1 = rand_individual();
  individual x2 = rand_individual();

  F(x1);
  F(x2);

  while(!terminate(x1, x2))
  {
    individual x_plus;
    individual x_minus;

    if(F(x1) >= F(x2))
    {
      x_plus = x1;
      x_minus = x2;
    }
    else
    {
      x_plus = x2;
      x_minus = x1;
    }

    for(int k = 0; k < d; ++k)
    {
      if(x_plus[k] && !x_minus[k])
	probabilities[k] += theta;
      if(!x_plus[k] && x_minus[k])
	probabilities[k] -= theta;
    }

    x1 = rand_individual();
    x2 = rand_individual();
  }

  print_result();
}

void print_result()
{
  cout << "resulting vector of probabilities:\n";
  for(int i = 0; i < d; ++i)
    cout << probabilities[i] << ' ';
  cout << endl;
}

double onemax(const individual& v)
{
  return (double)count(v.begin(), v.end(), true);
}

bool terminate(const individual&, const individual&)
{
  static int counter = 0;
  if(counter++ >= 100000)
    return true;
  return false;
}

int main()
{
  srand(time(0));

  cga(onemax, terminate);

  return 0;
}
