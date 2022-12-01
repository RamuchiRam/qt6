#include <QApplication>
#include "gamefield.h"
#include "gamesettings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameSettings settingWidget;
    a.setStyleSheet(
                "* { background-color: rgba(176, 196, 222, 255); }"
                "QPushButton { "
                "  background-color: rgba(255, 153, 102, 200); "
                "  border-style: outset;"
                "  border-width: 2px;"
                "  border-radius: 10px;"
                "  border-color: beige;"
                "  font: bold 14px;"
                "  width: 3em;"
                "  padding: 6px;"
                "}"
                "QPushButton:hover {"
                  "background-color: rgba(255, 102, 0, 200);"
                "}"
                "QPushButton:pressed {"
                  "background-color: rgba(255, 0, 0, 200);"
                "}"
                "QPushButton:disabled {"
                  "background-color: rgba(204, 153, 102, 200);"
                "}"
                "QTextEdit {"
                  "background-color: rgba(102, 204, 102, 200);"
                  "  border-style: outset;"
                  "  border-width: 0px;"
                  "  border-radius: 10px;"
                  "  border-color: black;"
                  "  width: 3em;"
                  "  padding: 6px;"
                "}"
              );

    settingWidget.show();

    return a.exec();
}
