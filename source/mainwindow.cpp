#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <qmath.h>
#include <QDebug>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Analytical(double le, double se, double fy, double p_ext, QList<xtractElement> elements, QList<xtractElement> &newElements){

    //defining buckling stress coefficients for the various cases
    double l = 0.00000;
    double s = 0.00000;

    if( le > se ){
        l = le*1.00000e-3; // converting [ mm ] to [ m ]
        s = se*1.00000e-3; // converting [ mm ] to [ m ]
    } else {
        l = se*1.00000e-3; // converting [ mm ] to [ m ]
        s = le*1.00000e-3; // converting [ mm ] to [ m ]
    }

    double kl = 4.00000; // buckling stress coefficient for longitudinally compressed simply supported plate
    double kt = qPow( (1 + qPow(s/l,2.00000)),2.00000 ); // buckling stress coefficient for transversly compressed siply supported plate
    double ks = 4*qPow(s/l,2.00000)+5.34; // buckling stress coefficient for simply supported plate with shear

    xtractElement temp;

    double sig_x_critical = 0.00000;
    double sig_y_critical = 0.00000;
    double tau_xy_critical = 0.00000;

    double E = 0.00000;
    double thk = 0.00000;
    double nu = 0.00000;

    double sig_x_ext = 0.00000;
    double sig_y_ext = 0.00000;
    double tau_xy_ext = 0.00000;

    double alpha_1 = 0.00000;
    double alpha_2 = 0.00000;
    double alpha_11 = 0.00000;
    double alpha_12 = 0.00000;

    double Cp_x = 0.00000;
    double Cp_y = 0.00000;

    double result = 0.00000;
    int bResult = 0; // 0 - safe , 1 buckling, 2 buckling pressure

    for(long i=0; i<elements.size(); i++){

        E = elements.at(i).materialProps.YOUNG;
        thk = elements.at(i).thinkness.TH;
        nu = elements.at(i).materialProps.POISS;
        if( le > se ){
            sig_x_ext = -1.00000*elements.at(i).sigmax;
            sig_y_ext = -1.00000*elements.at(i).sigmay;
        } else {
            sig_x_ext = -1.00000*elements.at(i).sigmay;
            sig_y_ext = -1.00000*elements.at(i).sigmax;
        }

        tau_xy_ext = -1.00000*elements.at(i).tauxy;

        if(sig_x_ext < 0){
            sig_x_ext = 0;
        }

        if(sig_y_ext < 0){
            sig_y_ext = 0;
        }

        if(tau_xy_ext < 0){
            tau_xy_ext = -1*tau_xy_ext;
        }

        if(p_ext == 0){
            sig_x_critical = kl * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000);
            sig_y_critical = kt * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000);
        } else {
            if( l/s < 2  ){
                Cp_x = 1.00000;
                Cp_y = 1.00000;

                sig_x_critical = Cp_x * kl * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000);
                sig_y_critical = Cp_y * kt * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000);

            } else {
                Cp_x = 1+(1/576)*qPow(p_ext*1e6*qPow(s,4)/E/qPow(thk,4),1.60000);
                Cp_y = 1+(1/160)*qPow(s/l,0.95)*qPow(p_ext*1e6*qPow(s,4)/E/qPow(thk,4),1.75000);

                sig_x_critical = Cp_x * kl * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000);
                sig_y_critical = Cp_y * kt * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000);
            }
        }

        tau_xy_critical = ks * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000);

        if( l/s <= qSqrt(2) ){
            alpha_1 = 1.00000;
            alpha_2 = 1.00000;
        } else {
            alpha_1 = 0.0293 * qPow(l/s,3) - 0.3364 * qPow(l/s,2) + 1.5854 * qPow(l/s,1) - 1.0596;
            alpha_2 = 0.0049 * qPow(l/s,3) - 0.1183 * qPow(l/s,2) + 0.6153 * qPow(l/s,1) + 0.8522;
        }

        if( l/s <= 3.2){
            alpha_11 = 0.6153 * qPow(l/s,1) + 1.082;
        } else {
            alpha_11 = 2.90;
        }

        if( l/s <= 2 ){
            alpha_12 = 0.10 * qPow(l/s,1) + 1.90 ;
        } else {
            if( l/s <= 6 ){
                alpha_12 = 0.70 * qPow(l/s,1) +0.70;
            } else {
                alpha_12 = 4.90;
            }
        }

        result =
  qPow( sig_x_ext / ( sig_x_critical * ( 1 - qPow( tau_xy_ext/tau_xy_critical, alpha_11 ) ) ) , alpha_1 ) +
  qPow( sig_y_ext / ( sig_y_critical * ( 1 - qPow( tau_xy_ext/tau_xy_critical, alpha_12 ) ) ) , alpha_2 ) ;

        if( result >= 1 ){
            bResult = 1; // 0 - safe , 1 buckling
        } else {
            bResult = 0;
        }

        qDebug() << "l/s: " << l/s << "alpha_1: " << alpha_1 << " alpha_2: " << alpha_2
                 << " alpha_11: " << alpha_11 << " alpha_12: " << alpha_12 << " UC: " << result  ;
        temp.number = elements.at(i).number;
        temp.eNumber = elements.at(i).eNumber;
        temp.bResult = bResult;
        temp.unitycheck = result;
        temp.sigmax = elements.at(i).sigmax;
        temp.sigmay = elements.at(i).sigmay;
        temp.tauxy = elements.at(i).tauxy;
        temp.materialProps.MATNO = elements.at(i).materialProps.MATNO;
        temp.materialProps.POISS = elements.at(i).materialProps.POISS;
        temp.materialProps.RHO = elements.at(i).materialProps.RHO;
        temp.materialProps.YOUNG = elements.at(i).materialProps.YOUNG;
        temp.thinkness.GEONO = elements.at(i).thinkness.GEONO;
        temp.thinkness.TH = elements.at(i).thinkness.TH;

        newElements << temp;
    }

}

