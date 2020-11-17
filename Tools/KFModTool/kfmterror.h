#ifndef KFMTERROR_H
#define KFMTERROR_H

#include <QWidget>

namespace _KFMTErrorInternal
{
    static QWidget *_KFMTErrorParent;
}

class KFMTError
{
    public:
        /*!
         * \brief Sets the parent for the error messages. Should only be called once in the main window.
         * \param parentPtr Pointer to the parent. (QWidget)
         */
        static void setParent(QWidget *parentPtr);

        /*!
         * \brief Displays a non-fatal error message.
         * \param errorMessage Error message to display.
         */
        static void error(const QString &errorMessage);

        /*!
         * \brief Displays a fatal error message.
         * \param errorMessage Error message to display.
         */
        static void fatalError(const QString &fatalErrorMessage);

        /*!
         * \brief Displays a non-fatal warning message.
         * \param warningMessage Warning message to display.
         */
        static void warning(const QString &warningMessage);

        /*!
         * \brief Displays a fatal out of range message.
         * \param index Index that caused the out of range exception.
         * \param arrayName Name of the array (e.g. "object class declaration").
         * \param exceptionWhat Result of the exception's .what() method.
         */
        static void outOfRange(const size_t &index, const QString &arrayName, const std::string &exceptionWhat);
};

#endif // KFMTERROR_H
