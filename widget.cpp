#include "widget.h"
#include "./ui_widget.h"

#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 中文标点符号
    chineseSignal = {
        "，", "。", "；", "：", "？", "！", "、", "——", "……",
        "（", "）", "【", "】", "《", "》", "“", "”", "‘", "’"
    };
    this->componentsInit();
}

Widget::~Widget()
{
    delete ui;
}
/**
 * 初始化配置页面组件
 * @brief Widget::componentsInit
 */
void Widget::componentsInit()
{

    // 启用抗锯齿
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);
    // 文本颜色
    ui->comboBox->addItem("black", QVariant::fromValue(Qt::black));
    ui->comboBox->addItem("white", QVariant::fromValue(Qt::white));
    ui->comboBox->addItem("red", QVariant::fromValue(Qt::red));
    ui->comboBox->addItem("green", QVariant::fromValue(Qt::green));
    ui->comboBox->addItem("blue", QVariant::fromValue(Qt::blue));
    ui->comboBox->addItem("darkRed", QVariant::fromValue(Qt::darkRed));
    ui->comboBox->addItem("darkGreen", QVariant::fromValue(Qt::darkGreen));
    ui->comboBox->addItem("darkBlue", QVariant::fromValue(Qt::darkBlue));
    ui->comboBox->addItem("magenta", QVariant::fromValue(Qt::magenta));
    ui->comboBox->addItem("yellow", QVariant::fromValue(Qt::yellow));
    ui->comboBox->addItem("gray", QVariant::fromValue(Qt::gray));
    ui->comboBox->addItem("cyan", QVariant::fromValue(Qt::cyan));
    ui->comboBox->addItem("darkCyan", QVariant::fromValue(Qt::darkCyan));
    ui->comboBox->addItem("darkMagenta", QVariant::fromValue(Qt::darkMagenta));
    ui->comboBox->addItem("darkYellow", QVariant::fromValue(Qt::darkYellow));
    ui->comboBox->addItem("darkGray", QVariant::fromValue(Qt::darkGray));
    ui->comboBox->addItem("lightGray", QVariant::fromValue(Qt::lightGray));
    // 背景色
    ui->comboBox_2->addItem("transparent", QVariant::fromValue(Qt::transparent));
    ui->comboBox_2->addItem("white", QVariant::fromValue(Qt::white));
    ui->comboBox_2->addItem("black", QVariant::fromValue(Qt::black));
    ui->comboBox_2->addItem("red", QVariant::fromValue(Qt::red));
    ui->comboBox_2->addItem("green", QVariant::fromValue(Qt::green));
    ui->comboBox_2->addItem("blue", QVariant::fromValue(Qt::blue));
    ui->comboBox_2->addItem("darkRed", QVariant::fromValue(Qt::darkRed));
    ui->comboBox_2->addItem("darkGreen", QVariant::fromValue(Qt::darkGreen));
    ui->comboBox_2->addItem("darkBlue", QVariant::fromValue(Qt::darkBlue));
    ui->comboBox_2->addItem("magenta", QVariant::fromValue(Qt::magenta));
    ui->comboBox_2->addItem("yellow", QVariant::fromValue(Qt::yellow));
    ui->comboBox_2->addItem("gray", QVariant::fromValue(Qt::gray));
    ui->comboBox_2->addItem("cyan", QVariant::fromValue(Qt::cyan));
    ui->comboBox_2->addItem("darkCyan", QVariant::fromValue(Qt::darkCyan));
    ui->comboBox_2->addItem("darkMagenta", QVariant::fromValue(Qt::darkMagenta));
    ui->comboBox_2->addItem("darkYellow", QVariant::fromValue(Qt::darkYellow));
    ui->comboBox_2->addItem("darkGray", QVariant::fromValue(Qt::darkGray));
    ui->comboBox_2->addItem("lightGray", QVariant::fromValue(Qt::lightGray));
    // 字体选择
    // 读取字体文件夹
    QDir dir("./font");
    QStringList files = dir.entryList(QDir::Files);  // 只读取文件
    for(QString file : files)
    {
        ui->comboBox_3->addItem(file.split(".")[0], "./font/" + file);
    }
    // 设置graphicsView可以鼠标拖动
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    // 隐藏graphicsView的scroll bar
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Widget::loadImage(QString imgPath)
{

    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    // 加载图片
    QPixmap pixmap(imgPath); // 使用资源文件路径或绝对路径
    if(!pixmap.isNull())
    {
        // 添加图画到页面
        QGraphicsPixmapItem *handWriting = scene->addPixmap(pixmap);
    }
    // 加载背景图片
    // QPixmap bgPixmap("./gqz.jpg");
    // if(!bgPixmap.isNull())
    // {
    //     // 添加到view
    //     QGraphicsPixmapItem *bgItem = scene->addPixmap(bgPixmap);
    //     // 设置到底层
    //     bgItem->setZValue(-1);
    // }

    // 自动适应视图大小
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

}
// 直接混合像素
QImage blendImages(const QImage &foreground, const QImage &background) {
    QImage result = background.copy();
    for (int y = 0; y < foreground.height(); ++y) {
        for (int x = 0; x < foreground.width(); ++x) {
            QColor fgColor = foreground.pixelColor(x, y);
            if (fgColor.alpha() > 0) { // 只处理非透明像素
                result.setPixelColor(x, y, fgColor);
            }
        }
    }
    return result;
}

