#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <QDebug>
#include <QLabel>
#include <QLayout>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QDockWidget>
#include <QPushButton>

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
    QLabel *expectL;
    QLabel *varianceL;
    QLabel *sizeL;

    QDoubleSpinBox *expectSB;
    QDoubleSpinBox *varianceSB;
    QSpinBox *sizeSB;

    QVBoxLayout *mainL;
    QHBoxLayout *paramL;
    QGroupBox *groupBox;

    QPushButton *runCalcualte;

    QDockWidget *paramDockWidget;
    QVector<QwtPlotCurve*> curveV;
    QwtPlot *seriesPlot;
    QwtLegend *legend;

    Ui::MainWindow *ui;
    void createCurve(QVector<double> x, QVector<double> y, QColor c, QString t);
    void setLegendsTrue();
private slots:
    void calculate();
    void showItem(QVariant n, bool b);
};

#endif // MAINWINDOW_H
