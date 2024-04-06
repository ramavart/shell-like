#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>

class ICommand {
public:
  virtual ~ICommand() = default;
  virtual void setUp(const std::string &command) = 0;
  virtual void operator()() = 0;
};

#endif // ICOMMAND_H
