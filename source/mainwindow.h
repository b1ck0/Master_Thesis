#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QTextStream>

class point{
public:
    double x;
    double y;
    double z;
};

class material{
public:
    double MATNO;
    double YOUNG;
    double POISS;
    double RHO;
};

class thinknesses{
public:
    double GEONO;
    double TH;
};

class xtractElement{
public:
    QList<point> nodes; // coordinates of the nodes
    double eNumber;
    int flag; // used for technical issues
    double number; // element
    QString parent; // superelement
    double sigmax, sigmay, tauxy, vonmises, unitycheck ;  // stress components
    int bResult; // 0 - safe , 1 buckling, 2 buckling pressure
    material materialProps;
    thinknesses thinkness;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_Browse_input_sigma_x_clicked();

    void on_Browse_input_Fem_clicked();

    void on_Browse_result_clicked();

    void on_Calculate_clicked();

    void on_pushButton_addpanel_clicked();

    void on_pushButton_removepanel_clicked();

    void on_Browse_input_sigma_y_clicked();

    void on_Browse_input_tau_xy_clicked();

    void on_actionExport_Panel_Data_triggered();

    void on_actionNew_Analysis_triggered();

    void on_actionImport_Panel_Data_triggered();

    void on_actionExit_2_triggered();

private:
    Ui::MainWindow *ui;
    void readListFile(QString, QString,QString, QList<xtractElement> elements, QList<xtractElement> &elements_new);
    double calculateAverage(double, double, double, double);
    void Analytical(double, double, double, double, QList<xtractElement>, QList<xtractElement> &);
    void DNV(double, double, double, double, QList<xtractElement>, QList<xtractElement> &);
    void ABS(double, double, double, double, QList<xtractElement>, QList<xtractElement> &);
    void ABS_ULS(double, double, double, double, QList<xtractElement>, QList<xtractElement> &);
    void writeLine(QTextStream&, xtractElement);
    void fillTable(QList<xtractElement>);
    void writeHeader(QTextStream &out);
    void readFemFile(QString, QList<xtractElement> &);
    void assignElementProperties(QList<xtractElement> &, QList<thinknesses> &,QList<material> &);
    void readMaterialProperties(QString, QList<material> &);
    void readQuadElements(QString filename, QList<xtractElement> &);
    void readthikness(QString, QList<thinknesses> &);
    void readElementProperties(QString, QList<xtractElement> &);
    void calculateBuckling(QList<xtractElement>);
    void writeResults(QString,QList<xtractElement>);
    void writeFem(QString,QString, QList<xtractElement>);
};

#endif // MAINWINDOW_H
