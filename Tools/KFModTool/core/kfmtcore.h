#ifndef KFMTCORE_H
#define KFMTCORE_H

#include "kfmtfile.h"

class KFMTCore
{
public:
    // The King's Field values in both Game and VersionedGame use the Japanese numeration standard.

    /*!
     * \brief Enum that defines which game is currently loaded without version information.
     * This enum should be used when a simple, non-version dependent game identification is desired.
     */
    enum class SimpleGame
    {
        None, ///< No game loaded.
        AC,   ///< Armored Core
        KF1,  ///< King's Field I
        KF2,  ///< King's Field II
        KF3,  ///< King's Field III
        KFPS, ///< King's Field III: Pilot Style
        ST    /// Shadow Tower
    };

    /*!
     * \brief Retrieves the current game with no version info.
     * \return A value from the KFMTCore::Game enum.
     * This function uses a switch case statement to transform the complex VersionedGame info that
     * KFMTCore stores into the simpler Game enum for checks which don't rely on version-specific
     * details.
     */
    SimpleGame currentGame() const;

    /*!
     * \brief Enum that defines which game is currently loaded, including the specific version.
     */
    enum class VersionedGame
    {
        None,      ///< No game loaded.
        ACU,       ///< Armored Core (USA) [SCUS-94182, SLUS-01323]
        ACDemo,    ///< Armored Core Demo from Interactive CD Sampler Volume 4 [SCUS-94418]
        ACProto,   ///< Armored Core "Preview Only 7-3-97" Prototype
        KF,        ///< King's Field I (Japan) [SLPS 00017, SLPS 03578]
        KFDemo,    ///< King's Field I Demo from DemoDemo PlayStation Soukan-gou Vol. 1 [PCPX 96003]
        KF2E,      ///< King's Field II (Europe) [SCES-00510]
        KF2Jv1_0,  ///< King's Field II (Japan) [SLPS-00069]
        KF2Jv1_7,  ///< King's Field II (Japan) (PSOne Classics) [NPJJ-00083]
        KF2Jv1_8A, ///< King's Field II (Japan) [SLPS-91003]
        KF2Jv1_8B, ///< King's Field II (Japan) [SLPS-03579, SLPS-91003, SLPS-91423]
        KF2U,      ///< King's Field (II) (USA) [SLUS-00158]
        KF3Jv1_3,  ///< King's Field III (Japan) [SLPS-00377]
        KF3Jv1_4,  ///< King's Field III (Japan) [SLPS-03580, SLPS-91089]
        KF3U,      ///< King's Field II (III) (USA) [SLUS-00255]
        KFPS,      ///< King's Field III: Pilot Style (Japan) [SLPM-80029]
        ST,        ///< Shadow Tower (FIXME: No version handling yet) [SLPS-01420, SLUS-00863]
        STDemo     ///< Shadow Tower Demo from PlayStation Underground v2.4 [SCUS-94298]
    };

    inline VersionedGame currentVersionedGame() const { return curGame; }
    /*!
     * \brief Retrieves a file from the core.
     * \param fileName File name.
     * \param subFile Sub file index (if the file name refers to a container)
     * \return Pointer to requested file or null if file not found.
     */
    KFMTFile* getFile(const QString& fileName, std::optional<size_t> subFile = -1);
    QDir getSrcDir() const { return curSourceDirectory; }

    void loadFrom(const QDir& srcDir);
    void saveTo(const QDir& outDir);

private:
    void detectGame(const QDir& srcDir);
    void loadMIX(QString path);
    void loadRaw(QString path);
    void loadT(QString path);

    VersionedGame curGame = VersionedGame::None;
    QDir curSourceDirectory;
    std::vector<KFMTFile> files;

    // FileListModel needs access to the files member.
    friend class FileListModel;
};

extern KFMTCore core;

#endif // KFMTCORE_H
