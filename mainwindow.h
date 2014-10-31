#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QVector<QwtPlotCurve*> curveV;
    QwtPlot *seriesPlot;
    Ui::MainWindow *ui;
    void createCurve(QVector<double> x, QVector<double> y, QColor c, QString t);
private slots:
    void showItem(QVariant n, bool b);
};

#endif // MAINWINDOW_H
