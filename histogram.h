#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <vector>

using namespace std;

struct Input {
 vector<double> numbers;
 vector<size_t> bins;
    size_t bin_count;
};


void find_minmax(vector<double> numbers, double& min, double& max);
vector<size_t> make_histogram(Input &) ;

#endif // HISTOGRAM_H_INCLUDED
