#include "generatehome.h"
#include "ui_generatehome.h"

generateHome::generateHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::generateHome)
{
    ui->setupUi(this);
    //modelQuery

}

generateHome::~generateHome()
{
    delete ui;
}

void generateHome::setData(QSqlDatabase dt,QString dbName){
    dbase = dt;
    dataName = dbName;

    /*modelQuery = new QSqlQueryModel();
    modelQuery->setQuery("SELECT TABLE_NAME as 'NAME', TABLE_ROWS as 'ROWS' from information_schema.tables where table_schema = '"+dataName+"'");
    query = new QSqlQuery(dbase);
    for(int i=0; i<modelQuery->rowCount();i++){
        QString TableName = modelQuery->data(modelQuery->index(0,i)).toString();
        query->exec("SELECT COUNT(*) from "+TableName+" ");
        QString x;
        while(query->next()) {
            x = query->value(0).toString();
            modelQuery->setData(modelQuery->index(1,i),x);
        }
    }
    ui->tableView->setModel(modelQuery);*/
    //f->readFile(ui->fileText);
    QFileSystemModel *mod = new QFileSystemModel;
    QString MPath = "C:/Users/sharkfisher/Documents/QT/Generator";
    Folder_PATH = MPath;
    mod->setRootPath(MPath);
    ui->FoldersList->setModel(mod);
    ui->FoldersList->setRootIndex(mod->index(MPath));
    ui->FoldersList->hideColumn(1);
    ui->FoldersList->hideColumn(2);
    ui->FoldersList->hideColumn(3);
    addingWidgets(dataName);
    //std::printf();
    QGridLayout *grid = new QGridLayout();
    txt = new QPlainTextEdit();
    txt->setAutoFillBackground(true);
    txt->setStyleSheet("background-color:rgb(25, 42, 86);color:rgb(245, 246, 250);");
    QFont tfont = QFont("Hack Regular");
    tfont.setPixelSize(14);
    txt->setFont(tfont);
    grid->addWidget(txt,0,0);
    ui->tab->setLayout(grid);
}
void generateHome::addingWidgets(QString name){

    dbase.open();
    query = new QSqlQuery(dbase);
    query->exec("SELECT TABLE_NAME, TABLE_ROWS from information_schema.tables where table_schema = '"+name+"'");
    while(query->next()){
        int row = ui->widgt->rowCount();
        ui->widgt->setRowCount(row+1);
        QString tableNN = query->value(0).toString();
        QTableWidgetItem *TABLES = new QTableWidgetItem(tableNN);
        QSqlQuery *NQuery = new QSqlQuery(dbase);
        NQuery->exec("SELECT COUNT(*) from "+tableNN+" ");
        QTableWidgetItem *ROWS;
        while(NQuery->next())
            ROWS = new QTableWidgetItem(NQuery->value(0).toString());
        TABLES->setFlags(TABLES->flags() & ~Qt::ItemIsEditable);
        ROWS->setFlags(ROWS->flags() & ~Qt::ItemIsEditable);
        ui->widgt->setItem(row,0,TABLES);
        ui->widgt->setItem(row,1,ROWS);
    }
    dbase.close();

}

void generateHome::on_addFolder_clicked()
{

}

void generateHome::on_openFolder_clicked()
{

}

void generateHome::on_addConfigFile_clicked()
{

}

void generateHome::on_OpenConfigFile_clicked()
{
    QString fileNAME = QFileDialog::getOpenFileName(this, tr("Open Config File"),Folder_PATH,"*.tmconf");
    QRegularExpression CONF_NAME("([a-zA-Z0-9_\.\-]+)\.tmconf$");
    QRegularExpressionMatch CONF_NAME_MATCH = CONF_NAME.match(fileNAME);
    fileNAME = CONF_NAME_MATCH.captured(0);
    generateLINES(fileNAME);
}

void generateHome::on_editConfigFile_clicked()
{

}

void generateHome::on_openCMD_clicked()
{

}

void generateHome::on_openDATABASES_clicked()
{
    DatabaseDialog *datadialog = new DatabaseDialog(this);
    datadialog->show();
}

void generateHome::on_SETTING_clicked()
{

}

void generateHome::on_PREFERENCES_clicked()
{

}

void generateHome::on_VALIDE_clicked()
{
    QFile saveFile(Under_Edit);
    saveFile.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream SV_STREAM(&saveFile);
    SV_STREAM << txt->toPlainText();
        saveFile.close();
        QMessageBox::information(this, "Message","File Saved");
}

void generateHome::on_DELETE_clicked()
{

}

void generateHome::on_ADD_clicked()
{

}

void generateHome::on_REFRESH_clicked()
{

}

void generateHome::on_FORWARD_clicked()
{

}

void generateHome::on_BACK_clicked()
{

        //QString::number(lines) LINES NUBER

}
int generateHome:: TextLines(){
    Q_ASSERT(txt);
        QTextCursor cursor = txt->textCursor();
        cursor.movePosition(QTextCursor::StartOfLine);

        int lines = 1;
        while(cursor.positionInBlock()>0) {
            cursor.movePosition(QTextCursor::Up);
            lines++;
        }
        QTextBlock block = cursor.block().previous();
        while(block.isValid()) {
            lines += block.lineCount();
            block = block.previous();
        }
        return lines;
}
void generateHome::on_FoldersList_doubleClicked(const QModelIndex &index)
{
    QVariant e = index.data();
    QString FileName_ToEdit = e.toString();
    generateLINES(FileName_ToEdit);
        //QStringList strList = data.split(QRegExp("[\n]"),QString::SkipEmptyParts);
    //;
}
void generateHome::generateLINES(QString _FILE_NAME){
    Under_Edit = _FILE_NAME;
    QRegularExpression EXT_FILE("\.(tmconf)$");
    QRegularExpressionMatch SPLITING_MATCH = EXT_FILE.match(_FILE_NAME);
        if(SPLITING_MATCH.hasMatch()){
            txt->insertPlainText(f->ReadCONFIG(dbase,Folder_PATH,_FILE_NAME));
        }
        else
            txt->setPlainText(f->readFile(Folder_PATH,_FILE_NAME));
}
/*

           QTextCursor cursor = QTextCursor(txt->document()->findBlockByLineNumber(TextLines()));
            txt->moveCursor(cursor.End);
            txt->setTextCursor(cursor);
*/
