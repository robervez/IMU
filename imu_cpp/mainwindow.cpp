

#include "mainwindow.h"




/*
Note:

imagerd = cvLoadImage(FileOpName.toAscii().data());
QImage imageView = QImage((const unsigned char*)(imagerd-> imageData), imagerd->width,imagerd-> height,QImage::Format_RGB888).rgbSwapped(); 
ui->label->setPixmap(QPixmap::fromImage(imageView));

*/

MainWindowVA::MainWindowVA(QWidget *parent) :
    QMainWindow(parent)
{

	// Layout and Components
	CreateLayout();

	// Create Actions
	CreateActions();

	// Create Menu
	CreateMenu();

	// Create Toolbar
	CreateToolbar();

	


	// data init
	Init();



}



MainWindowVA::~MainWindowVA()
{
	// uccisione puntatori interni
	delete _pviewer;

}


bool MainWindowVA::Init()
{

	_timer.setInterval(5);
	_timer.start();
	connect(&_timer, SIGNAL(timeout()), this, SLOT(Process()));

	
	return true;
}


bool MainWindowVA::CreateLayout()
{
	
	// creazione del widget centrale
	QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget( centralWidget );

	// creazione del layout della finestra (diverso da quello standard)
	QVBoxLayout	*playout = new QVBoxLayout(centralWidget);
	
		
	
	// aggiunta delle due zone per immagini, bottoni eccetera

	// label - titolo
	QLabel* pLabel = new QLabel("IMU");
	pLabel->setStyleSheet("QLabel { font:Arial; font-size:10px; }");
	
	playout->addWidget(pLabel,0,0);
	// Impostazione di stili e proprietà mediante CSS, simile ad HTML
	pLabel->setStyleSheet("QLabel { background-color : white; color : blue; qproperty-alignment: AlignCenter; }");

	// immagine sorgente -> visualizzata all'interno di una label 
	_pviewer = new CViewerGrafico(this);
	

	// aggiungo a layout
	playout->addWidget(_pviewer, 1, 0);

	// dimensione finestra
	this->resize(800, 600);


	return true;

}




bool MainWindowVA::CreateActions(){
	// creo azioni 
    _pactQuit = new QAction("Quit", this);

	
	 // collego azioni -> slot
	connect(_pactQuit,SIGNAL(triggered()),this, SLOT(Quit()));

	return true; 
}

bool  MainWindowVA::CreateMenu(){

	// creo il menu
	QMenu * pmnuMainMenu;
	pmnuMainMenu = new QMenu("File", this);
    pmnuMainMenu->addAction(_pactQuit);
	
	// creo menu bar
	QMenuBar *menubar = new QMenuBar();
	menubar->addMenu(pmnuMainMenu);

	// aggiungo alla finestra corrente
	setMenuBar(menubar);

	return true; 
}
	

bool MainWindowVA::CreateToolbar(){

	QToolBar *mainToolBar =  addToolBar("MainToolbar");


	// definizione dello stile
	mainToolBar->setAutoFillBackground(true);
	mainToolBar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );

	return false;  // per ora non creata
}




bool MainWindowVA::Quit(){

	// todo: chiedere conferma

	this->close();
	return true;

}
	
	
bool MainWindowVA::Process(){

	
	_Estimator.update(23, 3, 5, 35, 7, 4, 3, 5, 0.7, 0.5);

	_pviewer->AddDataPoint(_Estimator.eulerPitch(), 0);
	_pviewer->AddDataPoint(_Estimator.eulerRoll(), 1);
	_pviewer->AddDataPoint(_Estimator.eulerYaw(), 2);
	

		return true;
		

}