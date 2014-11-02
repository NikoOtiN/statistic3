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
    
    varianceL = new QLabel(tr("дисперсия"));
    expectL = new QLabel(tr("м.о."));
    sizeL = new QLabel(tr("Размер д.р."));

    varianceSB = new QDoubleSpinBox();
    varianceSB->setMinimum(0);
    varianceSB->setMaximum(1000);
    expectSB = new QDoubleSpinBox();
    expectSB->setMaximum(1000);
    expectSB->setMinimum(0);

    sizeSB = new QSpinBox();
    sizeSB->setMaximum(300);
    sizeSB->setMinimum(1);
    paramL = new QHBoxLayout();

    runCalcualte = new QPushButton(tr("Посчитать"));

    paramL->addWidget(expectL);
    paramL->addWidget(expectSB);
    paramL->addWidget(varianceL);
    paramL->addWidget(varianceSB);
    paramL->addWidget(sizeL);
    paramL->addWidget(sizeSB);
    paramL->addWidget(runCalcualte);
    groupBox = new QGroupBox();
    groupBox->setLayout(paramL);

    connect(runCalcualte,SIGNAL(clicked()),this,SLOT(calculate()));

    paramDockWidget = new QDockWidget("Ввод параметров");
    paramDockWidget->setWidget(groupBox);

    seriesPlot = new QwtPlot();
    seriesPlot->setTitle("График динамического ряда");
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setPalette(Qt::gray);
    seriesPlot->setCanvas(canvas);

    legend = new QwtLegend();
    legend->setDefaultItemMode(QwtLegendData::Checkable);

    seriesPlot->insertLegend(legend);
    connect(legend,SIGNAL(checked(QVariant,bool,int)),this,SLOT(showItem(QVariant,bool)));

    addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea,paramDockWidget);

    expectSB->setValue(5.0);
    varianceSB->setValue(2.0);
    sizeSB->setValue(50);
    emit calculate();
    setCentralWidget(seriesPlot);
    setMinimumSize(600,400);
}

void MainWindow::calculate()
{
    seriesPlot->detachItems();

    QVector<double> normalV = createSample(sizeSB->value(),expectSB->value(),varianceSB->value());
    createCurve(createX(normalV.size()),normalV,Qt::black,"Исходный ДР");
    QVector<double> simpleV3 = simple_moving_averge_v3(3,normalV);
    createCurve(createX(simpleV3.size(),1),simpleV3,Qt::blue,"Простое скользящее среднее(n=3)");
    QVector<double> simpleV5 = simple_moving_averge_v3(5,normalV);
    createCurve(createX(simpleV5.size(),2),simpleV5,Qt::yellow,"Простое скользящее среднее(n=5)");
    QVector<double> weightV = weighted_moving_average(normalV);
    createCurve(createX(weightV.size(),2),weightV,Qt::red,"Взвешенное скользящее среднее(n=5)");

    setLegendsTrue();
    seriesPlot->replot();
}

void MainWindow::setLegendsTrue()
{
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
    seriesPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
