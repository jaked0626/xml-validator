# Pull request description-like document (write/modify whatever you want, including this title)

## What?

Added:

- implementation of xml validator.
- test cases.
- Added options (help flag and verbose flag) for better user exerience.

## Why?

- Test cases help cover corner cases such as self closing tags, unclosed tags, cdata, comments, and processing instructions.
- help flag shows instructions on how to use the tool so new users will have guidance without referring to external resources.
- verbose flag outputs messages of how the xml is invalid so that users have an easier time correcting their invalid xml strings.

## How?

- Implementation of XML validator
  - I use a simple stack implementation for validating the xml input. This method validates the input in linear time with just one iteration. The method works like this:
    - I iterate through the input string to find xml tags, which are defined as tags enclosed in angle brackets `<>`
    - I regard self closing tags as valid and skip over comments, cdata, and processing instructions. Adding validity checks for these is easy if needed.
    - For every opening tag, I push the tag content to the stack.
    - For every closing tag, I compare its contents with the last opened tag found at the top of the stack. If they are equal, the string is valid and I pop the tag contents from the stack and continue. If they are not equal, there is a mismatch between opening and closing tags.
    - After iterating through the input string, the stack should be empty, meaning there was a corresponding closing tag for ever opening tag.
  - I rely on the native `string.find()` and `string.substring()` for identifying characters in a string and extracting substrings. I choose these over pointers which are more memory efficient in favor of readability. Given the simplicity of what is trying to be achieved and the unlikeliness of memory being a bottleneck, I believe this to be the better approach.
  - Implementation depends on certain formatting conventions for xml (such as the position of `/` having to be adjacent to `<>` ) which seems sufficient, but will be thrown off by unconventional spacing.
- Parsing Flags
  - I use `getopt_long` to parse flags because of its simplicity and wide use.

## Testing?

- Build `checker` and run in terminal. See `HowToBuild.md` for more detail.
- The test cases can be found in `checker.cpp`

## Anything Else?

- global using directives can cause name collisions down the line so i have moved all using directives to a local scope with higher specificity.
- I am using syntax specific to c++ std=17 (one line using directives) and have specified the cpp standard in `CMakeLists.txt`
