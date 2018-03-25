#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <iostream>
#include <QFileDialog>

QString fpath;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignCenter);

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QString("ETA'; UOMINI ; %UOMINI; DONNE ; %DONNE").split(";"));
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Text", "./", "Text Files (*.txt)");
    fpath = filePath;

    QFile inputFile(filePath);
    inputFile.open(QIODevice::ReadOnly);
    if (!inputFile.isOpen()){
        return;
    }

    ui->label->setText(filePath);

    QTextStream stream(&inputFile);
    QString line = stream.readLine();
    QString regione;
    QStringList lista_regioni;
    while (!line.isNull()) {

        if(line!="<END>"){
            QStringList list1 = line.split(" ");
            regione = list1[0];
            if (!lista_regioni.contains(regione)){
                lista_regioni.append(regione);
            }
        }

        line = stream.readLine();
    };

    for (int i = 0; i < lista_regioni.size(); ++i) {
        ui->comboBox->addItem(lista_regioni[i]);
    }

    QString selected_region = ui->comboBox->currentText();
    on_comboBox_activated(selected_region);

    inputFile.close();
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    QFile inputFile(fpath);
    inputFile.open(QIODevice::ReadOnly);
    if (!inputFile.isOpen()){
        return;
    }

    QTextStream stream(&inputFile);
    QString line = stream.readLine();
    QString eta;
    QString n_donne;
    QString n_uomini;
    QStringList lista_eta;
    QStringList lista_donne;
    QStringList lista_uomini;
    while (!line.isNull()) {

        if(line!="<END>"){
            QStringList list1 = line.split(" ");
            eta = list1[1];
            n_donne = list1[2];
            n_uomini = list1[3];
            if (!lista_eta.contains(eta) && list1[0] == arg1){
                lista_eta.append(eta);
                lista_donne.append(n_donne);
                lista_uomini.append(n_uomini);
            }
        }

        line = stream.readLine();
    };

    ui->tableWidget->setRowCount(lista_eta.size() + 1);
    ui->tableWidget->setColumnCount(5);

    double totale_uomini = 0;
    double totale_donne = 0;
    double final_item = 0;

    for (int i = 0; i < lista_eta.size(); ++i) {

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(lista_eta[i]));
        QString numero_donne_str = lista_donne.at(i);
        QString numero_donne_double = numero_donne_str.split(" ")[0];
        double numero_donne_doubleI = numero_donne_double.toDouble();
        QString numero_uomini_str = lista_uomini.at(i);
        QString numero_uomini_double = numero_uomini_str.split(" ")[0];
        double numero_uomini_doubleI = numero_uomini_double.toDouble();
        totale_uomini += numero_uomini_doubleI;
        totale_donne += numero_donne_doubleI;

        double p_donne = (numero_donne_doubleI * 100) / (numero_donne_doubleI + numero_uomini_doubleI);
        double p_uomini = (numero_uomini_doubleI * 100) / (numero_uomini_doubleI + numero_donne_doubleI);

        QString pe_donne = QString::number(p_donne);
        QString pe_uomini = QString::number(p_uomini);

        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(lista_uomini[i]));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(pe_uomini));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(lista_donne[i]));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(pe_donne));

        final_item = i;
    }

    double totale_p_uomini = (totale_uomini*100) / (totale_uomini + totale_donne);
    double totale_p_donne = (totale_donne * 100) / (totale_donne + totale_uomini);

    QString t_uomini = QString::number(totale_uomini);
    QString t_donne = QString::number(totale_donne);
    QString t_p_uomini = QString::number(totale_p_uomini);
    QString t_p_donne = QString::number(totale_p_donne);

    ui->tableWidget->setItem(final_item+1, 0, new QTableWidgetItem("Totale"));
    ui->tableWidget->setItem(final_item+1, 1, new QTableWidgetItem(t_uomini));
    ui->tableWidget->setItem(final_item+1, 2, new QTableWidgetItem(t_p_uomini));
    ui->tableWidget->setItem(final_item+1, 3, new QTableWidgetItem(t_donne));
    ui->tableWidget->setItem(final_item+1, 4, new QTableWidgetItem(t_p_donne));

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    inputFile.close();
}
