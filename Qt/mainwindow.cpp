#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QVBoxLayout>



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


    int totalMales = 0;
    int totalFemales = 0;

    QPieSeries * maleSeries = new QPieSeries();
    QPieSeries * femaleSeries = new QPieSeries();


    for(int i = start; i < end; i++)
    {
        QString age = lines.at(i).split(" ")[1];
        QString males = lines.at(i).split(" ")[2];
        QString females = lines.at(i).split(" ")[3];


        totalMales += males.toInt();
        totalFemales += females.toInt();

        QPieSlice * maleSlice  = new QPieSlice(age, males.toInt());
        maleSlice->setExploded(true);
        maleSlice->setBorderColor(QColor(Qt::black));
        maleSlice->setBorderWidth(0);
        QPieSlice * femaleSlice  = new QPieSlice(age, females.toInt());
        femaleSlice->setExploded(true);
        femaleSlice->setBorderColor(QColor(Qt::black));
        femaleSlice->setBorderWidth(0);


        maleSeries->append(maleSlice);
        femaleSeries->append(femaleSlice);

        ui->uitable->insertRow(row);
        ui->uitable->setItem(row, 0, new QTableWidgetItem(age));
        ui->uitable->setItem(row, 1, new QTableWidgetItem(males));
        ui->uitable->setItem(row, 2, new QTableWidgetItem(females));
        ++row;
    }

    maleChart->removeAllSeries();
    maleSeries->setHoleSize(0.35);
    maleSeries->setPieSize(0.85);
    maleSeries->setLabelsVisible();
    maleSeries->setLabelsPosition(QPieSlice::LabelInsideNormal);

    int colorOffset = 0;
    for(auto slice : maleSeries->slices()){
        slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));
        slice->setLabelColor(QColor(255, 255, 255, 255));
        slice->setColor(QColor(66, 134 + colorOffset, 244, 150 + colorOffset));
        colorOffset += 77 / maleSeries->slices().count();
    }
    maleChart->addSeries(maleSeries);

    femaleChart->removeAllSeries();
    femaleSeries->setHoleSize(0.35);
    femaleSeries->setPieSize(0.85);
    femaleSeries->setLabelsVisible();
    femaleSeries->setLabelsPosition(QPieSlice::LabelInsideNormal);

    colorOffset = 0;
    for(auto slice : femaleSeries->slices()){
        slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));
        slice->setLabelColor(QColor(255, 255, 255, 255));
        slice->setColor(QColor(244, 66, 155 + colorOffset, 50 + colorOffset));
        colorOffset += 86 / maleSeries->slices().count();
    }
    femaleChart->addSeries(femaleSeries);

    ui->uitable->insertRow(row);
    ui->uitable->setItem(row, 0, new QTableWidgetItem(QString("Totale")));
    ui->uitable->setItem(row, 1, new QTableWidgetItem(QString::number(totalMales)));
    ui->uitable->setItem(row, 2, new QTableWidgetItem(QString::number(totalFemales)));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //pasring file data.txt
    lines = read_file();

    // finding cities inside file
    QStringList cities = comboBoxHandler(lines);

    // adding cities to combobox
    ui->uicities->addItems(cities);

    // charts
    maleChart = new QChart();
    maleChart->legend()->setAlignment(Qt::AlignRight);
    maleChart->setTitleBrush(QBrush(Qt::black));
    maleChart->setTitle("Maschi");
    maleChart->setMargins(QMargins(3,3,3,3));


    femaleChart = new QChart();
    femaleChart->legend()->setAlignment(Qt::AlignRight);
    femaleChart->setTitleBrush(QBrush(Qt::black));
    femaleChart->setTitle("Femmine");
    femaleChart->setMargins(QMargins(3,3,3,3));

    QLinearGradient maleBackgroundGradient;
    maleBackgroundGradient.setStart(QPointF(0, 0));
    maleBackgroundGradient.setFinalStop(QPointF(1, 0));
    maleBackgroundGradient.setColorAt(0.0, QRgb(0xa1c4fd));
    maleBackgroundGradient.setColorAt(1.0, QRgb(0xc2e9fb));
    maleBackgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    QLinearGradient femaleBackgroundGradient;
    femaleBackgroundGradient.setStart(QPointF(0, 0));
    femaleBackgroundGradient.setFinalStop(QPointF(1, 0));
    femaleBackgroundGradient.setColorAt(0.0, QRgb(0xff867a));
    femaleBackgroundGradient.setColorAt(0.21, QRgb(0xff8c7f));
    femaleBackgroundGradient.setColorAt(0.52, QRgb(0xf99185));
    femaleBackgroundGradient.setColorAt(0.78, QRgb(0xcf556c));
    femaleBackgroundGradient.setColorAt(1.0, QRgb(0xb12a5b));
    femaleBackgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    maleChart->setBackgroundBrush(maleBackgroundGradient);
    femaleChart->setBackgroundBrush(femaleBackgroundGradient);

    QChartView * maleChartView = new QChartView(maleChart);
    QChartView * femaleChartView = new QChartView(femaleChart);


    ui->uitable->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    ui->uitable->setMinimumSize(330, 690);
    ui->uitable->setMaximumWidth(330);
    maleChartView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    maleChartView->setMinimumWidth(350);
    maleChartView->setMaximumWidth(370);
    femaleChartView->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    femaleChartView->setMinimumWidth(350);
    femaleChartView->setMaximumWidth(370);

    ui->charts->addWidget(maleChartView);
    ui->charts->addWidget(femaleChartView);

    // constructing table at first time
    QString currentCity = ui->uicities->currentText();
    updateTableContent(currentCity, lines);
    ui->uicity->setText(ui->uicities->currentText());


}


MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_uicities_activated(const QString &city)
{
    updateTableContent(city, lines);
    ui->uicity->setText(ui->uicities->currentText());
}
