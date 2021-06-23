#include <iostream>
#include <vector>
#include <curl/curl.h>
#include "histogram.h"
#include "svg.h"

using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<size_t>make_histogram(Input& name)
{
	vector<size_t>bins(name.bin_count);
	double min, max;
	find_minmax(name.numbers, min, max);
    double bin_size = (max - min) / name.bin_count;

	for (size_t i = 0; i < name.numbers.size(); i++)
	{
		bool found = false;
		for (size_t j = 0; (j < name.bin_count - 1) && !found; j++)
		{
			auto lo = min + j * bin_size;
			auto hi = min + (j + 1) * bin_size;

			if ((lo <= name.numbers[i]) && (name.numbers[i] < hi))
			{
				bins[j]++;
				found = true;
			}

		}
		if (!found)
		{
			bins[name.bin_count - 1]++;
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



Input read_input(istream& in, bool prompt)
{
    Input data;

    if(prompt)
    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if(prompt)
    cerr << "Enter bin count: ";
    in >> data.bin_count;

    return data;
}



int main(int argc, char* argv[])
{
    if(argc > 1)
        {
            cout << "argc :  " << argc << endl;

            for(int i = 0; i < argc; ++i)
            cout << "argv[" << i << "] :  " << argv[i] << endl;
        return 0;
        }

    curl_global_init(CURL_GLOBAL_ALL);

    Input name;
    const auto input = read_input(cin, true);
    vector<size_t>bins(name.bin_count);

    make_histogram(name);
	show_histogram_svg (bins);
	return 0;
}
