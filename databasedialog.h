#ifndef DATABASEDIALOG_H
#define DATABASEDIALOG_H

#include <QDialog>

namespace Ui {
class DatabaseDialog;
}

class DatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseDialog(QWidget *parent = nullptr);
    ~DatabaseDialog();

private:
    Ui::DatabaseDialog *ui;
};

#endif // DATABASEDIALOG_H
