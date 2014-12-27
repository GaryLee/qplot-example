qplot-example
=============

An example to show you how to use Qt's Graphics View framework to implement a
plot-like application.

![Screenshot](doc/qplot-screenshot.png "Screenshot 01")


This example show you
---------------------

- How to use QGraphicsScene to draw background and foreground.
- How to group items.
- How to resize scene acoording to main window size.
- How to fit view to the items in scene.
- How to pan graphics view.
- How to support multi-level zoom in operation.
- How to draw text on foreground of scene and the text won't be scaled acoording
  to view's transformation.
  
> **NOTE** To do multi-level zoom in. Use left button to drag the rect you want 
> to zoom. After zoom in several times, click right button to zoom out one level.
> Use reset button reset the zoom level.
  
How to build it
---------------------
- Open src/qplot.pro by Qt Creator.
- Press build button.
- Run!

> **NOTE** this program is built with Qt 5.4. However, it should be compatible
> with Qt4 and Qt5.
