#ifndef LISTCOMMAND_H
#define LISTCOMMAND_H

#include <filesystem>
#include <map>

#include "CommandParser.h"
#include "ICommand.h"

class ListCommand : public ICommand {
public:
  ListCommand() {}
  ListCommand(std::shared_ptr<ICommandParser> commandParser);
  ListCommand(ListCommand &&) = default;

public:
  void setUp(const std::string &instruction) override;
  void operator()() override;

private:
  std::string applyOptions(const std::string &dirEntryPath,
                           const std::vector<OptionArgument> &options);
  std::string getType(const std::string &dirEntryPath);
  std::string getPermissions(const std::string &dirEntryPath);
  std::string getSize(const std::string &dirEntryPath,
                      const std::string &sizeRatio = SIZE_TYPE_DEFAULT_OPTION);

private:
  std::shared_ptr<ICommandParser> mCommandParser;
  std::string mInstruction;
};

#endif // LISTCOMMAND_H
