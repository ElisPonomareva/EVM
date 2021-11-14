#include <iostream>
#include "Command.h"
#include "functions.h"
#include "constants.h"

const int FIRST_COMMAND_INDEX = 0;

using namespace std;

vector<int>& Command::getMas() {
    return mas;
}

void Command::setMas(const vector<int>& mas) {
    Command::mas = mas;
}

int Command::getMasStart() const {
    return masStart;
}

void Command::setMasStart(int masStart) {
    Command::masStart = masStart;
}

int Command::getMasEnd() const {
    return masEnd;
}

void Command::setMasEnd(int masEnd) {
    Command::masEnd = masEnd;
}

Command::Command() {}

Command::Command(int masStart) : masStart(masStart) {}

ostream& operator<<(ostream& os, Command& command) {
    unsigned long len = command.getMas().size();
    for (int i = 0; i < len; ++i) {
        if (command.getMas()[i] != 0) {
            os << command.getMas()[i];
        }
        else {
            os << "-";
        }
    }
    os << endl;
    return os;
}

void Command::setupCommand(int index, vector<Command> cmds) {
    this->setEmptySteps(index);
    this->getMas().push_back(MAS_OPCODE);
    this->getMas().push_back(MAS_DECODING);
    int regOrMem1 = Random(getChangePercent(registerChange));
    int regOrMem2 = Random(getChangePercent(registerChange));
    int commandType = Random(getChangePercent(typeChance));
    if (index == FIRST_COMMAND_INDEX) {
        this->setupFirstCommand(regOrMem1, regOrMem2, commandType);
    }
    else {
        this->setupNormalCommand(cmds, regOrMem1, regOrMem2, commandType);
    }
    if (commandType == TYPE_1) {
        this->addOne(MAS_CLOACKING);
    }
    else {
        this->addMultiple(typeAccess, MAS_CLOACKING);
    }
    if (regOrMem2 == TYPE_1) {
        this->addOne(MAS_REGISTER);
    }
    else {
        setMemoryClocks(cmds);
    }

    this->setStartEnd();
}

void Command::setMemoryClocks(vector<Command>& cmds) {
    int start = int(this->getMas().size());
    bool fl = true;
    int space = 0;
    while (fl) {
        bool finded = true;
        for (int i = 0; i < memAccess; i++) {
            for (Command cmd : cmds) {
                if (cmd.haveStep(start + i)) {
                    if (cmd.getMas()[start + i] == MAS_MEMORY) {
                        finded = false;
                    }
                }
            }
        }
        if (finded) {
            fl = false;
        }
        else {
            space++;
            start++;
        }
    }
    this->addMultiple(space, MAS_SPACE);
    this->addMultiple(memAccess, MAS_MEMORY);
}

void Command::setupNormalCommand(vector<Command>& cmds, int regOrMem1, int regOrMem2, int commandType) {
    // for 1st operand
    if (regOrMem1 == REGISTER_COMMAND) {
        this->addOne(MAS_REGISTER);
    }
    else {
        this->setMemoryClocks(cmds);
    }
    // for 2st operand
    if (regOrMem2 == REGISTER_COMMAND) {
        this->addOne(MAS_REGISTER);
    }
    else {
        this->setMemoryClocks(cmds);
    }
}

void Command::setupFirstCommand(int regOrMem1, int regOrMem2, int commandType) {
    if (regOrMem1 == REGISTER_COMMAND) {
        this->addOne(MAS_REGISTER);
    }
    else {
        this->addMultiple(memAccess, MAS_MEMORY);
    }
    if (regOrMem2 == REGISTER_COMMAND) {
        this->addOne(MAS_REGISTER);
    }
    else {
        this->addMultiple(memAccess, MAS_MEMORY);
    }
}

void Command::setEmptySteps(int index) {
    for (int i = 0; i < index; i++) {
        this->addOne(MAS_SPACE);
    }
}

void Command::addOne(int operand) {
    this->getMas().push_back(operand);
}

void Command::addMultiple(int count, int operand) {
    for (int i = 0; i < count; i++) {
        this->addOne(operand);
    }
}

void Command::setStartEnd() {
    this->masEnd = int(this->getMas().size()) - 1;
    int index = 0;
    for (int el : this->getMas()) {
        if (el != 0) {
            break;
        }
        index++;
    }
    this->masStart = index;
}

bool Command::haveStep(int index) {
    return (this->masStart <= index) && (this->masEnd >= index);
}
