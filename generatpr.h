#ifndef GENERATPR_H
#define GENERATPR_H

#include <QMainWindow>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <generatehome.h>
#include <AlgoFile.h>
QT_BEGIN_NAMESPACE
namespace Ui { class generatpr; }
QT_END_NAMESPACE

class generatpr : public QMainWindow
{
    Q_OBJECT

public:
    generatpr(QWidget *parent = nullptr);
    ~generatpr();
    void loadConnection(QString dbtype,QString dbserver,qint32 dbport, QString dbname,QString dbuser, QString dbpassword);


private slots:
    void on_ConectBtn_clicked();

private:
    Ui::generatpr *ui;
    QSqlQuery *query;
    QSqlDatabase database;

};
#endif // GENERATPR_H
