#include "mainwindow.h"
#include "ui_mainwindow.h"

// All relevant header files used in the program
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QTime>
#include <QProgressBar>
#include <QVBoxLayout>

// Header files involved fetching strings fromm local text file
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextEdit>
#include <QFile>

#include <QDesktopServices>
#include <QUrl>
#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    loadMotivationalQuotes(); // Function to load the quotes
    srand(QTime::currentTime().msec()); // Function to generate random index (used to randomize rand() each time)
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Linking all the buttons to their relevant pages
void MainWindow::on_InfoButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_LetsGoButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_MotivationButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_SetGoalButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_TrackGoalButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_ChallengeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_CreditsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_TrackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}
// End of linking buttons


// Linking Return Buttons on the corner of each page to point to Correct Page Index
void MainWindow::onReturnButtonclicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_ReturnButton1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_ReturnButton2_clicked()
{
    onReturnButtonclicked();
}

void MainWindow::on_ReturnButton3_clicked()
{
    onReturnButtonclicked();
}

void MainWindow::on_ReturnButton4_clicked()
{
    onReturnButtonclicked();
}

void MainWindow::on_ReturnButton5_clicked()
{
    onReturnButtonclicked();
}

void MainWindow::on_ReturnButton6_clicked()
{
    onReturnButtonclicked();
}

void MainWindow::on_ReturnButton7_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_ReturnButton8_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
// End linking of return buttons


/* Following is the code relevant to the Set Goals Page, the user inputs the Goal and the Deadline for
    that Goal. Once both boxes are filled in the valid format, the deadline date is used to calculate the
    number of days and hours left and stores this value in a string.
    Finally the Goal and calculated time left is displayed on the Track Goals Page */
void MainWindow::on_SubmitButton_clicked()
{
    // Get the text from the line edit boxes
    QString enteredGoal = ui->EnterGoalBox->text();
    QString enteredDeadline = ui->EnterDeadlineBox->text();

    // Check if both boxes are filled
    if (enteredGoal.isEmpty() || enteredDeadline.isEmpty()) {
        QMessageBox::warning(this, "Incomplete Fields", "Please fill in both the goal and deadline boxes.");
        return;
    }

    // Convert the entered deadline to QDate
    QDateTime deadline = QDateTime::fromString(enteredDeadline, "MM/dd/yyyy");

    // Check if the entered date is valid, display prompt if it is invalid
    if (!deadline.isValid())
    {
        QMessageBox::warning(this, "Invalid Format", "Please enter a valid date in the format MM/dd/yyyy");
        return;
    }
    QMessageBox::information(this, "Submitted", "Submitted Successfully!");

    // Calculate the remaining days and hours
    QDateTime currentDateTime = QDateTime::currentDateTime();
    qint64 secondsRemaining = currentDateTime.secsTo(deadline);
    qint64 daysLeft = secondsRemaining / (60 * 60 * 24);
    qint64 hoursLeft = (secondsRemaining % (60 * 60 * 24)) / (60 * 60);

    // Display the remaining days for the entered goal
    QString result = QString("%1 days %2 hours").arg(daysLeft).arg(hoursLeft);

    // Add the text to the corresponding lists
    ui->GoalsList->addItem(enteredGoal);
    ui->DeadlineList->addItem(result);

    // Clear the line edit boxes for user to enter more goals
    ui->EnterGoalBox->clear();
    ui->EnterDeadlineBox->clear();
}



// Function that loads the quotes from a predefined local text file containing quotes.
void MainWindow::loadMotivationalQuotes()
{
    // Linking the path of the file
    QFile file("C:/Users/legen/OneDrive/Desktop/Project Motimate/Motimate/MotivationQuotes35.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            motivationalQuotes.append(line); // Fetches quotes line by line
        }
        file.close();
    }
    else
    {
        qDebug() << "Failed to open motivational_quotes.txt";
    }
}



// With every click, a random quote is displayed on the screen
void MainWindow::on_quoteButton_clicked()
{
    displayRandomQuote();
}



// Function that changes index of quotes in order to display different quotes everytime
void MainWindow::displayRandomQuote()
{
    // Checks if there are quotes available
    if (!motivationalQuotes.isEmpty())
    {
        // Get a random index to pick a quote
        int randomIndex = rand() % motivationalQuotes.size();

        // Get the quote as a string from the list based on the random index
        QString randomQuote = motivationalQuotes[randomIndex];

        // Display the quote in the QTextEdit
        ui->quoteDisplay->setText(randomQuote);
    }
    else
    {
        // If no more quotes, display a message
        ui->quoteDisplay->setText("No more quotes available.");
    }
}



/* The following code is relevant to the Challenge feature, the names of two players are entered,
    the challenge is entered, the amount relevant to the challenge is entered as well as the prize the
    winner will get, all this data is saved and displayed in the Track Challenges page where two progress bars
    are located, one for each user, and can be incremented by pressing the button next to them, as a way to track
    the goal. The player to finish first, wins.  */
void MainWindow::on_ConfirmButton_clicked()
{
    // Taking the required inputs from the user in the relevant boxes
    QString player1Name = ui->Player1Box->text();
    QString player2Name = ui->Player2Box->text();
    QString goal = ui->GoalBox->text();
    QString amount = ui->AmountBox->text();
    QString prize = ui->PrizeBox->text();

    // Displaying the data taken from the user on the other page
    ui->P1Label->setText(player1Name);
    ui->P2Label->setText(player2Name);
    ui->GoalDisplay->setText(goal);
    ui->GoalDisplay->setAlignment(Qt::AlignCenter);

    // Check if any field is empty and prompt the user to fill it if field is empty
    if (player1Name.isEmpty() || player2Name.isEmpty() || goal.isEmpty() || amount.isEmpty() || prize.isEmpty())
    {
        QMessageBox::warning(this, "Incomplete Fields", "Please fill in all the fields.");
        return;
    }

    // Set maximum limit of Progress Bar by taking Amount value from user
    int maxAmount = amount.toInt();
    ui->P1Progress->setMaximum(maxAmount);
    ui->P2Progress->setMaximum(maxAmount);

    // Display a dialog box indicating successful challenge creation
    QMessageBox::information(this, "Challenge Created", "Challenge successfully created!");

    // Clear the boxes
    ui->GoalBox->clear();
    ui->AmountBox->clear();
    ui->PrizeBox->clear();
}



// Function to update Progress Bar on the Track Challenge Page
void MainWindow::updateProgressBar(QProgressBar* progressBar, const QString& playerName)
{
    // Increment the progress bar value by 1 everytime the button next to it pressed
    progressBar->setValue(progressBar->value() + 1);

    // Check if the progress bar reached its maximum value
    if (progressBar->value() >= progressBar->maximum())
    {

        // Display winner name if the corresponding progress bar is full
        QMessageBox::information(this, "Goal Achieved", playerName+" has won");

        //Reset Progress Bars
        ui->P1Progress->setValue(0);
        ui->P2Progress->setValue(0);

    }
}



// Button that increments Player1 progress bar by 1 when pressed
void MainWindow::on_P1plus_clicked()
{
    updateProgressBar(ui->P1Progress, ui->Player1Box->text());
}

// Button that increments Player2 progress bar by 1 when pressed
void MainWindow::on_P2plus_clicked()
{
    updateProgressBar(ui->P2Progress, ui->Player2Box->text());
}



// Button that takes you to a Personal AI Coach
void MainWindow::on_CoachButton_clicked()
{
    bool opened = QDesktopServices::openUrl(QUrl("https://chat.openai.com/c/5cb9e672-567c-4793-a024-8e43c70666f5"));
}

