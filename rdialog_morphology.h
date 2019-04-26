#ifndef RDIALOG_MORPHOLOGY_H
#define RDIALOG_MORPHOLOGY_H

#include <QDialog>
#include"rheaders.h"
namespace Ui {
class RDialog_morphology;
}

class RDialog_morphology : public QDialog
{
    Q_OBJECT

public:
    explicit RDialog_morphology(QWidget *parent = nullptr);
    ~RDialog_morphology();
    cv::Mat result;

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::RDialog_morphology *ui;
};

#endif // RDIALOG_MORPHOLOGY_H
