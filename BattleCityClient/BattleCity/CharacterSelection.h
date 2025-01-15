#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include <QDialog>
#include <QString>

class CharacterSelection : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterSelection(QWidget* parent = nullptr);

signals:
    void characterChosen(const QString& character);

private slots:
    void choosePoliceOfficer1();
    void choosePoliceOfficer2();
    void choosePoliceOfficer3();
    void choosePoliceOfficer4();
    void chooseZombieType1();
    void chooseZombieType2();
    void chooseZombieType3();
    void chooseZombieType4();

private:
    void setupUI();
};

#endif // CHARACTERSELECTION_H
