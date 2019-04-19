#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    static MainWindow* ins;
    bool overlayer_show=false;

public:
    void initUI();
    void setOverlayer(QPixmap &);
    void showOverlayer(bool status);
    static MainWindow* getInstance();

public:
    QPixmap pixmap_mainshow;//current image show
    QPixmap pixmap_overlayer;//overlayer image

    QGraphicsScene scene_mainshow;//current scene

private slots:
    void on_actionOpen_triggered();

    void on_actionZoom_2_triggered();

    void on_actionZoom_3_triggered();

    void on_actionRGB2Gray_triggered();

    void on_actionSave_As_triggered();

    void on_actionReset_triggered();

    void on_actionTools_Bar_triggered();

    void on_actionTools_Bar_toggled(bool arg1);

    void on_actionThreshold_triggered();

    void on_actionOverlayer_toggled(bool arg1);

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;






};

#endif // MAINWINDOW_H
