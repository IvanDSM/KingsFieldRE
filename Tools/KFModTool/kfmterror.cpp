#include "kfmterror.h"
#include <QMessageBox>
#include <iostream>

void KFMTError::setParent(QWidget * parentPtr)
{
    _KFMTErrorInternal::_KFMTErrorParent = parentPtr;
}

void KFMTError::error(const QString & errorMessage)
{
    if (!_KFMTErrorInternal::lastErrors.empty() && 
        (errorMessage == _KFMTErrorInternal::lastErrors.front() ||
         errorMessage == _KFMTErrorInternal::lastErrors.back())
       )
    {
        log("Error: " + errorMessage);
        return;
    }
    
    _KFMTErrorInternal::lastErrors.push(errorMessage);
    
    while (_KFMTErrorInternal::lastErrors.size() > 2)
        _KFMTErrorInternal::lastErrors.pop();
        
    std::cerr << "Error: " << errorMessage.toStdString() << '\n';
    QMessageBox::critical(_KFMTErrorInternal::_KFMTErrorParent, "Error", errorMessage);
}

void KFMTError::fatalError(const QString & fatalErrorMessage)
{
    std::cerr << "Fatal Error: " << fatalErrorMessage.toStdString() << '\n';
    QMessageBox::critical(_KFMTErrorInternal::_KFMTErrorParent, "Fatal Error", fatalErrorMessage);
    std::exit(-1);
}

void KFMTError::log(const QString & logMessage)
{
    std::cerr << logMessage.toStdString() << '\n';
}

void KFMTError::warning(const QString & warningMessage)
{
    std::cerr << "Warning: " << warningMessage.toStdString() << '\n';
    QMessageBox::warning(_KFMTErrorInternal::_KFMTErrorParent, "Warning", warningMessage);
}

void KFMTError::outOfRange(const size_t &index, const QString &arrayName, const std::string &exceptionWhat)
{
    QString errorMessage = "Tried to access index %1 of the %2 array.\n%3";
    errorMessage = errorMessage.arg(index).arg(arrayName, QString::fromStdString(exceptionWhat));
    fatalError(errorMessage);
}