void MainWindow::ABS(double le, double se, double fy, double p_ext, QList<xtractElement> elements, QList<xtractElement> &newElements){

    double alpha = 0.00000;
    if(le > se){
       alpha = le/se; // aspect ratio
    } else {
       alpha = le/se; // aspect ratio
    }

    double rec_alpha = 1/alpha/alpha; // substitution
    double Pr = 0.6; // proportional elastic strength for steel
    double C1 = 1.00000; // some safety coefficient
    double C2 = 1.00000; // some safety coefficient
    double eta = 0.00000; // allowable utilization factor / 0.8 for combined loading /
    if(ui->comboBox_load_type->currentText() == "Static Loading"){
        eta = 0.60000;
    } else {
        eta = 0.80000;
    }
    double kappa = 1.00000; // edge shear


    double l = 0.00000; // converted to cm from mm
    double s = 0.00000; // converted to cm from mm

    //after this check l will be the longer edge and s will be the shorter edge
    if(le > se){
        l = le*1e-1; // converted to cm from mm
        s = se*1e-1; // converted to cm from mm
    } else {
        l = se*1e-1; // converted to cm from mm
        s = le*1e-1; // converted to cm from mm
    }


    double E = 0.00000; // Young's Modulus
    double nu = 0.00000; // Poisson
    double thk = 0.00000; // thikness

    double sigma_ext_x = 0.00000; // external longitudinal stress
    double sigma_ext_y = 0.00000; // external transverse stress
    double tau_ext = 0.00000; // external shear stress
    double sigma_j = 0.00000; // Von Mises equivalent stress

    double sigma_cri_x = 0.00000;  // critical longitudinal stress
    double sigma_cri_y = 0.00000; // critical transverse stress
    double tau_cri = 0.00000; // critical shear stess
    double p_cri = 0.00000;  // critical lateral pressure

    double sigma_e_x = 0.00000; // elastic critical longitudinal stress
    double sigma_e_y = 0.00000; // elastic critical transverse stress
    double tau_e = 0.00000; // elastic critical shear stress

    double ksl = C1 * ( (8.4)/(kappa+1.1) ); // buckling stress coefficient for longitudinal
    double kst = C2 * ( qPow(1+rec_alpha,2.00000) * (1.675-0.675*kappa) ); // buckling stress coefficient for transverse
    double kss = (4*qPow(s/l,2.00000)+5.34)*C1;

    double sigma_0 = fy*1e2; // permisssible buckling stress for axial
    double tau_0 = (fy*1e2/qSqrt(3)); // permissible buckling stress for shear

    double result = 0; // unity check
    int bResult = 0; // boolean result

    for(long i=0; i<elements.size(); i++){
        xtractElement temp;

        E = elements.at(i).materialProps.YOUNG*0.0001; // converted to N/cm^2 from Pa
        thk = elements.at(i).thinkness.TH*100; // converted to cm from m
        nu = elements.at(i).materialProps.POISS;


        if(le > se){
            sigma_ext_x = -1.00*elements.at(i).sigmax*0.0001; // converted to N/cm^2 from Pa
            sigma_ext_y = -1.00*elements.at(i).sigmay*0.0001; // converted to N/cm^2 from Pa
        } else {
            sigma_ext_x = -1.00*elements.at(i).sigmay*0.0001; // converted to N/cm^2 from Pa
            sigma_ext_y = -1.00*elements.at(i).sigmax*0.0001; // converted to N/cm^2 from Pa
        }

        tau_ext = elements.at(i).tauxy*0.0001; // converted to N/cm^2 from Pa
        sigma_j = qSqrt( qPow(sigma_ext_x, 2) - sigma_ext_x*sigma_ext_y + qPow(sigma_ext_y, 2) + 3*qPow(tau_ext, 2) ); // in N/cm^2

        sigma_e_x = ksl * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000); // in N/cm^2
        sigma_e_y = kst * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000); // in N/cm^2
        tau_e = kss * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000); // in N/cm^2

        if( sigma_0*Pr >= sigma_e_x ){
            sigma_cri_x = sigma_e_x;
        } else {
            sigma_cri_x = sigma_0*( 1 - Pr*( 1 - Pr )*(sigma_0/sigma_e_x) );
        }

        if( sigma_0*Pr >= sigma_e_y ){
            sigma_cri_y = sigma_e_y;
        } else {
            sigma_cri_y = sigma_0*( 1 - Pr*( 1 - Pr )*(sigma_0/sigma_e_y) );
        }

        if( tau_0*Pr >= tau_e ){
            tau_cri = tau_e;
        } else {
            tau_cri = tau_0*( 1 - Pr*( 1 - Pr )*(tau_0/tau_e) );
        }

        result = qPow( (sigma_ext_x/(eta*sigma_cri_x)),2.00000 ) + qPow( (sigma_ext_y/(eta*sigma_cri_y)),2.00000 ) + qPow( (tau_ext/(eta*tau_cri)),2.00000 );
        p_cri = 4*eta*sigma_0*qPow((thk/s),2.00000)*(1+(1/(qPow(alpha,2.00000))))*qSqrt(1-qPow( (sigma_j/sigma_0),2.00000 ));

        if(result <= 1.00000){
            bResult = 0;
        }

        if(result > 1.00000){
            bResult = 1;
        }

        if(p_ext*1e2 > p_cri){
            bResult = 2;
        }

        temp.number = elements.at(i).number;
        temp.eNumber = elements.at(i).eNumber;
        temp.bResult = bResult;
        temp.unitycheck = result;
        temp.sigmax = elements.at(i).sigmax;
        temp.sigmay = elements.at(i).sigmay;
        temp.tauxy = elements.at(i).tauxy;
        temp.materialProps.MATNO = elements.at(i).materialProps.MATNO;
        temp.materialProps.POISS = elements.at(i).materialProps.POISS;
        temp.materialProps.RHO = elements.at(i).materialProps.RHO;
        temp.materialProps.YOUNG = elements.at(i).materialProps.YOUNG;
        temp.thinkness.GEONO = elements.at(i).thinkness.GEONO;
        temp.thinkness.TH = elements.at(i).thinkness.TH;

        newElements << temp;
    }

    qDebug() << "number of elements checked for buckling by ABS" << newElements.size();
}

