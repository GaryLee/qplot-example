#include <QDebug>
#include <QGraphicsItem>
#include <QPalette>
#include <QColorDialog>
#include <QResizeEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#define NUM_OF_POINT (100)

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	this->isGraphicsAdded = false;
	ui->setupUi(this);
	this->scene = new PlotScene(this);
	ui->graphicsView->setScene(this->scene);
	ui->radiusLabel->setText(QString("Radius(%1)").arg(ui->radiusSlider->value()));
	this->pointColor = QColor(Qt::red);
	this->setColorButton(this->pointColor);

	qDebug() << "Main window inited." << endl;
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	if (ui->chkBoxAutoResize->isChecked()) {
		ui->graphicsView->fitInContent();
	}
	QMainWindow::resizeEvent(event);
	this->statusBar()->showMessage(
				QString("window size: (%1, %2); view size: (%3, %4)")
				.arg(event->size().width())
				.arg(event->size().height())
				.arg(ui->graphicsView->size().width())
				.arg(ui->graphicsView->size().height())
				);
}

void MainWindow::showEvent(QShowEvent *event)
{
	if (!this->isGraphicsAdded) {
		const double margin = 10.0;
		ui->graphicsView->fitInView(this->scene->validArea().adjusted(-margin, -margin, margin, margin), Qt::KeepAspectRatio);
		this->isGraphicsAdded = true;
		ui->btnDraw->click();
	}
	QMainWindow::showEvent(event);
}


void MainWindow::setColorButton(const QColor &color)
{
	QPalette pal = ui->btnColor->palette();
	pal.setColor(QPalette::Button, color);
	pal.setColor(QPalette::Background, Qt::black);
	ui->btnColor->setAutoFillBackground(true);
	ui->btnColor->setPalette(pal);
	ui->btnColor->update();
}

void MainWindow::on_btnDraw_clicked()
{
	const int upperBound = this->scene->validArea().width();
	const int lowerBound = 0.0;
	double rad = double(ui->radiusSlider->value());
	QGraphicsEllipseItem *item;
	QPointF pt;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	qsrand(qrand());

	for (int i = 0; i < NUM_OF_POINT; ++i) {
		pt.setX(qrand() % ((upperBound + 1) - lowerBound) + lowerBound + this->scene->validArea().left());
		pt.setY(qrand() % ((upperBound + 1) - lowerBound) + lowerBound + this->scene->validArea().top());

		item = new QGraphicsEllipseItem(pt.x()-rad, pt.y()-rad, rad*2.0, rad*2.0);
		item->setPen(QPen(this->pointColor));
		item->setBrush(QBrush(this->pointColor));
		this->scene->addPoint(item);
	}
	QApplication::restoreOverrideCursor();
}

void MainWindow::on_btnClean_clicked()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	this->scene->clearPoint();
	QApplication::restoreOverrideCursor();
}

void MainWindow::on_radiusSlider_sliderMoved(int position)
{
	ui->radiusLabel->setText(QString("Radius(%1)").arg(position));
}

void MainWindow::on_btnColor_clicked()
{
	this->pointColor = QColorDialog::getColor(this->pointColor);
	this->setColorButton(this->pointColor);
}

void MainWindow::on_radioBtnZoom_clicked(bool checked)
{
	if (checked) {
		ui->graphicsView->setPlotDragMode(PlotView::ZoomMode);
		ui->chkBoxAutoResize->setChecked(false);
	}
}

void MainWindow::on_radioBtnPan_clicked(bool checked)
{
	if (checked) {
		ui->graphicsView->setPlotDragMode(PlotView::PanMode);
	}
}
