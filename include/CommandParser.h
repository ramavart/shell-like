#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <string>
#include <vector>

#include "ICommandParser.h"

class CommandParser : public ICommandParser {
public:
  ErrorCode getOptions(const std::string &command,
                       std::vector<OptionArgument> &options) override;
  void getCommand(const std::string &input, std::string &command) override;
  ErrorCode getPath(const std::string &command, std::string &path) override;

private:
  ErrorCode verifySizeArgument(const std::string &sizeArgument);
  ErrorCode verifyOption(char ch);
};

#endif // COMMANDPARSER_H