void MainWindow::ABS_ULS(double le, double se, double fy, double p_ext, QList<xtractElement> elements, QList<xtractElement> &newElements){

    double alpha = 0.00000;
    if(le > se){
       alpha = le/se; // aspect ratio
    } else {
       alpha = le/se; // aspect ratio
    }

    double rec_alpha = 1/alpha/alpha; // substitution
    double Pr = 0.6; // proportional elastic strength for steel
    double C1 = 1.00000; // some safety coefficient
    double C2 = 1.00000; // some safety coefficient
    double eta = 0.00000; // allowable utilization factor / 0.8 for combined loading /
    if(ui->comboBox_load_type->currentText() == "Static Loading"){
        eta = 0.60000;
    } else {
        eta = 0.80000;
    }
    double kappa = 1.00000; // edge shear


    double l = 0.00000; // converted to cm from mm
    double s = 0.00000; // converted to cm from mm

    //after this check l will be the longer edge and s will be the shorter edge
    if(le > se){
        l = le*1e-1; // converted to cm from mm
        s = se*1e-1; // converted to cm from mm
    } else {
        l = se*1e-1; // converted to cm from mm
        s = le*1e-1; // converted to cm from mm
    }


    double E = 0.00000; // Young's Modulus
    double nu = 0.00000; // Poisson
    double thk = 0.00000; // thikness

    double sigma_ext_x = 0.00000; // external longitudinal stress
    double sigma_ext_y = 0.00000; // external transverse stress
    double tau_ext = 0.00000; // external shear stress
    double sigma_j = 0.00000; // Von Mises equivalent stress

    double sigma_cri_x = 0.00000;  // critical longitudinal stress
    double sigma_cri_y = 0.00000; // critical transverse stress
    double tau_cri = 0.00000; // critical shear stess
    double p_cri = 0.00000;  // critical lateral pressure

    double sigma_e_x = 0.00000; // elastic critical longitudinal stress
    double sigma_e_y = 0.00000; // elastic critical transverse stress
    double tau_e = 0.00000; // elastic critical shear stress

    double ksl = C1 * ( (8.4)/(kappa+1.1) ); // buckling stress coefficient for longitudinal
    double kst = C2 * ( qPow(1+rec_alpha,2.00000) * (1.675-0.675*kappa) ); // buckling stress coefficient for transverse
    double kss = (4*qPow(s/l,2.00000)+5.34)*C1;

    double sigma_0 = fy*1e2; // permisssible buckling stress for axial
    double tau_0 = (fy*1e2/qSqrt(3)); // permissible buckling stress for shear

    double result = 0; // unity check
    int bResult = 0; // boolean result

    double fi = 0.00000;
    double betha = 0.00000;

    double sigma_U_x = 0.00000;
    double sigma_U_y = 0.00000;
    double tau_U = 0.00000;

    double CX = 0.00000;
    double CY = 0.00000;

    for(long i=0; i<elements.size(); i++){
        xtractElement temp;

        E = elements.at(i).materialProps.YOUNG*0.0001; // converted to N/cm^2 from Pa
        thk = elements.at(i).thinkness.TH*100; // converted to cm from m
        nu = elements.at(i).materialProps.POISS;

        betha = (s/thk)*qSqrt(sigma_0/E);
        fi = 1 - betha/2;

        if(betha > 1){
            CX = 2/betha - 1/betha/betha;
        } else {
            CX = 1;
        }
        CY = CX*(s/l)+0.1*(1-s/l)*qPow((1+1/betha/betha),2);
        if(CY > 1){
            CY = 1;
        }

        sigma_U_x = CX*sigma_0;
        sigma_U_y = CY*sigma_0;

        if(le > se){
            sigma_ext_x = -1.00*elements.at(i).sigmax*0.0001; // converted to N/cm^2 from Pa
            sigma_ext_y = -1.00*elements.at(i).sigmay*0.0001; // converted to N/cm^2 from Pa
        } else {
            sigma_ext_x = -1.00*elements.at(i).sigmay*0.0001; // converted to N/cm^2 from Pa
            sigma_ext_y = -1.00*elements.at(i).sigmax*0.0001; // converted to N/cm^2 from Pa
        }

        tau_ext = elements.at(i).tauxy*0.0001; // converted to N/cm^2 from Pa
        sigma_j = qSqrt( qPow(sigma_ext_x, 2) - sigma_ext_x*sigma_ext_y + qPow(sigma_ext_y, 2) + 3*qPow(tau_ext, 2) ); // in N/cm^2

        sigma_e_x = ksl * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000); // in N/cm^2
        sigma_e_y = kst * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000); // in N/cm^2
        tau_e = kss * ( (qPow(3.1415,2.00000) * E)/(12*(1 - qPow(nu,2.00000))) )* qPow(thk/s,2.00000); // in N/cm^2

        if( sigma_0*Pr >= sigma_e_x ){
            sigma_cri_x = sigma_e_x;
        } else {
            sigma_cri_x = sigma_0*( 1 - Pr*( 1 - Pr )*(sigma_0/sigma_e_x) );
        }

        if(sigma_cri_x > sigma_U_x){
            sigma_U_x = sigma_cri_x;
        }

        if(sigma_cri_y > sigma_U_y){
            sigma_U_y = sigma_cri_y;
        }

        if( sigma_0*Pr >= sigma_e_y ){
            sigma_cri_y = sigma_e_y;
        } else {
            sigma_cri_y = sigma_0*( 1 - Pr*( 1 - Pr )*(sigma_0/sigma_e_y) );
        }
        if( tau_0*Pr >= tau_e ){
            tau_cri = tau_e;
        } else {
            tau_cri = tau_0*( 1 - Pr*( 1 - Pr )*(tau_0/tau_e) );
        }

        tau_U = tau_cri + 0.5*(sigma_0 - qSqrt(3)*tau_cri)/qSqrt(1+alpha+alpha*alpha);

        if(tau_cri > tau_U){
            tau_U = tau_cri;
        }

        result = qPow( (sigma_ext_x/(eta*sigma_U_x)),2.00000 ) + qPow( (sigma_ext_y/(eta*sigma_U_y)),2.00000 ) + qPow( (tau_ext/(eta*tau_U)),2.00000 ) - fi*(sigma_ext_x/eta/sigma_U_x)*(sigma_ext_y/eta/sigma_U_y);
        p_cri = 4*eta*sigma_0*qPow((thk/s),2.00000)*(1+(1/(qPow(alpha,2.00000))))*qSqrt(1-qPow( (sigma_j/sigma_0),2.00000 ));

        if(result <= 1.00000){
            bResult = 0;
        }

        if(result > 1.00000){
            bResult = 1;
        }

        if(p_ext*1e2 > p_cri){
            bResult = 2;
        }

        temp.number = elements.at(i).number;
        temp.eNumber = elements.at(i).eNumber;
        temp.bResult = bResult;
        temp.unitycheck = result;
        temp.sigmax = elements.at(i).sigmax;
        temp.sigmay = elements.at(i).sigmay;
        temp.tauxy = elements.at(i).tauxy;
        temp.materialProps.MATNO = elements.at(i).materialProps.MATNO;
        temp.materialProps.POISS = elements.at(i).materialProps.POISS;
        temp.materialProps.RHO = elements.at(i).materialProps.RHO;
        temp.materialProps.YOUNG = elements.at(i).materialProps.YOUNG;
        temp.thinkness.GEONO = elements.at(i).thinkness.GEONO;
        temp.thinkness.TH = elements.at(i).thinkness.TH;

        newElements << temp;
    }

    qDebug() << "number of elements checked for buckling by ABS" << newElements.size();
}

