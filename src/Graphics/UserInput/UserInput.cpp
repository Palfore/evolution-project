#include "UserInput.h"
#include "GFramework.h"
#include "Drawing/text.h"
#include "Audio.h"

#include "Drawing/shapes.h"

UserInput::UserInput() : inputString(""), functions({}) {
    //ctor
}

UserInput::~UserInput() {
    while (!functions.empty()) {
        delete functions.back().element;
        functions.pop_back();
    }
}

void UserInput::draw() const {
    for (const auto& f : functions) {
        f.draw();
    }
}

#include <iostream>
void UserInput::setToDefault() { // Functions that all gamemodes should have
    while (!functions.empty()) {
        delete functions.back().element;
        functions.pop_back();
    }

    functions.push_back(UserFunction(new UIchar(ESC), [](){NORMAL_EXIT();}));
    functions.push_back(UserFunction(new UIchar(TAB), [](){
        glutFullScreenToggle();
    }));
    functions.push_back(UserFunction(new UIchar(GLUT_KEY_F9), [](){
        saveScreenShot();
        puts("Saved ScreenShot");
    }));

    functions.push_back(UserFunction(new UIchar('0'), [](){
        LOG("Test debug message.", LogDegree::DEBUG, LogType::GENERAL);
    }));
    functions.push_back(UserFunction(new UIchar('9'), [](){
        LOG("Test fatal message.", LogDegree::FATAL, LogType::GENERAL);
    }));
    functions.push_back(UserFunction(new UIchar('8'), [](){
        LOG("Test warning message.", LogDegree::WARNING, LogType::GENERAL);
    }));

    /* Audio Test */
//    functions.push_back(UserFunction(new UIchar('.'), [](){
//        GFramework::get->audio->playSound("gunShot.wav");
//    }));

//    functions.push_back(UserFunction(new UIchar('+', 200), [](){
//        GFramework::get->audio->volumeUp(5);
//        puts("Volume Up");
//    }));
//    functions.push_back(UserFunction(new UIchar('-', 200), [](){
//        GFramework::get->audio->volumeDown(5);
//        puts("Volume Down");
//    }));
//    functions.push_back(UserFunction(new UIchar('*'), [](){
//        GFramework::get->audio->toggleMute();
//        puts("Volume Muted");
//    }));
}

bool UserInput::isInputStringSubmitted() {
    return inputString.back() == TERMINATING_CHAR;
}
void UserInput::submitInputString() {
    inputString += TERMINATING_CHAR;
}

void UserInput::drawUserString(double x, double y, bool xCenter, bool yCenter) {
    if (isInputStringSubmitted() && ((inputString.size() - 1) > 0)) {
        DrawString<Appearance::GRASS>(inputString.substr(0, inputString.size()-1), x, y, by_percentage(), xCenter, yCenter);
    }
}

