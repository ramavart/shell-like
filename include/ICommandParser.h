#ifndef ICOMMANDPARSER_H
#define ICOMMANDPARSER_H

#include <vector>

#include "DataTypes.h"

class ICommandParser {
public:
  virtual ErrorCode getOptions(const std::string &command,
                               std::vector<OptionArgument> &options) = 0;
  virtual void getCommand(const std::string &input, std::string &command) = 0;
  virtual ErrorCode getPath(const std::string &command, std::string &path) = 0;
};

#endif // ICOMMANDPARSER_H
