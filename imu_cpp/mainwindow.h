#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <qmainwindow.h>
#include <qapplication.h>
#include <qwidget.h>
#include <qtoolbar.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qaction.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qfiledialog.h>

#include <qgraphicsview.h>
#include <qtimer.h>
#include "ViewerGrafico.h"

#include "attitude_estimator.h"

using namespace stateestimation;


class MainWindowVA : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowVA(QWidget *parent = 0);
    ~MainWindowVA();

    bool Init();

	// creazione di layout, actions, menu, toolbar
	bool CreateLayout();	
	bool CreateActions();
	bool CreateMenu();
	bool CreateToolbar();


private slots:
    
	bool Quit();

	bool Process();


protected:
	

	CViewerGrafico *_pviewer;

	// actions
	QAction * _pactLoad; // load image
	QAction * _pactSave; // save image
	QAction * _pactProcess;  // process image
	QAction * _pactQuit; // quit

	QTimer _timer;

	AttitudeEstimator _Estimator;


};

#endif // MAINWINDOW_H
