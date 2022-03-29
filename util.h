const std::string kShellStyle = " ~$TestShell > ";

#define RED "\033[34m"
#define RESET "\033[0m"

enum state
{
    EXIT_SUCC,
    EXIT_FAUL
};

void style_print(std::string cnt)
{
    std::cout << RED << cnt << RESET << std::endl;
}

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