void MainWindow::DNV(double l, double s, double fy, double p_ext, QList<xtractElement> elements, QList<xtractElement> &newElements){

    //defining some constants
    double gamma_m = 1.15000; //resulting material factor

    //defining variables
    xtractElement temp;
    //------------------------------------------------------
    double length = 0.00000;
    double width = 0.00000;

    // after this check length will be the longer dimension and width will be the shorter one
    if(l > s){
        length = l; // length of the panel
        width = s; // width of the panel
    } else {
        length = s; // length of the panel
        width = l; // width of the panel
    }
    double thk = 0.00000; // thikness of the panel
    double E = 0.00000; // Young's modulus of the panel
    double sig_x_ext = 0.00000; // external stress along x direction
    double sig_y_ext = 0.00000; // external stress along y direction
    double tau_ext = 0.00000; // external stress along xy direction
    //------------------------------------------------------
    double lambda_p = 0.00000; // plate slenderness for longitudinal compression
    double Cx = 0.00000; // buckling factor for stresses in x-direction
    //------------------------------------------------------
    double sig_x_rd = 0.00000; // permissible stress along x direction by DNV rules
    //------------------------------------------------------
    double lambda_c = 0.00000;
    //------------------------------------------------------
    double mu = 0.00000; // geometric parameter
    double k = 0.00000;
    double ha = 0.00000;
    double kp = 0.00000; // reduction factor due to lateral load
    double sig_y_r = 0.00000;
    double sig_y_rd = 0.00000; // permissible stress along y direction by DNV rules
    //------------------------------------------------------
    double kl = 0.00000;
    double lambda_w = 0.00000;
    double Cte = 0.00000;
    double Ct = 0.00000;
    double tau_rd = 0.00000;
    double tau_rd_1 = 0.00000;
    double tau_rd_2 = 0.00000;// permissible stress along xy direction by DNV rules
    //------------------------------------------------------
    double sig_j_ext = 0.00000; // external Von Mises equvalent stress
    double psi_x = 0.00000;
    double psi_y = 0.00000;
    double p_rd = 0.00000; // permissible lateral stress by DNV rules
    //------------------------------------------------------
    int return_res = 0.00000; // 0 - safe , 1 buckling, 2 buckling pressure
    double ci = 0.00000;
    double result = 0.00000;

    //------------------------------------------------------
    double stress_coefficient = 1.00000e-6; // coefficient to transform stress in [ MPa ]
    double thikness_coefficient = 1.00000e3; // coeficient to transform thinkness in [ mm ]
    double young_coefficient = 1.00000e-6; // coefficient to transform young modulus in [ MPa ]

    for(long i=0; i<elements.size(); i++){

        //after this check sig_x will be the stress on the longer edge
        if(l > s){
            sig_x_ext = -1.00000*elements.at(i).sigmax*stress_coefficient; // in DNV rules tension is negative and compression is positive
            sig_y_ext = -1.00000*elements.at(i).sigmay*stress_coefficient; // in DNV rules tension is negative and compression is positive
        } else {
            sig_x_ext = -1.00000*elements.at(i).sigmay*stress_coefficient; // in DNV rules tension is negative and compression is positive
            sig_y_ext = -1.00000*elements.at(i).sigmax*stress_coefficient; // in DNV rules tension is negative and compression is positive
        }

        tau_ext = elements.at(i).tauxy*stress_coefficient;
        E = elements.at(i).materialProps.YOUNG*young_coefficient;
        thk = elements.at(i).thinkness.TH*thikness_coefficient;
        //--------------------------------------------------
        lambda_p = 0.52500*(width/thk)*qSqrt(fy/E);
        if(lambda_p <= 0.67300){
            Cx = 1.00000;
        } else {
            Cx = (lambda_p-0.22000)/qPow(lambda_p,2.00000);
        }
        sig_x_rd = Cx*(fy/gamma_m);
        //--------------------------------------------------
        lambda_c = 1.10000*(width/thk)*qSqrt(fy/E);
        mu = 0.21000*(lambda_c - 0.20000);
        if(lambda_c <= 0.20000){
            k = 1.00000;
        } else {
            if(lambda_c < 2.00000 && lambda_c > 0.20000){
                k = (1.00000/(2.00000*qPow(lambda_c,2.00000)))*(1.00000+mu+qPow(lambda_c,2.00000)
                                              -qSqrt( qPow((1.00000+mu+qPow(lambda_c,2.00000)),2.00000)-4.00000*qPow(lambda_c,2.00000) ));
            } else {
                k = (1.00000/(2.00000*qPow(lambda_c,2.00000)))+0.07000;
            }
        }
        ha = 0.05000*(width/thk)-0.75000;
        if(ha < 0.00000){
            ha = 0.00000;
        }
        if(p_ext <= (2.00000*qPow(thk/width,2.00000)*fy) ){
            kp = 1.00000;
        } else {
            kp = 1.00000-ha*( (p_ext/fy) - 2.00000*qPow(thk/width,2.00000) );
        }
        if(kp < 0.00000){
            kp = 0.00000;
        }
        sig_y_r = ( (1.30000*thk/length)*qSqrt(E/fy) + k*(1.00000 - (1.30000*thk/length)*qSqrt(E/fy) ))*fy*kp;
        sig_y_rd = sig_y_r/gamma_m;
        //-------------------------------------------------
        if(length >= width){
            kl = 5.34000 + 4.00000*qPow(width/length,2.00000);
        } else {
            kl = 5.34000*qPow(width/length,2.00000) + 4.00000;
        }
        lambda_w = 0.79500* (width/thk) * qSqrt(fy/(E*kl));
        if(lambda_w <= 0.80000){
            Cte = 1.00000;
        } else {
            if(lambda_w <= 1.25000 && lambda_w > 0.80000){
                Cte = 1.00000 - 0.80000*(lambda_w - 0.80000);
            } else {
                Cte = 1.00000/qPow(lambda_w,2.00000);
            }
        }
        tau_rd_2 = (Cte/gamma_m)*(fy/qSqrt(3.00000));
        if(lambda_w <= 0.80000){
            Ct = 1.00000;
        } else {
            if(lambda_w <= 1.20000 && lambda_w > 0.80000){
                Ct = 1.00000 - 0.62500*(lambda_w - 0.80000);
            } else {
                Ct = 0.90000/lambda_w;
            }
        }
        tau_rd_1 = (Ct/gamma_m)*(fy/qSqrt(3.00000));
        //-------------------------------------------------
        sig_j_ext = qSqrt( qPow(sig_x_ext,2.00000) + qPow(sig_y_ext,2.00000) - sig_x_ext*sig_y_ext + 3.00000* qPow(tau_ext,2.00000) );
        psi_x = ( (1.00000 - qPow(sig_j_ext/fy,2.00000))/( qSqrt(1.00000 - (3.00000/4.00000)*qPow(sig_y_ext/fy,2.00000) - 3.00000*qPow(tau_ext/fy,2.00000) ) ));
        psi_y = ( (1.00000 - qPow(sig_j_ext/fy,2.00000))/( qSqrt(1.00000 - (3.00000/4.00000)*qPow(sig_x_ext/fy,2.00000) - 3.00000*qPow(tau_ext/fy,2.00000) ) ));
        p_rd = 4.00000*(fy/gamma_m)*qPow(thk/width,2.00000)*( psi_y + qPow(width/length,2.00000)*psi_x );
        //-------------------------------------------------
        if(width/thk <= 120.00000){
            ci = 1.00000 - (width/(120.00000*thk));
        } else {
            ci = 0.00000;
        }
        if( (sig_x_ext < 0.00000 || sig_y_ext < 0.00000) || (sig_x_ext < 0.00000 && sig_y_ext < 0.00000)){
            ci = 0.00000;
        }
        if(sig_x_ext < 0.00000){
            sig_x_rd = -1.00000*fy/gamma_m;
        }
        if(sig_y_ext < 0.00000){
            sig_y_rd = -1.00000*fy/gamma_m;
        }
        if(sig_y_ext <= 0.00000){
            tau_rd = tau_rd_1;
        } else {
            tau_rd = tau_rd_2;
        }
        result = qPow(sig_x_ext/sig_x_rd,2.00000) + qPow(sig_y_ext/sig_y_rd,2.00000)- ci*(sig_x_ext/sig_x_rd)*(sig_y_ext/sig_y_rd) + qPow(tau_ext/tau_rd,2.00000);
        if(result <= 1.00000){
            return_res = 0; // buckling safe
        }
        if(result > 1.00000){
            return_res = 1; // buckling occurs due to biaxially load plus shear load
        }
        if(p_rd < p_ext){
            return_res = 2; //buckling occurs due to lateral load
        }

        temp.number = elements.at(i).number;
        temp.eNumber = elements.at(i).eNumber;
        temp.parent = elements.at(i).parent;
        temp.sigmax = elements.at(i).sigmax;
        temp.sigmay = elements.at(i).sigmay;
        temp.tauxy = elements.at(i).tauxy;
        temp.materialProps.MATNO = elements.at(i).materialProps.MATNO;
        temp.materialProps.POISS = elements.at(i).materialProps.POISS;
        temp.materialProps.RHO = elements.at(i).materialProps.RHO;
        temp.materialProps.YOUNG = elements.at(i).materialProps.YOUNG;
        temp.thinkness.GEONO = elements.at(i).thinkness.GEONO;
        temp.thinkness.TH = elements.at(i).thinkness.TH;
        temp.bResult = return_res;
        temp.unitycheck = result;

        newElements << temp;
    }

    qDebug() << "number of elements checked for buckling by DNV" << newElements.size();
}

