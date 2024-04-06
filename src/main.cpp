#include <iostream>

#include "include/CommandDirector.h"
#include "include/ListCommand.h"

using namespace std;

int main() {
  string command;
  auto commandParser = make_shared<CommandParser>();
  CommandDirector commandDirector(commandParser);
  commandDirector.addCommand(LIST_COMMAND,
                             make_unique<ListCommand>(commandParser));
  while (getline(cin, command)) {
    commandDirector.execute(command);
  }

  return 0;
}
