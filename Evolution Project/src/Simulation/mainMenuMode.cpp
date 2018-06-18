#include "Simulation.h"
#include "Shapes.h"
#include "Objects.h"
#include "GFramework.h"
#include "Population.h"
#include <math.h>
#include "MyMath.h"
#include "Button.h"

static Population pop(200);

static void cinematicCamera();

static void draw() {
    const int r = 50;
    int bounds = 1000;
    for (int x = -bounds; x < bounds; x+=r) {
        for (int y = -bounds; y < bounds;y += r) {
           DrawPlane<Appearance::GRASS>(Vec(x, y, 0), r/2);
        }
    }

    DrawCylinder<Appearance::BARK>(Vec(-50, 50, 0), Vec(-50, 50, 50), 8);
    DrawSphere<Appearance::TREE_TOP>(Vec(-50, 50, 50), 25);
    DrawSkybox(500);
    pop.draw();

//    DrawRectangle<Appearance::LION>(0.6, 0.5, 1, 0.9);

    DrawRectangle<Appearance::PALFORE>(0, 0.875, 0.07, 1);
    DrawRectangle<Appearance::GAME_TITLE>(0.25, 0.05, 0.75, 0.2);
}

void Simulation::mainMenuMode() {
    pop.nextStep();
    draw();
    cinematicCamera();
}

#include "Audio.h"
#include <thread>
void Simulation::loadMainMenu() {
    std::vector<UserFunction> *userFunctions = &GFramework::get->userInput.functions;
    userFunctions->push_back(UserFunction(new UIchar(ENTER), [this](){
        this->setGameMode(GameMode::EVOLVE);
    }));
    userFunctions->push_back(UserFunction(new Button<Appearance::BUTTON>("Enter Simulation Mode", 0.1, 0.44, 0.3, 0.48, by_position()), [this](){
        GFramework::get->audio->playSound("click.wav");
        this->setGameMode(GameMode::EVOLVE);
    }));
    userFunctions->push_back(UserFunction(new Button<Appearance::BUTTON>("Exit", 0.1, 0.48, 0.3, 0.52, by_position()), [this](){
        GFramework::get->audio->playSound("click.wav");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        NORMAL_EXIT();
    }));
}


static void cinematicCamera() {
    static int step = 0;

    double SPEED = 10.0;
    double speed = SPEED * 1 / 2000.0;
    static double arr[3] = {0.5, 1.0, 1.5};

    double static theta = 0.0; // 0 - 2pi
    double static phi = 0.0;
    double static r = 200;

    double static thetaDot = 1.0 / 1000.0;
    double static phiDot = 1.0 / 1000.0;
    double static rDot = 1.0 / 1000.0;

    /* Change Speeds Randomly */
    if (randf(100) < (0.1)) {
        int shift = rand() % 3;
        arr[0] = arr[(shift + 0) % 3];
        arr[1] = arr[(shift + 1) % 3];
        arr[2] = arr[(shift + 2) % 3];
    }

    theta += 3*thetaDot * arr[0];
    phi += 3*phiDot * arr[1];
    r += 3*rDot * arr[2];

    if (phi > 3.14159/2.0) {
        phiDot = -fabs(phiDot);
        phi = 3.14159/2.0 - 0.001;
    } else if (phi < 0.1745) {
        phiDot = fabs(phiDot);
        phi = 0.1745 + 0.0001;
    }
    if (theta > 2*3.14159) {
        thetaDot = -fabs(thetaDot);
        theta = 2*3.14159 - 0.001;
    } else if (theta < 0) {
        thetaDot = fabs(thetaDot);
        theta = 0.001;
    }

    auto camera = GFramework::get->camera;
    /* Move and Look at New Position */
    camera->pos.x = r*cos(theta)*sin(phi);
    camera->pos.y = r*sin(theta)*sin(phi);
    camera->pos.z = r*cos(phi);

    camera->dir.x = -camera->pos.x + 50 * sinf(step * speed);
    camera->dir.y = -camera->pos.y + 50 * sinf(step * speed);
    camera->dir.z = -camera->pos.z + 50 * sinf(step * speed) + 20;
    step++;
}