double MainWindow::calculateAverage(double a1, double a2, double a3, double a4){
    if(a4 != 0.00000){
        return (a1+a2+a3+a4)/4.00000;
    } else {
        return (a1+a2+a3)/3.00000;
    }

}

void MainWindow::readListFile(QString listfile, QString listfile1, QString listfile2,
                              QList<xtractElement> elements, QList<xtractElement> &elements_new){

    QList<xtractElement> e1;

    QList<QPair<double, double> > s_x;
    QList<QPair<double, double> > s_y;
    QList<QPair<double, double> > t_xy;

    double junk = 0.00000;

    xtractElement temp;

    //------------------------------------------------------ reading sigma-x from third list file
    QFile file(listfile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QStringList list2;
        QString line = in.readLine();
        QStringList list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++){
            if(list.at(i) != ""){
                list2 << list.at(i);
            }
        }
        if(list2.size() == 6){
            junk = calculateAverage(list2.at(2).toDouble(),list2.at(3).toDouble(),
                list2.at(4).toDouble(),list2.at(5).toDouble());
        } else {
            junk = calculateAverage(list2.at(2).toDouble(),list2.at(3).toDouble(),
                list2.at(4).toDouble(),0);
        }
        s_x.append(qMakePair(list2.at(1).toDouble(),junk ));
    }

    file.close();

    qDebug() << "=========== s-x elements:" << s_x.size();

    //------------------------------------------------------ reading sigma-y from third list file
    QFile file1(listfile1);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in1(&file1);
    while (!in1.atEnd()) {
        QStringList list2;
        QString line = in1.readLine();
        QStringList list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++){
            if(list.at(i) != ""){
                list2 << list.at(i);
            }
        }
        if(list2.size() == 6){
            junk = calculateAverage(list2.at(2).toDouble(),list2.at(3).toDouble(),
                list2.at(4).toDouble(),list2.at(5).toDouble());
        } else {
            junk = calculateAverage(list2.at(2).toDouble(),list2.at(3).toDouble(),
                list2.at(4).toDouble(),0);
        }
        s_y.append(qMakePair(list2.at(1).toDouble(),junk ));
    }

    file1.close();

    qDebug() << "=========== s-y elements:" << s_y.size();

    //------------------------------------------------------ reading tau_xy from third list file
    QFile file2(listfile2);
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in2(&file2);
    while (!in2.atEnd()) {
        QStringList list2;
        QString line = in2.readLine();
        QStringList list = line.split(" ", QString::SkipEmptyParts);
        for(int i=0;i<list.size();i++){
            if(list.at(i) != ""){
                list2 << list.at(i);
            }
        }
        if(list2.size() == 6){
            junk = calculateAverage(list2.at(2).toDouble(),list2.at(3).toDouble(),
                list2.at(4).toDouble(),list2.at(5).toDouble());
        } else {
            junk = calculateAverage(list2.at(2).toDouble(),list2.at(3).toDouble(),
                list2.at(4).toDouble(),0);
        }
        t_xy.append(qMakePair(list2.at(1).toDouble(),junk ));
    }

    file2.close();

    qDebug() << "=========== t-xy elements:" << t_xy.size();

    for(int i=0; i<s_x.size(); i++){
        temp.sigmax = s_x.at(i).second;
        temp.sigmay = s_y.at(i).second;
        temp.tauxy = t_xy.at(i).second;
        temp.eNumber = s_x.at(i).first;

        e1 << temp;
    }

    qDebug() << "===== number of elements read from list file:" << e1.size();
    // combining the elements from the list file and the FEM file in one single array "elements_new",
    // which array is to be used in the actual Buckling calculation
    for(int i=0; i<e1.size(); i++){
        for(int j=0; j<elements.size(); j++){
            if( e1.at(i).eNumber == elements.at(j).eNumber){
                temp.number = elements.at(j).number;
                temp.eNumber = e1.at(i).eNumber;

                temp.sigmax = e1.at(i).sigmax;
                temp.sigmay = e1.at(i).sigmay;
                temp.tauxy = e1.at(i).tauxy;

                temp.materialProps.MATNO = elements.at(j).materialProps.MATNO;
                temp.materialProps.POISS = elements.at(j).materialProps.POISS;
                temp.materialProps.RHO = elements.at(j).materialProps.RHO;
                temp.materialProps.YOUNG = elements.at(j).materialProps.YOUNG;

                temp.thinkness.GEONO = elements.at(j).thinkness.GEONO;
                temp.thinkness.TH = elements.at(j).thinkness.TH;

                elements_new << temp;
                break;
            } else {
                continue;
            }
        }
    }

    qDebug() << "===== number of elements with loads and properties:" << elements_new.size();
}

void MainWindow::assignElementProperties(QList<xtractElement> &GELMNT1, QList<thinknesses> &GELTH,
                                         QList<material> &MISOSEL){
   xtractElement temp;
   do{
       for(int j=0; j<GELTH.size(); j++){
           if(GELMNT1.front().thinkness.GEONO == GELTH.at(j).GEONO ){
               temp.number = GELMNT1.front().number;
               temp.eNumber = GELMNT1.front().eNumber;
               temp.materialProps.MATNO = GELMNT1.front().materialProps.MATNO;
               temp.materialProps.POISS = -666;
               temp.thinkness.GEONO = GELTH.at(j).GEONO;
               temp.thinkness.TH = GELTH.at(j).TH;
               GELMNT1.push_back(temp);
               GELMNT1.erase(GELMNT1.begin());
               break;
           } else {
               continue;
           }
       }
   } while(GELMNT1.front().thinkness.TH == -666);

   do{
       for(int k=0; k<MISOSEL.size(); k++){
           if(MISOSEL.at(k).MATNO == GELMNT1.front().materialProps.MATNO){
               temp.number = GELMNT1.front().number;
               temp.eNumber = GELMNT1.front().eNumber;
               temp.materialProps.MATNO = GELMNT1.front().materialProps.MATNO;
               temp.thinkness.GEONO = GELMNT1.front().thinkness.GEONO;
               temp.thinkness.TH = GELMNT1.front().thinkness.TH;
               temp.materialProps.POISS = MISOSEL.at(k).POISS;
               temp.materialProps.RHO = MISOSEL.at(k).RHO;
               temp.materialProps.YOUNG = MISOSEL.at(k).YOUNG;
               temp.flag = 1;
               GELMNT1.push_back(temp);
               GELMNT1.erase(GELMNT1.begin());
               break;
           } else {
               continue;
           }
       }
   }while(GELMNT1.front().materialProps.POISS == -666);
}

