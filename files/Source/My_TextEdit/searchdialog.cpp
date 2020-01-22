#include "searchdialog.h"
#include "ui_searchdialog.h"


SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_Find_next_clicked()
{
    SearchText=ui->SearchBox->toPlainText();
    if(!SearchText.isEmpty())
        emit callTextSearch(SearchText,         //搜索文本
                            SearchWay,          //搜索方向;true:向前;false:向后
                            isCaseSensitive);   //是否区分大小写
}

void SearchDialog::on_RB_up_clicked()
{
    SearchWay=true;
}

void SearchDialog::on_RB_down_clicked()
{
    SearchWay=false;
}

void SearchDialog::on_CaseSensitive_clicked(bool checked)
{
    if(checked)
        isCaseSensitive=true;
    else
        isCaseSensitive=false;
}
