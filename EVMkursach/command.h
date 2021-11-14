#ifndef UNTITLED1_COMMAND_H
#define UNTITLED1_COMMAND_H

#include <vector>
#include <ostream>

using namespace std;

class Command {
private:

    vector<int> mas;
    int masStart;
    int masEnd;

public:

    const int MAS_SPACE = 0;
    const int MAS_OPCODE = 1;
    const int MAS_REGISTER = 2;
    const int MAS_MEMORY = 3;
    const int MAS_CLOACKING = 4;
    const int MAS_DECODING = 5;

    Command();

    Command(int masStart);

    friend ostream& operator<<(ostream& os, Command& command);
    bool haveStep(int index);
    void setEmptySteps(int index);
    void setStartEnd();
    void setupCommand(int index, vector<Command> cmds);
    void setupNormalCommand(vector<Command>& cmds, int regOrMem1, int regOrMem2, int commandType);
    void setupFirstCommand(int regOrMem1, int regOrMem2, int commandType);
    void setMemoryClocks(vector<Command>& cmds);
    int getMasStart() const;
    void setMasStart(int masStart);
    int getMasEnd() const;
    void setMasEnd(int masEnd);
    vector<int>& getMas();
    void addOne(int operand);
    void addMultiple(int count, int operand);
    void setMas(const vector<int>& mas);
};


#endif //UNTITLED1_COMMAND_H

