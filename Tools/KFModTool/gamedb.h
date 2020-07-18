#ifndef GAMEDB_H
#define GAMEDB_H

#include "tfile.h"
#include "kftypes.h"

class GameDB
{
public:
    explicit GameDB(TFile &fdatTFile);

private:
    TFile &fdat;

    bool changed = false;
    QByteArray database;
    std::vector<KingsField::ObjectClassDeclaration> objClassDeclarations;
};

#endif // GAMEDB_H
