/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed May 23 10:19:39 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QAction *actionNew_Analysis;
    QAction *actionExport_Panel_Data;
    QAction *actionExit_2;
    QAction *actionDNV_Rules;
    QAction *actionABS_Rules;
    QAction *actionTheory_of_Elastic_Stability;
    QAction *actionAbout_Keppel_Fels_Baltech;
    QAction *actionImport_Panel_Data;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *groupBox_input;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *filePath_sigma_m_x;
    QLineEdit *filePath_sigma_m_y;
    QLineEdit *filePath_tau_m_xy;
    QLineEdit *filePath_fem;
    QVBoxLayout *verticalLayout_3;
    QPushButton *Browse_input_sigma_x;
    QPushButton *Browse_input_sigma_y;
    QPushButton *Browse_input_tau_xy;
    QPushButton *Browse_input_Fem;
    QGroupBox *groupBox_result;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *filePath_result;
    QPushButton *Browse_result;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *groupBox_parameters;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_11;
    QLabel *label_5;
    QLabel *label_14;
    QLabel *label_16;
    QLabel *label_18;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *lineEdit_p;
    QLineEdit *lineEdit_fy;
    QComboBox *comboBox_cs;
    QComboBox *comboBox_load_type;
    QLineEdit *lineEdit_sf;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_12;
    QLabel *label_7;
    QLabel *label_15;
    QLabel *label_17;
    QLabel *label_19;
    QGroupBox *groupBox_panels;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_8;
    QLabel *label_9;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *linEdit_length;
    QLineEdit *lineEdit_width;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_10;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_addpanel;
    QPushButton *pushButton_removepanel;
    QComboBox *comboBox_panels;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *progressBar;
    QPushButton *Calculate;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(658, 465);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        actionNew_Analysis = new QAction(MainWindow);
        actionNew_Analysis->setObjectName(QString::fromUtf8("actionNew_Analysis"));
        actionExport_Panel_Data = new QAction(MainWindow);
        actionExport_Panel_Data->setObjectName(QString::fromUtf8("actionExport_Panel_Data"));
        actionExit_2 = new QAction(MainWindow);
        actionExit_2->setObjectName(QString::fromUtf8("actionExit_2"));
        actionDNV_Rules = new QAction(MainWindow);
        actionDNV_Rules->setObjectName(QString::fromUtf8("actionDNV_Rules"));
        actionABS_Rules = new QAction(MainWindow);
        actionABS_Rules->setObjectName(QString::fromUtf8("actionABS_Rules"));
        actionTheory_of_Elastic_Stability = new QAction(MainWindow);
        actionTheory_of_Elastic_Stability->setObjectName(QString::fromUtf8("actionTheory_of_Elastic_Stability"));
        actionAbout_Keppel_Fels_Baltech = new QAction(MainWindow);
        actionAbout_Keppel_Fels_Baltech->setObjectName(QString::fromUtf8("actionAbout_Keppel_Fels_Baltech"));
        actionImport_Panel_Data = new QAction(MainWindow);
        actionImport_Panel_Data->setObjectName(QString::fromUtf8("actionImport_Panel_Data"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_11 = new QVBoxLayout(centralWidget);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        groupBox_input = new QGroupBox(centralWidget);
        groupBox_input->setObjectName(QString::fromUtf8("groupBox_input"));
        horizontalLayout = new QHBoxLayout(groupBox_input);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(groupBox_input);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(groupBox_input);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(groupBox_input);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(groupBox_input);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        filePath_sigma_m_x = new QLineEdit(groupBox_input);
        filePath_sigma_m_x->setObjectName(QString::fromUtf8("filePath_sigma_m_x"));

        verticalLayout_2->addWidget(filePath_sigma_m_x);

        filePath_sigma_m_y = new QLineEdit(groupBox_input);
        filePath_sigma_m_y->setObjectName(QString::fromUtf8("filePath_sigma_m_y"));

        verticalLayout_2->addWidget(filePath_sigma_m_y);

        filePath_tau_m_xy = new QLineEdit(groupBox_input);
        filePath_tau_m_xy->setObjectName(QString::fromUtf8("filePath_tau_m_xy"));

        verticalLayout_2->addWidget(filePath_tau_m_xy);

        filePath_fem = new QLineEdit(groupBox_input);
        filePath_fem->setObjectName(QString::fromUtf8("filePath_fem"));

        verticalLayout_2->addWidget(filePath_fem);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        Browse_input_sigma_x = new QPushButton(groupBox_input);
        Browse_input_sigma_x->setObjectName(QString::fromUtf8("Browse_input_sigma_x"));

        verticalLayout_3->addWidget(Browse_input_sigma_x);

        Browse_input_sigma_y = new QPushButton(groupBox_input);
        Browse_input_sigma_y->setObjectName(QString::fromUtf8("Browse_input_sigma_y"));

        verticalLayout_3->addWidget(Browse_input_sigma_y);

        Browse_input_tau_xy = new QPushButton(groupBox_input);
        Browse_input_tau_xy->setObjectName(QString::fromUtf8("Browse_input_tau_xy"));

        verticalLayout_3->addWidget(Browse_input_tau_xy);

        Browse_input_Fem = new QPushButton(groupBox_input);
        Browse_input_Fem->setObjectName(QString::fromUtf8("Browse_input_Fem"));

        verticalLayout_3->addWidget(Browse_input_Fem);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_11->addWidget(groupBox_input);

        groupBox_result = new QGroupBox(centralWidget);
        groupBox_result->setObjectName(QString::fromUtf8("groupBox_result"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_result);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(groupBox_result);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        filePath_result = new QLineEdit(groupBox_result);
        filePath_result->setObjectName(QString::fromUtf8("filePath_result"));

        horizontalLayout_5->addWidget(filePath_result);

        Browse_result = new QPushButton(groupBox_result);
        Browse_result->setObjectName(QString::fromUtf8("Browse_result"));

        horizontalLayout_5->addWidget(Browse_result);


        verticalLayout_11->addWidget(groupBox_result);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        groupBox_parameters = new QGroupBox(centralWidget);
        groupBox_parameters->setObjectName(QString::fromUtf8("groupBox_parameters"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_parameters);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_11 = new QLabel(groupBox_parameters);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_7->addWidget(label_11);

        label_5 = new QLabel(groupBox_parameters);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_7->addWidget(label_5);

        label_14 = new QLabel(groupBox_parameters);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        verticalLayout_7->addWidget(label_14);

        label_16 = new QLabel(groupBox_parameters);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        verticalLayout_7->addWidget(label_16);

        label_18 = new QLabel(groupBox_parameters);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        verticalLayout_7->addWidget(label_18);


        horizontalLayout_2->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        lineEdit_p = new QLineEdit(groupBox_parameters);
        lineEdit_p->setObjectName(QString::fromUtf8("lineEdit_p"));

        verticalLayout_8->addWidget(lineEdit_p);

        lineEdit_fy = new QLineEdit(groupBox_parameters);
        lineEdit_fy->setObjectName(QString::fromUtf8("lineEdit_fy"));

        verticalLayout_8->addWidget(lineEdit_fy);

        comboBox_cs = new QComboBox(groupBox_parameters);
        comboBox_cs->setObjectName(QString::fromUtf8("comboBox_cs"));
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        comboBox_cs->setFont(font);
        comboBox_cs->setMaxVisibleItems(5);
        comboBox_cs->setMaxCount(5);

        verticalLayout_8->addWidget(comboBox_cs);

        comboBox_load_type = new QComboBox(groupBox_parameters);
        comboBox_load_type->setObjectName(QString::fromUtf8("comboBox_load_type"));
        QFont font1;
        font1.setItalic(true);
        comboBox_load_type->setFont(font1);
        comboBox_load_type->setMaxCount(5);

        verticalLayout_8->addWidget(comboBox_load_type);

        lineEdit_sf = new QLineEdit(groupBox_parameters);
        lineEdit_sf->setObjectName(QString::fromUtf8("lineEdit_sf"));

        verticalLayout_8->addWidget(lineEdit_sf);


        horizontalLayout_2->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_12 = new QLabel(groupBox_parameters);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_12);

        label_7 = new QLabel(groupBox_parameters);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_7);

        label_15 = new QLabel(groupBox_parameters);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_15);

        label_17 = new QLabel(groupBox_parameters);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_17);

        label_19 = new QLabel(groupBox_parameters);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_19);


        horizontalLayout_2->addLayout(verticalLayout_9);


        horizontalLayout_7->addWidget(groupBox_parameters);

        groupBox_panels = new QGroupBox(centralWidget);
        groupBox_panels->setObjectName(QString::fromUtf8("groupBox_panels"));
        verticalLayout_10 = new QVBoxLayout(groupBox_panels);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_8 = new QLabel(groupBox_panels);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_6->addWidget(label_8);

        label_9 = new QLabel(groupBox_panels);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_6->addWidget(label_9);


        horizontalLayout_4->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        linEdit_length = new QLineEdit(groupBox_panels);
        linEdit_length->setObjectName(QString::fromUtf8("linEdit_length"));

        verticalLayout_5->addWidget(linEdit_length);

        lineEdit_width = new QLineEdit(groupBox_panels);
        lineEdit_width->setObjectName(QString::fromUtf8("lineEdit_width"));

        verticalLayout_5->addWidget(lineEdit_width);


        horizontalLayout_4->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_10 = new QLabel(groupBox_panels);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_10);

        label_13 = new QLabel(groupBox_panels);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_13);


        horizontalLayout_4->addLayout(verticalLayout_4);


        verticalLayout_10->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pushButton_addpanel = new QPushButton(groupBox_panels);
        pushButton_addpanel->setObjectName(QString::fromUtf8("pushButton_addpanel"));

        horizontalLayout_6->addWidget(pushButton_addpanel);

        pushButton_removepanel = new QPushButton(groupBox_panels);
        pushButton_removepanel->setObjectName(QString::fromUtf8("pushButton_removepanel"));

        horizontalLayout_6->addWidget(pushButton_removepanel);


        verticalLayout_10->addLayout(horizontalLayout_6);

        comboBox_panels = new QComboBox(groupBox_panels);
        comboBox_panels->setObjectName(QString::fromUtf8("comboBox_panels"));
        comboBox_panels->setEditable(false);
        comboBox_panels->setMaxCount(100);

        verticalLayout_10->addWidget(comboBox_panels);


        horizontalLayout_7->addWidget(groupBox_panels);


        verticalLayout_11->addLayout(horizontalLayout_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        horizontalLayout_3->addWidget(progressBar);

        Calculate = new QPushButton(centralWidget);
        Calculate->setObjectName(QString::fromUtf8("Calculate"));

        horizontalLayout_3->addWidget(Calculate);


        verticalLayout_11->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 658, 18));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_Analysis);
        menuFile->addAction(actionImport_Panel_Data);
        menuFile->addAction(actionExport_Panel_Data);
        menuFile->addSeparator();
        menuFile->addAction(actionExit_2);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAbout_Qt);
        menuHelp->addAction(actionAbout_Keppel_Fels_Baltech);
        menuHelp->addSeparator();
        menuHelp->addAction(actionDNV_Rules);
        menuHelp->addAction(actionABS_Rules);
        menuHelp->addAction(actionTheory_of_Elastic_Stability);

        retranslateUi(MainWindow);

        comboBox_panels->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Keppel Fels Baltech - Buckling Post-Processor", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About Qt", 0, QApplication::UnicodeUTF8));
        actionNew_Analysis->setText(QApplication::translate("MainWindow", "New Analysis", 0, QApplication::UnicodeUTF8));
        actionExport_Panel_Data->setText(QApplication::translate("MainWindow", "Export Panel Data", 0, QApplication::UnicodeUTF8));
        actionExit_2->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionDNV_Rules->setText(QApplication::translate("MainWindow", "DNV Rules", 0, QApplication::UnicodeUTF8));
        actionABS_Rules->setText(QApplication::translate("MainWindow", "ABS Rules", 0, QApplication::UnicodeUTF8));
        actionTheory_of_Elastic_Stability->setText(QApplication::translate("MainWindow", "Theory of Elastic Stability", 0, QApplication::UnicodeUTF8));
        actionAbout_Keppel_Fels_Baltech->setText(QApplication::translate("MainWindow", "About \"Keppel Fels Baltech\"", 0, QApplication::UnicodeUTF8));
        actionImport_Panel_Data->setText(QApplication::translate("MainWindow", "Import Panel Data", 0, QApplication::UnicodeUTF8));
        groupBox_input->setTitle(QApplication::translate("MainWindow", "Input Files", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">[ \317\203</span><span style=\" font-size:8pt; vertical-align:sub;\">x  </span><span style=\" font-size:8pt;\">]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">[ \317\203</span><span style=\" font-size:8pt; vertical-align:sub;\">y  </span><span style=\" font-size:8pt;\">]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">[ \317\204</span><span style=\" font-size:8pt; vertical-align:sub;\">xy  </span><span style=\" font-size:8pt;\">]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "FEM", 0, QApplication::UnicodeUTF8));
        filePath_sigma_m_x->setText(QApplication::translate("MainWindow", "C:/Users/vyordanov/Desktop/buckling analysis/T206-sigmx.txt", 0, QApplication::UnicodeUTF8));
        filePath_sigma_m_y->setText(QApplication::translate("MainWindow", "C:/Users/vyordanov/Desktop/buckling analysis/T206-sigmy.txt", 0, QApplication::UnicodeUTF8));
        filePath_tau_m_xy->setText(QApplication::translate("MainWindow", "C:/Users/vyordanov/Desktop/buckling analysis/T206-taumxy.txt", 0, QApplication::UnicodeUTF8));
        filePath_fem->setText(QApplication::translate("MainWindow", "C:/Users/vyordanov/Desktop/buckling analysis/T206.FEM", 0, QApplication::UnicodeUTF8));
        Browse_input_sigma_x->setText(QApplication::translate("MainWindow", "Browse", 0, QApplication::UnicodeUTF8));
        Browse_input_sigma_y->setText(QApplication::translate("MainWindow", "Browse", 0, QApplication::UnicodeUTF8));
        Browse_input_tau_xy->setText(QApplication::translate("MainWindow", "Browse", 0, QApplication::UnicodeUTF8));
        Browse_input_Fem->setText(QApplication::translate("MainWindow", "Browse", 0, QApplication::UnicodeUTF8));
        groupBox_result->setTitle(QApplication::translate("MainWindow", "Results Directory", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "DIR", 0, QApplication::UnicodeUTF8));
        filePath_result->setText(QApplication::translate("MainWindow", "C:\\Users\\vyordanov\\Desktop\\buckling analysis\\T206", 0, QApplication::UnicodeUTF8));
        Browse_result->setText(QApplication::translate("MainWindow", "Browse", 0, QApplication::UnicodeUTF8));
        groupBox_parameters->setTitle(QApplication::translate("MainWindow", "Other Parameters", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Lateral Pressure [ p ]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Yield strength [ \317\203</span><span style=\" font-size:8pt; vertical-align:sub;\">0</span><span style=\" font-size:8pt;\"> ]</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Classification Society", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "Load Conditions", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "Safety Factor", 0, QApplication::UnicodeUTF8));
        lineEdit_p->setText(QApplication::translate("MainWindow", "0.00", 0, QApplication::UnicodeUTF8));
        lineEdit_fy->setText(QApplication::translate("MainWindow", "235", 0, QApplication::UnicodeUTF8));
        comboBox_cs->clear();
        comboBox_cs->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "American Bureau of Shipping", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "American Bureau of Shipping - ULS", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Det Norske Veritas", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Paik and Thayamballi + Fujikubo correction", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_WHATSTHIS
        comboBox_cs->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        comboBox_load_type->clear();
        comboBox_load_type->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Static Loading", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Combined Loading", 0, QApplication::UnicodeUTF8)
        );
        lineEdit_sf->setText(QApplication::translate("MainWindow", "1.00", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "[ MPa ]", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "[ MPa ]", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "[ - ]", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "[ - ]", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "[ - ]", 0, QApplication::UnicodeUTF8));
        groupBox_panels->setTitle(QApplication::translate("MainWindow", "Typical Panels", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Length", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Width", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "[ mm ]", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "[ mm ]", 0, QApplication::UnicodeUTF8));
        pushButton_addpanel->setText(QApplication::translate("MainWindow", "Add Panel", 0, QApplication::UnicodeUTF8));
        pushButton_removepanel->setText(QApplication::translate("MainWindow", "Remove Panel", 0, QApplication::UnicodeUTF8));
        comboBox_panels->clear();
        comboBox_panels->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "2438 x 610", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "1524 x 610", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2133.5 x 610", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2286 x 610", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2032 x 610", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2235 x 610", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "2184.5 x 610", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        comboBox_panels->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        comboBox_panels->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        Calculate->setText(QApplication::translate("MainWindow", "Calculate", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
