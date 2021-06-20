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


vector<double> input_numbers(size_t count)
{
	vector<double> result(count);
	for (size_t i = 0; i < count; i++)
	{
		cin  >> result[i];
	}
	return result;
}

int main()
{
	size_t i;
	size_t number_count;
	cerr << "Enter number count: ";
	cin >> number_count;
	const auto numbers = input_numbers(number_count);
	size_t bin_count;
	cerr << "bin_count: ";
	cin >> bin_count;
	const auto bins = make_histogram(numbers, bin_count);
	show_histogram_svg (bins);
	return 0;
}
