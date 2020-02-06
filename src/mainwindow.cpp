#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	

}

void MainWindow::resizeEvent(QResizeEvent * event) {

	ui->mazeGLWidget->update();
	QWidget::connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetClicked()));
	
}

void MainWindow::resetClicked() {
	ui->resetButton->setEnabled(false);
	int w = ui->widthEdit->text().toUInt();
	int h = ui->heightEdit_2->text().toUInt();
	ui->mazeGLWidget->reset(w, h);

	ui->resetButton->setEnabled(true);
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_actionExit_triggered()
{
	this->close();
}

void MainWindow::congratsMessage() {
	
	congrats = new QMessageBox(this);
	congrats->setText("Congrats! You've reached the destination.");
	congrats->setWindowTitle("Game Over");
	congrats->show();
	
}