#ifndef KEYBOARD_INPUT_HPP_
#define KEYBOARD_INPUT_HPP_

class keyboardInput{


public:
    int gasPedalPos = 0;
    
    keyboardInput(Database &_db); //setting initial state of database?
    void keyReader(Database &_db);
    void inputText();
    //~keyboardInput();
private:
};

#endif /* KEYBOARD_INPUT_HPP_ */