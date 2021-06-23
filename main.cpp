#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"

using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<size_t>make_histogram(vector<double>numbers, size_t bin_count)
{
	vector<size_t>bins(bin_count);
	double min, max;
	find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;

	for (size_t i = 0; i < numbers.size(); i++)
	{
		bool found = false;
		for (size_t j = 0; (j < bin_count - 1) && !found; j++)
		{
			auto lo = min + j * bin_size;
			auto hi = min + (j + 1) * bin_size;

			if ((lo <= numbers[i]) && (numbers[i] < hi))
			{
				bins[j]++;
				found = true;
			}

		}
		if (!found)
		{
			bins[bin_count - 1]++;
		}
	}

	return bins;
}


vector <size_t>show_histogram_text(vector<size_t>bins)
{

	size_t max_count = bins[0];
	for (size_t x : bins)
		if (x > max_count)
			max_count = x;
	if (max_count > 76)
	{

		for (size_t x : bins)
		{
			if (x < 100)
				cout << " ";
			if (x < 10)
				cout << " ";
			cout << x << "|";
			size_t height = 76 * (static_cast<double> (x) / max_count);
			for (size_t j = 0; j < height; j++)
				cout << "*";
			cout << endl;
		}

	}
	else
	{
		for (size_t x : bins)
		{
			if (x < 100)
				cout << " ";
			if (x < 10)
				cout << " ";
			cout << x << "|";
			for (size_t j = 0; j < x; j++)
				cout << "*";
			cout <<  endl;
		}
	}
	return bins;
}


vector<double> input_numbers(istream& in, size_t count)
{
	vector<double> result(count);
	for (size_t i = 0; i < count; i++)
	{
		in  >> result[i];
	}
	return result;
}

struct Input
{
    vector<double> numbers;
    size_t bin_count;
};


Input read_input(istream& in)
{
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count: ";
    in >> data.bin_count;

    return data;
}



int main()
{
    Input name;
    name = read_input(cin);
    vector<size_t>bins(name.bin_count);

    make_histogram(name.numbers, name.bin_count);

	show_histogram_svg (bins);
	return 0;
}
