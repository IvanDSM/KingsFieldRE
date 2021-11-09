#include "kfmtcore.h"
#include "kfmterror.h"
#include <QCryptographicHash>

// Declaring the global
KFMTCore core;

KFMTCore::SimpleGame KFMTCore::currentGame() const
{
    switch (curGame)
    {
        case VersionedGame::None: return SimpleGame::None;
        case VersionedGame::ACDemo: [[fallthrough]];
        case VersionedGame::ACProto: return SimpleGame::AC;
        case VersionedGame::KF: [[fallthrough]];
        case VersionedGame::KFDemo: return SimpleGame::KF1;
        case VersionedGame::KF2E: [[fallthrough]];
        case VersionedGame::KF2Jv1_0: [[fallthrough]];
        case VersionedGame::KF2Jv1_7: [[fallthrough]];
        case VersionedGame::KF2Jv1_8A: [[fallthrough]];
        case VersionedGame::KF2Jv1_8B: [[fallthrough]];
        case VersionedGame::KF2U: return SimpleGame::KF2;
        case VersionedGame::KF3Jv1_3: [[fallthrough]];
        case VersionedGame::KF3Jv1_4: [[fallthrough]];
        case VersionedGame::KF3U: return SimpleGame::KF3;
        case VersionedGame::KFPS: return SimpleGame::KFPS;
        case VersionedGame::ST: [[fallthrough]];
        case VersionedGame::STDemo: return SimpleGame::ST;
        default: KFMTError::fatalError(QStringLiteral("KFMTCore::currentGame: Unhandled game!"));
    }
}

KFMTFile* KFMTCore::getFile(const QString& fileName, std::optional<size_t> subFile)
{
    for (auto& f : files)
        if (f.filePath.endsWith(fileName)) return subFile ? f.getSubFile(subFile.value()) : &f;

    return nullptr;
}

