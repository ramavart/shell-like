#ifndef DATATYPES_H
#define DATATYPES_H

#include <filesystem>
#include <map>

static const char *LIST_COMMAND = "ls";
static const char *SIZE_TYPE_DEFAULT_OPTION = "b";
static const size_t COUNT_POSSIBLE_OPTIONS_AT_ONCE = 3;

enum class Options : uint8_t {
  TYPE = static_cast<uint8_t>('t'),
  SIZE = static_cast<uint8_t>('s'),
  PERMISSION = static_cast<uint8_t>('p'),
  HELP = static_cast<uint8_t>('h')
};

struct OptionArgument {
  Options option;
  std::string argument;
};

enum ErrorCode {
  OK,
  WRONG_SYNTAX,
  PATH_IS_NOT_PROVIDED,
  TOO_MUCH_OPTIONS,
  INCORRECT_OPTIONS,
  INCORRECT_ARGUMENT
};

enum class SizeRatio : long {
  B = 1,
  KB = 1'000,
  MB = 1'000'000,
  GB = 1'000'000'000,
  TB = 1'000'000'000'000
};

static const std::map<std::string, SizeRatio> SIZE_RATIO{
    {SIZE_TYPE_DEFAULT_OPTION, SizeRatio::B},
    {"kb", SizeRatio::KB},
    {"mb", SizeRatio::MB},
    {"gb", SizeRatio::GB},
    {"tb", SizeRatio::TB}};

#endif // DATATYPES_H
