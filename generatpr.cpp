#include "generatpr.h"
#include "ui_generatpr.h"

generatpr::generatpr(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::generatpr)
{
    ui->setupUi(this);
}

generatpr::~generatpr()
{
    delete ui;
}
void generatpr::loadConnection(QString dbtype,QString dbserver,qint32 dbport, QString dbname,QString dbuser, QString dbpassword){
    database = QSqlDatabase::addDatabase("Q"+dbtype);
    database.setHostName(dbserver);
    database.setPort(dbport);
    database.setUserName(dbuser);
    database.setPassword(dbpassword);
    database.setDatabaseName(dbname);
    if(database.open()){
       QMessageBox::information(this, "Connection Info", "Connection done.");
        generateHome *d = new generateHome();
        d->setData(database,dbname);
        d->show();
        this->close();
    }else QMessageBox::information(this, "Connection Info", "Connection error!");
}

void generatpr::on_ConectBtn_clicked()
{
    QString Name = ui->dbName->text();
    QString User = ui->dbUser->text();
    QString Server = ui->dbServer->text();
    QString Password = ui->dbPassword->text();
    qint32 port = ui->dbPort->text().toInt();
    QComboBox *Type = ui->dbType;
    QString databaseType = Type->currentText();
    generatpr::loadConnection(databaseType, Server, port,Name, User, Password);
}
