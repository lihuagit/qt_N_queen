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
    QToolButton** mat=NULL; // 皇后矩阵
    QIcon QueenIcon;    // 开始是用图片表示皇后，现在换成了改变btu背景色已经所以不用了
    int n;  // n皇后的n，棋盘大小。
    int cnt=0;  // 当前显示第cnt个方案
    std::vector<std::vector<int>> ans;  // 储存方案结果
    int arr[20];//arr[i]=j，表示皇后在第i行第j列
    QIntValidator* MaxN;    // 跳转解法最大数值
private:
    void DeleteMat();   // 删除皇后矩阵
    bool PaintingMat(); // 画皇后矩阵
    void PaintingQueen();   // 画出第cnt个解法
    void Queens(int i=0);   // n皇后递归算法
    void PaintingPreQueen();    // 画前一个解
    void PaintingNextQueen();   // 画后一个解
    void PaintingNQueen();      // 跳转到任意解法
};
#endif // MAINWINDOW_H
