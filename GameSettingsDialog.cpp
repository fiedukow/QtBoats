#include "GameSettingsDialog.h"
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

GameSettingsDialog::GameSettingsDialog(const QString& currentPlayer1Name,
                                       const QString& currentPlayer2Name,
                                       QWidget *parent)
   : QDialog(parent)
{
    QFormLayout* layout = new QFormLayout(this);
    setLayout(layout);
    player1NameEdit = new QLineEdit(currentPlayer1Name, this);
    player2NameEdit = new QLineEdit(currentPlayer2Name, this);
    layout->addRow("Player 1 name", player1NameEdit);
    layout->addRow("Player 2 name", player2NameEdit);
    QWidget* buttonFrame = new QWidget(this);
    QHBoxLayout* frameLay = new QHBoxLayout(buttonFrame);
    QPushButton* okButton = new QPushButton("Ok");
    QPushButton* cancelButton = new QPushButton("Cancel");
    frameLay->addWidget(okButton);
    frameLay->addWidget(cancelButton);
    connect(okButton, SIGNAL(released()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(released()), this, SLOT(reject()));
    layout->addRow(buttonFrame);
}

QString GameSettingsDialog::getPlayer1Name()
{
    return player1NameEdit->text();
}

QString GameSettingsDialog::getPlayer2Name()
{
    return player2NameEdit->text();
}
