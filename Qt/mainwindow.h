#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_uicities_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void updateTableContent(const QString &city, const QStringList &lines);
};

#endif // MAINWINDOW_H
