#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QColor>
#include "plotscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void resizeEvent(QResizeEvent *event);
	void showEvent(QShowEvent *event);
	void fitContent();
	void setColorButton(const QColor &color);

private slots:
	void on_btnDraw_clicked();
	void on_btnClean_clicked();

	void on_radiusSlider_sliderMoved(int position);

	void on_btnColor_clicked();

private:
	Ui::MainWindow *ui;
	QColor pointColor;
	PlotScene *scene;
	bool isGraphicsAdded;
};

#endif // MAINWINDOW_H
