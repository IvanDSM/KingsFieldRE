#include "exeeditor.h"
#include "datahandlers/gameexe.h"
#include "models/shoplistmodel.h"
#include "models/shoptablemodel.h"
#include "models/stringtablemodels.h"
#include "ui_exeeditor.h"

EXEEditor::EXEEditor(KFMTFile& file_, QWidget* parent)
    : KFMTEditor(file_, parent), ui(new Ui::EXEEditor)
{
    ui->setupUi(this);
    handler = std::make_unique<GameEXE>(file_);

    auto& exe = *reinterpret_cast<GameEXE*>(handler.get());

    // Set table models
    ui->uiStr1Tbl->setModel(new UIStrings1TableModel(exe, ui->uiStr1Tbl));
    ui->uiStr2Tbl->setModel(new UIStrings2TableModel(exe, ui->uiStr2Tbl));
    ui->itemStrTbl->setModel(new ItemStringsTableModel(exe, ui->itemStrTbl));
    ui->magicStrTbl->setModel(new MagicStringsTableModel(exe, ui->magicStrTbl));
    ui->shopTbl->setModel(new ShopTableModel(exe, ui->shopTbl));

    // Set list models
    ui->shopCombo->setModel(new ShopListModel(ui->shopCombo));

    // Set string delegate for string tables
    ui->uiStr1Tbl->setItemDelegate(new KingsFieldII::KF2UTextDelegate(ui->uiStr1Tbl));
}

EXEEditor::~EXEEditor()
{
    delete ui;
}

void EXEEditor::on_shopCombo_currentIndexChanged(int index)
{
    reinterpret_cast<ShopTableModel*>(ui->shopTbl->model())->setShopIndex(index);
}
