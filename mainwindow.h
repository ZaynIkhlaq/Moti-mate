#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit> // Used for text editing in Qt
#include <QProgressBar> // Used for Progress Bar Widget
#include <QVBoxLayout>



QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// All the functions used in main.cpp
private slots:

    void on_LetsGoButton_clicked();
    void on_SetGoalButton_clicked();
    void on_TrackGoalButton_clicked();
    void on_SubmitButton_clicked();
    void on_CreditsButton_clicked();
    void on_MotivationButton_clicked();
    void on_InfoButton_clicked();
    void on_ChallengeButton_clicked();

    // All the Return Buttons
    void on_ReturnButton1_clicked();
    void on_ReturnButton2_clicked();
    void on_ReturnButton3_clicked();
    void on_ReturnButton4_clicked();
    void on_ReturnButton5_clicked();
    void on_ReturnButton6_clicked();
    void on_ReturnButton7_clicked();
    void on_ReturnButton8_clicked();

    void on_quoteButton_clicked();
    void on_ConfirmButton_clicked();
    void on_TrackButton_clicked();
    void on_P1plus_clicked();
    void on_P2plus_clicked();
    void on_CoachButton_clicked();

private:

    Ui::MainWindow *ui;
    void onReturnButtonclicked();
    QTextEdit *quoteDisplay;
    QStringList motivationalQuotes;
    void loadMotivationalQuotes();
    void displayRandomQuote();
    void updateProgressBar(QProgressBar* progressBar, const QString& playerName);
};

#endif // MAINWINDOW_H
