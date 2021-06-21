#include <iostream>
#include "svg.h"

using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

void foo(int Dash_length, int Void_length, double top, int BIN_HEIGHT, int max_bin_count)
{
    cout << "<line x1='50' y1='" <<  top + BIN_HEIGHT + 5 <<"' x2='" << max_bin_count * 50 << "' y2='" <<  top + BIN_HEIGHT + 5
    <<"' stroke='black' stroke-dasharray='" << Dash_length  << " " << Void_length << "' />";
}

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

void show_histogram_svg(const vector<size_t>& bins)
{
    //Индивидуальное задание
    int Dash_length = 0;
    int Void_length = 0;

    cerr << "Enter the length of the dash :  ";
    cin >> Dash_length;
    cerr << "Enter the length of the skip :  ";
    cin >> Void_length;

    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    double top = 0;

    //Маcштабирование
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

    foo(Dash_length, Void_length, top, BIN_HEIGHT, max_bin_count);

    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "lime", "#00ff00");
    top += BIN_HEIGHT +10;
    }


    svg_end();


}
