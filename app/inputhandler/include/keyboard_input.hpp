#ifndef KEYBOARD_INPUT_HPP_
#define KEYBOARD_INPUT_HPP_
#include "database.hpp"

class keyboardInput {
 public:
    int gasPedalPos = 0;
    bool running = true;
    //keyboardInput();
    //keyboardInput(database_type::Database &_db);  //  setting initial state of database?
    void keyReader(database_type::Database &_db);
    void switchCaseInput(database_type::Database &_db, const int &_in);
    void printState(database_type::Database &_db);
    std::string ignitionToString(database_type::Ignition &_e);
    std::string gearToString(database_type::Gear &_e);
    std::string driveModeToString(database_type::DriveMode &_e);
    void inputText();
    //keyboardInput(const keyboardInput&) = delete;
    ~keyboardInput();
 private:
};

#endif  //  KEYBOARD_INPUT_HPP_