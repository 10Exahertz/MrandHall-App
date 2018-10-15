#ifndef MRHALL_H
#define MRHALL_H

#include <QWidget>
#include <QVector>
#include <QTextStream>
#include <QFile>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_FileSelect_clicked();

    void on_Selectdestinationbutton_clicked();

    void on_RunProgram_clicked();

    void on_pushButton_clicked();

    void on_ShowGraph_clicked();


private:
    Ui::Widget *ui;
    QString fileName;
    QString destName;
};

#endif // MRHALL_H
