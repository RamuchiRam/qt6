// ЗАДАЧИ к лекции 6:
// 1) вместо Setting сделать меню с кнопками "играть" и "статистика" ++сделано
// 2) статистика считывается с файла ++окей, файлик прочитали, осталось научиться туда записывать
/*  --Cтруктура файла с сохранением--
Имя_игрока\tИмя_игрока          |Cross	Zero
Число_побед\tЧисло_поражений    |4  5
Число_побед\tЧисло_поражений    |5	4

*/
// 3) после победы запрашивать имя победителя и увеличивать счетчик в статистике --TO DO
// 4) после нажатия "играть" открывается поле 10 на 10 ++сделано
// 5) после окончания игры открывается окно меню ++я надеюсь это так работает, так что сделано
// 6) игра 5 в ряд -- неправильно считается количество Х/О на поле, по горизонтали в первом может засчитать два в ряд как победу
// по вертикали считается только 6 в ряд
// 7) попробовать написать хороший код --чо

#include "gamesettings.h"
#include "ui_gamesettings.h"
#include <QMessageBox>
#include "gamefield.h"
#include <QTextStream>
#include <QFile>

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
    m_field = nullptr;
    this->setVisible(true);
    ui->start->setEnabled(true);
}

void GameSettings::status_changed(QString status) {
    ui->game_status->setText(status);
}

void GameSettings::readSaveFile(){
    QFile infile("C:\\Users\\gd200\\Desktop\\GithubRepos\\qt6\\stats.txt");
    infile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&infile);
    QList< QStringList > lists;
    QString line;
    do {
        line = in.readLine();
        lists << line.split("\t");
    } while (!line.isNull());

    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setVerticalHeaderLabels(lists[0]);
    ui->tableWidget->setHorizontalHeaderLabels({"Победа", "Поражение"});

    for ( int row = 0; row < 2; ++row ) {
        for ( int column = 0; column < lists[row].size(); ++column ) {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem(lists[row+1][column]));
        }
    }
    infile.close();
}

void GameSettings::updateScore() {
    int winCross = ui->tableWidget->takeItem(0,0)->text().toInt();
    int winZero = ui->tableWidget->takeItem(1,0)->text().toInt();

}

void GameSettings::writeSaveFile(){
    QFile outfile("C:\\Users\\gd200\\Desktop\\GithubRepos\\qt6\\stats.txt");
    outfile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    outfile.resize(0);
    QTextStream out(&outfile);
    out << ui->tableWidget->takeVerticalHeaderItem(0)->text() << '\t'
        << ui->tableWidget->takeVerticalHeaderItem(1)->text() << '\n';
    for ( int row = 0; row < 2; ++row ) {
        for ( int column = 0; column < 2; ++column ) {
            out << ui->tableWidget->takeItem(row, column)->text() << '\t';
        }
        out << '\n';
    }
    outfile.close();
}
