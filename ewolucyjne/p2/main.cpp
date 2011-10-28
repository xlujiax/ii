#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>
#include <ctime>
#include <set>
using namespace std;

const int MAX_N = 100;
int a[MAX_N][MAX_N];
int b[MAX_N][MAX_N];
int n;

double uniform_deviate ( int seed )
{
  return seed * ( 1.0 / ( RAND_MAX + 1.0 ) );
}

float uniform_random()
{
  return uniform_deviate(rand());
}

void print_data()
{
  cout << n << '\n';
  for(int x = 0; x < n; ++x)
  {
    for(int y = 0; y < n; ++y)
      cout << b[x][y] << ' ';
    cout << '\n';
  }
  cout << '\n';
  for(int x = 0; x < n; ++x)
  {
    for(int y = 0; y < n; ++y)
      cout << a[x][y] << ' ';
    cout << '\n';
  }
}

bool is_perm(const vector<int>& p)
{
  vector<bool> is_in(n, false);
  for(int i = 0; i < n; ++i)
    if(is_in[p[i]])
      return false;
    else
      is_in[p[i]] = true;
  for(int i = 0; i < n; ++i)
    if(!is_in[i])
      return false;
  return true;
}

vector<int> random_permutation()
{
  vector<int> result;
  result.reserve(n);
  for(int i = 0; i < n; ++i)
    result.push_back(i);
  for(int i = 0; i < n; ++i)
    swap(result[i], result[rand() % (i + 1)]);
  return result;
}

int eval(const vector<int>& p)
{
  int sum = 0;
  for(int i = 0; i < n; ++i)
    for(int j = i+1; j < n; ++j)
      sum += a[i][j] * b[p[i]][p[j]];
  return sum;
}

void print_perm(const vector<int>& v)
{
  cout << "[ ";
  for(int i = 0; i < n; ++i)
    cout << v[i] << ' ';
  cout << "]\n";
}

struct eval_cmp
{
  int operator()(const vector<int>& p1, const vector<int>& p2) const
  {
    return less_equal<int>()(eval(p1), eval(p2));
  }
};

vector<int> mutation(const vector<int>& p, int r, int s)
{
  assert(is_perm(p));
  assert(r <= s);

  vector<int> result(p.begin(), p.end());
  swap(result[r], result[s]);

  assert(is_perm(result));
  return result;
}

int pos_in_perm(const vector<int>& p, int v)
{
  assert(v <= n);
  assert(is_perm(p));
  vector<int>::const_iterator i = find(p.begin(), p.end(), v);
  assert(i != p.end());
  return i - p.begin();
}

pair<vector<int>, vector<int> > crossover(const vector<int>& p1, const vector<int>& p2, int r, int s)
{
  assert(is_perm(p1));
  assert(is_perm(p2));
  assert(r <= s);
  assert(s <= n);
  assert(r <= n);

  vector<int> result1(p1.begin(), p1.end());
  vector<int> result2(p2.begin(), p2.end());

  assert(p1.size() == n);
  assert(p2.size() == n);

  const int empty = -1;
  // range <r, s>
  for(int i = r; i < s + 1; ++i)
  {
    result1[i] = result2[i] = empty;
  }
  // generating result1 from <r,s> part of p2
  for(int i = r; i < s + 1; ++i)
  {
    int p_gene = p2[i];
    int proposed_gene = p_gene;
    while(true)
    {
      if(result1.end() == find(result1.begin(), result1.end(), proposed_gene))
      {
        // no proposed_gene in result1
        result1[i] = proposed_gene;
        break;
      }
      else
      {
        // proposed_gene in result already
        // we should find new value

        proposed_gene = p2[pos_in_perm(p1, proposed_gene)];
      }
    }
  }

  // generating result2 from <r,s> part of p1
  for(int i = r; i < s + 1; ++i)
  {
    int p_gene = p1[i];
    int proposed_gene = p_gene;
    while(true)
    {
      if(result2.end() == find(result2.begin(), result2.end(), proposed_gene))
      {
        // no proposed_gene in result1
        result2[i] = proposed_gene;
        break;
      }
      else
      {
        // proposed_gene in result already
        // we should find new value

        proposed_gene = p1[pos_in_perm(p2, proposed_gene)];
      }
    }
  }

  assert(is_perm(result1));
  assert(is_perm(result2));
  return make_pair(result1, result2);
}

void read_input()
{
  cin >> n;

  for(int x = 0; x < n; ++x)
    for(int y = 0; y < n; ++y)
      cin >> b[x][y];

  for(int x = 0; x < n; ++x)
    for(int y = 0; y < n; ++y)
      cin >> a[x][y];
}

// SGA
set<vector<int>, eval_cmp> population;
const int population_size = 100;
const int parents = 50;
const int max_iter = 10000;
const float mutation_prob = 0.01;

int iteration = 0;

void fill_population()
{
  for(int i = 0; i < population_size; ++i)
    population.insert(random_permutation());
}

void print_population()
{
  for(set<vector<int>, eval_cmp>::iterator i = population.begin(); i != population.end(); ++i)
  {
    cout << eval(*i) << " = ";
    print_perm(*i);
  }
}

bool termination_condition()
{
  return iteration > max_iter;
}

void population_replacement()
{
  // first one in population is the weakest one
  float Fmin = eval(*population.begin());
  float Fsum = 0;
  for(set<vector<int>, eval_cmp>::iterator i = population.begin(); i != population.end(); ++i)
    Fsum += eval(*i) - Fmin;

  if(Fsum > 0.0)
  {
    for(set<vector<int>, eval_cmp>::iterator i = population.begin(); i != population.end(); ++i)
    {
      float adaptation = (eval(*i) - Fmin) / Fsum;
      assert(0.0 <= adaptation && adaptation <= 1.0);
      if(uniform_random() <= adaptation)
      {
        population.erase(i);
      }

      assert(population_size <= population.size());
    }
  }
  else
  {
    // unimplemented
    // every one in population is a copy of the same entity
    assert(false);
  }

  // if after erasing with adaptation method there are still too many entities
  while(population_size < population.size())
    population.erase(population.begin());
}

void population_crossover()
{
  assert(population.size() > 0);
  for(int i = 0; i < parents; ++i)
  {
    set<vector<int>, eval_cmp>::const_iterator p1i = population.begin();
    advance(p1i, rand() % population.size());

    set<vector<int>, eval_cmp>::const_iterator p2i = population.begin();
    advance(p2i, rand() % population.size());

    int r = rand() % n;
    int s = rand() % n;
    if(r > s)
      swap(r, s);

    pair<vector<int>, vector<int> > crossed = crossover(*p1i, *p2i, r, s);
    population.insert(crossed.first);
    population.insert(crossed.second);
  }
}

void population_mutation()
{
  for(set<vector<int>, eval_cmp>::iterator i = population.begin(); i != population.end(); ++i)
  {
    int r = rand() % n;
    int s = rand() % n;
    if(r > s)
      swap(r, s);
    if(uniform_random() < mutation_prob)
      population.insert(mutation(*i, r, s));
  }
}

void sga()
{
  fill_population();
  while(!termination_condition())
  {
    population_crossover();
    population_mutation();
    population_replacement();
    ++iteration;
  }

  print_population();
}

void init_random()
{
  srand(time(0));
}

int main()
{
  init_random();
  read_input();
  sga();

  return 0;
}
