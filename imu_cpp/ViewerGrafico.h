#pragma once

#include <QWidget>
#include "qcustomplot.h"

class CViewerGrafico : public QCustomPlot
{
	
	Q_OBJECT

public:
	CViewerGrafico(QWidget *parent=0) :QCustomPlot(parent){

		/*  versione per riempire aree
		addGraph();
		graph(0)->setPen(QPen(Qt::blue));
		graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
		graph(0)->setAntialiasedFill(false);
		
		
		addGraph(); // red line
		graph(1)->setPen(QPen(Qt::red));
		graph(0)->setChannelFillGraph(graph(1));
		*/

		addGraph(); // red line  (detection)
		graph(0)->setPen(QPen(Qt::red));
		graph(0)->setName("P");

		addGraph(); // green line  (tracking)
		graph(1)->setPen(QPen(Qt::green));
		graph(1)->setName("R");

		addGraph(); // green line  (tracking)
		graph(2)->setPen(QPen(Qt::blue));
		graph(2)->setName("Y");
		

		// visualizzo la legenda ed aumento la font di ogni item
		legend->setVisible(true);
		for (int i = 0; i < legend->itemCount(); ++i)
		{

			QFont tmpFont = legend->item(i)->font();
			tmpFont.setPointSize(12);
			legend->item(i)->setFont(tmpFont);
		}
		
		
		
		xAxis->setTickLabelType(QCPAxis::ltNumber);
		yAxis->setTickLabelType(QCPAxis::ltNumber);
		
		yAxis->setRange(0,10);
		yAxis->setAutoTickStep(0);
		yAxis->setTickStep(1);


		

		connect(xAxis, SIGNAL(rangeChanged(QCPRange)), xAxis2, SLOT(setRange(QCPRange)));
		connect(yAxis, SIGNAL(rangeChanged(QCPRange)), yAxis2, SLOT(setRange(QCPRange)));

		replot();

		_inumval = 0;
		_iWidth = 500;

		// 0 people at the beginning
		AddDataPoint(0);
	}


	public slots:

	void AddDataPoint(int val, int iGraph=0){


		// aggiungo dati
		graph(iGraph)->addData(_inumval++, val);

		xAxis->setRange(_inumval+0.25, _iWidth, Qt::AlignRight);

		graph(iGraph)->removeDataBefore(_inumval - _iWidth);
		replot();
	}


protected:

	// x axis counter
	int _inumval;
	// number of visible values
	int _iWidth;

	
};
	