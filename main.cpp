#include <iostream>
#include <getopt.h>
#include <string>
#include "simple_validator.hpp"

const char* program_name;

/* add file input? */
void print_usage(std::ostream& stream)
{
    stream <<  "Usage:" << program_name << " options <xmlString>\n";
    stream << " -h --help display this usage information.\n";
    stream << " -v --verbose display verbose messages.\n";
    stream << "Arguments:\n";
    stream << " <xmlString>   The XML string to validate.\n";
}

int main(int argc, char *argv[])
{
    // global using directives can cause name collisions down the line
    using std::string, std::cout, std::cerr, std::endl, std::exit;

    program_name = argv[0];
    bool verbose = false;
    const char* const short_options = "hv";
    const struct option long_options[] =
    {
        {"help", 0, NULL, 'h'},
        {"verbose", 0, NULL, 'v'},
        {NULL, 0, NULL, 0}
    };
    int next_option;
    while ((next_option = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
    {
        switch(next_option)
        {
        case 'h':
            print_usage(cout);
            exit(0);
        case 'v':
            verbose = true;
            break;
        case '?':
            print_usage(cerr);
            exit(1);
        default:
            break;
        }
    }

    string input;
    if (optind == argc - 1)
    {
        input = string(argv[optind]);
    }
    else
    {
        print_usage(cerr);
        exit(1);
    }

    cout << (DetermineXml(input, verbose) ? "Valid" : "Invalid") << endl;
    return 0;
}