#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "colorutils.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void initComponents();
    void updateStaticUiComponents();
    static constexpr double SMALL_AA_ACCEPTANCE = 4.5;
    static constexpr double LARGE_AA_ACCEPTANCE = 3.0;
    static constexpr double UI_COMPONENT_AA_ACCEPTANCE = 3.0;
    static constexpr double SMALL_AAA_ACCEPTANCE = 7;
    static constexpr double LARGE_AAA_ACCEPTANCE = 4.5;
    static constexpr double UI_COMPONENT_AAA_ACCEPTANCE = 3.0;
private slots:
    QColor askForegroundColor();
    QColor askBackgroundColor();
    void onBackgroundColorChoose();
    void onForegroundColorChoose();
    void onForegroundColorEditUpdate();
    void onBackgroundColorEditUpdate();
};

#endif // MAINWINDOW_HPP
