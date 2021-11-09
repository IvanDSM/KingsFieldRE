#ifndef KFMTERROR_H
#define KFMTERROR_H

#include <queue>
#include <QWidget>

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
        [[noreturn]] static void fatalError(const QString &fatalErrorMessage);

        /*!
         * \brief Writes a quiet log message to stderr.
         * \param logMessage Log message to write.
         */
        static void log(const QString &logMessage);

        /*!
         * \brief Displays a non-fatal warning message.
         * \param warningMessage Warning message to display.
         */
        static void warning(const QString &warningMessage);

        /*!
         * \brief Displays a fatal out of range message.
         * \param index Index that caused the out of range exception.
         * \param arrayName Name of the array (e.g. "object class declaration").
         */
        [[noreturn]] inline static void outOfRange(const size_t& index, const QString& arrayName)
        {
            fatalError(QStringLiteral("Tried to access index %1 of the %2 array.\n")
                           .arg(index)
                           .arg(arrayName));
        }
};

#endif // KFMTERROR_H
