#include "gamedb.h"

GameDB::GameDB(TFile &fdatTFile) : fdat(fdatTFile), database(fdat.getFile(28))
{
    QDataStream dbStream(database);
    for (size_t i = 0; i < 320; i++)
    {

    }
}
