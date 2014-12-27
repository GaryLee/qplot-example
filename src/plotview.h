#ifndef PLOTVIEW_H
#define PLOTVIEW_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QRubberBand>
#include <QStack>
#include <QRectF>
#include <QGraphicsView>

class PlotView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit PlotView(QWidget *parent = 0);
	~PlotView();

	enum PlotDragMode {
		PanMode = 0,
		ZoomMode = 1
	};

	void setPlotDragMode(PlotDragMode mode);

public slots:
	void fitInContent();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private:
	PlotDragMode _plotDragMode;
	QRubberBand *_rubberBand;
	QPoint _rubberBandOrigin;
	bool _isLastZoomValid;
	QRectF _lastZoomRect;
	QStack<QRectF> _zoomLevels;

};

#endif // PLOTVIEW_H
