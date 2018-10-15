#include "MRHall.h"
#include "ui_MRHall.h"
#include "QFileDialog"
#include "locale"
#include "fstream"
#include "iostream"
#include "QStringList"
#include "QString"
#include "qcustomplot.h"

using namespace std;
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_FileSelect_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Open File"), tr("Text File (.txt)"));
    ui->Filetextpath->setText(fileName);
}

void Widget::on_Selectdestinationbutton_clicked()
{
    destName = QFileDialog::getSaveFileName(this,tr("Open File"), tr("Text File (.txt)"));
    ui->Filetextpathdest->setText(destName);
}

void Widget::on_RunProgram_clicked()
{
    ifstream ip(fileName.toStdString() );
    ofstream outFile;
    outFile.open(destName.toStdString());

    if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';
    ip.ignore(48);
    string x;
    string y;

    while(getline(ip,x,',')){
      getline(ip,y,'\n');
      ltrim(y);
      if(y!="")
       outFile <<x<<","<< y << '\n';
    }
    ip.close();
    outFile.close();
}

void Widget::on_ShowGraph_clicked()
{
    ifstream ip(fileName.toStdString() );
    ofstream outFile;
    ofstream imFilex;
    ofstream imFiley;
    outFile.open(destName.toStdString());
    imFilex.open("/Users/10Exahertz/Documents/Hall Data/Test/datax.txt");
    imFiley.open("/Users/10Exahertz/Documents/Hall Data/Test/datay.txt");

    if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';
    ip.ignore(42);
    string x;
    string y;

    while(getline(ip,x,',')){
      getline(ip,y,'\n');
      ltrim(y);
      if(y!="")
       outFile <<x<<","<< y << '\n';
    }
    ip.close();
    outFile.close();
}

void Widget::on_pushButton_clicked()
{      ifstream ip(destName.toStdString());
       ofstream imFilex;
       ofstream imFiley;
       imFilex.open("datax.txt");
       imFiley.open("datay.txt");

       if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';
       string c;
       string d;
       while(getline(ip,c,',')){
         getline(ip,d,'\n');
         if(d!="")
             imFilex << c << '\n';
             imFiley << d << '\n';
       }
       ip.close();
       imFilex.close();
       imFiley.close();

    QVector<double> v, k;
        QFile textFile("datax.txt");
        QFile Dfile("datay.txt");
        if(textFile.open(QIODevice::ReadOnly))
        {

            double d;
            double L;
            QTextStream textStream(&textFile);
            while (!textStream.atEnd()) {
                textStream >> d;
                if(textStream.status() == QTextStream::Ok){
                    v.append(d);

                }
                else
                    break;
            }
            if(Dfile.open(QIODevice::ReadOnly)){
            QTextStream textStream(&Dfile);
            while (!textStream.atEnd()) {
                textStream >> L;
                if(textStream.status() == QTextStream::Ok){
                    k.append(L);

                }
                else
                    break;
            }
            auto size = v.size();
            QVector<double> x(size), y(size);
            for(int i=0; i<size; ++i)
            {
                x[i] = v[i];
                y[i] = k[i];
            }
        ui->customPlot->addGraph();
    // create graph and assign data to it:
    //ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    //ui->customPlot->graph(0)->addData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    //ui->customPlot->xAxis->setRange(0, 20);
    //ui->customPlot->yAxis->setRange(0, 20);
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->customPlot->replot();
}}}




