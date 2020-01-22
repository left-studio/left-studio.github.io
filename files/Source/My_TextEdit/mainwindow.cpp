/*  By Left Studio  */
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QFontComboBox>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QCloseEvent>
//#include <QSettings>
#include <QDebug>
#include <QToolBar>
#include <QDir>

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iniUI();
    iniSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniUI()
{
    QLabel *myLable;
    QFont font("Microsoft YaHei",9);

    //setWindowFlags (Qt::CustomizeWindowHint);
    ui->actClear->setEnabled(false);

    // 状态栏
    fLabCurFile=new QLabel;
    fLabCurFile->setMinimumWidth(150);
    fLabCurFile->setText(tr("当前文件:"));
    ui->statusBar->addWidget(fLabCurFile);

    progressBar1=new QProgressBar;
    progressBar1->setMaximumWidth(100);
    progressBar1->setMinimum(5);
    progressBar1->setMaximum(50);
    progressBar1->setValue(ui->txtEdit->font().pointSize());
    ui->statusBar->addWidget(progressBar1);

    nCurposLable=new QLabel;
    nCurposLable->setMinimumWidth(130);
    nCurposLable->setText(tr("行:%1  列:%2  字数:%3")
        .arg(ui->txtEdit->textCursor().blockNumber()+1)
        .arg(ui->txtEdit->textCursor().columnNumber())
        .arg(ui->txtEdit->document()->characterCount()-1));
    ui->statusBar->addWidget(nCurposLable);

    isSaveLable=new QLabel;
    isSaveLable->setText(tr("文件已保存"));
    isSaveLable->setVisible(isSave);
    ui->statusBar->addWidget(isSaveLable);

    // 文本样式工具栏
    TextStyleToolBar=new QToolBar();
    addToolBar(TextStyleToolBar);
    TextStyleToolBar->hide();

    TextStyleToolBar->addAction(ui->actFontItalic);
    TextStyleToolBar->addAction(ui->actFontBold);
    TextStyleToolBar->addAction(ui->actFontUnder);
    TextStyleToolBar->addSeparator();       // 分隔栏

    myLable=new QLabel(tr("字体大小 "));
    myLable->setFont(font);
    spinFontSize=new QSpinBox;
    spinFontSize->setMinimum(5);
    spinFontSize->setMaximum(50);
    spinFontSize->setValue(ui->txtEdit->font().pointSize());
    spinFontSize->setMinimumWidth(50);
    TextStyleToolBar->addWidget(myLable);
    TextStyleToolBar->addWidget(spinFontSize);
    TextStyleToolBar->addSeparator();       // 分隔栏

    myLable=new QLabel(tr("字体 "));
    myLable->setFont(font);
    comboFont=new QFontComboBox;
    comboFont->setMinimumWidth(50);
    comboFont->setMaximumWidth(115);
    TextStyleToolBar->addWidget(myLable);
    TextStyleToolBar->addWidget(comboFont);
    TextStyleToolBar->addSeparator();       // 分隔栏

    TextStyleToolBar->addAction(ui->actSetTextColor);

    TextStyleToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    setCentralWidget(ui->txtEdit);
}

void MainWindow::iniSignalSlots()
{
    // 关联自定义信号槽
    connect(spinFontSize,SIGNAL(valueChanged(int)),this,
            SLOT(on_spinBoxFontSize_vauleChanged(int)));
    connect(comboFont,SIGNAL(currentIndexChanged(const QString &)),this,
            SLOT(on_comboFont_currentIndexChanged(const QString &)));
    connect(ui->txtEdit,SIGNAL(textChanged()),this,
            SLOT(on_textChanged()));
    connect(ui->txtEdit,SIGNAL(cursorPositionChanged()),this,
            SLOT(CursorIsChanged()));
}

void MainWindow::on_txtEdit_copyAvailable(bool b)
{
    // 更新cut,copy,paste的enabled属性
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->txtEdit->canPaste());
}

void MainWindow::on_txtEdit_selectionChanged()
{
    // 更新粗体，斜体和下划线3种action的checked属性
    QTextCharFormat fmt=ui->txtEdit->currentCharFormat();
    ui->actFontBold->setChecked(fmt.font().bold());
    ui->actFontUnder->setChecked(fmt.fontUnderline());
    ui->actFontItalic->setChecked(fmt.fontUnderline());
}

