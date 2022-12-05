#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QPushButton>
#include <vector>
#include <QCloseEvent>
#include "gamemodel.h"

using namespace std;

class GameField : public QWidget
{
    Q_OBJECT
public:
    explicit GameField(int n, int m, QWidget *parent = nullptr);

signals:
    void closed();
    void status(QString);
public slots:
    void button_pressed();
    void closeEvent(QCloseEvent *event);

    void changePlayer();
    void show_model();

    void set_active(bool is_active);

private:
    vector<vector<QPushButton*>> m_field;
    void writeSaveFile(QString);
    void winDialog();
    GameModel m_model;
    int m_n, m_m;
};

#endif // GAMEFIELD_H