// 为 originalImage 添加背景图片
QImage addBackgroundToImage(const QImage &originalImage, const QString &backgroundPath) {
    // 1. 加载背景图片
    QImage background(backgroundPath);
    if (background.isNull()) {
        qWarning() << "Failed to load background image!";
        return originalImage; // 返回原图（或处理错误）
    }

    // 2. 调整背景大小（可选：缩放至原图大小）
    background = background.scaled(originalImage.size(), Qt::KeepAspectRatioByExpanding);

    // 3. 创建目标图像（与背景同大小）
    QImage result(background.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent); // 透明背景

    // 4. 绘制背景和原图
    QPainter painter(&result);
    painter.drawImage(0, 0, background); // 先画背景
    painter.drawImage(
        (result.width() - originalImage.width()) / 2,  // 水平居中
        (result.height() - originalImage.height()) / 2, // 垂直居中
        originalImage
        );
    painter.end();

    return result;
}

bool Widget::drawHandWriting(
    const QString& text,  // 文本内容
    const QString& fontPath,  // 字体文件地址
    const QString& outputPath,  // 保存图片地址
    int fontSize,  // 字体大小
    int startX,  // 起始位置X(左边距)
    int startY,  // 起始位置Y(上边距)
    int endX,  // 结束位置X(右边距)
    int endY,  // 结束位置Y(下边距)
    int rowSpacing,  // 行距
    int wordSpacing, // 字距
    int rowSpacingDisturbance,  // 行距扰动
    int wordHorizontalDisturbance,  // 单字横向扰动
    int wordVerticalDisturbance,  // 单字纵向扰动
    int wordSizeDisturbance,  // 单字大小扰动
    float wordRotateDisturbance,  // 单字旋转扰动
    qreal wordScaleXDisturbance,  // 单字X轴缩放扰动
    qreal wordScaleYDisturbance,  // 单字Y轴缩放扰动
    QColor textColor,  // 文本颜色
    int width_mm,  // 纸张宽度  A4纸
    int height_mm,  // 纸张高度
    int dpi,  // 分辨率
    QColor bgColor  // 画布背景
    )
{

    // 画布大小
    QSize canvasSize = QSize(width_mm * dpi / 25.4, height_mm * dpi / 25.4);
    // 加载字体文件
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if(fontId == -1) {
        qWarning() << "字体加载失败:" << fontPath;
        return false;
    }
    // 获取字体族名称
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if(fontFamilies.empty()) {
        qWarning() << "字体文件不包含有效字体族:" << fontPath;
        return false;
    }
    // 设置字体
    QFont font(fontFamilies.first(), fontSize);
    // 记录当前文字坐标
    int index_text = 0;
    // 记录当前 页序
    int page_count = 0;
    // 当还有剩余字符 继续操作
    while(index_text < text.length())
    {
        // 记录当前X、Y的位置
        int pointX = startX;
        int pointY = startY;

        // 创建画布
        QImage image(canvasSize, QImage::Format_ARGB32);
        image.fill(bgColor);

        // 设置绘制器
        QPainter painter(&image);
        painter.setPen(textColor);
        // 启用抗锯齿
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::TextAntialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

        // 行距扰动
        int rsdValue = QRandomGenerator::global()->bounded(rowSpacingDisturbance+1);
        // 行位置
        pointY = pointY + fontSize + rowSpacing + rsdValue;  // 下一行位置 = 当前行位置 + 字体大小 + 行距 - 行距扰动
        // 随机数生成器
        QRandomGenerator *random = QRandomGenerator::global();
        // 在指定位置绘制文字
        for(; index_text < text.length(); index_text ++)
        {
            QChar ch = text.at(index_text);
            // 遇到换行符
            if(ch == '\n')
            {
                // 行距扰动
                int rsdValue = QRandomGenerator::global()->bounded(rowSpacingDisturbance+1);
                // 行位置
                pointY = pointY + fontSize + rowSpacing + rsdValue;  // 下一行位置 = 当前行位置 + 字体大小 + 行距 - 行距扰动
                // X轴回到行首且保持留白空间
                pointX = startX;
                // 判断当前页剩余空间是否可以容下一行字
                if(pointY > canvasSize.height() - endY)
                {
                    break;
                }
                continue;
            }

            // 单字横向扰动
            int whdValue = random->bounded(wordHorizontalDisturbance+1);
            // 单字纵向扰动
            int wvdValue = random->bounded(wordVerticalDisturbance+1);
            // 单字大小扰动
            int wsdValue = random->bounded(wordSizeDisturbance+1);
            // 单字旋转扰动
            double wrdValue = random->generateDouble() * wordRotateDisturbance * 360;
            // 单字X轴缩放扰动
            qreal wsXdValue = random->generateDouble() * (2 * wordScaleXDisturbance) - wordScaleXDisturbance + 1;
            // 单字Y轴缩放扰动
            qreal wsYdValue = random->generateDouble() * (2 * wordScaleYDisturbance) - wordScaleYDisturbance + 1;
            // 设置单字X轴位置
            int wordX = pointX - whdValue;

            // 当前行内容占满，不足以再容下一个字（加入右边距计算）
            if(wordX + fontSize > canvasSize.width() - endX)
            {
                // 行距扰动
                int rsdValue = QRandomGenerator::global()->bounded(rowSpacingDisturbance+1);
                // 行位置
                pointY = pointY + fontSize + rowSpacing + rsdValue;  // 下一行位置 = 当前行位置 + 字体大小 + 行距 - 行距扰动
                // X轴回到行首且保持留白空间
                pointX = startX;
                // 设置单字X轴位置
                wordX = pointX - whdValue;
                // 判断当前页剩余空间是否可以容下一行字
                if(pointY > canvasSize.height() - endY)
                {
                    break;
                }
            }

            // 设置单字Y轴位置
            int wordY = pointY - wvdValue;
            // 设置单字大小
            font.setPixelSize(fontSize + wsdValue);
            painter.setFont(font);

            // 下一个字X轴开始位置
            // 判断当前字符是否为符号 英文字母 数字
            if(chineseSignal.contains(ch) || ch.unicode() <= 127)
            {
                pointX = pointX + fontSize / 2 + wordSpacing;  // 下一个字位置 = 当前字位置 + 字体大小(减半) + 字距
            }
            else
            {
                pointX = pointX + fontSize + wordSpacing;  // 下一个字位置 = 当前字位置 + 字体大小 + 字距
            }

            // transform隔离 保存当前画笔状态
            painter.save();
            // 缩放
            painter.scale(wsXdValue, wsYdValue);
            painter.drawText(QPoint(wordX / wsXdValue, wordY / wsYdValue), ch);  // 画出单字
            // 恢复到之前画笔状态
            painter.restore();
        }
        // 判断是否选中了背景图片
        if(ui->radioButton->isChecked())
        {
            // QImage background("./gqz.jpg");
            // blendImages(image, background).save(outputPath + "/output" + QString::number(page_count) +".png");
            addBackgroundToImage(image, bgPath).save(outputPath + "/output" + QString::number(page_count) +".png");
        }
        else
        {
            // 保存图片
            image.save(outputPath + "/output" + QString::number(page_count) +".png");
        }
        page_count ++;  // 页面 ＋1
    }
    return true;
}



