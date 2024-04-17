#include <string>
#include <stack>

/**
 * @brief Determines if an XML string is valid.
 *
 * @param input The XML string to be checked.
 * @param verbose A boolean flag indicating output of verbose messages.
 *
 * @return true if XML string valid, false otherwise.
 *
 * @note assumes that any "<" or ">" characters intended to be part of a string
 * are written as their respective character entity references. Ignores contents
 * of tag enclosed within its angle brackets, cdata, and comments.
 */
bool DetermineXml(const std::string &input, const bool verbose)
{
    using std::string, std::stack, std::cout;

    stack<string> el_stack;
    int el_start = 0;
    int el_end = 0;
    string el;

    while ((el_start = input.find('<', el_end)) != string::npos)
    {
        el_end = input.find('>', el_start);

        // unclosed tags are invalid
        if (el_end == string::npos) {
            if (verbose) { cout << "Message: Unclosed tag.\n"; }
            return false;
        }

        el = input.substr(el_start, el_end - el_start + 1);

        // catch ill formatted tags
        if (el[0] != '<' || el[el.size() - 1] != '>') {
            if (verbose) { cout << "Message: Tag structure is invalid.\n"; }
            return false;
        }
        // skip self closing tags, cdata, and comments
        if (el[el.size() - 2] == '/' || el[1] == '!' || el[1] == '?')
        {
            continue;
        }

        // opening tag
        if (el[1] != '/')
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
