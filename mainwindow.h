#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QString>
#include <QMessageBox>
#include <QValidator>
#include <vector>
#include <stdio.h>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QToolButton** mat=NULL;
    QIcon QueenIcon;    // 开始是用图片表示皇后，现在换成了改变btu背景色已经所以不用了
    int n;
    int cnt=0;
    std::vector<std::vector<int>> ans;
    int arr[20];//arr[i]=j，表示皇后在第i行第j列
    QIntValidator* MaxN;    // 跳转解法最大数值
private:
    void DeleteMat();
    bool PaintingMat();
    void PaintingQueen();
    void Queens(int i=0);
    void PaintingPreQueen();
    void PaintingNextQueen();
    void PaintingNQueen();
};
#endif // MAINWINDOW_H