void Widget::on_pushButton_clicked()
{
    QDir output("./output");
    // 设置过滤 只获取文件
    output.setFilter(QDir::Files);
    const QFileInfoList fileList = output.entryInfoList();
    // 遍历删除 旧的文件
    for(const QFileInfo &fileInfo : fileList)
    {
        if(!QFile::remove(fileInfo.absoluteFilePath()))
        {
            qDebug() << fileInfo.absoluteFilePath() << "remove fail";
        }
    }
    // 获取页面数据
    QString text = ui->textEdit->toPlainText();
    QString fontPath = ui->comboBox_3->currentData().toString();
    QString outputPath = "./output";
    int fontSize = ui->spinBox->value();
    int startX = ui->spinBox_2->value();
    int endX = ui->spinBox_3->value();
    int startY = ui->spinBox_4->value();
    int endY = ui->spinBox_5->value();
    int rowSpacing = ui->spinBox_6->value();
    int wordSpacing = ui->spinBox_7->value();
    int rowSpacingDisturbance = ui->spinBox_8->value();
    int wordHorizontalDisturbance = ui->spinBox_9->value();
    int wordVerticalDisturbance = ui->spinBox_10->value();
    int wordSizeDisturbance = ui->spinBox_11->value();
    int height_mm = ui->spinBox_12->value();
    int width_mm = ui->spinBox_13->value();
    int dpi = ui->spinBox_14->value();
    qreal wordScaleXDisturbance = ui->doubleSpinBox->value();
    qreal wordScaleYDisturbance = ui->doubleSpinBox_2->value();
    QVariant data =  ui->comboBox->currentData();
    Qt::GlobalColor textColor = data.value<Qt::GlobalColor>();
    data = ui->comboBox_2->currentData();
    Qt::GlobalColor bgColor = data.value<Qt::GlobalColor>();

    drawHandWriting(
        text,
        fontPath,
        outputPath,
        fontSize,
        startX,
        startY,
        endX,
        endY,
        rowSpacing,
        wordSpacing,
        rowSpacingDisturbance,
        wordHorizontalDisturbance,
        wordVerticalDisturbance,
        wordSizeDisturbance,
        0.0,
        wordScaleXDisturbance,
        wordScaleYDisturbance,
        textColor,
        width_mm,
        height_mm,
        dpi,
        bgColor
        );
    // 加载图片
    loadImage("./output/output0.png");
    // qDebug() << "绘制结果:" << (success ? "成功" : "失败");
    // 图片列表
    QDir dir("./output");
    pageFileList = dir.entryList(QDir::Files);  // 读取图片文件列表
    ui->label_22->setText(QString::number(nowPage) + "/" + QString::number(pageFileList.size()));
}