void MainWindow::readElementProperties(QString filename, QList<xtractElement> &GELMNT1){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return; //open FEM file
    QTextStream in(&file);
    xtractElement temp;
    QList<xtractElement> elements;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list2,list3;
        QStringList list = line.split(" ");
        for(int i=0;i<list.size();i++){
            if(list.at(i) != ""){
                list2 << list.at(i);
            }
        }
        if(list2.at(0) == "GELREF1"){
            temp.number = list2.at(1).toDouble();
            temp.materialProps.MATNO = list2.at(2).toDouble();
            in.readLine();
            line = in.readLine();
            list = line.split(" ");
            for(int i=0;i<list.size();i++){
                if(list.at(i) != ""){
                    list3 << list.at(i);
                }
            }
            temp.thinkness.GEONO = list3.at(0).toDouble();
            elements.push_back(temp);
        } else {
            continue;
        }
    }
    file.close();

    do{
        for(int j=0; j<elements.size(); j++){
            if(GELMNT1.front().number == elements.at(j).number){
                temp.number = elements.at(j).number;
                temp.eNumber = GELMNT1.front().eNumber;
                temp.vonmises = 0;
                temp.materialProps.MATNO = elements.at(j).materialProps.MATNO;
                temp.thinkness.GEONO = elements.at(j).thinkness.GEONO;
                temp.thinkness.TH = -666;
                GELMNT1.push_back(temp);
                GELMNT1.erase(GELMNT1.begin());
                elements.erase(elements.begin()+j);
                j--;
                break;
            } else {
                continue;
            }
        }
    }while(GELMNT1.front().vonmises == -666);
}

void MainWindow::readFemFile(QString filename, QList<xtractElement> &GELMNT1){

    qDebug() << "reading material properties from FEM file";
    QList<material> MISOSEL;
    readMaterialProperties(filename, MISOSEL); // reads only material properties from FEM File
    qDebug() << "number of material properties: " << MISOSEL.size();

    qDebug() << "reading quad and tri elements from FEM file";
    readQuadElements(filename, GELMNT1); // reads only Quad Shell Elements from FEM File
    qDebug() << "number of quad and tri elements: " << GELMNT1.size();

    QList<thinknesses> GELTH;
    qDebug() << "reading thicknesses from FEM file";
    readthikness(filename, GELTH); // read only thiknesses from FEM file
    qDebug() << "number of thicknesses: " << GELTH.size();

    qDebug() << "reading element properties from FEM file";
    readElementProperties(filename, GELMNT1); //read the properties of the existing elements in GELMNT1
    qDebug() << "number of elements with properties" << GELMNT1.size();

    qDebug() << "assigning properties and thicknesses to elements";
    assignElementProperties(GELMNT1, GELTH, MISOSEL); //assigns all properties to the FEM Elements
                                                      //and also calculates the FEM Elements Dimensions
    qDebug() << "number of elements with assigned properties and thicknessses: " << GELMNT1.size();
}

void MainWindow::readMaterialProperties(QString filename, QList<material> &MISOSEL){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return; //open FEM file
    QTextStream in(&file);
    material simple;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list2;
        QStringList list = line.split(" ");
        for(int i=0;i<list.size();i++){
            if(list.at(i) != ""){
                list2 << list.at(i);
            }
        }
        if(list2[0] == "MISOSEL"){
            simple.MATNO = list2[1].toDouble();
            simple.YOUNG = list2[2].toDouble();
            simple.POISS = list2[3].toDouble();
            simple.RHO = list2[4].toDouble();
            MISOSEL << simple;
        } else {
            continue;
        }
    }
    file.close();
}

void MainWindow::readQuadElements(QString filename, QList<xtractElement> &GELMNT1){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return; //open FEM file
    QTextStream in(&file);
    xtractElement simple;
    in.setRealNumberPrecision(9);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list2;
        QStringList list = line.split(" ");
        for(int i=0;i<list.size();i++){
            if(list.at(i) != ""){
                list2 << list.at(i);
            }
        }

        if(list2.at(0) == "GELMNT1" && list2.at(3).toDouble() == 24.00){
            simple.number = list2.at(2).toDouble();
            simple.eNumber = list2.at(1).toDouble();
            simple.vonmises = -666;
            GELMNT1 << simple;
        } else {
            continue;
        }
    }
    file.close();
}



void MainWindow::readthikness(QString filename, QList<thinknesses> &GELTH){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return; //open FEM file
    QTextStream in(&file);
    thinknesses simple;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list2;
        QStringList list = line.split(" ");
        for(int i=0;i<list.size();i++){
            if(list.at(i) != ""){
                list2 << list.at(i);
            }
        }
        if(list2.at(0) == "GELTH"){
            simple.GEONO = list2.at(1).toDouble() ;
            simple.TH = list2.at(2).toDouble();
            GELTH << simple;
        } else {
            continue;
        }
    }
    file.close();
}

void MainWindow::writeResults(QString fileName,QList<xtractElement> e){
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    out.setRealNumberPrecision(8);
    out << "Element Number" << ";"
        << "Unitycheck"     << ";"
        << "Result"         << ";"
        << "SIGMX"          << ";"
        << "SIGMY"          << ";"
        << "TAUMXY"         << ";"
        << "Thikness"       << ";"
        << "Young Modulus"  << "\n";

    for(long i=0; i< e.size(); i++){
        out << e.at(i).eNumber                << ";"
            << e.at(i).unitycheck             << ";"
            << e.at(i).bResult                << ";"
            << e.at(i).sigmax                 << ";"
            << e.at(i).sigmay                 << ";"
            << e.at(i).tauxy                  << ";"
            << e.at(i).thinkness.TH           << ";"
            << e.at(i).materialProps.YOUNG    << "\n";
    }

    file.close();
}

