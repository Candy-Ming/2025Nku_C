#include <QApplication>
#include <QStyleFactory>
#include "StartScreen.h"
#include "mazewidget.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    StartScreen startScreen;
    mazeWidget mazeGame;

    QObject::connect(&startScreen, &StartScreen::startGame, [&](int difficulty) {
        startScreen.hide();
        mazeGame.setDifficulty(difficulty);
        mazeGame.show();
    });

    startScreen.show();
    return a.exec();
}
