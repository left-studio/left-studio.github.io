#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QLabel>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    iniUI();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::iniUI()
{
    /* 限定窗口大小 */
    this->setFixedSize(this->width(), this->height());
    /* 窗口背景颜色 */
    QPalette palette = this->palette();
    QColor color(255,255,255);          // 白色
    palette.setBrush(QPalette::Window, QBrush(color));
    this->setPalette(palette);
    /* 显示Logo */
    QImage *LogoImage=new QImage;
    LogoImage->load(":/images/images/Left Studio.png");             // 加载图片
    LogoImage->scaled(ui->LogoLabel->size(),Qt::KeepAspectRatio);   // 设置缩放尺寸
    ui->LogoLabel->setScaledContents(true);                         // 允许图片充满整个窗件
    ui->LogoLabel->setPixmap(QPixmap::fromImage(*LogoImage));       // 显示LOGO
}
