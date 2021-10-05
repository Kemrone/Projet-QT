#include "printview.h"
#include "ui_printview.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QTextDocument>

PrintView::PrintView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintView)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

}





PrintView::~PrintView()
{
    delete ui;
}






void PrintView::receiveMessage(const QString &msg){

    ui->recapText->setText(msg);
}

void PrintView::receiveTitle(const QString &title){

    ui->typeTransactionLabel->setText(title);
}


Article PrintView::getArt(){
    return this->art;
}

void PrintView::setArt(Article art){
    this->art = art;
}

Operations PrintView::getOpe(){
    return this->ope;

}

void PrintView::setOpe(Operations ope){
    this->ope = ope;
}



void PrintView::on_QuitterButton_clicked()
{
    hide();
}

void PrintView::on_ImprimerButton_clicked()
{



   // QPrintDialog(&printer,this).exec();
   // printer.setOutputFormat(QPrinter::PdfFormat);
   // printer.setOutputFileName("test.pdf");
   // this->render(&printer);
   // printer.setPrinterName("HP ENVY-5544");

     QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer,this);
    if(dialog.exec()==QDialog::Rejected) return;
    printer.setPageMargins(12, 16, 12, 20, QPrinter::Millimeter);
    printer.setFullPage(false);


   QPainter painter(&printer);

           double xscale = printer.pageRect().width() / double(this->width());
           double yscale = printer.pageRect().height() / double(this->height());
           double scale = qMin(xscale, yscale);
           painter.translate(printer.paperRect().center());
           painter.scale(scale, scale);
           painter.translate(-this->width()/ 2, -this->height()/ 2);
           this->render(&painter);



}
