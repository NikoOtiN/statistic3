#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <user_func.cpp>
#include <qwt_legend_label.h>
#include <qwt_plot_canvas.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    seriesPlot = new QwtPlot();
    seriesPlot->setTitle("График динамического ряда");
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setPalette(Qt::gray);
    seriesPlot->setCanvas(canvas);

    QwtLegend *legend = new QwtLegend();
    legend->setDefaultItemMode(QwtLegendData::Checkable);

    seriesPlot->insertLegend(legend);
    connect(legend,SIGNAL(checked(QVariant,bool,int)),this,SLOT(showItem(QVariant,bool)));
    QVector<double> normalV = createSample(50);
    createCurve(createX(50),normalV,Qt::black,"Исходны ДР");

    QVector<double> simpleV3 = simple_moving_averge_v3(3,normalV);
    createCurve(createX(simpleV3.size(),1),simpleV3,Qt::blue,"Простое скользящее среднее(n=3)");

    QVector<double> simpleV5 = simple_moving_averge_v3(5,normalV);
    createCurve(createX(simpleV5.size(),2),simpleV5,Qt::yellow,"Простое скользящее среднее(n=5)");

    QVector<double> weightV = weighted_moving_average(normalV);

    createCurve(createX(weightV.size(),2),weightV,Qt::red,"Взвешенное скользящее среднее(n=5)");
    setCentralWidget(seriesPlot);

    QwtPlotItemList items = seriesPlot->itemList(QwtPlotItem::Rtti_PlotCurve);
    for ( int i = 0; i < items.size(); i++ )
    {
            const QVariant itemInfo = seriesPlot->itemToInfo( items[i] );

            QwtLegendLabel *legendLabel =
                qobject_cast<QwtLegendLabel *>( legend->legendWidget( itemInfo ) );
            if ( legendLabel )
                legendLabel->setChecked( true );
    }

}

void MainWindow::createCurve(QVector<double> x, QVector<double> y, QColor c, QString t)
{
    curveV.push_back(new QwtPlotCurve());
    curveV.back()->setTitle(t);
    curveV.back()->setPen(c,2);
    curveV.back()->setSamples(x,y);
    curveV.back()->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curveV.back()->attach(seriesPlot);
}

void MainWindow::showItem(QVariant n, bool b)
{
    QwtPlotItem *item = seriesPlot->infoToItem(n);
    item->setVisible(b);
    qDebug() << b;
    seriesPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
