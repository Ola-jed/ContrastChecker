#include "mainwindow.hpp"
#include "../include/ui_mainwindow.h"
#include <QColorDialog>
#include <QScreen>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Contrast Checker");
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(),
                                    QGuiApplication::primaryScreen()->availableGeometry()));
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
    initComponents();
    connect(ui->foregroundColorChoose, &QPushButton::clicked, this, &MainWindow::onForegroundColorChoose);
    connect(ui->backgroundColorChoose, &QPushButton::clicked, this, &MainWindow::onBackgroundColorChoose);
    connect(ui->foregroundColorEdit, &QLineEdit::textChanged, this, &MainWindow::onForegroundColorEditUpdate);
    connect(ui->backgroundColorEdit, &QLineEdit::textChanged, this, &MainWindow::onBackgroundColorEditUpdate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QColor MainWindow::askForegroundColor()
{
    return QColorDialog::getColor(Qt::white, this, "Choose the foreground color");
}

QColor MainWindow::askBackgroundColor()
{
    return QColorDialog::getColor(Qt::white, this, "Choose the background color");
}

void MainWindow::onBackgroundColorChoose()
{
    const auto bgColor = askBackgroundColor();
    ui->backgroundColorEdit->setText(bgColor.name());
    ui->backgroundColorChoose->setStyleSheet("background-color: " + bgColor.name());
    updateStaticUiComponents();
}

void MainWindow::onForegroundColorChoose()
{
    const auto fgColor = askForegroundColor();
    ui->foregroundColorEdit->setText(fgColor.name());
    ui->foregroundColorChoose->setStyleSheet("background-color: " + fgColor.name());
    updateStaticUiComponents();
}

void MainWindow::onForegroundColorEditUpdate()
{
    if (!QColor::isValidColor(ui->foregroundColorEdit->text()))
    {
        return;
    }
    ui->foregroundColorChoose->setStyleSheet("background-color: " + ui->foregroundColorEdit->text());
    updateStaticUiComponents();
}

void MainWindow::onBackgroundColorEditUpdate()
{
    if (!QColor::isValidColor(ui->backgroundColorEdit->text()))
    {
        return;
    }
    ui->backgroundColorChoose->setStyleSheet("background-color: " + ui->backgroundColorEdit->text());
    updateStaticUiComponents();
}

void MainWindow::updateStaticUiComponents()
{
    const auto fgColor = ui->foregroundColorEdit->text();
    const auto bgColor = ui->backgroundColorEdit->text();
    ui->backgroundWidget->setStyleSheet("background-color: " + bgColor);
    const auto fgColorStr = "color: " + fgColor;
    ui->smallTextLabel->setStyleSheet(fgColorStr);
    ui->largeTextLabel->setStyleSheet(fgColorStr);
    ui->componentButton->setStyleSheet(ui->componentButton->styleSheet() + "color: " + fgColor + ";");
    ui->componentButton->setStyleSheet(
            ui->componentButton->styleSheet() + "background-color: " + bgColor + ";");
    const auto contrastRatio = colorUtils::computeContrastRatio(QColor{fgColor}, QColor{bgColor});
    ui->contrastRatioLabel->setText(QString::number(contrastRatio) + ":1");
    ui->aaSmallText->setText(contrastRatio >= SMALL_AA_ACCEPTANCE ? "PASS" : "FAIL");
    ui->aaLargeText->setText(contrastRatio >= LARGE_AA_ACCEPTANCE ? "PASS" : "FAIL");
    ui->aaUiComponent->setText(contrastRatio >= UI_COMPONENT_AA_ACCEPTANCE ? "PASS" : "FAIL" );
    ui->aaaSmallText->setText(contrastRatio >= SMALL_AAA_ACCEPTANCE ? "PASS" : "FAIL");
    ui->aaaLargeText->setText(contrastRatio >= LARGE_AAA_ACCEPTANCE ? "PASS" : "FAIL");
    ui->aaaUiComponent->setText(contrastRatio >= UI_COMPONENT_AAA_ACCEPTANCE ? "PASS" : "FAIL");
}

void MainWindow::initComponents()
{
    ui->foregroundColorEdit->setText("#ffffff");
    ui->backgroundColorEdit->setText("#000000");
    ui->foregroundColorChoose->setStyleSheet("background-color: #ffffff");
    ui->backgroundColorChoose->setStyleSheet("background-color: #000000");
}
