#include <QDebug>
#include "plotview.h"

PlotView::PlotView(QWidget *parent) : QGraphicsView(parent), _rubberBand(NULL), _isLastZoomValid(false)
{
	setPlotDragMode(PlotView::PanMode);
}

PlotView::~PlotView()
{

}

void PlotView::setPlotDragMode(PlotView::PlotDragMode mode)
{
	_plotDragMode = mode;
	if (mode == PlotView::PanMode) {
		setDragMode(QGraphicsView::ScrollHandDrag);

	} else if (mode == PlotView::ZoomMode) {
		setDragMode(QGraphicsView::NoDrag);

	}
}

void PlotView::fitInContent()
{
	const double margin = 20.0;
	QRectF itemsBoundingRect = scene()->itemsBoundingRect().adjusted(-margin, -margin, margin, margin);
	fitInView(itemsBoundingRect, Qt::KeepAspectRatio);
	_zoomLevels.clear();
	_isLastZoomValid = false;
}

void PlotView::mousePressEvent(QMouseEvent *event)
{
	if (_rubberBand == NULL && _plotDragMode == PlotView::ZoomMode && event->button() == Qt::LeftButton) {
		_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
		QPalette palette;
		palette.setBrush(QPalette::Highlight, QBrush(Qt::red));
		_rubberBand->setPalette(palette);
		_rubberBandOrigin = event->pos();
		_rubberBand->setGeometry(_rubberBandOrigin.x(), _rubberBandOrigin.y(), 0, 0);
		_rubberBand->show();
	} else {
		QGraphicsView::mousePressEvent(event);
	}
}

void PlotView::mouseMoveEvent(QMouseEvent *event)
{
	if (_rubberBand != NULL) {
		QRect rect;
		rect.setCoords(
					qMin(_rubberBandOrigin.x(), event->pos().x()),
					qMin(_rubberBandOrigin.y(), event->pos().y()),
					qMax(_rubberBandOrigin.x(), event->pos().x()),
					qMax(_rubberBandOrigin.y(), event->pos().y())
					);
		_rubberBand->setGeometry(rect);
	} else {
		QGraphicsView::mouseMoveEvent(event);
	}
}

void PlotView::mouseReleaseEvent(QMouseEvent *event)
{
	if (_rubberBand) {
		_rubberBand->hide();
		QRect rect = _rubberBand->geometry().normalized();
		if (rect.width() > 0 && rect.height() > 0) {
			QRectF zoomRect(mapToScene(rect.topLeft()), mapToScene(rect.bottomRight()));
			fitInView(zoomRect, Qt::KeepAspectRatio);
			if (_isLastZoomValid) {
				_zoomLevels.push(_lastZoomRect);
			}
			_lastZoomRect = zoomRect;
			_isLastZoomValid = true;
		}

		delete _rubberBand;
		_rubberBand = NULL;

	} else if (event->button() == Qt::RightButton) {
		if (_zoomLevels.isEmpty()) {
			fitInContent();
			_isLastZoomValid = false;
		} else {
			fitInView(_zoomLevels.pop(), Qt::KeepAspectRatio);
		}
	} else {
		QGraphicsView::mouseReleaseEvent(event);
	}
}

