#ifndef RDIALOG_THRESHOLD_H
#define RDIALOG_THRESHOLD_H

#include <QDialog>
#include<QPainter>
#include<rcontroller.h>
namespace Ui {
class RDialog_threshold;
}

class RDialog_threshold : public QDialog
{
    Q_OBJECT

public:
    explicit RDialog_threshold(QWidget *parent = nullptr);
    ~RDialog_threshold();
protected:
    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        auto his=RController::getInstance()->getHistogramPixmap();
        painter.drawPixmap(90,0,his);
    }


private:
    int threshold_1=0;
    int threshold_2=0;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::RDialog_threshold *ui;




};

#endif // RDIALOG_THRESHOLD_H
