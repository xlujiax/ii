#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

void print_result();

int d = 1000;
double theta = 1.0 / double(d);

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
  if(p < 0)
    p = 0;
  if(p > 1.0)
    p = 1.0;
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

  static int l = 0;

  while(!terminate(x1, x2))
  {
      ++l;
      if(l % 200 == 0)
        print_result();
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
        if(probabilities[k] > 1)
            probabilities[k] = 1;
        if(probabilities[k] < 0)
            probabilities[k] = 0;
    }

    x1 = rand_individual();
    x2 = rand_individual();
  }

  print_result();
}

double add(double a, double b)
{
    return a + b;
}

void print_result()
{

    double sum = 0;
 for(int i = 0; i < d; ++i)
    sum += probabilities[i];
    double avg = sum / (double)d;

int cons = 0;
        int c = 0;
    for(int i = 0; i < d; ++i)
    {
        if(probabilities[i] < 0.5)
            ++c;
        else
            c = 0;
        if(cons < c)
            cons = c;
    }

  cout << "average: " << avg << "; longest almost-zeros sequence: " << cons << endl;

  //cout << "resulting vector of probabilities:\n";

  //for(int i = 0; i < d; ++i)
  //  cout << probabilities[i] << ' ';
  //cout << endl;
}

double onemax(const individual& v)
{
  return (double)count(v.begin(), v.end(), true);
}

double zeromax(const individual& v)
{
  return (double)count(v.begin(), v.end(), false);
}

double deceptive_onemax(const individual& v)
{
    int sum = count(v.begin(), v.end(), true);
    if(sum == 0)
    return d + 1;
  return (double)sum;
}

int k = 5;
double k_deceptive_onemax(const individual& v)
{
    int sum = 0;
    int i = 0;
    while(i != d)
    {
        int ksum = 0;
        for(int j = 0; j < k; ++j)
        {
            ++i;
            if(v[i])
                ksum ++;
        }
        if(ksum == 0)
            sum += k + 1;
        else
            sum += ksum;
    }
    return sum;
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

  cga(k_deceptive_onemax, terminate);

  return 0;
}
