#ifndef PLOTSCENE_H
#define PLOTSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>

class PlotScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit PlotScene(QObject *parent = 0);
	~PlotScene();

	QRectF validArea();
	void addPoint(QGraphicsItem *item);
	void clearPoint();

private:
	void drawBackground(QPainter *painter, const QRectF &rect);
	void drawForeground(QPainter *painter, const QRectF &rect);

	QGraphicsItemGroup *points;
};

#endif // PLOTSCENE_H
