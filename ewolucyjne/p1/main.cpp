#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>
using namespace std;

int d = 80;
double theta = 1.0 / 30;


double uniform_random(double a, double b)
{
    return a + (b - a) * ((double)rand() / (double)RAND_MAX);
}

bool binary_random(double p)
{
    if(uniform_random(0,1) < p)
        return 1;
    return 0;
}


vector<double> p;
void init_prob_vector()
{
    p.reserve(d);
    fill_n(back_inserter(p), d, 0.5);
}

vector<bool> rand_individual()
{
    vector<bool> v;
    v.reserve(d);
    for(int i = 0; i < d; ++i)
        v[i] = binary_random(p[i]);
    return v;
}


void cga(double (*F)(vector<bool>))
{
    init_prob_vector();

    vector<bool> x1 = rand_individual();
    vector<bool> x2 = rand_individual();

    F(x1);
    F(x2);

    while(!terminate)
    {
        for(int k = 0; k < d; ++k)
        {
            if(x1[k] && !x2[k])
	    {
	      
	    }
        }
    }

    cout << "p:\n";
    for(int i = 0; i < d; ++i)
        cout << p[i] << ' ';
    cout << endl;
}

double onemax(vector<bool> v)
{
    return (double)count(v.begin(), v.end(), true);
}

int main()
{
    srand(time(0));

    cga(onemax);

    return 0;
}
