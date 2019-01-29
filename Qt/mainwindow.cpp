#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QVBoxLayout>
#include <QtCharts>
using namespace QtCharts;

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
QStringList comboBoxHandler(const QStringList &list)
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
void MainWindow::updateTableContent(const QString &city, const QStringList &lines)
{
    int i = 0;
    QString prefix;
    int start = 0;
    int end = 0;
    int row = 0;
    ui->uitable->setRowCount(row);

    // scanning to find city
    while(i < lines.length())
    {
        // extracting city from current line
        prefix = lines.at(i).split(" ")[0];
        if(prefix == city) { break; }
        ++i;
    }
    start = i;

    // i is index of first occurrence
    // updating table until end of city occurrence
    while(i < lines.length())
    {
        prefix = lines.at(i).split(" ")[0];
        if(prefix != city) { break; }

        ++i;
    }
    end = i;

    std::cout << start << std::endl;
    std::cout << end << std::endl;
    std::cout << end - start << std::endl;
    for(int i = start; i < end; i++)
    {
        QString age = lines.at(i).split(" ")[1];
        QString males = lines.at(i).split(" ")[2];
        QString females = lines.at(i).split(" ")[3];
        std::cout << "OK" << std::endl;

        ui->uitable->insertRow(row);
        ui->uitable->setItem(row, 0, new QTableWidgetItem(age));
        ui->uitable->setItem(row, 1, new QTableWidgetItem(males));
        ui->uitable->setItem(row, 2, new QTableWidgetItem(females));
        ++row;
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
    ui->uicity->setText(ui->uicities->currentText());

    QPieSeries * series = new QPieSeries();
    QPieSlice * slice  = new QPieSlice(QString("Prova"), 20);
    QPieSlice * slice2  = new QPieSlice(QString("Prova"), 80);
    series->append(slice);
    series->append(slice2);

    QChart * chart = new QChart();
    chart->addSeries(series);
    QChartView *chartView = new QChartView(chart);

    // Set layout in QWidget
    ui->charts_container->addWidget(chartView);

    // Set QWidget as the central layout of the main window
    //setCentralWidget(window);

    //ui -> navigationBar -> addStretch();
    //ui -> saveLoadBar-> addStretch();
    //setFixedHeight(sizeHint().height());
    //setFixedWidth(sizeHint().width());

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_uicities_activated(const QString &city)
{

    updateTableContent(city, read_file());
    ui->uicity->setText(ui->uicities->currentText());
}
