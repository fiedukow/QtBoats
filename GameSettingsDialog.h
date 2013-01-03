#ifndef GAMESETTINGSDIALOG_H
#define GAMESETTINGSDIALOG_H

#include <QDialog>

class QLineEdit;

class GameSettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GameSettingsDialog(const QString &currentPlayer1Name,
                                const QString &currentPlayer2Name,
                                QWidget *parent = 0);
    QString getPlayer1Name();
    QString getPlayer2Name();

signals:
    
public slots:

private:
    QLineEdit* player1NameEdit;
    QLineEdit* player2NameEdit;
};

#endif // GAMESETTINGSDIALOG_H
