#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include "histogram.h"
#include <string>

void foo(int Dash_length, int Void_length, double top, int BIN_HEIGHT, int max_bin_count);
void show_histogram_svg(const vector<size_t>& bins);
void svg_begin(double width, double height);
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke, string fill);
void svg_end();


#endif // SVG_H_INCLUDED
