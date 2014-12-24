#include <QPainter>
#include <QDebug>
#include "plotscene.h"

#define MIN_COORD_OF_PLOT (-500)
#define MAX_COORD_OF_PLOT (500)
#define PLOT_SIZE (MAX_COORD_OF_PLOT-MIN_COORD_OF_PLOT)

PlotScene::PlotScene(QObject *parent) : QGraphicsScene(parent), points(NULL)
{
}

PlotScene::~PlotScene()
{
	if (points) {
		delete points;
	}
}

QRectF PlotScene::validArea()
{
	return QRectF(MIN_COORD_OF_PLOT, MIN_COORD_OF_PLOT, PLOT_SIZE, PLOT_SIZE);
}

void PlotScene::addPoint(QGraphicsItem *item)
{
	if (points == NULL) {
		points = new QGraphicsItemGroup();
		this->addItem(this->points);
	}
	points->addToGroup(item);
}

void PlotScene::clearPoint()
{
	if (points != NULL) {
		delete points;
		points = NULL;
	}
}

void PlotScene::drawBackground(QPainter *painter, const QRectF &rect)
{
	Q_UNUSED(rect);
	const int gridInterval1 = 20;
	const int gridInterval2 = 100;
	const QPen gridLinePen1 = QPen(QColor("#DCDCDC"), 1);
	const QPen gridLinePen2 = QPen(QColor("#BCBCBC"), 1);

	painter->save();

	QRect windowRect = painter->transform().inverted().mapRect(painter->window());
	QPointF topLeft = windowRect.topLeft();
	QPointF bottomRight = windowRect.bottomRight();

	// Draw vertical grid lines.
	for (int gridX = int(topLeft.x() / gridInterval1) * gridInterval1; gridX < bottomRight.x(); gridX += gridInterval1) {
		painter->setPen((gridX % gridInterval2 != 0) ? gridLinePen1 : gridLinePen2);
		painter->drawLine(gridX, topLeft.y(), gridX, bottomRight.y());
	}

	// Draw horizontal grid lines.
	for (int gridY = int(topLeft.y() / gridInterval1) * gridInterval1; gridY < bottomRight.y(); gridY += gridInterval1) {
		painter->setPen((gridY % gridInterval2 != 0) ? gridLinePen1 : gridLinePen2);
		painter->drawLine(topLeft.x(), gridY, bottomRight.x(), gridY);
	}

	// Draw X/Y axis and boundary.
	painter->setPen(QPen(Qt::black, 1.5));
	painter->drawLine(MIN_COORD_OF_PLOT, 0, MAX_COORD_OF_PLOT, 0); // Draw X axis.
	painter->drawLine(0, MIN_COORD_OF_PLOT, 0, MAX_COORD_OF_PLOT); // Draw Y axis.
	painter->drawRect(MIN_COORD_OF_PLOT, MIN_COORD_OF_PLOT, PLOT_SIZE, PLOT_SIZE);

	painter->restore();
}

void PlotScene::drawForeground(QPainter *painter, const QRectF &rect)
{
	Q_UNUSED(rect);
	QPoint posAxisX = painter->transform().map(QPoint(500 - 20, 0));
	QPoint posAxisY = painter->transform().map(QPoint(0, -500 + 20));

	painter->save();
	painter->setTransform(QTransform()); // Use identify matrix.
	painter->setBrush(Qt::red);
	painter->setPen(Qt::red);

	painter->setFont(QFont("Arial", -1, QFont::Bold, false));
	painter->drawText(posAxisX, QString("X"));
	painter->drawText(posAxisY, QString("Y"));
	painter->restore();
}

