#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fdat28.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLoad_FDAT_28_triggered();

    void on_actionShow_Hide_Unknown_toggled(bool arg1);

    void on_spinLevel_valueChanged(int arg1);

    void on_comboMagic_currentIndexChanged(int index);

    void on_spinGOKIndex_valueChanged(int arg1);

    void on_comboWeapon_currentIndexChanged(int index);

private:
    void displayGOKData(const KingsField80175914OddStruct &gokData);
    void displayLevelData(const KingsFieldPlayerLvlData &levelData);
    void displayMagicData(const KingsFieldMagicStructure &magicData);
    void displayWeaponStats(const KingsFieldWeaponStats &weaponStats);

    FDAT28 fdat28;
    Ui::MainWindow *ui;
    const QStringList sillyTitles = {
        "Where can I turn when my fair weather friends cop out?",
        "If I only had a little pad...",
        "Hangin' down from my window, those are my wind chimes.",
        "Light the lamp and fire mellow, cabin essence timely hello.",
        "Who ran the iron horse?",
        "Canvas the town and brush the backdrop. Are you sleeping?",
        "Surf's Up aboard a tidal wave.",
        "We all live in a yellow submarine!",
        "Lovely Rita, meter maid!",
        "It's getting better all the time!",
        "Nothing is real and nothing to get hung about!",
        "Strawberry Fields Forever!",
        "Living is easy with eyes closed, misunderstanding all you see.",
        "Bang, bang, Maxwell's silver hammer came down upon her head!",
        "She came in through the bathroom window!",
        "My baby says she's trav'ling on the one after 909!",
        "Sit beside a mountain stream, see her waters rise.",
        "Swaying daisies sing a lazy song beneath the sun.",
        "Hey, Boy Blue is back!",
        "Des notes sans fin, des visages identiques.",
        "Minds blind, empty eyes, cracked smiles, black tongues ablaze.",
        "No names, breathe in dreams, standin' in line, cracked smiles.",
        "The places that I go don't feel good anymore.",
        "It makes me feel so sad to think what I might've had.",
        "The waves that crush upon the sand, another place on far-off land.",
        "Chuck Biscuits, they always caught him eating in the class!",
        "Dumb Larry, they always caught him smoking in the john!",
        "Piss Aaron, they always caught him pissing in the hall!",
        "Bring back the Boston rag!",
        "Do you throw out your gold teeth?",
        "Do you see how they roll?",
        "William and Mary won't do, now!",
        "Guadalajara won't do, now!",
        "I can see by what you carry that you come from Barrytown!",
        "Did you realize that you were a champion in their eyes?",
        "Is there gas in the car?",
        "Yes there's gas in the car!",
        "I'm never gonna do it without the fez on!",
        "Don't make me do it without the fez on!",
        "They got a name for the winners in the world. I want a name when I lose.",
        "They call Alabama the Crimson Tide. Call me Deacon Blues.",
        "Local boys will spend a quarter just to shine the silver bowl!",
        "An independent station: WJAZ!",
        "Thanks for calling. I wait all night for calls like these."
    };
};
#endif // MAINWINDOW_H
