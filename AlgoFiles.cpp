#include <AlgoFile.h>

ALgoFiles::ALgoFiles(){
    //C:\\Users\\sharkfisher\\Documents\\QT\\Generator
}
ALgoFiles::~ALgoFiles(){}
QString ALgoFiles::readFile(QString path,QString fname){
    QDir::setCurrent(path);
    QFile t(fname);
    t.open(QIODevice::ReadWrite);
    QTextStream strm(&t);
    QString txt = strm.readAll();
    return txt;
}

QString ALgoFiles::ReadCONFIG(QSqlDatabase db,QString path,QString fname){
    QDir::setCurrent(path);
    QFile _f(fname);
    _f.open(QIODevice::ReadOnly);
    QString method,action,inputs,dbtable,option,POSTS = "",__CODE="", _S_POSTS = "";
    QString _AJAX_INPUTS = "",_AJAX_CODE = "", _AJAX_DATA = "";
    while(!_f.atEnd()){
        QString ActualLine = _f.readLine();
        //change later , deprecated v >=5.15

        QRegularExpression CON_SPLITING("(method|input|action|table|option)");
        QRegularExpressionMatch SPLITING_MATCH = CON_SPLITING.match(ActualLine);
        if(SPLITING_MATCH.hasMatch()){
            QStringList strList = ActualLine.split(QRegExp(":"),QString::SkipEmptyParts);
            QString __OPTION = strList[0];
            QString __OPTION_VALUE = strList[1];
            QString __OPTION_VALUE_S = "";
            QRegularExpression __OPTION_VALUE_CORRECTOR("([a-zA-Z0-9_\\?=\.]+)");
            QRegularExpressionMatch __OPTION_VALUE_CORRECTOR_MATCH = __OPTION_VALUE_CORRECTOR.match(__OPTION_VALUE);
            __OPTION_VALUE_S = __OPTION_VALUE_CORRECTOR_MATCH.captured(0);
            if( __OPTION == "option" ){
                option =__OPTION_VALUE_S;
            }else if(__OPTION == "method"){
                method =__OPTION_VALUE_S;
            }else if(__OPTION == "action"){
                action =__OPTION_VALUE_S;
            }else if(__OPTION == "inputs"){
                inputs =__OPTION_VALUE;
                        QRegularExpression INPUTS_VAL_REG("([a-zA-Z0-9]+)");
                        QRegularExpressionMatchIterator INPUTS_VAL_REG_MATCHER = INPUTS_VAL_REG.globalMatch(inputs);
                        while(INPUTS_VAL_REG_MATCHER.hasNext()){
                            QRegularExpressionMatch TEMP_MATCH = INPUTS_VAL_REG_MATCHER.next();
                            QString val_TEMP = TEMP_MATCH.captured(1);
                            if(method == "POST"){
                                POSTS += "$"+val_TEMP+" = $_POST['"+val_TEMP+"'];\n";
                                _S_POSTS += "'\".$"+val_TEMP+".\"',";
                            }
                            else if(method == "GET")
                                POSTS += "$GET['"+val_TEMP+"'];\n";
                            else return " Error Method Undefined !";
                            _AJAX_INPUTS += "  "+val_TEMP.toLower() +" = $(\"input[name='"+val_TEMP+"']\").val(),\n";
                            _AJAX_DATA += "\t"+val_TEMP.toLower()+":"+val_TEMP.toLower()+",\n";
                        }
            }else if(__OPTION == "table"){
                dbtable =__OPTION_VALUE_S;
            }
            // isAjax ==> Require : AJAX : {}

        }else continue;
    }
    db.open();
        QSqlQuery *DATABASE_QUERY = new QSqlQuery(db);
        DATABASE_QUERY->exec("SHOW COLUMNS FROM "+dbtable+" ");
        QString ROWS_TABLE = "";
        while(DATABASE_QUERY->next()) ROWS_TABLE += DATABASE_QUERY->value(0).toString()+",";
    db.close();
    _S_POSTS.remove(QRegularExpression(",$"));
    ROWS_TABLE.remove(QRegularExpression(",$"));
    _AJAX_INPUTS.replace(QRegularExpression(",\\n$"),";");
    _AJAX_DATA.remove(QRegularExpression(",$"));
    _AJAX_CODE += "// ===== AJAX CODE START  ======== \n";
    _AJAX_CODE += "<script type=\"text/javascript\">";
    _AJAX_CODE += "\r var "+_AJAX_INPUTS;
     _AJAX_CODE += "\r $.ajax({ ";
     _AJAX_CODE += " \r  method:'"+method+"', ";
     _AJAX_CODE += " \r  url:'"+action+"', ";
     _AJAX_CODE += " \r  data:{\n "+_AJAX_DATA+" }";
     _AJAX_CODE += "\r }).done(function(result){ ";
     _AJAX_CODE += " \r // ===== AJAX RESULT HERE ======== ";
     _AJAX_CODE += "\r \r });\n";
     _AJAX_CODE += "</script> \n";
     _AJAX_CODE += "// ===== AJAX CODE END  ======== \n ";
    __CODE += " // ================ Generated PHP Code Start Here ================ \n \n ";
    __CODE += POSTS+"\n ";
    __CODE +="$EXEC_SQL->run(); \n ";
    __CODE += "$EXEC_SQL->exec(";
    __CODE +="$SQL->insert(\""+dbtable+"\",\""+ROWS_TABLE+"\",\""+_S_POSTS+"\")";
    __CODE +=");\n";
    __CODE +="$EXEC_SQL->disconnect(); \n";
    __CODE += " // ================ Generated PHP Code End Here ================ \n \n ";
    __CODE += _AJAX_CODE;
    return __CODE;
}
