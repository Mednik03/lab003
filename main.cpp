#include <iostream>
#include <vector>
#include <curl/curl.h>
#include <sstream>
#include <string>
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


size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    auto data_size = item_size * item_count;

    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);

    buffer->write(reinterpret_cast<const char*>(items), data_size);

    return data_size;
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


Input download(const string& address)
{
    stringstream buffer;

    CURL *curl = curl_easy_init();

    if(curl)

    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, &buffer);

        res = curl_easy_perform(curl);
        if (res != 0)
        {

            cerr<< "curl_easy_perform() failed: %s\n"<< curl_easy_strerror(res);
            exit(1);
        }


        if(res == CURLE_OK)
        {
            long req;
            res = curl_easy_getinfo(curl, CURLINFO_REQUEST_SIZE, &req);
            if(!res)
                fprintf(stderr,"Request size: %ld bytes\n", req);

        }
        curl_easy_cleanup(curl);
    }

    return read_input(buffer, false);
}

string make_info_text()
{
    stringstream buffer;
    // TODO: получить версию системы, записать в буфер.
    // TODO: получить имя компьютера, записать в буфер.
    return buffer.str();
}

int main(int argc, char* argv[])
{

    Input name;
    if (argc > 1)
    {
        name = download(argv[1]);
    }
    else
    {
        name = read_input(cin, true);
    }

    curl_global_init(CURL_GLOBAL_ALL);

    vector<size_t>bins = make_histogram(name);
    show_histogram_svg (bins);
    return 0;
}