void MainWindow::writeFem(QString inFileName,QString outFileName, QList<xtractElement> elements){

    //----------------------------------------- getting the numbers of our elements
    QList<long> elementNumbers;
    for(int i=0; i<elements.size(); i++){
        elementNumbers << elements.at(i).number;
    }

    qDebug() << elementNumbers.size();

    //----------------------------------------- reading the number of material properties datatypes
    QFile::remove(outFileName);
    QFile::copy(inFileName,outFileName);
    QFile file(outFileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    QTextStream io(&file);
    QStringList fileContents;
    QList<QPair<double,long> > temp;
    QList<QPair<double,long> > pairs;

    int materialPropertiesCount = 0;
    long iterator = 1;
    QList<long> positions;

    while(!io.atEnd()){
        QString line = io.readLine();
        fileContents << line;
        QStringList tabs = line.split(" ");
        QStringList cleanTabs;
        for(int i=0; i<tabs.size(); i++){
            if(tabs.at(i) != ""){
                cleanTabs << tabs.at(i);
            }
        }
        if(cleanTabs.at(0) == "GELREF1" && elementNumbers.indexOf(cleanTabs.at(1).toDouble()) != -1){
            temp.append(qMakePair(cleanTabs.at(1).toDouble(),iterator));
        }
        if(cleanTabs.at(0) == "MISOSEL"){
            materialPropertiesCount++;
            positions << iterator;
        }
        iterator++;
    }

    qDebug() << temp.size();

    file.close();

    //----------------------------------------------------------------------
    QList<double> numbersOfBuckledElements;

    for(long i=0; i<elements.size(); i++){
        if(elements.at(i).bResult != 0){
            numbersOfBuckledElements << elements.at(i).number;
        }
    }

    qDebug() << numbersOfBuckledElements.size();
    if(numbersOfBuckledElements.size() == 0){
        return;
    }

    for(long i=0; i<numbersOfBuckledElements.size(); i++){
        for(long j=0; j<temp.size(); j++){
            if(numbersOfBuckledElements.at(i) == temp.at(j).first){
                pairs << temp.at(j);
            }
        }
    }

    //----------------------------------------- adding new material property

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }

    QTextStream out(&file);
    QString linesForIsert = "TEXT     5.00000000e+000 " + QString::number(materialPropertiesCount+65, 'e', 8) +
            "  1.00000000e+000 7.20000000e+001\n        buckled\nMISOSEL  " + QString::number(materialPropertiesCount+65, 'e', 8) +
            "  2.05999997e+011 3.00000012e-001 1.00000005e-003\n         0.00000000e+000 0.00000000e+000\n";
    iterator = 1;

    for(long i=0; i<fileContents.size(); i++){
        if(i != (positions.at(materialPropertiesCount-1)+1)){
            out << fileContents.at(i) << "\n";
        } else {
            out << linesForIsert;
            out << fileContents.at(i) << "\n";
        }
    }

    file.close();

    //----------------------------------------- changing material properties of our elements
    fileContents.clear();

            //--------------------------------- reading all file contents ( again / after been modified )
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }

    QTextStream in2(&file);
    while(!in2.atEnd()){
        QString line = in2.readLine();
        fileContents << line;
    }
    file.close();

           //---------------------------------- changing material properties in the QStringList

    do{
        double position = pairs.front().second;
        QString line = fileContents.at(position-1);
        QStringList tabs = line.split(" ");
        QStringList cleanTabs;
        for(int i=0; i<tabs.size(); i++){
            if(tabs.at(i) != ""){
                cleanTabs << tabs.at(i);
            }
        }

        QString new_line ="GELREF1  " + QString::number(pairs.front().first, 'e', 8) +"  "
                + QString::number(materialPropertiesCount+65,'e',8)
                +"  0.00000000e+000 0.00000000e+000";

        fileContents.erase(fileContents.begin()+position-1);
        fileContents.insert(position-1, new_line);

        pairs.erase(pairs.begin());

    }while(pairs.size() != 0);

        //---------------------------------- writting to FEM File

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QTextStream out2(&file);
    for(long i=0; i<fileContents.size(); i++){
        out2 << fileContents.at(i) << "\n";
    }
}

void MainWindow::calculateBuckling(QList<xtractElement> GELMNT1){
    QString CS = ui->comboBox_cs->currentText(); // defining of the classification society
    int numberOfPanels = ui->comboBox_panels->count(); // reading the number of typical panels
    QString fileName;
    QString fileName2;
    int l,s;

    for(int i=0; i<numberOfPanels; i++){
        QList<xtractElement> e1,e2;
        QString panelName = ui->comboBox_panels->itemText(i);
        QStringList dimensions = panelName.split("x",QString::SkipEmptyParts);
        l = dimensions.at(0).toDouble();
        s = dimensions.at(1).toDouble();
        qDebug() << l << " x " << s ;
        if(CS == "Det Norske Veritas"){
            DNV(l,s,ui->lineEdit_fy->text().toDouble(),ui->lineEdit_p->text().toDouble(), GELMNT1, e1);
            fileName = ui->filePath_result->text() + "/Buckling-results-DNV-" + ui->comboBox_panels->itemText(i) + ".csv";
            writeResults(fileName, e1);
            fileName2 = ui->filePath_result->text() + "/Buckling-results-DNV-" + ui->comboBox_panels->itemText(i)+ ".FEM";
            writeFem(ui->filePath_fem->text(), fileName2, e1);

            DNV(s,l,ui->lineEdit_fy->text().toDouble(),ui->lineEdit_p->text().toDouble(), GELMNT1, e2);
            fileName = ui->filePath_result->text() + "/Buckling-results-DNV-" + ui->comboBox_panels->itemText(i) + "-reversed.csv";
            writeResults(fileName, e2);

            fileName2 = ui->filePath_result->text() + "/Buckling-results-DNV-" + ui->comboBox_panels->itemText(i) + "-reversed.FEM";
            writeFem(ui->filePath_fem->text(), fileName2, e2);
        }
        if(CS == "American Bureau of Shipping"){
            ABS(l,s,ui->lineEdit_fy->text().toDouble(),ui->lineEdit_p->text().toDouble(), GELMNT1, e1);
            if(ui->comboBox_load_type->currentText() == "Static Loading"){
                fileName = ui->filePath_result->text() + "/Buckling-results-ABS-static-" + ui->comboBox_panels->itemText(i)+ ".csv";
                fileName2 = ui->filePath_result->text() + "/Buckling-results-ABS-static-" + ui->comboBox_panels->itemText(i) + ".FEM";
            } else {
                fileName = ui->filePath_result->text() + "/Buckling-results-ABS-combined-" + ui->comboBox_panels->itemText(i)+ ".csv";
                fileName2 = ui->filePath_result->text() + "/Buckling-results-ABS-combined-" + ui->comboBox_panels->itemText(i) + ".FEM";
            }
            qDebug() << "writing result csv file";
            writeResults(fileName, e1);
            qDebug() << "writing result FEM file" << fileName2;
            qDebug() << "size of e1" << e1.size();
            writeFem(ui->filePath_fem->text(), fileName2, e1);

            ABS(s,l,ui->lineEdit_fy->text().toDouble(),ui->lineEdit_p->text().toDouble(), GELMNT1, e2);
            if(ui->comboBox_load_type->currentText() == "Static Loading"){
                fileName = ui->filePath_result->text() + "/Buckling-results-ABS-static-" + ui->comboBox_panels->itemText(i) + "-reversed.csv";
                fileName2 = ui->filePath_result->text() + "/Buckling-results-ABS-static-" + ui->comboBox_panels->itemText(i) + "-reversed.FEM";
            } else {
                fileName = ui->filePath_result->text() + "/Buckling-results-ABS-combined-" + ui->comboBox_panels->itemText(i) + "-reversed.csv";
                fileName2 = ui->filePath_result->text() + "/Buckling-results-ABS-combined-" + ui->comboBox_panels->itemText(i) + "-reversed.FEM";
            }
            qDebug() << "writing result csv file";
            writeResults(fileName, e2);
            qDebug() << "writing result FEM file" << fileName2;
            qDebug() << "size of e2" << e2.size();
            writeFem(ui->filePath_fem->text(), fileName2, e2);
            qDebug() << "ok" ;
        }
        if(CS == "Paik and Thayamballi + Fujikubo correction"){
            Analytical(l,s,ui->lineEdit_fy->text().toDouble(),ui->lineEdit_p->text().toDouble(), GELMNT1, e1);
            fileName = ui->filePath_result->text() + "/Buckling-results-EST-" + ui->comboBox_panels->itemText(i)+ ".csv";
            writeResults(fileName, e1);
            fileName2 = ui->filePath_result->text() + "/Buckling-results-EST-" + ui->comboBox_panels->itemText(i) + ".FEM";
            writeFem(ui->filePath_fem->text(), fileName2, e1);

            Analytical(s,l,ui->lineEdit_fy->text().toDouble(),ui->lineEdit_p->text().toDouble(), GELMNT1, e2);
            fileName = ui->filePath_result->text() + "/Buckling-results-EST-" + ui->comboBox_panels->itemText(i) + "-reversed.csv";
            writeResults(fileName, e2);
            fileName2 = ui->filePath_result->text() + "/Buckling-results-EST-" + ui->comboBox_panels->itemText(i) + "-reversed.FEM";
            writeFem(ui->filePath_fem->text(), fileName2, e2);
        }
        if(CS == "American Bureau of Shipping - ULS" ){
            ABS_ULS(l,s,ui->lineEdit_fy->text().toDouble(),ui->lineEdit_p->text().toDouble(), GELMNT1, e1);
            if(ui->comboBox_load_type->currentText() == "Static Loading"){
                fileName = ui->filePath_result->text() + "/ULS-results-ABS-static-" + ui->comboBox_panels->itemText(i)+ ".csv";
                fileName2 = ui->filePath_result->text() + "/ULS-results-ABS-static-" + ui->comboBox_panels->itemText(i) + ".FEM";
            } else {
                fileName = ui->filePath_result->text() + "/ULS-results-ABS-combined-" + ui->comboBox_panels->itemText(i)+ ".csv";
                fileName2 = ui->filePath_result->text() + "/ULS-results-ABS-combined-" + ui->comboBox_panels->itemText(i) + ".FEM";
            }
            qDebug() << "writing result csv file";
            writeResults(fileName, e1);
            qDebug() << "writing result FEM file" << fileName2;
            qDebug() << "size of e1" << e1.size();
            writeFem(ui->filePath_fem->text(), fileName2, e1);

            ABS_ULS(s,l,ui->lineEdit_fy->text().toDouble(),ui->lineEdit_p->text().toDouble(), GELMNT1, e2);
            if(ui->comboBox_load_type->currentText() == "Static Loading"){
                fileName = ui->filePath_result->text() + "/ULS-results-ABS-static-" + ui->comboBox_panels->itemText(i) + "-reversed.csv";
                fileName2 = ui->filePath_result->text() + "/ULS-results-ABS-static-" + ui->comboBox_panels->itemText(i) + "-reversed.FEM";
            } else {
                fileName = ui->filePath_result->text() + "/ULS-results-ABS-combined-" + ui->comboBox_panels->itemText(i) + "-reversed.csv";
                fileName2 = ui->filePath_result->text() + "/ULS-results-ABS-combined-" + ui->comboBox_panels->itemText(i) + "-reversed.FEM";
            }
            qDebug() << "writing result csv file";
            writeResults(fileName, e2);
            qDebug() << "writing result FEM file" << fileName2;
            qDebug() << "size of e2" << e2.size();
            writeFem(ui->filePath_fem->text(), fileName2, e2);
            qDebug() << "ok" ;
        }
    }
}

