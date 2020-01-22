#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QTextEdit>


namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();

private slots:
    void on_Find_next_clicked();

    void on_RB_up_clicked();

    void on_RB_down_clicked();

    void on_CaseSensitive_clicked(bool checked);

signals:
    void callTextSearch(QString,    // 搜索文本
                        bool,       // 搜索方向;true:向前;false:向后
                        bool);      // 是否区分大小写

private:
    Ui::SearchDialog *ui;

    bool isCaseSensitive=false; // 是否区分大小写
    bool SearchWay=false;       // 搜索方向;true:向前;false:向后
    QString SearchText;         // 搜索文本
};

#endif // SEARCHDIALOG_H
