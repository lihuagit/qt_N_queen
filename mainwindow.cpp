#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QueenIcon=QIcon("./queen_pix/queen.jpg");
//    if(QueenIcon.isNull()) QueenIcon=QIcon("./queen.jpg");
    n=0;
    cnt=0;
    MaxN=new QIntValidator(0,0,this);
    int w=this->width();
    int h=this->height();
    ui->mat_widget->setFixedSize(h-10,w-120);
    connect(ui->startbutton,&QToolButton::clicked,this,&MainWindow::PaintingMat);
    connect(ui->prebutton,&QToolButton::clicked,this,&MainWindow::PaintingPreQueen);
    connect(ui->nextbutton,&QToolButton::clicked,this,&MainWindow::PaintingNextQueen);
    connect(ui->to_btu,&QToolButton::clicked,this,&MainWindow::PaintingNQueen);

}

MainWindow::~MainWindow()     
{
    DeleteMat();
    delete ui;
}

bool MainWindow::PaintingMat(){
    DeleteMat();
    cnt=0;
    ans.clear();
    n=0;
    n=(ui->n_Edit->text()).toInt();
    if(n==0 || n>20){
        QMessageBox::critical(this,"错误","请输入有效数值！！！\n有效数值为1~20\n注意数值太大需要很长的时间！！！");
        return false;
    }
    mat=new QToolButton*[n];
    for(int i=0;i<n;i++)
        mat[i]=new QToolButton[n];
    int w=ui->mat_widget->width();
    int h=ui->mat_widget->height();

    int nw=w/n;
    int nh=h/n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            mat[i][j].setParent(ui->mat_widget);
            mat[i][j].setFixedSize(nw,nh);
            mat[i][j].move(i*nw,j*nh);
            mat[i][j].setStyleSheet("background-color: rgb(255,255,255)");
            mat[i][j].show();
        }
    Queens(0);
    char str[20];
    sprintf(str,"共有%d种解法",ans.size());
    ui->ans_label->setText(str);
    PaintingQueen();
    delete MaxN;
    MaxN=new QIntValidator(1,ans.size(),this);
    ui->to_Edit->setValidator(MaxN);
    return true;
}

void MainWindow::DeleteMat(){
    if(!mat){
        qDebug()<<"not delete mat"<<endl;
        return;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        mat[i][j].close();
    delete mat;
    mat=NULL;
    qDebug()<<"delete mat"<<endl;
}

void MainWindow::Queens(int i)
{
//    if(i>0) PaintingQueen(i);
    if(i==n)
    {
        std::vector<int> temp;
        for(int j=0;j<n;j++)
            temp.push_back(arr[j]);
        ans.push_back(temp);
        temp.clear();
        // ++cnt;
        return ;
    }
    else
        for(int j = 0; j<n; j++)
        {
            arr[i]=j;//表示皇后放在第i行第j列
            int k;
            for(k=0;k<i;++k)
                if(j==arr[k]||k-arr[k]==i-j||k+arr[k]==i+j)//判断位置是否冲突
                    break;
            if(k==i)
                Queens(i+1);
        }
}

void MainWindow::PaintingQueen(){
    if(cnt<0 || cnt>=ans.size()) return;

    int w=ui->mat_widget->width();
    int h=ui->mat_widget->height();
    int nw=w/n;
    int nh=h/n;

//    if(i-1>n) return;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            mat[i][j].setStyleSheet("background-color: rgb(255,255,255)");
        }
    for(int i=0;i<n;i++){
//        mat[i][ans[cnt][i]].setIcon(QueenIcon);
        mat[i][ans[cnt][i]].setStyleSheet("background-color: rgb(125,225,225)");
        mat[i][ans[cnt][i]].setIconSize(QSize(nw,nh));
    }

    char str[20];
    sprintf(str,"第%d种解法",cnt+1);
    ui->now_label->setText(str);
}

void MainWindow::PaintingPreQueen(){
    if(cnt-1<0 || cnt-1>=ans.size()) cnt=ans.size();
    cnt--;
    PaintingQueen();
}

void MainWindow::PaintingNextQueen(){
    if(cnt+1<0 || cnt+1>=ans.size()) cnt=-1;
    cnt++;
    PaintingQueen();
}

void MainWindow::PaintingNQueen(){
    int n=ui->to_Edit->text().toInt();
    n--;
    if(n<0 || n>=ans.size()){
        QMessageBox::critical(this,"错误","请输入有效数值！！！");
        return ;
    }
    cnt=n;
    PaintingQueen();
}
