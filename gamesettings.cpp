// ЗАДАЧИ к лекции 6:
// 1) вместо Setting сделать меню с кнопками "играть" и "статистика" ++сделано
// 2) статистика считывается с файла ++окей, файлик прочитали, осталось научиться туда записывать
/*  --Cтруктура файла с сохранением--
Имя_игрока\tЧисло побед\n

*/
// 3) после победы запрашивать имя победителя и увеличивать счетчик в статистике ++есть
// 4) после нажатия "играть" открывается поле 10 на 10 ++сделано
// 5) после окончания игры открывается окно меню ++я надеюсь это так работает, так что сделано
// 6) игра 5 в ряд -- не работает проверка на не главных диагоналях
// 7) попробовать написать хороший код --чо

#include "gamesettings.h"
#include "ui_gamesettings.h"
#include <QMessageBox>
#include "gamefield.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>

GameSettings::GameSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameSettings) {
    ui->setupUi(this);

    connect(ui->start, SIGNAL(clicked()),
            this, SLOT(start_pressed()));

    m_field = nullptr;
    readSaveFile();
    ui->game_status->setText("игра не начата");
}

GameSettings::~GameSettings()
{
    delete ui;
}

void GameSettings::start_pressed() {
    if (m_field != nullptr)
        return;

    m_field = new GameField(10, 10);

    this->connect(m_field, SIGNAL(status(QString)),
                  SLOT(status_changed(QString)));

    connect(m_field, SIGNAL(closed()),
            this, SLOT(field_closed()));

    m_field->show();
    ui->game_status->setText("игра начата");
    ui->start->setEnabled(false);
    this->setVisible(false);
}

void GameSettings::field_closed() {
    readSaveFile();
    m_field = nullptr;
    this->setVisible(true);
    ui->start->setEnabled(true);
}

void GameSettings::status_changed(QString status) {
    ui->game_status->setText(status);
    if(!m_field)
        updateScore(status);
}

void GameSettings::updateScore(QString status) {
    if(status=="выиграл X"){
        int winCross = ui->tableWidget->takeItem(0,0)->text().toInt();
        winCross++;
        ui->tableWidget->setItem(0,0, new QTableWidgetItem(winCross));
        ui->tableWidget->setItem(1,1, new QTableWidgetItem(winCross));
    }
    else if (status == "выиграл O"){
        int winZero = ui->tableWidget->takeItem(1,0)->text().toInt();
        winZero++;
        ui->tableWidget->setItem(0,1, new QTableWidgetItem(winZero));
        ui->tableWidget->setItem(1, 0, new QTableWidgetItem(winZero));
    }
}

void GameSettings::readSaveFile(){
    QFile infile("D:\\stats.txt");

    if(!(infile.exists())){
        infile.open(QIODevice::ReadWrite | QIODevice::Text);
        infile.write("\n");
        infile.close();
        return;
    }
    else{
        infile.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream in(&infile);
        QList< QStringList > lists;
        QString line;
        do {
            line = in.readLine();
            lists << line.split("\t");
        } while (!line.isNull());

        ui->tableWidget->setRowCount(lists.length()-1);
        ui->tableWidget->setColumnCount(1);
        //ui->tableWidget->setVerticalHeaderLabels(lists[0]);
        QList<QString> names;
        for (int i = 0; i < lists.length(); i++)
        {
            names.insert(names.size(), lists[i][0]);
            qDebug()<<names;
            qDebug()<<lists[0];
        }
        ui->tableWidget->setVerticalHeaderLabels(names);
        ui->tableWidget->setHorizontalHeaderLabels({"Победа", "Поражение"});

        for ( int row = 0; row < lists.length()-1; ++row ) {
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(lists[row][1]));
        }
        infile.close();
    }
}
void GameSettings::writeSaveFile(){
    QFile outfile("D:\\statistics.txt");
    outfile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    outfile.resize(0);
    QTextStream out(&outfile);

    outfile.close();
}