void MainWindow::on_Calculate_clicked()
{
    QTime t;
    t.start();
    if(ui->comboBox_panels->count() == 0 ){
        QMessageBox msgBox;
        msgBox.setText("You need to define at least 1 typical panel for calculation");
        msgBox.exec();
    } else {
        ui->progressBar->setValue(0); // setting the progress bar, progress, to zero
        QString fileName_FEM = ui->filePath_fem->text(); // getting the filename of the fem file
        QString fileName_SMX = ui->filePath_sigma_m_x->text(); // getting the filename of the sx list file
        QString fileName_SMY = ui->filePath_sigma_m_y->text(); // getting the filename of the sy list file
        QString fileName_TXY = ui->filePath_tau_m_xy->text(); // getting the filename of the tauxy list file

        QList<xtractElement> GELMNT1; // creating a list with elements with properties, only

        ui->statusBar->showMessage("Reading Element Properties from T*.FEM File"); // changing the message in the status bar
        readFemFile(fileName_FEM, GELMNT1); // reads all avaliable information for all Quad elements in the
                                            // given FEM file ( material properties, thikness )

        ui->progressBar->setValue(35); // updating the progress of the progress bar

        QList<xtractElement> elements; // creating a list with elements with properties and loading

        ui->statusBar->showMessage("Reading Element Stresses from Xtract List File");
        readListFile(fileName_SMX, fileName_SMY, fileName_TXY, GELMNT1, elements); // reads and assigns stresses for the
                                                                          // elements given in the List Files

        ui->progressBar->setValue(55); // updating the proigress of in the progress bar

        ui->statusBar->showMessage("Calculating Elements Buckling Modes"); // changing the message in the status bar
        calculateBuckling(elements); // this calculates the buckling modes and writes the results at the same time

        ui->progressBar->setValue(100); // updating the progress of the porgress bar
        ui->statusBar->showMessage("Results have been prepared"); // changing the message of the status bar
    }
     qDebug("Time elapsed: %d ms", t.elapsed());
}

void MainWindow::on_Browse_input_sigma_x_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open List File"));
    ui->filePath_sigma_m_x->setText(filename);
}

void MainWindow::on_Browse_input_Fem_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open List File"));
    ui->filePath_fem->setText(filename);
}

void MainWindow::on_Browse_result_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     "/home",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    ui->filePath_result->setText(dir);
}

void MainWindow::on_pushButton_addpanel_clicked()
{
    if(ui->linEdit_length->text() == "" || ui->lineEdit_width->text() == ""){
        QMessageBox msgBox;
        msgBox.setText("You need to define dimensions for the typical panel before adding it");
        msgBox.exec();
    } else {
        QString panel = ui->linEdit_length->text() + " x " + ui->lineEdit_width->text();
        ui->comboBox_panels->addItem(panel);
    }
}

void MainWindow::on_pushButton_removepanel_clicked()
{
    if(ui->comboBox_panels->count() == 0){
        QMessageBox msgBox;
        msgBox.setText("There are no panels to remove ( Panel List is already empty )");
        msgBox.exec();
    } else {
        int curr = ui->comboBox_panels->currentIndex();
        ui->comboBox_panels->removeItem(curr);
    }
}

void MainWindow::on_Browse_input_sigma_y_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open List File"));
    ui->filePath_sigma_m_y->setText(filename);
}

void MainWindow::on_Browse_input_tau_xy_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open List File"));
    ui->filePath_tau_m_xy->setText(filename);
}

void MainWindow::on_actionNew_Analysis_triggered()
{
    ui->lineEdit_fy->text() = "235";
    ui->lineEdit_p->text() = "0.00";
    ui->lineEdit_sf->text() = "1.00";
    ui->lineEdit_width->text() = "";
    ui->linEdit_length->text() = "";
    ui->filePath_fem->text() = "";
    ui->filePath_result->text() = "";
    ui->filePath_sigma_m_x->text() = "";
    ui->filePath_sigma_m_y->text() = "";
    ui->filePath_tau_m_xy->text() = "";
}

void MainWindow::on_actionExport_Panel_Data_triggered()
{

}

void MainWindow::on_actionImport_Panel_Data_triggered()
{

}

void MainWindow::on_actionExit_2_triggered()
{

}
