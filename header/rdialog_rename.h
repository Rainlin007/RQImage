#ifndef RDIALOG_RENAME_H
#define RDIALOG_RENAME_H

#include <QDialog>

namespace Ui
{
class RDialog_rename;
}

class RDialog_rename : public QDialog
{
    Q_OBJECT

public:
    explicit RDialog_rename(QWidget *parent = nullptr);
    ~RDialog_rename();
    QString getValue();
    void setValue(QString t);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::RDialog_rename *ui;
};

#endif // RDIALOG_RENAME_H
