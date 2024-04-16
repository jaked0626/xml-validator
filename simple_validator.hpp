#include <string>
#include <stack>

/**
 * @brief check for corner case of self closing tags. Assumes "<" or ">" that are intended 
 * to be strings are written as their respective character entity references. 
*/
bool DetermineXml(const std::string &input)
{
    using std::string, std::stack;

    stack<string> el_stack;
    int el_start = 0;
    int el_end = 0;
    string el;

    while ((el_start = input.find('<', el_end)) != string::npos)
    {
        el_end = input.find('>', el_start);
        el = input.substr(el_start, el_end - el_start + 1);

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
                return false;
            }
            el_stack.pop();
        }
    }
    
    return el_stack.empty();
}
