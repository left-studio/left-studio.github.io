#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "searchdialog.h"
#include "aboutdialog.h"
//#include "gitdialog.h"

class QLabel;
class QProgressBar;
class QSpinBox;
class QFontComboBox;
class QToolBar;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actFontBold_triggered(bool checked);

    void on_txtEdit_copyAvailable(bool b);

    void on_txtEdit_selectionChanged();

    void on_actFontItalic_triggered(bool checked);

    void on_actFontUnder_triggered(bool checked);

    void on_actToolbarStyle_triggered(bool checked);

    void on_actOpen_triggered();

    void on_actNoWrap_triggered();

    void on_actWidgetWidth_triggered();

    void on_actFixedPixelWidth_triggered();

    void on_actSave_triggered();

    void on_actNew_triggered();

    void on_actSaveAs_triggered();

    void on_actTextStyleToolBar_triggered(bool checked);

    void on_actSetTextColor_triggered();

    void on_actSearch_triggered();

    void on_actAbout_triggered();

    void on_actUpdateToGit_triggered();


    // 自定义槽函数
    void on_spinBoxFontSize_vauleChanged(int aFontSize);        // 改变字体大小
    void on_comboFont_currentIndexChanged(const QString &arg1); // 选中文字改变(更新cut,copy,paste状态)
    void on_textChanged();              // 文字改变
    void CursorIsChanged();             // 光标位置改变
    void TextSearch(QString,bool,bool); // 搜索文本

    void on_actClear_triggered();

private:
    Ui::MainWindow *ui;
    SearchDialog *m_SearchDialog;
    AboutDialog *m_AboutDialog;
    //GitDialog *m_GitDialog;

    bool isSave=true;           // 保存状态
    QString FileName;           // 当前文件名

    QLabel *fLabCurFile;        // 文件名QLabel
    QLabel *isSaveLable;        // "文件以保存"Qlabel
    QLabel *nCurposLable;       // 光标位置QLabel
    QProgressBar *progressBar1; // 文本大小进度条
    QSpinBox *spinFontSize;     // 文本大小
    QFontComboBox *comboFont;   // 文本字体
    QToolBar *TextStyleToolBar; // 字体样式工具栏

    void iniUI();
    void iniSignalSlots();
    bool SaveFile(QString &FileName);   // 写入文件
    void CheckFileIsSave();             // 检查文件是否保存

    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
