#include <algorithm>
#include <filesystem>
#include <iostream>
#include <sstream>

#include "include/CommandParser.h"
#include "include/ListCommand.h"
#include "include/templates.h"

using namespace std;
namespace {
const char *HELP_MESSAGE =
    "ls\n"
    "NAME \n"
    "              ls - list directory contents\n"
    "SYNOPSIS"
    "              ls [OPTION]... [FILE]\n"
    "DESCRIPTION\n"
    "List information about the FILEs\n"
    "OPTION:\n"
    "-t shows type of the file\n"
    "-s shows size of the file(by default bytes)\n"
    "   can accept one of the following arguments:\n"
    "   kb   (kilobytes)\n"
    "   mb   (megabytes)\n"
    "   gb   (gigabytes)\n"
    "   tb   (terrabytes)\n"
    "-p shows standard permissions related to users/groups\n"
    "-h shows this help message. Works exclusevly. This means if use\n"
    "   this option along with others. Only this message will be shown\n"
    "FILE\n"
    "file path should always be presend in command and start with . or / \n"
    "EXAMPLES\n"
    "ls -stp /bin\n"
    "ls -s -t -p /bin\n"
    "ls -s kb -tp /bin\n";

const size_t PATH_RESERVED_LENGTH = 100;
const size_t AFTER_PATH_EXTRA_GAP = 5;
const size_t SIZE_RESERVED_LENGTH = 15;
const size_t TYPE_RESERVED_LENGTH = 12;
const size_t PERMISSION_RESERVED_LENGTH = 20;
const std::map<std::filesystem::file_type, std::string> FILE_TYPES{
    {std::filesystem::file_type::none, "none"},
    {std::filesystem::file_type::not_found, "not_found"},
    {std::filesystem::file_type::regular, "regular"},
    {std::filesystem::file_type::directory, "directory"},
    {std::filesystem::file_type::symlink, "symlink"},
    {std::filesystem::file_type::block, "block"},
    {std::filesystem::file_type::character, "character"},
    {std::filesystem::file_type::fifo, "fifo"},
    {std::filesystem::file_type::socket, "socket"},
    {std::filesystem::file_type::unknown, "unknown"}};
} // namespace

namespace fs = std::filesystem;

auto addSpacing = [](string &input, int sizeOfGap) {
  input += std::string(sizeOfGap, ' ');
};

ListCommand::ListCommand(std::shared_ptr<ICommandParser> commandParser)
    : mCommandParser(commandParser) {}

void ListCommand::setUp(const string &instruction) {
  mInstruction = instruction;
}

void ListCommand::operator()() {
  stringstream s(mInstruction);
  string path;

  vector<OptionArgument> options{COUNT_POSSIBLE_OPTIONS_AT_ONCE};

  if (auto errorCode =
          mCommandParser->getOptions(mInstruction, options) != ErrorCode::OK) {
    return;
  }

  if (find_if(options.begin(), options.end(), [](auto optionArg) {
        return optionArg.option == Options::HELP ? true : false;
      }) != options.end()) {
    print(HELP_MESSAGE);
    return;
  }

  if (auto errorCode =
          mCommandParser->getPath(mInstruction, path) != ErrorCode::OK) {
    print("cannot get path, error code: ", errorCode, '\n',
          "path should start with . or / symbols");
    return;
  }

  if (!std::filesystem::exists(path)) {
    print("this path: ", path, "doesn't exist");
    return;
  }

  string columnNames = string(" path");
  addSpacing(columnNames, PATH_RESERVED_LENGTH - columnNames.size());

  for (auto opt : options) {
    switch (opt.option) {
    case Options::TYPE: {
      string type("file type");
      columnNames += type;
      addSpacing(columnNames, TYPE_RESERVED_LENGTH - type.size());
      break;
    }
    case Options::SIZE: {
      string size("size");
      columnNames += size;
      addSpacing(columnNames, SIZE_RESERVED_LENGTH - size.size());
      break;
    }
    case Options::PERMISSION: {
      string permissions("permissions");
      columnNames += permissions;
      addSpacing(columnNames, PERMISSION_RESERVED_LENGTH - permissions.size());
      break;
    }
    default:
      print("Such option does not exist: ", static_cast<char>(opt.option));
      return;
    }
  }

  print(columnNames);

  for (auto const &dir_entry : fs::directory_iterator{path}) {
    print(dir_entry.path().c_str(), applyOptions(dir_entry.path(), options));
  }
}

std::string ListCommand::applyOptions(const string &dirEntryPath,
                                      const vector<OptionArgument> &options) {
  string spacing;
  if (dirEntryPath.size() < PATH_RESERVED_LENGTH) {
    addSpacing(spacing, PATH_RESERVED_LENGTH - dirEntryPath.size());
  } else {
    addSpacing(spacing, AFTER_PATH_EXTRA_GAP);
  }

  string description = spacing;
  for (auto opt : options) {
    switch (opt.option) {
    case Options::TYPE:
      description += getType(dirEntryPath);
      break;
    case Options::SIZE:
      if (opt.argument.size() != 0) {
        description += getSize(dirEntryPath, opt.argument);
      } else {
        description += getSize(dirEntryPath);
      }
      break;
    case Options::PERMISSION:
      description += getPermissions(dirEntryPath);
      break;
    default:
      print("Such option does not exist: ", static_cast<char>(opt.option));
    }
  }

  mInstruction.clear();
  return description;
}

std::string ListCommand::getType(const string &dirEntryPath) {
  string result;
  auto type = fs::status(dirEntryPath).type();
  auto typeName = FILE_TYPES.at(type);
  result += typeName;

  addSpacing(result, TYPE_RESERVED_LENGTH - typeName.size());
  return result;
}

std::string ListCommand::getPermissions(const string &dirEntryPath) {
  using fs::perms;

  auto permissions = fs::status(dirEntryPath).permissions();
  string permissionsInfo;
  auto decorate = [&permissionsInfo, permissions](char op, perms p) {
    permissionsInfo += (perms::none == (permissions & p) ? '-' : op);
  };
  decorate('r', perms::owner_read);
  decorate('w', perms::owner_write);
  decorate('x', perms::owner_exec);
  decorate('r', perms::group_read);
  decorate('w', perms::group_write);
  decorate('x', perms::group_exec);
  decorate('r', perms::others_read);
  decorate('w', perms::others_write);
  decorate('x', perms::others_exec);

  addSpacing(permissionsInfo,
             PERMISSION_RESERVED_LENGTH - permissionsInfo.size());
  return permissionsInfo;
}

string ListCommand::getSize(const string &dirEntryPath,
                            const string &sizeType) {
  string result;
  if (!fs::is_directory(dirEntryPath)) {
    auto size = fs::file_size(fs::path(dirEntryPath));
    auto ratioI = SIZE_RATIO.find(sizeType);

    string fileSize;
    if ((*ratioI).second == SizeRatio::B) {
      fileSize = to_string(size / static_cast<long>((*ratioI).second));
    } else {
      fileSize = to_string(size / static_cast<float>((*ratioI).second));
    }

    result += fileSize;
    addSpacing(result, SIZE_RESERVED_LENGTH - fileSize.size());
  } else {
    result += string(SIZE_RESERVED_LENGTH, ' ');
  }
  return result;
}
