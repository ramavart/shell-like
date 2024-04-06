#ifndef ICOMMANDDIRECTOR_H
#define ICOMMANDDIRECTOR_H

#include <memory>
#include <string>

#include "ICommand.h"

class ICommandDirector {
public:
  virtual void addCommand(const std::string &commandName,
                          std::unique_ptr<ICommand> command) = 0;
  virtual void execute(const std::string &instruction) = 0;
};

#endif // ICOMMANDDIRECTOR_H
