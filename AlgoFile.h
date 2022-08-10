#ifndef ALGOFILE_H
#define ALGOFILE_H
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QLabel>
#include <QTextStream>
#include <QSplitter>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

namespace Ui {
class AlgoFiles;
}

class ALgoFiles{
    public:
        explicit ALgoFiles();
        ~ALgoFiles();
        QString readFile(QString path, QString fname);
        QString ReadCONFIG(QSqlDatabase db,QString path,QString fname);
        void algoPHP(QFile _f);
        void algoJAVA(QFile _f);
        QSqlDatabase dbase;
    private :
        QFile ff;
};


#endif // ALGOFILE_H
