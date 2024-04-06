#ifndef COMMANDDIRECTOR_H
#define COMMANDDIRECTOR_H

#include <map>

#include "ICommand.h"
#include "ICommandDirector.h"

class ICommandParser;

class CommandDirector : public ICommandDirector {
public:
  CommandDirector(std::shared_ptr<ICommandParser> commandParser);

public:
  void addCommand(const std::string &commandName,
                  std::unique_ptr<ICommand> command) override;
  void execute(const std::string &instruction) override;

private:
  bool verifyCommandExists(const std::string &command);

private:
  std::map<std::string, std::unique_ptr<ICommand>> mCommands;
  std::shared_ptr<ICommandParser> mCommandParser;
};

#endif // COMMANDDIRECTOR_H
