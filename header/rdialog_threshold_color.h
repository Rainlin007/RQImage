#ifndef RDIALOG_THRESHOLD_COLOR_H
#define RDIALOG_THRESHOLD_COLOR_H

#include <QDialog>
#include <QPainter>
#include <rcontroller.h>
namespace Ui
{
class RDialog_threshold_color;
}

class RDialog_threshold_color : public QDialog
{
    Q_OBJECT

public:
    explicit RDialog_threshold_color(QWidget *parent = nullptr);
    ~RDialog_threshold_color();

protected:
    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        auto his = RController::getInstance()->getHistogramPixmap_color();
        painter.drawPixmap(90, 10, his[0]);
        painter.drawPixmap(90, 240, his[1]);
        painter.drawPixmap(90, 470, his[2]);
    }

private slots:

    void on_checkBox_stateChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_6_valueChanged(int arg1);

    void on_spinBox_4_valueChanged(int arg1);

    void on_spinBox_5_valueChanged(int arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::RDialog_threshold_color *ui;
    int threshold[3][2] = {{0, 0}, {0, 0}, {0, 0}};
};

#endif // RDIALOG_THRESHOLD_COLOR_H
