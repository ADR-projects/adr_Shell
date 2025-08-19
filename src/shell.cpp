#include <iostream>
#include <string>
#include <windows.h>
#include <direct.h>
#include <fcntl.h>
#include <io.h>
using namespace std;
void intro()
{
    std::cout << " ____              _        ____  _          _ _    ____\n"
              << " \\ \\ \\    __ _  __| |_ __  / ___|| |__   ___| | |  / / /\n"
              << "  \\ \\ \\  / _` |/ _` | '__| \\___ \\| '_ \\ / _ \\ | | / / / \n"
              << "  / / / | (_| | (_| | |     ___) | | | |  __/ | | \\ \\ \\ \n"
              << " /_/_/   \\__,_|\\__,_|_|    |____/|_| |_|\\___|_|_|  \\_\\_\\\n";
    std::cout << "\n\tWelcome to adrShell v1.0\n\tRuns On: Windows\n";
    std::cout << "\tType help to see guide.\n";
}

void systemcmd(std::string cmd, std::string arg)
{
    std::string systemCmd = "cmd /C " + cmd + " " + arg; // changing color
    system(systemCmd.c_str());
}
void run_cmd(std::string input)
{
    if (input.empty())
        return;

    size_t pos_space = input.find(' ');
    std::string cmd = (pos_space == std::string::npos) ? input : input.substr(0, pos_space);
    std::string arg = (pos_space == std::string::npos) ? "" : input.substr(pos_space + 1);

    if (cmd == "exit")
    {
        std::cout << "Bye-Bye!\n";
        exit(0);
    }
    else if (cmd == "hello")
    {
        std::cout << "Well hello there :)\n";
    }
    else if (cmd == "time")
    {
        systemcmd("time /t", "");
    }
    else if (cmd == "date")
    {
        systemcmd("date /t", "");
    }
    else if (cmd == "weather")
    {   if(arg.empty()){
        systemcmd("curl wttr.in?0/", "");
        }
        else{
        systemcmd(("curl wttr.in/"+arg), "");
        }
    }
    else if (cmd == "sys")
    {
        systemcmd("systeminfo", "");
    }
    else if (cmd == "exp")
    {
        if (!arg.empty())
        {
            systemcmd("explorer", arg);
        }
        else
        {
            systemcmd("explorer", ".");
        }
    }
    else if (cmd == "tasks")
    {
        systemcmd("tasklist", "");
    }
    else if (cmd == "kill")
    {
        if (!arg.empty())
        {
            systemcmd("taskkill /IM", (arg + " /F"));
        }
        else
            std::cout << "What process do I kill?\n";
    }
    else if (cmd == "g")
    {
        systemcmd("start", "https://www.google.com");
    }
        else if (cmd == "gh")
    {
        systemcmd("start", "https://github.com/");
    }
    else if (cmd == "donut")
    {
        char choice;
        std::cout << "You'll need to press Ctrl+C to stop & exit.\nProceed? (y/n) ";
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            systemcmd("curl ascii.live/donut", "");
        }
        else
            std::cout << "Donut cancelled.\n ";
    }
    else if (cmd == "intro")
    {
        intro();
    }
    else if (cmd == "help")
    {
        std::cout
            << "GUIDE: adrShell :\n"
            << "--------\n"
            << "Type hello          -->  Say hello\n"
            << "Type time           -->  Show the current time\n"
            << "Type date           -->  Show the current date\n"
            << "Type weather        -->  Display current Weather\n"
            << "Type weather <c>    -->  Display Weather in city \"c\" \n"
            << "Type sys            -->  Display system information\n"
            << "Type tasks          -->  Show all tasks (processes)\n"
            << "Type kill <p>       -->  Kill a process by name (e.g., kill notepad.exe)\n"
            << "Type g              -->  Open Google in your default browser\n"
            << "Type gh             -->  Open GitHub in your default browser\n"
            << "Type intro          -->  Show intro screen again!\n"
            << "Type donut          -->  See a donut animation!\n"
            << "Type exit           -->  Quit the shell\n"
            << "Type exp <d>        -->  Open directory <d> in File Explorer\n"
            << "\nYou can also use standard CMD commands directly.\n";
    }
    else if (cmd == "mkdir")
    {
        if (!_mkdir(arg.c_str()))
            std::cout << "New Directory " << arg << " created!\n";
        else
            std::cout << "Could not create directory.\n";
    }
    else if (cmd == "rmdir")
    {
        if (!_rmdir(arg.c_str()))
            std::cout << " Directory " << arg << " deleted!\n";
        else
            std::cout << "Could not delete directory.\n";
    }
    else if (cmd == "cd")
    {
        if (!_chdir(arg.c_str()))
            std::cout << "Changed directory to " << arg << "\n";
        else
            std::cout << "Invalid path.\n";
    }
    else
    {
        systemcmd(input, "");
    }
}

int main()
{
    // CONSOLE FUNCTIONs
    // Detach from parent console & open a new one
    FreeConsole();
    AllocConsole();

    SetConsoleTitle(TEXT("adrShell v1.0"));

    systemcmd("color 0a", "");
    intro();

    std::string input;
    while (true)
    {
        std::cout << ">>";
        std::getline(std::cin, input);
        run_cmd(input);
    }
}
