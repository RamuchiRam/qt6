#include "gamefield.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QInputDialog>
#include <QDir>

GameField::GameField(int n, int m, QWidget *parent) :
    QWidget(parent), m_model(n, m)
{
    m_n = n, m_m = m;
    QGridLayout* layer = new QGridLayout(this);

    m_field.resize(m_n);
    for (int i = 0; i < m_n; ++i) {
        m_field[i].resize(m_m);
        for (int j = 0; j < m_m; ++j) {
            m_field[i][j] = new QPushButton(this);

            layer->addWidget(m_field[i][j], i, j);
            connect(m_field[i][j], SIGNAL(clicked()),
                    this, SLOT(button_pressed()));
        }
    }

    show_model();
}

void GameField::set_active(bool is_active){
    for (int i = 0; i < m_n; ++i) {
        for (int j = 0; j < m_m; ++j) {
            m_field[i][j]->setEnabled(is_active);
        }
    }
}

void GameField::changePlayer() {
    m_model.change_player();
}

void GameField::button_pressed() {
    QPushButton* sender_obj = qobject_cast<QPushButton*>(sender());
    int i = 0, j = 0;

    for (i = 0; i < m_n; ++i) {
        for (j = 0; j < m_m; ++j) {
           if (sender_obj == m_field[i][j])
               break;
        }
        if (j < m_m)
            break;
    }

    m_model.step(i, j);
    show_model();

    if (m_model.checkHLines(Cross) || m_model.checkVLines(Cross)) {
        emit status("выиграл X");
        set_active(false);
        winDialog();
    }
    if (m_model.checkHLines(Zero) || m_model.checkVLines(Zero)) {
        emit status("выиграл O");
        set_active(false);
        winDialog();
    }
    if (m_model.checkEven()) {
        emit status("Победила дружба");
        set_active(false);
        QMessageBox evenBox;
        evenBox.setText("Ничья");
        evenBox.exec();
        this->close();
    }
}

void GameField::closeEvent(QCloseEvent *event) {
    emit closed();
}

void GameField::show_model() {
    for (int i = 0; i < m_n; ++i) {
        for (int j = 0; j < m_m; ++j) {
            if (m_model.model[i][j] == Empty) {
                m_field[i][j]->setText("_");
            }
            else if (m_model.model[i][j] == Cross) {
                m_field[i][j]->setText("X");
            }
            else if (m_model.model[i][j] == Zero) {
                m_field[i][j]->setText("O");
            }
        }
    }

    if (m_model.player == Cross) {
        emit status("ход Х");
    }
    else if (m_model.player == Zero) {
        emit status("ход O");
    }
    else {
         emit status("игра не начата");
    }
}

void GameField::writeSaveFile(QString name){
    QFile file("D:\\stats.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(&file);
    QList< QStringList > lists;
    QString line;
    bool nameIsFounded = false;
    unsigned char nameIndex = 0;
    do {
        line = stream.readLine();
        lists << line.split("\t");
    } while (!line.isNull());
    for (int i = 0;i<lists.length();i++) {

        if(lists[i][0]==name){
         nameIsFounded = true;
         nameIndex = i;
         break;
        }
    }

    if(nameIsFounded){
        int score = lists[nameIndex][1].toInt();
        score+=1;
        lists[nameIndex][1]=QString::number(score);
    }
    else{
        stream << name << "\t" << "1" << "\n";
    }

    file.resize(0);
    for(int i = 0; i<lists.length()-1;i++)
    {
        stream << lists[i][0] << "\t" << lists[i][1] << "\n";
    }
    file.close();
}

void GameField::winDialog(){
    bool ok;
    QString text = QInputDialog::getText(this,
                                 QString::fromUtf8("Введите текст"),
                                 QString::fromUtf8("Ваш текст:"),
                                 QLineEdit::Normal,
                                 QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()){
        writeSaveFile(text);
    }
    this->close();
}
