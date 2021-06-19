#include <iostream>
#include <vector>
using namespace std;

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text(double left, double baseline, string text)
{
cout << "<text x='" << left <<"' y='"<<baseline<<"' >"<<text<<"</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill) //За цвет линий в SVG отвечает атрибут stroke, а за цвет заливки — fill.
{
cout << "<rect x=' " <<x<< "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='#" << fill << " '/>";
}
void svg_end()
{
    cout << "</svg>\n";
}

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    double top = 0;

    int max_bin_count = bins[0];

    for (int i = 0; i < bins.size(); i++)
    if (bins[i] > max_bin_count)
    max_bin_count = bins[i];

    for (size_t i=0; i< bins.size(); ++i)
    {
        int height = bins[i];

        if  (max_bin_count > MAX_ASTERISK)
            height = 76 * (static_cast<double>(bins[i])/ max_bin_count);
    }


    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    for (size_t bin : bins)
    {
    const double bin_width = BLOCK_WIDTH * bin;
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "blue", "#aaffaa");
    top += BIN_HEIGHT;
    }

    svg_end();


}

void find_minmax(vector<double> numbers, double& min, double& max)
{
	min = numbers[0];
	max = numbers[0];
	for (double x : numbers)
	{
		if (x < min)
		{
			min = x;
		}
		else if (x > max)
		{
			max = x;
		}
	}
}


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
