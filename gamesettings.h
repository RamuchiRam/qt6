#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QWidget>
#include <QLabel>
#include "gamefield.h"

namespace Ui {
    class GameSettings;
}

class GameSettings : public QWidget
{
    Q_OBJECT

public:
    explicit GameSettings(QWidget *parent = nullptr);
    ~GameSettings();

public slots:
    void start_pressed();
    void field_closed();
    void updateScore(QString);
    void status_changed(QString);

private:
    Ui::GameSettings *ui;

    GameField *m_field;
    void readSaveFile();
    void writeSaveFile();
};

#endif // GAMESETTINGS_H
