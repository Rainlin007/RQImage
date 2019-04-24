#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include<QListWidgetItem>
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

public:
    static MainWindow* getInstance();

    //related method
    void initUI();
    void showOverlayer(bool status);

    void setInfo(QString);
    void setCurrentImage(int pm_num=-1,QString text="");



    //list
    void addListItem(QString text,int pm_num);
    void removeListItem(int );
public:

    QGraphicsScene scene_mainshow;//current scene
    QMenu * list_m_contextMenu;




private slots:
    void on_actionOpen_triggered();

    void on_actionZoom_2_triggered();

    void on_actionZoom_3_triggered();

    void on_actionRGB2Gray_triggered();

    void on_actionSave_As_triggered();

    void on_actionReset_triggered();

    void on_actionTools_Bar_toggled(bool arg1);

    void on_actionThreshold_triggered();

    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_2_customContextMenuRequested(const QPoint &pos);

    void on_actionRemove_Image_triggered();

    void on_actionRename_triggered();

private:
    Ui::MainWindow *ui;






};

#endif // MAINWINDOW_H