void KFMTCore::loadFrom(const QDir& srcDir)
{
    detectGame(srcDir);
    files.clear();
    if (curGame != VersionedGame::None) curSourceDirectory = srcDir;
    switch (curGame)
    {
        case VersionedGame::None: return;
        case VersionedGame::ACDemo:
            loadT("COM/FDAT.T");
            loadT("COM/RTIM.T");
            loadT("MS/ARMS_T.T");
            loadT("MS/BST_T.T");
            loadT("MS/BWL_T.T");
            loadT("MS/BWR_T.T");
            loadT("MS/COMP_T.T");
            loadT("MS/CORE_T.T");
            loadT("MS/GENE_T.T");
            loadT("MS/HEAD_T.T");
            loadT("MS/LEG_T.T");
            loadT("MS/MENU_TIM.T");
            loadT("MS/MENU_TMD.T");
            loadT("MS/MENU_VAB.T");
            loadT("MS/MIS.T");
            loadT("MS/SPEC_T.T");
            loadT("MS/WEL_T.T");
            loadT("MS/WER_T.T");
            break;
        case VersionedGame::ACU: [[fallthrough]];
        case VersionedGame::ACProto:
            loadT("GG/COM/FDAT.T");
            loadT("GG/COM/RTIM.T");
            loadT("GG/MS/ARMS_T.T");
            loadT("GG/MS/BST_T.T");
            loadT("GG/MS/BWL_T.T");
            loadT("GG/MS/BWR_T.T");
            loadT("GG/MS/COMP_T.T");
            loadT("GG/MS/CORE_T.T");
            loadT("GG/MS/GENE_T.T");
            loadT("GG/MS/HEAD_T.T");
            loadT("GG/MS/LEG_T.T");
            loadT("GG/MS/MENU_TIM.T");
            loadT("GG/MS/MENU_TMD.T");
            loadT("GG/MS/MENU_VAB.T");
            loadT("GG/MS/MIS.T");
            loadT("GG/MS/SPEC_T.T");
            loadT("GG/MS/WEL_T.T");
            loadT("GG/MS/WER_T.T");
            break;
        case VersionedGame::KF:

            loadMIX("KF/B0/L0");
            loadMIX("KF/B0/MIX0");
            loadMIX("KF/B0/MIX3");
            loadMIX("KF/B0/MIX9");
            loadMIX("KF/B0/MIXB0");
            loadMIX("KF/B0/MIXB3");
            loadMIX("KF/B0/MIXBE");
            for (auto b = 1; b <= 5; b++)
            {
                if (b == 5)
                {
                    loadMIX("KF/B5/CHR1.MIM");
                    loadMIX("KF/B5/CHR2.MIM");
                    loadMIX("KF/B5/CHR3.MIM");
                }
                loadMIX(QStringLiteral("KF/B%1/MIX.TIM").arg(b));
                loadMIX(QStringLiteral("KF/B%1/MIXA.DAT").arg(b));
                loadMIX(QStringLiteral("KF/B%1/MIXB.DAT").arg(b));
            }
            loadMIX("KF/COM/MIX.TIM");
            // The following piece of code is confusing, so let me explain it.
            // The ENE folders go from ENE1 to ENE5. In both ENE1 and ENE2, there are files that go from
            // EI00 to EI09. However, the "ranges" of the other ENE folders are as follows:
            // ENE3: EI00 to EI06
            // ENE4: EI00 to EI07
            // ENE5: EI00 to EI08
            // Note that for all these cases, we can say that the maximum EI number obeys the rule of
            // maximumEiNum - eneNum = 3. Therefore, to avoid making multiple for statements for each ENE
            // folder or having a HUGE list of files, we can just stop loading files from each ENE
            // folder when eiNum - eneNum = 4.
            for (auto eneNum = 1; eneNum <= 5; eneNum++)
                for (auto eiNum = 0; (eneNum < 3 && eiNum <= 9) || eiNum - eneNum <= 3; eiNum++)
                    loadRaw(QStringLiteral("KF/ENE%1/EI0%2.TIM").arg(eneNum).arg(eiNum));
            loadRaw("KF/ITEM1/I001.TMD");
            loadRaw("KF/ITEM1/I002.TMD");
            loadRaw("KF/ITEM1/I003.TMD");
            loadRaw("KF/ITEM1/I004.TMD");
            loadRaw("KF/ITEM1/I005.TMD");
            loadRaw("KF/ITEM1/I006.TMD");
            loadRaw("KF/ITEM1/I007.TMD");
            loadRaw("KF/ITEM1/I008.TMD");
            loadRaw("KF/ITEM1/I009.TMD");
            loadRaw("KF/ITEM1/I010.TMD");
            loadRaw("KF/ITEM1/I011.TMD");
            loadRaw("KF/ITEM1/I012.TMD");
            loadRaw("KF/ITEM1/I014.TMD");
            loadRaw("KF/ITEM1/I015.TMD");
            loadRaw("KF/ITEM1/I016.TMD");
            loadRaw("KF/ITEM1/I017.TMD");
            loadRaw("KF/ITEM1/I018.TMD");
            loadRaw("KF/ITEM1/I020.TMD");
            loadRaw("KF/ITEM1/I021.TMD");
            loadRaw("KF/ITEM1/I022.TMD");
            loadRaw("KF/ITEM1/I023.TMD");
            loadRaw("KF/ITEM1/I024.TMD");
            loadRaw("KF/ITEM1/I025.TMD");
            loadRaw("KF/ITEM1/I027.TMD");
            loadRaw("KF/ITEM1/I028.TMD");
            loadRaw("KF/ITEM1/I029.TMD");
            loadRaw("KF/ITEM1/I030.TMD");
            loadRaw("KF/ITEM2/I031.TMD");
            loadRaw("KF/ITEM2/I033.TMD");
            loadRaw("KF/ITEM2/I034.TMD");
            loadRaw("KF/ITEM2/I035.TMD");
            loadRaw("KF/ITEM2/I036.TMD");
            loadRaw("KF/ITEM2/I037.TMD");
            loadRaw("KF/ITEM2/I038.TMD");
            loadRaw("KF/ITEM2/I039.TMD");
            loadRaw("KF/ITEM2/I040.TMD");
            loadRaw("KF/ITEM2/I041.TMD");
            loadRaw("KF/ITEM2/I042.TMD");
            loadRaw("KF/ITEM2/I043.TMD");
            loadRaw("KF/ITEM2/I044.TMD");
            loadRaw("KF/ITEM2/I045.TMD");
            loadRaw("KF/ITEM2/I046.TMD");
            loadRaw("KF/ITEM2/I047.TMD");
            loadRaw("KF/ITEM2/I048.TMD");
            loadRaw("KF/ITEM2/I049.TMD");
            loadRaw("KF/ITEM2/I050.TMD");
            loadRaw("KF/ITEM2/I051.TMD");
            loadRaw("KF/ITEM2/I052.TMD");
            loadRaw("KF/ITEM2/I053.TMD");
            loadRaw("KF/ITEM2/I054.TMD");
            loadRaw("KF/ITEM2/I055.TMD");
            loadRaw("KF/ITEM2/I056.TMD");
            loadRaw("KF/ITEM2/I057.TMD");
            loadRaw("KF/ITEM2/I058.TMD");
            loadRaw("KF/ITEM2/I059.TMD");
            loadRaw("KF/ITEM2/I060.TMD");
            loadRaw("KF/ITEM3/I061.TMD");
            loadRaw("KF/ITEM3/I062.TMD");
            loadRaw("KF/ITEM3/I063.TMD");
            loadRaw("KF/ITEM3/I064.TMD");
            loadRaw("KF/ITEM3/I065.TMD");
            loadRaw("KF/ITEM3/I069.TMD");
            loadRaw("KF/ITEM3/I070.TMD");
            loadRaw("KF/ITEM3/I074.TMD");
            loadRaw("KF/ITEM3/I075.TMD");
            loadRaw("KF/ITEM4/I106.TMD");
            loadRaw("KF/ITEM4/I110.TMD");
            loadRaw("KF/KAN/B1/K000.TIM");
            loadRaw("KF/KAN/B1/K001.TIM");
            loadRaw("KF/KAN/B1/K002.TIM");
            loadRaw("KF/KAN/B1/K003.TIM");
            loadRaw("KF/KAN/B1/K004.TIM");
            loadRaw("KF/KAN/B1/K005.TIM");
            loadRaw("KF/KAN/B1/K006.TIM");
            loadRaw("KF/KAN/B1/K007.TIM");
            loadRaw("KF/KAN/B1/K008.TIM");
            loadRaw("KF/KAN/B1/K100.TIM");
            loadRaw("KF/KAN/B1/K101.TIM");
            loadRaw("KF/KAN/B1/K102.TIM");
            loadRaw("KF/KAN/B1/K103.TIM");
            loadRaw("KF/KAN/B2/K000.TIM");
            loadRaw("KF/KAN/B2/K001.TIM");
            loadRaw("KF/KAN/B2/K002.TIM");
            loadRaw("KF/KAN/B2/K003.TIM");
            loadRaw("KF/KAN/B2/K004.TIM");
            loadRaw("KF/KAN/B2/K005.TIM");
            loadRaw("KF/KAN/B2/K006.TIM");
            loadRaw("KF/KAN/B2/K100.TIM");
            loadRaw("KF/KAN/B2/K101.TIM");
            loadRaw("KF/KAN/B2/K102.TIM");
            loadRaw("KF/KAN/B3/K000.TIM");
            loadRaw("KF/KAN/B3/K001.TIM");
            loadRaw("KF/KAN/B3/K002.TIM");
            loadRaw("KF/KAN/B3/K003.TIM");
            loadRaw("KF/KAN/B3/K004.TIM");
            loadRaw("KF/KAN/B3/K101.TIM");
            loadRaw("KF/KAN/B3/K102.TIM");
            loadRaw("KF/KAN/B3/K103.TIM");
            loadRaw("KF/KAN/B3/K104.TIM");
            loadRaw("KF/KAN/B4/K000.TIM");
            loadRaw("KF/KAN/B4/K001.TIM");
            loadRaw("KF/KAN/B4/K002.TIM");
            loadRaw("KF/KAN/B4/K004.TIM");
            loadRaw("KF/KAN/B4/K101.TIM");
            loadRaw("KF/KAN/B4/K102.TIM");
            loadRaw("KF/KAN/B4/K103.TIM");
            for (auto i = 11; i <= 25; i == 15 ? i = 21 : i++)
                loadRaw(QStringLiteral("KF/MAP/%1").arg(i, 2, 10, QChar('0')));
            for (auto prsn = 1; prsn <= 17; prsn++)
                loadRaw(QStringLiteral("KF/PRSN/PER%1.TIM").arg(prsn, 2, 10, QChar('0')));
            loadRaw("KF/TALK/C01/T11011.TIM");
            loadRaw("KF/TALK/C01/T11012.TIM");
            loadRaw("KF/TALK/C01/T11013.TIM");
            loadRaw("KF/TALK/C01/T11014.TIM");
            loadRaw("KF/TALK/C01/T11015.TIM");
            loadRaw("KF/TALK/C01/T11016.TIM");
            loadRaw("KF/TALK/C01/T11017.TIM");
            loadRaw("KF/TALK/C01/T11018.TIM");
            loadRaw("KF/TALK/C01/T11019.TIM");
            loadRaw("KF/TALK/C01/T12011.TIM");
            loadRaw("KF/TALK/C01/T12012.TIM");
            loadRaw("KF/TALK/C01/T12013.TIM");
            loadRaw("KF/TALK/C01/T13011.TIM");
            loadRaw("KF/TALK/C01/T14011.TIM");
            loadRaw("KF/TALK/C01/T15011.TIM");
            loadRaw("KF/TALK/C02/T11021.TIM");
            loadRaw("KF/TALK/C02/T11022.TIM");
            loadRaw("KF/TALK/C02/T11023.TIM");
            loadRaw("KF/TALK/C02/T11024.TIM");
            loadRaw("KF/TALK/C02/T11025.TIM");
            loadRaw("KF/TALK/C02/T11026.TIM");
            loadRaw("KF/TALK/C02/T11027.TIM");
            loadRaw("KF/TALK/C02/T11028.TIM");
            loadRaw("KF/TALK/C02/T11029.TIM");
            loadRaw("KF/TALK/C02/T12021.TIM");
            loadRaw("KF/TALK/C02/T12022.TIM");
            loadRaw("KF/TALK/C02/T12023.TIM");
            loadRaw("KF/TALK/C02/T12045.TIM");
            loadRaw("KF/TALK/C02/T13021.TIM");
            loadRaw("KF/TALK/C02/T14021.TIM");
            loadRaw("KF/TALK/C02/T15021.TIM");
            loadRaw("KF/TALK/C03/T11031.TIM");
            loadRaw("KF/TALK/C03/T11032.TIM");
            loadRaw("KF/TALK/C03/T11033.TIM");
            loadRaw("KF/TALK/C03/T11034.TIM");
            loadRaw("KF/TALK/C03/T11035.TIM");
            loadRaw("KF/TALK/C03/T11036.TIM");
            loadRaw("KF/TALK/C03/T11037.TIM");
            loadRaw("KF/TALK/C03/T11038.TIM");
            loadRaw("KF/TALK/C03/T12031.TIM");
            loadRaw("KF/TALK/C03/T12032.TIM");
            loadRaw("KF/TALK/C03/T12035.TIM");
            loadRaw("KF/TALK/C03/T13031.TIM");
            loadRaw("KF/TALK/C03/T13032.TIM");
            loadRaw("KF/TALK/C03/T14031.TIM");
            loadRaw("KF/TALK/C03/T15031.TIM");
            loadRaw("KF/TALK/C04/T11041.TIM");
            loadRaw("KF/TALK/C04/T11042.TIM");
            loadRaw("KF/TALK/C04/T11043.TIM");
            loadRaw("KF/TALK/C04/T11044.TIM");
            loadRaw("KF/TALK/C04/T11045.TIM");
            loadRaw("KF/TALK/C04/T11046.TIM");
            loadRaw("KF/TALK/C04/T11047.TIM");
            loadRaw("KF/TALK/C04/T11048.TIM");
            loadRaw("KF/TALK/C04/T12041.TIM");
            loadRaw("KF/TALK/C04/T12042.TIM");
            loadRaw("KF/TALK/C04/T12043.TIM");
            loadRaw("KF/TALK/C04/T12044.TIM");
            loadRaw("KF/TALK/C04/T12045.TIM");
            loadRaw("KF/TALK/C04/T13041.TIM");
            loadRaw("KF/TALK/C04/T13042.TIM");
            loadRaw("KF/TALK/C04/T14041.TIM");
            loadRaw("KF/TALK/C04/T14042.TIM");
            loadRaw("KF/TALK/C04/T15041.TIM");
            loadRaw("KF/TALK/C05/T44051.TIM");
            loadRaw("KF/TALK/C05/T44052.TIM");
            loadRaw("KF/TALK/C05/T44053.TIM");
            loadRaw("KF/TALK/C06/T22061.TIM");
            loadRaw("KF/TALK/C06/T22062.TIM");
            loadRaw("KF/TALK/C06/T22063.TIM");
            loadRaw("KF/TALK/C06/T22064.TIM");
            loadRaw("KF/TALK/C06/T22065.TIM");
            loadRaw("KF/TALK/C06/T22066.TIM");
            loadRaw("KF/TALK/C06/T22067.TIM");
            loadRaw("KF/TALK/C06/T22068.TIM");
            loadRaw("KF/TALK/C06/T22069.TIM");
            loadRaw("KF/TALK/C06/T33061.TIM");
            loadRaw("KF/TALK/C06/T33062.TIM");
            loadRaw("KF/TALK/C06/T33063.TIM");
            loadRaw("KF/TALK/C06/T33064.TIM");
            loadRaw("KF/TALK/C06/T33065.TIM");
            loadRaw("KF/TALK/C06/T33066.TIM");
            loadRaw("KF/TALK/C06/T33067.TIM");
            loadRaw("KF/TALK/C06/T33068.TIM");
            loadRaw("KF/TALK/C06/T33069.TIM");
            loadRaw("KF/TALK/C06/T34061.TIM");
            loadRaw("KF/TALK/C06/T34062.TIM");
            loadRaw("KF/TALK/C06/T35061.TIM");
            loadRaw("KF/TALK/C06/T35062.TIM");
            loadRaw("KF/TALK/C06/T35063.TIM");
            loadRaw("KF/TALK/C06/T35064.TIM");
            loadRaw("KF/TALK/C07/T22071.TIM");
            loadRaw("KF/TALK/C07/T22072.TIM");
            loadRaw("KF/TALK/C07/T22073.TIM");
            loadRaw("KF/TALK/C07/T22074.TIM");
            loadRaw("KF/TALK/C07/T22075.TIM");
            loadRaw("KF/TALK/C07/T23071.TIM");
            loadRaw("KF/TALK/C07/T23072.TIM");
            loadRaw("KF/TALK/C08/T22081.TIM");
            loadRaw("KF/TALK/C08/T22082.TIM");
            loadRaw("KF/TALK/C08/T22083.TIM");
            loadRaw("KF/TALK/C08/T22084.TIM");
            loadRaw("KF/TALK/C08/T22085.TIM");
            loadRaw("KF/TALK/C08/T22086.TIM");
            loadRaw("KF/TALK/C08/T22087.TIM");
            loadRaw("KF/TALK/C08/T23081.TIM");
            loadRaw("KF/TALK/C08/T23082.TIM");
            loadRaw("KF/TALK/C08/T23083.TIM");
            loadRaw("KF/TALK/C08/T24081.TIM");
            loadRaw("KF/TALK/C08/T24082.TIM");
            loadRaw("KF/TALK/C08/T25081.TIM");
            loadRaw("KF/TALK/C08/T25082.TIM");
            loadRaw("KF/TALK/C08/T25083.TIM");
            loadRaw("KF/TALK/C09/T11091.TIM");
            loadRaw("KF/TALK/C09/T11092.TIM");
            loadRaw("KF/TALK/C09/T11093.TIM");
            loadRaw("KF/TALK/C09/T11094.TIM");
            loadRaw("KF/TALK/C09/T11095.TIM");
            loadRaw("KF/TALK/C09/T11096.TIM");
            loadRaw("KF/TALK/C09/T12091.TIM");
            loadRaw("KF/TALK/C09/T12092.TIM");
            loadRaw("KF/TALK/C09/T13091.TIM");
            loadRaw("KF/TALK/C09/T13092.TIM");
            loadRaw("KF/TALK/C11/T22111.TIM");
            loadRaw("KF/TALK/C11/T55111.TIM");
            loadRaw("KF/TALK/C11/T55112.TIM");
            loadRaw("KF/TALK/C11/T55113.TIM");
            loadRaw("KF/TALK/C12/T33121.TIM");
            loadRaw("KF/TALK/C12/T33122.TIM");
            loadRaw("KF/TALK/C12/T33123.TIM");
            loadRaw("KF/TALK/C12/T34121.TIM");
            loadRaw("KF/TALK/C13/T11131.TIM");
            loadRaw("KF/TALK/C13/T11132.TIM");
            loadRaw("KF/TALK/C13/T11133.TIM");
            loadRaw("KF/TALK/C13/T11134.TIM");
            loadRaw("KF/TALK/C13/T11135.TIM");
            loadRaw("KF/TALK/C13/T11136.TIM");
            loadRaw("KF/TALK/C13/T11137.TIM");
            loadRaw("KF/TALK/C13/T11138.TIM");
            loadRaw("KF/TALK/C13/T12131.TIM");
            loadRaw("KF/TALK/C13/T12132.TIM");
            loadRaw("KF/TALK/C13/T12133.TIM");
            loadRaw("KF/TALK/C13/T12134.TIM");
            loadRaw("KF/TALK/C13/T12135.TIM");
            loadRaw("KF/TALK/C13/T12136.TIM");
            loadRaw("KF/TALK/C14/T44141.TIM");
            loadRaw("KF/TALK/C15/T44151.TIM");
            loadRaw("KF/TALK/C17/T55171.TIM");
            loadRaw("KF/TALK/C17/T55172.TIM");
            for (auto i = 0; i <= 3; i++) loadRaw(QStringLiteral("KF/TIM/ICO%1.TIM").arg(i));
            for (const auto& i : {1,   2,   3,   4,   5,   6,   7,   8,   9,   101, 102, 103, 104,
                                  105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 999})
                loadRaw(QStringLiteral("KF/TIM/M%1").arg(i, 4, 10, QChar('0')));
            for (auto i = 0; i <= 15; i++)
                loadRaw(QStringLiteral("KF/WEPON/WEP%1.MIM").arg(i, 2, 10, QChar('0')));
            for (auto i = 0; i <= 3; i++) loadRaw(QStringLiteral("E%1").arg(i));
            break;
        case VersionedGame::KFDemo:
            loadRaw("MAP/M561.TIM");
            for (const auto& i : {301, 302, 303, 401, 402, 403, 901, 902, 903, 1301, 1302, 1303})
                loadRaw(QStringLiteral("TIM/1%1.TIM").arg(i, 4, 10, QChar('0')));
            for (auto i = 0; i <= 12; i++)
                loadRaw(QStringLiteral("TIM/M0%1.TIM").arg(i, 2, 10, QChar('0')));
            for (const auto& i : {1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 40, 41, 44, 45, 53, 55, 56, 57})
                loadRaw(QStringLiteral("TMD/I0%1.TMD").arg(i, 2, 10, QChar('0')));
            loadRaw("TMD/MIX.TMD");
            loadRaw("FANM.TMD");
            loadRaw("ITMTMD.001");
            loadMIX("IVMIM.001");
            loadMIX("MIM.001");
            loadMIX("MIX.TIM");
            loadRaw("MIX.TMD");
            loadRaw("SCRD.MIM");
            loadMIX("SFXMIM.001");
            loadRaw("WEP00.MIM");
            break;
        case VersionedGame::KF2E:
            loadT("CD/COM/FDAT.T");
            loadT("CD/COM/ITEM0.T");
            loadT("CD/COM/ITEM1.T");
            loadT("CD/COM/ITEM2.T");
            loadT("CD/COM/MO.T");
            loadT("CD/COM/RTIM.T");
            loadT("CD/COM/RTMD.T");
            loadT("CD/COM/TALK0.T");
            loadT("CD/COM/TALK1.T");
            loadT("CD/COM/TALK2.T");
            loadT("CD/COM/VAB.T");
            loadRaw("CD/MSG0.TIM");
            loadRaw("CD/MSG1.TIM");
            loadRaw("CD/MSG2.TIM");
            // TODO: ED.D is weird and thus unsupported.
            //loadMIXFile("OP/ED.D");
            loadMIX("OP/EUR.D");
            loadMIX("OP/OP.D");
            break;
        case VersionedGame::KF2Jv1_0: [[fallthrough]];
        case VersionedGame::KF2Jv1_7: [[fallthrough]];
        case VersionedGame::KF2Jv1_8A: [[fallthrough]];
        case VersionedGame::KF2Jv1_8B: [[fallthrough]];
        case VersionedGame::KF2U:
            loadT("CD/COM/FDAT.T");
            loadT("CD/COM/ITEM.T");
            loadT("CD/COM/MO.T");
            loadT("CD/COM/RTIM.T");
            loadT("CD/COM/RTMD.T");
            loadT("CD/COM/TALK.T");
            loadT("CD/COM/VAB.T");
            // TODO: ED.D is weird and thus unsupported.
            //loadMIXFile("OP/ED.D");
            loadMIX("OP/OP.D");

            if (curGame == VersionedGame::KF2U)
            {
                loadMIX("OP/OPU.D");
                loadRaw("GAME.EXE");
            }
            break;
        case VersionedGame::KF3Jv1_3: [[fallthrough]];
        case VersionedGame::KF3Jv1_4: [[fallthrough]];
        case VersionedGame::KF3U: [[fallthrough]];
        case VersionedGame::KFPS:
            loadT("CD/COM/FDAT.T");
            loadT("CD/COM/ITEM.T");
            loadT("CD/COM/MO.T");
            loadT("CD/COM/MOF.T");
            loadT("CD/COM/RTIM.T");
            loadT("CD/COM/RTMD.T");
            loadT("CD/COM/STALK.T");
            loadT("CD/COM/TALK.T");
            loadT("CD/COM/VAB.T");
            loadMIX("OP/OP.D");
            //loadRawFile("GAME.EXE");
            loadRaw("LOAD.MSG");
            break;
        case VersionedGame::ST:
            for (int i = 0; i <= 4; i++)
                for (int j = 0; j <= (i == 4 ? 7 : 9); j++)
                    loadT(QStringLiteral("ST/CHR%1/M%1%2.T").arg(i).arg(j));
            loadT("ST/COM/CRT.T");
            loadT("ST/COM/EQUIP.T");
            loadT("ST/COM/FDAT.T");
            loadT("ST/COM/ICON.T");
            loadT("ST/COM/ITEM.T");
            loadT("ST/COM/MO.T");
            loadT("ST/COM/STAT.T");
            loadT("ST/COM/TALKMSG.T");
            loadMIX("ST/OPTXT/OPTXT.MIC");
            loadRaw("ST/STR/COPYRIGT.TIM");
            loadRaw("ST/STR/D_TITLE.TIM");
            loadRaw("ST/STR/FLOGO320.TIM");
            loadRaw("ST/STR/POISON.TIM");
            loadMIX("ST/STR/STAFF.MIC");
            loadMIX("ST/TITLE/TITLE.MIC");
            loadT("ST/VS/STAT.T");
            loadT("ST/VS/VS_CRT.T");
            loadT("ST/VS/VS_ETC.T");
            loadRaw("LOAD02.TIM");
            break;
        case VersionedGame::STDemo:
            loadT("CHR0/M04.T");
            loadT("CHR0/M05.T");
            loadT("COM/CRT.T");
            loadT("COM/EQUIP.T");
            loadT("COM/FDAT.T");
            loadT("COM/ICON.T");
            loadT("COM/ITEM.T");
            loadT("COM/MO.T");
            loadT("COM/STAT.T");
            loadT("COM/TALKMSG.T");
            loadRaw("END.TIM");
            loadRaw("LOAD02.TIM");
            loadMIX("TITLE.MIC");
            break;
        default:
            KFMTError::error(QStringLiteral("KFMTCore::loadFrom: Unhandled Game value %1")
                                 .arg(static_cast<int>(curGame)));
            break;
    }

    if (curGame != VersionedGame::KF2E && curGame != VersionedGame::KF2Jv1_0 && curGame != VersionedGame::KF2Jv1_8A
        && curGame != VersionedGame::KF2Jv1_8B && curGame != VersionedGame::KF2U)
        KFMTError::warning(QStringLiteral("Support for the game you loaded is INCOMPLETE. Things "
                                          "will be broken, and names will be incorrect."));
}

