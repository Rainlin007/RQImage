#ifndef RDIALOG_EDGEDETECTION_H
#define RDIALOG_EDGEDETECTION_H

#include <QDialog>

namespace Ui {
class RDialog_EdgeDetection;
}

class RDialog_EdgeDetection : public QDialog
{
    Q_OBJECT

public:
    explicit RDialog_EdgeDetection(QWidget *parent = nullptr);
    ~RDialog_EdgeDetection();

private slots:
    void on_buttonBox_accepted();

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::RDialog_EdgeDetection *ui;
};

#endif // RDIALOG_EDGEDETECTION_H
