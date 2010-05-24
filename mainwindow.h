#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QScrollArea;
class DesignWidget;
class PreviewWidget;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:    
    void createMenus();

    QWidget *centralWidget;

    //bigger area for designe (2d)
    QScrollArea *designArea;
    //smaller area for preview (3d)
    QScrollArea *previewArea;

    DesignWidget *designWidget;
    PreviewWidget *previewWidget;

    QTextEdit * reportWidget;
    QMenu *fileMenu;
    QMenu *helpMenu;

    void mousePressEvent(QMouseEvent *event);

};

#endif // MAINWINDOW_H
