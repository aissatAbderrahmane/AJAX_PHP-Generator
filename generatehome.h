#ifndef GENERATEHOME_H
#define GENERATEHOME_H

#include <QWidget>
#include <QLabel>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QTableView>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QMessageBox>
#include <QVariant>
#include <QStandardItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTreeView>
#include <QFileSystemModel>
#include <QTabWidget>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QTextBlock>
#include <QFileDialog>
#include "AlgoFile.h"
#include "databasedialog.h"
#include "settingsdialog.h"
#include "configdialog.h"
namespace Ui {
class generateHome;
}

class generateHome : public QWidget
{
    Q_OBJECT

public:
    explicit generateHome(QWidget *parent = nullptr);
    ~generateHome();
    void setData(QSqlDatabase dt,QString dbName);
    QSqlDatabase dbase;
    void addingWidgets(QString name);
    ALgoFiles *f;
    QPlainTextEdit *txt;
    qint32 indx;
    QString Folder_PATH;
    QString Under_Edit;
    int TextLines();
    void generateLINES(QString _FILE_NAME);
private slots:
    void on_addFolder_clicked();

    void on_openFolder_clicked();

    void on_addConfigFile_clicked();

    void on_OpenConfigFile_clicked();

    void on_editConfigFile_clicked();

    void on_openCMD_clicked();

    void on_openDATABASES_clicked();

    void on_SETTING_clicked();

    void on_PREFERENCES_clicked();

    void on_VALIDE_clicked();

    void on_DELETE_clicked();

    void on_ADD_clicked();

    void on_REFRESH_clicked();

    void on_FORWARD_clicked();

    void on_BACK_clicked();

    void on_FoldersList_doubleClicked(const QModelIndex &index);

private:
    Ui::generateHome *ui;
    QSqlQueryModel *modelQuery;
    QSqlQuery *query;
    QString dataName;

};

#endif // GENERATEHOME_H
