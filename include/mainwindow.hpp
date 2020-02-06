#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QMessageBox * congrats;
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionExit_triggered();
	void resetClicked();
	void congratsMessage();

protected:
	void resizeEvent(QResizeEvent * event);

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
