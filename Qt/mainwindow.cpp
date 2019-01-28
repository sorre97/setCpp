#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>

// returns each line of file inside a QStringList data structure
QStringList read_file(void)
{
    // opening file
    QFile file("./dataset/data.txt");
    QStringList list;

    try {
        file.open(QIODevice::ReadOnly);
    } catch (...) {
        std::cout << "Cannot Read" << std::endl;
    }

    // data stream for reading
    QTextStream in(&file);

    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(QString::compare(line, QString("<END>")))
        {
            list.append(line);
        }
    }

    file.close();

    return list;
}

// returns list of cities inside the file
QStringList comboBoxHandler(QStringList &list)
{
    QStringList cities;

    for (int i = 0; i < list.length(); i++) {
        QString city = list.at(i).split(" ")[0];
        if(cities.indexOf(city) == -1)
        {
            cities.append(city);
        }
    }

    return cities;
}

// updates table with content of current city
void MainWindow::updateTableContent(QString &city, QStringList &lines)
{
    int i = 0;
    QString prefix;

    // scanning to find city
    while(i < lines.length())
    {
        // extracting city from current line
        prefix = lines.at(i).split(" ")[0];
        if(QString::compare(prefix, city)) { std:: cout << city.toStdString() << " = "; break; }
        ++i;
    }

    // i is index of first occurrence
    // updating table until end of city occurrence
    while(i < lines.length() && !QString::compare(prefix, city))
    {
        ui->uitable->insertRow(1);
        ++i;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //pasring file data.txt
    QStringList lines = read_file();

    // finding cities inside file
    QStringList cities = comboBoxHandler(lines);

    // adding cities to combobox
    ui->uicities->addItems(cities);

    // constructing table at first time
    QString currentCity = ui->uicities->currentText();
    updateTableContent(currentCity, lines);

    //ui -> navigationBar -> addStretch();
    //ui -> saveLoadBar-> addStretch();
    //setFixedHeight(sizeHint().height());
    //setFixedWidth(sizeHint().width());

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_uicities_activated(const QString &arg)
{
    std::cout << arg.toStdString() << std::endl;
}
