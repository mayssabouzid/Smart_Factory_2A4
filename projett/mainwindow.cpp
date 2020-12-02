#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"voiture.h"
#include"chaine.h"
#include"connexion.h"
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QSqlRelationalTableModel>
#include "C:\Users\Mayssa\Desktop\Qt-Table-Printer-master\Qt-Table-Printer-master/tableprinter.h"
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include<QPixmap>




class PrintBorder : public PagePrepare {
public:
    virtual void preparePage(QPainter *painter);
    static int pageNumber;
};

int PrintBorder::pageNumber = 0;

void PrintBorder::preparePage(QPainter *painter) { // print a border on each page
    QRect rec = painter->viewport();
    painter->setPen(QPen(QColor(0, 0, 0), 1));
    painter->drawRect(rec);
    painter->translate(10, painter->viewport().height() - 10);
    painter->drawText(0, 0, QString("Page %1").arg(pageNumber));
    pageNumber += 1;
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     ui->setupUi(this);
     QPixmap pix("C:/Users/Mayssa/Desktop/gestion_production/image1.jpg");
     int w=ui->label_pic->width();
     int h=ui->label_pic->height();
     ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
     son =new QSound("C:/Users/Mayssa/Desktop/gestion_production/projett/son.wav");
     movie=new QMovie("C:/Users/Mayssa/Desktop/gestion_production/projett/movie.gif");
     movie->start();
     ui->label_gif->setMovie(movie);
     ui->tableView->setModel(vtmp.afficher());
     ui->tableView_2->setModel(ctmp.afficher());
     ui->comboBox->setModel(vtmp.load());
     ui->comboBox_2->addItem("REFERENCE");
     ui->comboBox_2->addItem("NB_MACHINE");
     ui->comboBox_2->addItem("TYPE_PRODUIT");
     ui->comboBox_ch->setModel(ctmp.load_ch());
     //pfd
     model = new QSqlTableModel;
     model->setTable("chaine");
     model->select();


     ui->tableView_2->setModel(model);
     ui->lineEdit_prix->setValidator(new QIntValidator(0,999999,this));
     ui->lineEdit_p->setValidator(new QIntValidator(0,999999,this));
     ui->lineEdit_p_op->setValidator(new QIntValidator(0,999999,this));
     ui->lineEdit_po->setValidator(new QIntValidator(0,999999,this));
     ui->lineEdit_ref->setValidator(new QIntValidator(0,99999999,this));
     ui->lineEdit_ref_ch->setValidator(new QIntValidator(0,99999999,this));
     ui->lineEdit_refer->setValidator(new QIntValidator(0,99999999,this));
     ui->lineEdit_reference->setValidator(new QIntValidator(0,99999999,this));
     ui->lineEdit_referencee->setValidator(new QIntValidator(0,99999999,this));
     ui->lineEdit_reff_ch->setValidator(new QIntValidator(0,99999999,this));
     ui->lineEdit_nb_mach->setValidator(new QIntValidator(0,999999,this));
     ui->lineEdit_maq->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_marque->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_marquee->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_mod->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_modele->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_modelee->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_col->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_couleur->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_ops->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_option->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_typ->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_type->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_type_p->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
     ui->lineEdit_type_prod->setValidator(new QRegExpValidator( QRegExp("[A-Za-z0_]{0,255}"), this ));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    son->play();
    QString marque = ui->lineEdit_marque->text();
     QString modele=ui->lineEdit_modele->text();
     QString type=ui->lineEdit_type->text();
     QString options=ui->lineEdit_option->text();
     QString couleur=ui->lineEdit_couleur->text();
     int prix=ui->lineEdit_prix->text().toInt();
     int  prix_option=ui->lineEdit_p_op->text().toInt();
     int reference=ui->lineEdit_reference->text().toInt();
     voiture v(marque,reference,modele,prix,type,prix_option,couleur,options);
     bool test=v.ajouter();
     if(test)
     {
         ui->tableView->setModel(vtmp.afficher());
         QMessageBox::information(nullptr, QObject::tr("ajout effectuee"),
                     QObject::tr("voiture ajouté avec succés.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     }
     else
         QMessageBox::critical(nullptr, QObject::tr("ajout non effectuee"),
                     QObject::tr("voiture non ajouté.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_pushButton_ajouter_chaine_clicked()
{
     son->play();
    QString type_produit = ui->lineEdit_type_p->text();
     int  reference=ui->lineEdit_ref->text().toInt();
     int nb_machine=ui->spinBox->text().toInt();
     chaine c(reference,nb_machine,type_produit);
     bool test=c.ajouter();
     if(test)
     {
          ui->tableView_2->setModel(ctmp.afficher());
         QMessageBox::information(nullptr, QObject::tr("ajout effectuee"),
                     QObject::tr("chaine ajouté avec succés.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     }
     else
         QMessageBox::critical(nullptr, QObject::tr("ajout non effectuee"),
                     QObject::tr("chaine non ajouté.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_afficher_clicked()
{
     son->play();
     ui->stackedWidget->setCurrentIndex(1);
 ui->tableView->setModel(vtmp.afficher());
}

void MainWindow::on_retour_clicked()
{
     son->play();
    ui->stackedWidget->setCurrentIndex(0);
}




void MainWindow::on_quitter_clicked()
{
     son->play();
    QMessageBox::StandardButton reply=QMessageBox::question
            (this,"quitter","voulez-vous vraiment quitter?",QMessageBox::Yes |QMessageBox::No);
    if(reply==QMessageBox::Yes)
{
        close();
    }else
    {

    }
}


void MainWindow::on_retour_2_clicked()
{
     son->play();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_modifier_clicked()
{
     son->play();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_retour_3_clicked()
{
     son->play();
     ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_supprimer_clicked()
{
     son->play();
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_retour_4_clicked()
{
     son->play();
      ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_retour_clicked()
{
     son->play();
      ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_retour_2_clicked()
{
     son->play();
      ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_afficher_chaine_clicked()
{
     son->play();
      ui->stackedWidget_2->setCurrentIndex(1);
       ui->tableView_2->setModel(ctmp.afficher());
}

void MainWindow::on_pushButton_modifier_chaine_clicked()
{
     son->play();
      ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_pushButton_supprimer_chaine_clicked()
{
     son->play();
      ui->stackedWidget_2->setCurrentIndex(1);
}



void MainWindow::on_quitter_2_clicked()
{
     son->play();
    QMessageBox::StandardButton reply=QMessageBox::question
         (this,"quitter","voulez-vous vraiment quitter?",QMessageBox::Yes |QMessageBox::No);
    if(reply==QMessageBox::Yes)
{
        close();
    }else
    {

    }
}

void MainWindow::on_load_data_clicked()
{
     son->play();
     ui->comboBox->setModel(vtmp.load());
}

void MainWindow::on_modifier_3_clicked()//voiture
{
    son->play();
    QMessageBox msgBox;
    QMessageBox msgBox1;
     voiture v(ui->lineEdit_maq->text(),ui->lineEdit_refer->text().toInt(),ui->lineEdit_mod->text(),ui->lineEdit_p->text().toInt(),ui->lineEdit_typ->text(),ui->lineEdit_po->text().toInt(),ui->lineEdit_col->text(),ui->lineEdit_ops->text());
     bool test=v.modifier();
    if(test)
    {
       ui->tableView->setModel(vtmp.afficher());
       msgBox.setText("voiture modifié");
       msgBox.exec();
    }
else
    {
       msgBox1.setText("voiture non modifié");
           msgBox1.exec();
     }

}


void MainWindow::on_comboBox_currentIndexChanged()
{
     son->play();
    QString reference = ui->comboBox->currentText();
    QSqlQuery query;
    query.prepare("select*  from voiture1 where reference='"+reference+"'");
       if(query.exec())
    {
        while(query.next())
        {
             ui->lineEdit_refer->setText(query.value(0).toString());
             ui->lineEdit_maq->setText(query.value(1).toString());
             ui->lineEdit_mod->setText(query.value(2).toString());
             ui->lineEdit_p->setText(query.value(3).toString());
             ui->lineEdit_typ->setText(query.value(4).toString());
             ui->lineEdit_po->setText(query.value(5).toString());
             ui->lineEdit_col->setText(query.value(6).toString());
             ui->lineEdit_ops->setText(query.value(7).toString());

       }
    }

}


void MainWindow::on_sup_clicked()
{
     son->play();
     int reference=ui->lineEdit_referencee->text().toInt();
    bool test=vtmp.supprimer(reference);
    if(test)
    {
         ui->tableView->setModel(vtmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("suppression effectuee"),
                    QObject::tr("voiture supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
 }
    else
        QMessageBox::critical(nullptr, QObject::tr("suppression non effectuee"),
                              QObject::tr("voiture non supprimé.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_tri_clicked()
{

 son->play();
    int test=0;

      if (ui->comboBox_2->currentText()=="REFERENCE")
                 {test=1;}

      else if (ui->comboBox_2->currentText()=="NB_MACHINE")
                  {test=2;}

      else if (ui->comboBox_2->currentText()=="TYPE_PRODUIT")
                  {test=3;}

      ui->tableView_2->setModel(ctmp.trier(test)) ;

   /* QSqlQueryModel *model=new QSqlQueryModel() ;

       model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NB_MACHINE"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE_PRODUIT"));
        ui->tableView_2->setModel(model);
        QSqlQuery query ;
            if(ui->comboBox_2->currentText()=="REFERENCE")
            query.prepare("SELECT *  FROM CHAINE ORDER BY REFERENCE ASC ") ;
          else

            if (ui->comboBox_2->currentText()=="NB_MACHINE")
            query.prepare("SELECT *  FROM CHAINE ORDER BY NB_MACHINE ASC ") ;
          else

            if (ui->comboBox_2->currentText()=="TYPE_PRODUIT")
         query.prepare("SELECT *  FROM CHAINE ORDER BY TYPE_PRODUIT ASC ") ;

            if (query.exec()&& query.next()) {
                model->setQuery(query) ;

                ui->tableView_2->setModel(model) ;
            }


*/
}






void MainWindow::on_recherche_clicked()
{
     son->play();
    /* QString marque = ui->lineEdit_marquee->text();
      QString modele=ui->lineEdit_modelee->text();
      int reference=ui->lineEdit_referencee->text().toInt();*/
     ui->tableView->setModel(vtmp.recherche(ui->lineEdit_referencee->text(),ui->lineEdit_marquee->text(),ui->lineEdit_modelee->text()));
}

void MainWindow::on_load_ch_clicked()
{
     son->play();
     ui->comboBox_ch->setModel(ctmp.load_ch());
}



void MainWindow::on_comboBox_ch_currentIndexChanged()
{
     son->play();
   QString REFERENCE = ui->comboBox_ch->currentText();
    QSqlQuery query;
    query.prepare("select*  from CHAINE where REFERENCE =:REFERENCE");
  query.bindValue(":REFERENCE",REFERENCE);
       if(query.exec())
    {
       while(query.next())
{
            ui->lineEdit_ref_ch->setText(query.value(0).toString());
            ui->lineEdit_nb_mach->setText(query.value(1).toString());
            ui->lineEdit_type_prod->setText(query.value(2).toString());
}
    }

}

void MainWindow::on_modifier_ch_clicked()//chaine
{
     son->play();
    QSqlQuery query;
    QMessageBox msgBox;
    QMessageBox msgBox1;
     chaine c(ui->lineEdit_ref_ch->text().toInt(),ui->lineEdit_nb_mach->text().toInt(),ui->lineEdit_type_prod->text());
     bool test=c.modifier();
    if(test)
    {
       ui->tableView_2->setModel(ctmp.afficher());
       msgBox.setText("chaine modifié");
       msgBox.exec();
    }
else
    {
       msgBox1.setText("chaine non modifié");
           msgBox1.exec();
     }

}


void MainWindow::on_sup_ch_clicked()
{
     son->play();
    //int reference=ui->lineEdit_reff_ch->text().toInt();
   bool test=ctmp.supprimer(ui->lineEdit_reff_ch->text().toInt());
   if(test)
   {
        ui->tableView_2->setModel(ctmp.afficher());
       QMessageBox::information(nullptr, QObject::tr("suppression effectuee"),
                   QObject::tr("chaine supprimé.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
  }
   else
       QMessageBox::critical(nullptr, QObject::tr("suppression non effectuee"),
                             QObject::tr("chaine non supprimé.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::print(QPrinter *printer)
{
    QPainter painter;
    if(!painter.begin(printer)) {
        qWarning() << "can't start printer";
        return;
    }
    // print table
    TablePrinter tablePrinter(&painter, printer);
    QVector<int> columnStretch = QVector<int>() << 2 << 5 << 10 ;
    if(!tablePrinter.printTable(ui->tableView_2->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }
    // print second table
   /* painter.translate(0, 100);
    if(!tablePrinter.printTable(ui->tableView_2->model(), columnStretch)) {
        qDebug() << tablePrinter.lastError();
    }*/
    painter.end();
}

void MainWindow::on_pushButton_imprimer_clicked()
{
     son->play();
    QPrintPreviewDialog dialog;
      connect(&dialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
      dialog.exec();
}

void MainWindow::on_pushButton_stat_clicked()
{
     son->play();
    stat=new Statistique (this);
    stat->exec();
}

