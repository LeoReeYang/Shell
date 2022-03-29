#include "shell.h"

template <typename Out>
void split(const std::string &s, char delim, Out result)
{
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim))
    {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

internel_func resolveOption(std::string inputfunc) // string to interel_func
{
    static const std::map<std::string, internel_func>
        funcStrings{
            {"cd", cd},
            {"pwd", pwd},
            {"ls", ls},
            {"help", help},
            {"echo", echo},
            {"exit", exits},
        };

    auto itr = funcStrings.find(inputfunc);
    if (itr != funcStrings.end())
    {
        return itr->second;
    }
    return invalid_func;
}

void shell::execute()
{
    switch (resolveOption(get_command()))
    {
    case 6: // echo
        echo();
        break;
    case 5: // exits
        break;
    case 4: // help,wait for api
        break;
    case 3: // ls
        pwd();
        break;
    case 2:
        ls();
        break;
    case 1: // cd
        cd(split_commands[1]);
        break;
    default: // invalid_func
        style_print("command is not support.");
        break;
    }
}

void shell::style_print(std::string cnt)
{
    std::cout << RED << cnt << RESET << std::endl;
}

void shell::show_shell_style() { std::cout << RED << fs::current_path() << kShellStyle << RESET; }

shell::shell()
{
    shell_loop();
}

void shell::pwd()
{
    std::cout << fs::current_path() << std::endl;
}
void shell::cd(std::string tarDir)
{
    fs::current_path(tarDir);
}

void shell::echo()
{
    std::string temp;
    for (const auto &elem : split_commands)
    {
        temp += elem;
    }
    std::cout << temp << std::endl;
}

void shell::ls()
{
    for (const auto &entry : fs::directory_iterator(fs::current_path()))
    {
        std::string fn(entry.path());
        std::string reversefn(fn);
        std::reverse(reversefn.begin(), reversefn.end());

        std::cout << fn.substr(fn.size() - reversefn.find("/")) << std::endl;
    }
}

void shell::print_commands()
{
    for (const auto &elem : get_commands())
        std::cout << elem << " ";
    std::cout << std::endl;
}

void shell::shell_loop()
{
    do
    {
    label:
        show_shell_style();
        readline();

        if (commands.size() != 0)
        {
            command_split(commands);
            execute();
        }
        else
            goto label;
    } while (split_commands[0] != "exit");
}

void shell::readline()
{
    std::getline(std::cin, commands);
}

void shell::command_split(std::string command)
{
    split_commands = split(command, delimiter);
}

std::vector<std::string> shell::get_commands() { return split_commands; }
std::string shell::get_command() { return get_commands()[0]; }