void KFMTCore::saveTo(const QDir& outDir)
{
    for (auto& file : files) file.writeFile(outDir);
}

void KFMTCore::detectGame(const QDir& srcDir)
{
    if (srcDir.exists("SCUS_941.82") || srcDir.exists("SLUS_013.23"))
        curGame = VersionedGame::ACU;
    else if (srcDir.exists("USA10.EXE"))
        curGame = VersionedGame::ACDemo;
    else if (srcDir.exists("SLPS_009.00"))
        curGame = VersionedGame::ACProto;
    else if (srcDir.exists("PSX.EXE") && srcDir.exists("E0") && srcDir.exists("E1")
             && srcDir.exists("E2") && srcDir.exists("E3"))
        curGame = VersionedGame::KF;
    else if (srcDir.exists("KFIELD.EXE") && srcDir.exists("MAP.001"))
        curGame = VersionedGame::KFDemo;
    else if (srcDir.exists("SCES_005.10") && srcDir.exists("END.EXE")
             && srcDir.exists("LICENSEE.DAT"))
        curGame = VersionedGame::KF2E;
    else if (srcDir.exists("END.EXE") && srcDir.exists("GAME.EXE") && srcDir.exists("OPEN.EXE")
             && srcDir.exists("PSX.EXE"))
    {
        auto gameExeHandle = QFile(srcDir.absoluteFilePath("GAME.EXE"));
        if (!gameExeHandle.open(QIODevice::ReadOnly)) return;

        auto gameExeHash = QCryptographicHash::hash(gameExeHandle.readAll(),
                                                    QCryptographicHash::Algorithm::Md5);
        if (gameExeHash == QByteArray::fromHex("20e673906133201fded29b3af6d7b6cd"))
            curGame = VersionedGame::KF2Jv1_0;
        else if (gameExeHash == QByteArray::fromHex("5522e7cdeb6c0261befd6eedf95065a3"))
            curGame = VersionedGame::KF2Jv1_7;
    }
    else if (srcDir.exists("SLPS_910.03"))
    {
        auto copyTxtHandle = QFile(srcDir.absoluteFilePath("COPY.TXT"));
        if (!copyTxtHandle.open(QIODevice::ReadOnly)) return;

        const auto copyTxt = copyTxtHandle.readAll();

        if (copyTxt.contains(QByteArrayLiteral("1.8A")))
            curGame = VersionedGame::KF2Jv1_8A;
        else if (copyTxt.contains(QByteArrayLiteral("1.8B")))
            curGame = VersionedGame::KF2Jv1_8B;
        else
            KFMTError::error(
                QStringLiteral("Your copy of KF2 could not be identified. Please open an issue on "
                               "our GitHub repo or contact us on Discord!"));
    }
    else if (srcDir.exists("SLUS_001.58"))
        curGame = VersionedGame::KF2U;
    else if (srcDir.exists("SLPS_003.77"))
    {
        auto copyTxtHandle = QFile(srcDir.absoluteFilePath("COPY.TXT"));
        if (!copyTxtHandle.open(QIODevice::ReadOnly)) return;

        const auto copyTxt = copyTxtHandle.readAll();

        if (copyTxt.contains(QByteArrayLiteral("1.3")))
            curGame = VersionedGame::KF3Jv1_3;
        else if (copyTxt.contains(QByteArrayLiteral("1.4")))
            curGame = VersionedGame::KF3Jv1_4;
        else
            KFMTError::error(
                QStringLiteral("Your copy of KF3 could not be identified. Please open an issue on "
                               "our GitHub repo or contact us on Discord!"));
    }
    else if (srcDir.exists("SLUS_002.55"))
        curGame = VersionedGame::KF3U;
    else if (srcDir.exists("SLPM_800.29"))
        curGame = VersionedGame::KFPS;
    else if (srcDir.exists("END.EXE") && srcDir.exists("ST.EXE") && srcDir.exists("OPTXT.EXE"))
        curGame = VersionedGame::ST;
    else if (srcDir.exists("ST.EXE") && srcDir.exists("TITLE.MIC") && srcDir.exists("TITLE.XA"))
        curGame = VersionedGame::STDemo;
    else
        curGame = VersionedGame::None;
}

void KFMTCore::loadMIX(QString path)
{
    // Replace the unix-style forward slashes in the path with the current system's separator.
    path.replace(QChar('/'), QDir::separator());

    if (!QFile(curSourceDirectory.absoluteFilePath(path)).exists()) return;

    files.emplace_back(curSourceDirectory.path(), path, KFMTFile::FileType::MIX);
}

void KFMTCore::loadRaw(QString path)
{
    // Replace the unix-style forward slashes in the path with the current system's separator.
    path.replace(QChar('/'), QDir::separator());

    if (!QFile(curSourceDirectory.absoluteFilePath(path)).exists()) return;

    files.emplace_back(curSourceDirectory.path(), path, KFMTFile::FileType::Raw);
}

void KFMTCore::loadT(QString path)
{
    // Replace the unix-style forward slashes in the path with the current system's separator.
    path.replace(QChar('/'), QDir::separator());

    if (!QFile(curSourceDirectory.absoluteFilePath(path)).exists()) return;

    files.emplace_back(curSourceDirectory.path(), path, KFMTFile::FileType::T);
}
