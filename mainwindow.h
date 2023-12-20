#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QLineEdit>
#include <QStack>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_LetsGoButton_clicked();

    void on_SetGoalButton_clicked();

    void on_TrackGoalButton_clicked();

    void on_ReturnButton1_clicked();

    void on_ReturnButton2_clicked();

    void on_ReturnButton3_clicked();



    void on_SubmitButton_clicked();

private:
    Ui::MainWindow *ui;
    QDate deadline;
    void onReturnButtonclicked();
};
#endif // MAINWINDOW_H
