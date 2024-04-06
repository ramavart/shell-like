#include "include/CommandDirector.h"
#include "include/CommandParser.h"
#include "include/templates.h"

using namespace std;

CommandDirector::CommandDirector(std::shared_ptr<ICommandParser> commandParser)
    : mCommandParser(commandParser) {}

void CommandDirector::addCommand(const std::string &commandName,
                                 std::unique_ptr<ICommand> command) {
  mCommands[commandName] = std::move(command);
}

bool CommandDirector::verifyCommandExists(const string &command) {
  return mCommands.find(command) != mCommands.end() ? true : false;
}

void CommandDirector::execute(const std::string &instruction) {
  string command;
  mCommandParser->getCommand(instruction, command);
  if (verifyCommandExists(command)) {
    mCommands[command]->setUp(instruction);
    mCommands[command]->operator()();
  } else {
    print("No such command: ", command);
  }
}
