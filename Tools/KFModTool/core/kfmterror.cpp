#include "core/kfmterror.h"
#include <QMessageBox>
#include <iostream>

static QWidget* KFMTErrorParent;
static std::queue<QString> lastErrors{};

static const auto errorStr = QStringLiteral("Error: ");
static const auto fatalErrorStr = QStringLiteral("Fatal Error: ");
static const auto warningStr = QStringLiteral("Warning: ");

void KFMTError::setParent(QWidget * parentPtr)
{
    KFMTErrorParent = parentPtr;
}

void KFMTError::error(const QString & errorMessage)
{
    log(errorStr + errorMessage);

    if (!lastErrors.empty()
        && (errorMessage == lastErrors.front() || errorMessage == lastErrors.back()))
        return;

    lastErrors.push(errorMessage);
    lastErrors.pop();

    QMessageBox::critical(KFMTErrorParent, QStringLiteral("Error"), errorMessage);
}

void KFMTError::fatalError(const QString & fatalErrorMessage)
{
    log(fatalErrorStr + fatalErrorMessage);
    QMessageBox::critical(KFMTErrorParent, QStringLiteral("Fatal Error"), fatalErrorMessage);
    std::exit(-1);
}

void KFMTError::log(const QString & logMessage)
{
    std::cerr << logMessage.toStdString() << '\n';
}

void KFMTError::warning(const QString & warningMessage)
{
    log(warningStr + warningMessage);
    QMessageBox::warning(KFMTErrorParent, QStringLiteral("Warning"), warningMessage);
}
