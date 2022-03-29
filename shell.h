//
// Created by Administrator on 2022/3/10.
//
// #ifndef OSKERNEL_SHELL_H
// #define OSKERNEL_SHELL_H

// #include "util.hpp"

#include <unistd.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include <filesystem>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
namespace fs = std::filesystem;

const std::string kShellStyle = " ~$TestShell > ";

#define RED "\033[34m"
#define RESET "\033[0m"

enum state
{
    EXIT_SUCC,
    EXIT_FAUL
};

enum internel_func
{
    invalid_func,
    cd,
    ls,
    pwd,
    help,
    exits,
    echo,
};

class shell
{
private:
    std::vector<std::string> split_commands; // Store the input for call the internel func
    char delimiter = ' ';
    std::string commands;
    void show_shell_style();
    void style_print(std::string cnt);

public:
    // void Print_system_info();
    // std::string *Command_Split(std::string message);
    // std::vector<std::string> Command_Identification();

    shell();
    void readline();       // get commands
    void print_commands(); // log  commands

private:
    std::vector<std::string> get_commands(); //{ return split_commands; }
    std::string get_command();               //{ return get_commands()[0]; }

    void command_split(std::string command); // split the commands to get command and args
    void shell_loop();
    void cd(std::string tarDir);
    void ls();
    void echo();
    void exit();
    void execute();
    void pwd();
};

// #endif // OSKERNEL_SHELL_H
