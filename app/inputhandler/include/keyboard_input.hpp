#ifndef KEYBOARD_INPUT_HPP_
#define KEYBOARD_INPUT_HPP_
#include "database.hpp"

class keyboardInput {
public:
    void keyReader(database_type::Database &_db);
private:
    int gasPedalPos = 0;
    bool running = true;
    void switchCaseInput(database_type::Database &_db, const int &_in);
    void printState(database_type::Database &_db);
    void inputText();
};

#endif  //  KEYBOARD_INPUT_HPP_
