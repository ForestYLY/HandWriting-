#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QImage>
#include <QPainter>
#include <QFontDatabase>
#include <QTextDocument>
#include <QDebug>
#include <QRandomGenerator>
#include <QSet>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void componentsInit();
    void loadImage(QString imgPath);
    bool drawHandWriting(
        const QString& text,  // 文本内容
        const QString& fontPath,  // 字体文件地址
        const QString& outputPath,  // 保存图片地址
        int fontSize = 28,  // 字体大小
        int startX = 10,  // 起始位置X(左边距)
        int startY = 10,  // 起始位置Y(上边距)
        int endX = 10,  // 结束位置X(右边距)
        int endY = 10,  // 结束位置Y(下边距)
        int rowSpacing = 10,  // 行距
        int wordSpacing = 6, // 字距
        int rowSpacingDisturbance = 1,  // 行距扰动
        int wordHorizontalDisturbance = 6,  // 单字横向扰动
        int wordVerticalDisturbance = 6,  // 单字纵向扰动
        int wordSizeDisturbance = 10,  // 单字大小扰动
        float wordRotateDisturbance = 0.005f,  // 单字旋转扰动
        qreal wordScaleXDisturbance = 0.15f,  // 单字X轴缩放扰动
        qreal wordScaleYDisturbance = 0.15f,  // 单字Y轴缩放扰动
        QColor textColor = Qt::black,  // 文本颜色
        int width_mm = 210,  // 纸张宽度  A4纸
        int height_mm = 297,  // 纸张高度
        int dpi = 100,  // 分辨率
        QColor bgColor = Qt::white  // 画布颜色 white  transparent
        );

private:
    QSet<QString> chineseSignal;
    QStringList pageFileList;
    int nowPage = 1;
    QString bgPath;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_radioButton_clicked(bool checked);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