/**
 * 上一页
 * @brief Widget::on_pushButton_4_clicked
 */
void Widget::on_pushButton_4_clicked()
{
    // 如果不是第一页
    if(nowPage > 1)
    {
        // 当前页面 -1
        nowPage --;
    }
    else
    {
        // 最后一页
        nowPage = pageFileList.size();
    }
    // 加载图片
    loadImage("./output/" + pageFileList.at(nowPage-1));
    // 页码更新
    ui->label_22->setText(QString::number(nowPage) + "/" + QString::number(pageFileList.size()));
}

/**
 * 下一页
 * @brief Widget::on_pushButton_3_clicked
 */
void Widget::on_pushButton_3_clicked()
{
    // 如果不是最后一页
    if(nowPage < pageFileList.size())
    {
        // 当前页码 +1
        nowPage ++;
    }
    else
    {
        // 第一页
        nowPage = 1;
    }
    // 加载图片
    loadImage("./output/" + pageFileList.at(nowPage-1));
    // 页码更新
    ui->label_22->setText(QString::number(nowPage) + "/" + QString::number(pageFileList.size()));
}

/**
 * 选择背景文件
 * @brief Widget::on_radioButton_toggled
 * @param checked
 */
void Widget::on_radioButton_clicked(bool checked)
{
    // checked
    if (true)
    {
        QString filePath = QFileDialog::getOpenFileName(
            this,                  // 父窗口
            "选择背景文件",          // 窗口标题
            QDir::homePath(),      // 初始目录
            "*.png *.jpg *.jpeg"   // 文件过滤器
            );
        // 如果选择了文件
        if(!filePath.isEmpty())
        {
            ui->radioButton->setText("已选背景图片");
            bgPath = filePath;
        }
        // 如果没有选择文件
        else
        {
            // 取消选中
            ui->radioButton->setChecked(false);
        }
    }
    // unchecked
    else
    {
        ui->radioButton->setText("选择背景图");
    }
}

/**
 * 放大图像
 * @brief Widget::on_pushButton_5_clicked
 */
void Widget::on_pushButton_5_clicked()
{
    // 限制放大
    if(ui->graphicsView->transform().m11() < 3.0)
    {
        ui->graphicsView->scale(1.1, 1.1);
    }

}

/**
 * 缩小图像
 * @brief Widget::on_pushButton_6_clicked
 */
void Widget::on_pushButton_6_clicked()
{
    // 限制缩小
    if(ui->graphicsView->transform().m11() > 0.2)
    {
        ui->graphicsView->scale(0.9, 0.9);
    }

}

