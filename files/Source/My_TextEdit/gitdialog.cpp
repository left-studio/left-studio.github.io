#include "gitdialog.h"
#include "ui_gitdialog.h"

#include <QFileDialog>
#include <QMessageBox>

#ifdef WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

GitDialog::GitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GitDialog)
{
    ui->setupUi(this);
}

GitDialog::~GitDialog()
{
    delete ui;
}

void GitDialog::GetPath(QString FilePath)
{
    m_FilePath=FilePath;
    ui->FilePathEdit->setPlainText(m_FilePath);
}

void GitDialog::on_GitPathBtn_clicked()
{
    QString Path=QFileDialog::getExistingDirectory(this,tr("请选择Git目录"),
        QDir::currentPath());
    ui->GitPathEdit->setPlainText(Path);
}

void GitDialog::on_FilePathBtn_clicked()
{
    QString Path= QFileDialog::getOpenFileName(this,tr("选择文件"),QDir::currentPath(),
        tr("文本文件(*.txt);;源文件(*.c *.cpp *.py *.html *.xml *.js *.vbs *.bat);;所有文件(*.*)"));
    ui->FilePathEdit->setPlainText(Path);
}

void GitDialog::on_CommitBtn_clicked()
{
    m_GitPath=ui->GitPathEdit->toPlainText();
    m_FilePath=ui->FilePathEdit->toPlainText();
    m_Notes=ui->NotesEdit->toPlainText();
    if(m_GitPath.isEmpty()||m_FilePath.isEmpty())
        QMessageBox::warning(this,tr("警告"),tr("请输入Git目录和文件目录"));
    else
    {
        system(QString("cd \"%1\"\ngit add %2\ngit commit -m \"%3\"\n").arg(m_GitPath)
            .arg(m_FilePath).arg(m_Notes).toLatin1().data());
    }
}
