#include <string>
#include <stack>

/**
 * @brief check for corner case of self closing tags. Assumes "<" or ">" that are intended 
 * to be strings are written as their respective character entity references. 
*/
bool DetermineXml(const std::string &input, const bool verbose)
{
    using std::string, std::stack, std::cout, std::endl;

    stack<string> el_stack;
    int el_start = 0;
    int el_end = 0;
    string el;

    while ((el_start = input.find('<', el_end)) != string::npos)
    {
        el_end = input.find('>', el_start);
        if (el_end == string::npos) {
            if (verbose) { cout << "Message: Unclosed tag.\n"; }
            return false;
        }

        el = input.substr(el_start, el_end - el_start + 1);
        if (el[0] != '<' || el[el.size() - 1] != '>') {
            if (verbose) { cout << "Message: Tag structure is invalid.\n"; }
            return false;
        }

        // skip self closing tag
        if (el[el.size() - 2] == '/')
        {
            continue;
        }
        // opening tag
        else if (el[1] != '/')
        {
            el_stack.push(el.substr(1, el.size() - 1));
        }
        // closing tag
        else
        {
            if (el_stack.empty() || el.substr(2, el.size()) != el_stack.top())
            {
                if (verbose) { cout << "Message: Mismatched closing tag\n"; }
                return false;
            }
            el_stack.pop();
        }
    }
    
    if (!el_stack.empty()) 
    { 
        if (verbose) { cout << "Message: Unmatched opening tag\n"; }
        return false;
    }

    return true;
}
