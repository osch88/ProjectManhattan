#ifndef KEYBOARD_INPUT_HPP_
#define KEYBOARD_INPUT_HPP_
#include "database.hpp"

class keyboardInput {
public:
    bool keyReader(database_type::Database &_db);
private:
    bool keyReaderRunning = true;
    int gasPedalPos = 0;
    void switchCaseInput(database_type::Database &_db, const int &_in);
    void printState(database_type::Database &_db);
    void inputText();
};

#endif  //  KEYBOARD_INPUT_HPP_