void MainWindow::on_actFontBold_triggered(bool checked)
{
    // 粗体 || Normal
    QTextCharFormat fmt=ui->txtEdit->currentCharFormat();
    if(checked)
        fmt.setFontWeight((QFont::Bold));
    else
        fmt.setFontWeight(QFont::Normal);
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actFontItalic_triggered(bool checked)
{
    // 斜体 || Normal
    QTextCharFormat fmt=ui->txtEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actFontUnder_triggered(bool checked)
{
    // 下划线 || Normal
    QTextCharFormat fmt=ui->txtEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_spinBoxFontSize_vauleChanged(int aFontSize)
{
    // 改变字体大小
    QTextCharFormat fmt;
    fmt.setFontPointSize(aFontSize);
    ui->txtEdit->mergeCurrentCharFormat(fmt);
    progressBar1->setValue(aFontSize);
}

void MainWindow::on_comboFont_currentIndexChanged(const QString &arg1)
{
    // 选择字体
    QTextCharFormat fmt;
    fmt.setFontFamily(arg1);
    ui->txtEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actToolbarStyle_triggered(bool checked)
{
    if(checked)
    {
        ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        TextStyleToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
    else
    {
        ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        TextStyleToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    }
}

void MainWindow::on_actTextStyleToolBar_triggered(bool checked)
{
    if(checked)
        TextStyleToolBar->show();
    else
        TextStyleToolBar->hide();
}

bool MainWindow::SaveFile(QString &FileName)
{
    //将文本框数据取出并按行排列
    QFile file(FileName);//文件命名
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))     //检测文件是否打开
        return false;
    QTextStream out(&file);                 //分行写入文件
    out << ui->txtEdit->toPlainText();
    file.close();
    isSave=true;
    isSaveLable->setVisible(isSave);
    return true;
}

void MainWindow::CheckFileIsSave()
{
    if((!isSave)&&ui->txtEdit->document()->characterCount()-1!=0)
    {
        if(QMessageBox::question(this,tr("警告"),tr("是否保存当前文件"),
           QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            on_actSave_triggered();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    CheckFileIsSave();
    event->accept();
}

void MainWindow::on_actOpen_triggered()
{
    CheckFileIsSave();
    FileName = QFileDialog::getOpenFileName(nullptr,tr("打开文件"),QDir::currentPath(),
        tr("文本文件(*.txt);;源文件(*.c *.cpp *.py *.html *.xml *.js *.vbs *.bat);;所有文件(*.*)"));
    if(!FileName.isEmpty())
    {
        QFile file(FileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
            return;
        }
        else
        {
            if(file.isReadable())
            {
                QTextStream in(&file);
                while (!in.atEnd())
                     ui->txtEdit->setText(in.readAll());
                file.close();
                fLabCurFile->setText(tr("当前文件:%1").arg(FileName));
                isSave=true;
            }
            else
               QMessageBox::warning(this,tr("错误"),tr("该文件不可读"));
        }
    }
    return;
}

void MainWindow::on_actSave_triggered()
{
    if(FileName.isEmpty())
    {
        FileName = QFileDialog::getSaveFileName(this,tr("保存文件"),QDir::currentPath(),
            tr("文本文件(*.txt);;源文件(*.c *.cpp *.py *.html *.xml *.js *.vbs *.bat);;所有文件(*.*)"));
        if(FileName.isEmpty())
            return;
    }
    if(!SaveFile(FileName))
        QMessageBox::warning(this,tr("错误"),tr("文件保存失败"));
    else
        fLabCurFile->setText(tr("当前文件:%1").arg(FileName));
    return;
}

void MainWindow::on_actNew_triggered()
{
    QString NewFileName = QFileDialog::getSaveFileName(this,tr("新建文件"),QDir::currentPath(),
        tr("文本文件(*.txt);;源文件(*.c *.cpp *.py *.html *.xml *.js *.vbs *.bat);;所有文件(*.*)"));
    if(NewFileName.isEmpty())
        return;
    CheckFileIsSave();
    if(!SaveFile(NewFileName))
        QMessageBox::warning(this,tr("错误"),tr("文件创建失败"));
    else
    {
        FileName=NewFileName;
        fLabCurFile->setText(tr("当前文件:%1").arg(FileName));
        ui->txtEdit->clear();
    }
    return;
}

void MainWindow::on_actSaveAs_triggered()
{
    QString SaveAsFileName = QFileDialog::getSaveFileName(this,tr("另存为..."),QDir::currentPath(),
        tr("文本文件(*.txt);;源文件(*.c *.cpp *.py *.html *.xml *.js *.vbs *.bat);;所有文件(*.*)"));
    if(SaveAsFileName.isEmpty())
        return;
    if(!SaveFile(SaveAsFileName))
        QMessageBox::warning(this,tr("错误"),tr("文件另存为失败"));
    return;
}

void MainWindow::on_actNoWrap_triggered()
{
    ui->txtEdit->setLineWrapMode(QTextEdit::NoWrap);
    return;
}

void MainWindow::on_actWidgetWidth_triggered()
{
    ui->txtEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    return;
}

void MainWindow::on_actFixedPixelWidth_triggered()
{
    ui->txtEdit->setLineWrapMode(QTextEdit::FixedPixelWidth);
    return;
}

void MainWindow::on_textChanged()
{
    if(ui->txtEdit->document()->characterCount()-1==0)
    {
        ui->actClear->setEnabled(false);
        ui->actSearch->setEnabled(false);
    }
    else
    {
        ui->actClear->setEnabled(true);
        ui->actSearch->setEnabled(true);
    }
    isSave=false;
    isSaveLable->setVisible(isSave);
    return;
}

void MainWindow::CursorIsChanged()
{
    nCurposLable->setText(tr("行:%1  列:%2  字数:%3")
        .arg(ui->txtEdit->textCursor().blockNumber()+1)
        .arg(ui->txtEdit->textCursor().columnNumber())
        .arg(ui->txtEdit->document()->characterCount()-1));
}

void MainWindow::TextSearch(QString text,bool SearchWay,bool isCaseSensitive)
{
    bool isFind;
    if(SearchWay)
    {
        if(isCaseSensitive)
            isFind=ui->txtEdit->find(text,QTextDocument::FindCaseSensitively|
                                     QTextDocument::FindBackward);
        else
            isFind=ui->txtEdit->find(text,QTextDocument::FindBackward);
    }
    else
    {
        if(isCaseSensitive)
            isFind=ui->txtEdit->find(text,QTextDocument::FindCaseSensitively);
        else
            isFind=ui->txtEdit->find(text);
    }
    if(!isFind)
        QMessageBox::warning(this,tr("查找"),tr("找不到 \"%1\"").arg(text));
}

void MainWindow::on_actSetTextColor_triggered()
{
    QPalette pal=ui->txtEdit->palette();
    QColor nColor=pal.color(QPalette::Text);
    QColor ChoseColor=QColorDialog::getColor(nColor,this,tr("选择颜色"));
    if(ChoseColor.isValid())
    {
        QTextCharFormat fmt;                            //文本字符格式
        fmt.setForeground(ChoseColor);                  //前景色(即字体色)设为color色
        QTextCursor cursor = ui->txtEdit->textCursor(); //获取文本光标
        cursor.mergeCharFormat(fmt);                    //光标后的文字就用该格式显示
        ui->txtEdit->mergeCurrentCharFormat(fmt);       //QTextEdit使用当前的字符格式
    }
}

void MainWindow::on_actSearch_triggered()
{
    m_SearchDialog=new SearchDialog(this);
    connect(m_SearchDialog,SIGNAL(callTextSearch(QString,bool,bool)),this,
            SLOT(TextSearch(QString,bool,bool)));
    m_SearchDialog->setModal(false);
    m_SearchDialog->show();
}

void MainWindow::on_actAbout_triggered()
{
    m_AboutDialog=new AboutDialog(this);
    m_AboutDialog->setModal(false);
    m_AboutDialog->show();
}

void MainWindow::on_actUpdateToGit_triggered()
{
    /*CheckFileIsSave();
    m_GitDialog=new GitDialog(this);
    m_GitDialog->GetPath(FileName);
    m_GitDialog->setModal(true);
    m_GitDialog->show();*/
    //system(QString("git remote %1").arg(FileName).toLatin1().data());
}

void MainWindow::on_actClear_triggered()
{
    if(!ui->txtEdit->toPlainText().isEmpty())
    {
        if(QMessageBox::warning(this,tr("警告"),tr("是否清空文本内容"),
            QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        ui->txtEdit->clear();
    }
}
