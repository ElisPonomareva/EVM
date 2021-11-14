#include <iostream>

#include "Command.h"
#include "constants.h"
#include "functions.h"
#include <ctime>

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    input();

    vector<Command> commands;
    for (int i = 0; i < commandsCount; i++) {
        auto* cmd = new Command(i);
        cmd->setupCommand(i, commands);
        commands.push_back(*cmd);
    }

    int count = 0;
    for (Command cmd : commands) {
        cout << cmd;
        count += cmd.getMasEnd() - cmd.getMasStart();
    }
    cout << "Затраченное время на комманду: " << count / commandsCount << endl;
    return 0;
}




