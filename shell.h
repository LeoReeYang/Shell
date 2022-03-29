//
// Created by Administrator on 2022/3/10.
//
#ifndef OSKERNEL_SHELL_H
#define OSKERNEL_SHELL_H

#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <filesystem>
#include <algorithm>
#include <map>

#include "util.h"

namespace fs = std::filesystem;

class shell
{
private:
    std::vector<std::string> split_commands; // Store the input for call the internel func
    char delimiter = ' ';
    std::string commands;

public:
    void Print_system_info();
    std::string *Command_Split(std::string message);
    std::vector<std::string> Command_Identification();

    shell() { shell_loop(); }
    void readline();       // get commands
    void print_commands(); // log  commands

private:
    std::vector<std::string> get_commands() { return split_commands; }
    std::string get_command() { return get_commands()[0]; }

    void command_split(std::string command); // split the commands to get command and args
    void shell_loop();
    void cd(std::string tarDir);
    void ls();
    void echo();
    void exit();
    void execute();
    void pwd();

    void show_shell_sytle() { std::cout << RED << fs::current_path() << kShellStyle << RESET; }
};

#endif // OSKERNEL_SHELL_H
