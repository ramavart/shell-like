#include <algorithm>
#include <iostream>
#include <sstream>

#include "include/CommandParser.h"
#include "include/templates.h"

using namespace std;

auto isPath = [](auto ch) { return (ch == '/' || ch == '.'); };
auto isOptionBegin = [](auto ch) { return ch == '-'; };

static const auto SIZE_OF_ANY_OPTION = 2;

ErrorCode CommandParser::getOptions(const string &command,
                                    vector<OptionArgument> &options) {
  ErrorCode code = ErrorCode::OK;
  auto optionsStart = find_if(command.begin(), command.end(), isOptionBegin);
  auto optionsEnd = find_if(command.begin(), command.end(), isPath);
  int actualOptionsCount = 0;
  if (optionsStart != command.end()) {
    string optionsData;
    if (optionsStart < optionsEnd) {
      optionsData = std::string(optionsStart, optionsEnd);
    } else {
      print("PATH is in a wrong place");
      return ErrorCode::WRONG_SYNTAX;
    }

    stringstream s(optionsData);
    string optionToken;

    while (s >> optionToken) {
      if (actualOptionsCount == COUNT_POSSIBLE_OPTIONS_AT_ONCE) {
        print("Max count of options were provided");
        code = ErrorCode::TOO_MUCH_OPTIONS;
        break;
      }

      if (isOptionBegin(optionToken[0]) &&
          verifyOption(optionToken[1]) == ErrorCode::OK) {
        // option like -s
        if (optionToken.size() == SIZE_OF_ANY_OPTION) {
          string argument;
          auto beforeArgCheckPos = s.tellg();
          s >> argument;

          if (!isOptionBegin(argument[0]) && !isPath(argument[0]) &&
              argument.size() != 0) {
            if (optionToken[1] == static_cast<char>(Options::SIZE)) {
              if ((code = verifySizeArgument(argument)) == ErrorCode::OK) {
                options[actualOptionsCount] = {
                    static_cast<Options>(optionToken[1]), argument};
                actualOptionsCount++;
              } else {
                print("Error code is ErrorCode::INCORRECT_ARGUMENT, check "
                      "argument for -s (size) option");
                break;
              }
            }
          } else {
            options[actualOptionsCount] = {
                static_cast<Options>(optionToken[1])};
            actualOptionsCount++;
            s.seekg(beforeArgCheckPos);
          }
        } // options like -stp
        else {
          for (int i = 1; i < optionToken.size(); i++) {
            if (actualOptionsCount == COUNT_POSSIBLE_OPTIONS_AT_ONCE) {
              print("Max count options were provided");
              code = ErrorCode::TOO_MUCH_OPTIONS;
              break;
            }

            if ((code = verifyOption(optionToken[i])) == ErrorCode::OK) {
              options[actualOptionsCount] = {
                  static_cast<Options>(optionToken[i])};
              actualOptionsCount++;
            } else {
              break;
            }
          }

          if (code != ErrorCode::OK)
            break;
        }
      } else {
        print("Is not an option: ", optionToken);
      }
    }
  }
  options.resize(actualOptionsCount);

  return code;
}

ErrorCode CommandParser::getPath(const string &command, string &path) {
  stringstream s(command);
  ErrorCode code = ErrorCode::PATH_IS_NOT_PROVIDED;

  while (s >> path) {
    if (find_if(path.begin(), path.end(), isPath) != path.end()) {
      code = ErrorCode::OK;
      break;
    }
  }

  return code;
}

void CommandParser::getCommand(const string &input, string &command) {
  stringstream s(input);
  s >> command;
}

ErrorCode CommandParser::verifySizeArgument(const string &sizeArgument) {
  auto ratioI = SIZE_RATIO.find(sizeArgument);
  return ratioI != SIZE_RATIO.end() ? ErrorCode::OK
                                    : ErrorCode::INCORRECT_ARGUMENT;
}

ErrorCode CommandParser::verifyOption(char ch) {
  ErrorCode res = ErrorCode::INCORRECT_OPTIONS;
  if (ch == static_cast<char>(Options::HELP) ||
      ch == static_cast<char>(Options::PERMISSION) ||
      ch == static_cast<char>(Options::SIZE) ||
      ch == static_cast<char>(Options::TYPE)) {
    res = ErrorCode::OK;
  } else {
    print("There is no such option: ", ch);
  }
  return res;
}
