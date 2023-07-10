#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QTimeEdit>
#include <QSplitter>
#include <QLineEdit>
#include <QSpinBox>
#include <QDebug>
#include <QTimer>

#include <iostream>
#include <fstream>
#include <filesystem>

#include "LayoutWidget.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTimeEdit *time_edit;
    QLineEdit *input_file_lineedit;
    QLineEdit *output_file_lineedit;
    QCheckBox *remove_checkbox;
    QComboBox *action_if_exists;
    QCheckBox *timer_checkbox;
    // 8-bit Mask
    QSpinBox *spinbox;
    std::ifstream fin;
    std::ofstream fout;
    QTimer timer;

    void convert(){
        std::string inputFile = input_file_lineedit->text().toStdString();
        std::string outputFile = output_file_lineedit->text().toStdString();
        auto pos = outputFile.rfind('.');
        std::string extension {outputFile.substr(pos)};

        if (action_if_exists->currentText() == "Increment filename"){
            int i {1};
            while (std::filesystem::exists(outputFile)){
                outputFile.erase(outputFile.begin() + pos, outputFile.end());
                outputFile.append("(" + std::to_string(i) + ")" + extension);
                ++i;
            }
        }

        fin.open(inputFile, std::fstream::binary);
        fout.open(outputFile, std::fstream::binary);

        if (!fin.is_open()){
            qDebug() << "File not opened!";
            return;
        }

        if (!fout.is_open()){
            qDebug() << "File not opened!";
            return;
        }

        char buf{};
        int val{spinbox->value()};
        while(!fin.eof()){
            fin.read(&buf, 1);
            buf ^= val;
            fout.write(&buf, 1);
        }

        if (remove_checkbox->isChecked()){
            fin.close();
            std::filesystem::remove(inputFile);
        }

        fin.close();
        fout.close();
    }

public slots:
    void browseInputFiles(){
        QString filename = QFileDialog::getOpenFileName(
            this, "Select file", QDir::currentPath(),
            input_file_lineedit->text());

        input_file_lineedit->setText(filename);
    }

    void browseOutputFiles(){
        QString filename = QFileDialog::getSaveFileName(
            this, "Select file", QDir::currentPath(), "",
            nullptr, QFileDialog::DontConfirmOverwrite);

        output_file_lineedit->setText(filename);
    }

    void startConvertion(){
        qDebug() << size();
        if (timer_checkbox->isChecked()){
            timer.setInterval(time_edit->time().hour()*60*60*1000 + time_edit->time().minute()*60*1000);
            connect(&timer, &QTimer::timeout, this, &MainWindow::convert);
            timer.start();
        }

        convert();
    }

    void timerCheckboxToggled(){
        time_edit->setDisabled(time_edit->isEnabled());
    }
};
#endif // MAINWINDOW_HPP
