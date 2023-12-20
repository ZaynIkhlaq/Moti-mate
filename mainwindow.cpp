#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LetsGoButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->ReturnButton1->setVisible(true);
}



void MainWindow::on_SetGoalButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->ReturnButton1->setVisible(true);
}


void MainWindow::on_TrackGoalButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->ReturnButton1->setVisible(true);
}



void MainWindow::onReturnButtonclicked()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(currentIndex - 1);
}




void MainWindow::on_ReturnButton1_clicked()
{
    onReturnButtonclicked();
}



void MainWindow::on_ReturnButton2_clicked()
{
    onReturnButtonclicked();
}



void MainWindow::on_ReturnButton3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}




void MainWindow::on_SubmitButton_clicked()
{
    // Get the text from the line edit boxes
    QString EnteredGoal = ui->EnterGoalBox->text();  // Trim to remove leading/trailing whitespaces
    QString EnteredDeadline = ui->EnterDeadlineBox->text();
    // Convert the entered deadline to QDate
    deadline = QDate::fromString(EnteredDeadline, "dd-MM-yyyy");
    // Check if the entered date is valid
    if (!deadline.isValid()) {
        QMessageBox::warning(this, "Invalid Date", "Please enter a valid date in the format dd-MM-yyyy.");
        return;
    }

    // Calculate the number of days left
    QDate currentDate = QDate::currentDate();
    int daysLeft = currentDate.daysTo(deadline);

    QString Result = QString("Days left: %1").arg(daysLeft);


    // Check if both boxes are filled
    if (EnteredGoal.isEmpty() || EnteredDeadline.isEmpty()) {
        QMessageBox::warning(this, "Incomplete Fields", "Please fill in both the goal and deadline boxes.");
        return;
    }

    // Add the text to the corresponding lists
    ui->GoalsList->addItem(EnteredGoal);
    ui->DeadlineList->addItem(Result);
    // Clear the line edit boxes
    ui->EnterGoalBox->clear();
    ui->EnterDeadlineBox->clear();
}

