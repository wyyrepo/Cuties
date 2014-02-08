
#include <QDebug>

#include <QGradient>
#include <QRadioButton>
#include <QSlider>
#include <QLabel>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QBoxLayout>
#include <QLinearGradient>
#include <QConicalGradient>
#include <QRadialGradient>
#include <QPainter>

#include "kccolorselector.h"


KCColorDoubleBoardBase::KCColorDoubleBoardBase(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(259,259);
    setAutoFillBackground(true);
    hsvGreyGradient.setStart(0,0);
}

void KCColorDoubleBoardBase::setColor(const QString &elementName,
                                      const QColor &color)
{
    if(elementName=="S:")
    {
        currentMode=saturationMode;
    }
    else if(elementName=="V:")
    {
        currentMode=valueMode;
    }
    else
    {
        currentMode=hueMode;
    }
    syncColor(color);
}

void KCColorDoubleBoardBase::syncColor(const QColor &color)
{
    if(currentMode==saturationMode)
    {
        saturationGradient=QLinearGradient(0,0,width(),0);
        QColor color0, color16, color33, color50, color66, color83, color100;
        color0.setHsv(0, color.saturation(), 255);
        color16.setHsv(60, color.saturation(), 255);
        color33.setHsv(120, color.saturation(), 255);
        color50.setHsv(180, color.saturation(), 255);
        color66.setHsv(240, color.saturation(), 255);
        color83.setHsv(300, color.saturation(), 255);
        color100.setHsv(0, color.saturation(), 255);
        saturationGradient.setColorAt(0.00, color0);
        saturationGradient.setColorAt(0.16, color16);
        saturationGradient.setColorAt(0.33, color33);
        saturationGradient.setColorAt(0.50, color50);
        saturationGradient.setColorAt(0.66, color66);
        saturationGradient.setColorAt(0.83, color83);
        saturationGradient.setColorAt(1.00, color100);
        hsvGreyGradient.setColorAt(0, QColor(0,0,0,0));
        hsvGreyGradient.setColorAt(1, QColor(0,0,0,255));
    }
    else if(currentMode==valueMode)
    {
        saturationGradient=QLinearGradient(0,0,width(),0);
        QColor color0, color16, color33, color50, color66, color83, color100;
        color0.setHsv(0, 255, color.value());
        color16.setHsv(60, 255, color.value());
        color33.setHsv(120, 255, color.value());
        color50.setHsv(180, 255, color.value());
        color66.setHsv(240, 255, color.value());
        color83.setHsv(300, 255, color.value());
        color100.setHsv(0, 255, color.value());
        saturationGradient.setColorAt(0.00, color0);
        saturationGradient.setColorAt(0.16, color16);
        saturationGradient.setColorAt(0.33, color33);
        saturationGradient.setColorAt(0.50, color50);
        saturationGradient.setColorAt(0.66, color66);
        saturationGradient.setColorAt(0.83, color83);
        saturationGradient.setColorAt(1.00, color100);
        hsvGreyGradient.setColorAt(0, QColor(255,255,255,0));
        hsvGreyGradient.setColorAt(1, QColor(255,255,255,255));
    }
    else
    {
        hueLevelGradient=QRadialGradient(width(),0,width(),width(),0);
        QColor startColor, endColor;
        startColor.setHsv(color.hue(), 255, 255);
        endColor.setHsv(color.hue(), 0, 255);
        hueLevelGradient.setColorAt(0, startColor);
        hueLevelGradient.setColorAt(1, endColor);
        hsvGreyGradient.setColorAt(0, QColor(0,0,0,0));
        hsvGreyGradient.setColorAt(1, QColor(0,0,0,255));
    }
    update();
}

void KCColorDoubleBoardBase::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    QRect renderRect(2,2,255,255);
    painter.setPen(QColor(0xcf, 0xcf, 0xcf));
    painter.drawRect(0,0,258,258);
    painter.setPen(Qt::NoPen);
    switch(currentMode)
    {
    case hueMode:
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(hueLevelGradient));
        painter.drawRect(renderRect);
        painter.setBrush(QBrush(hsvGreyGradient));
        painter.drawRect(renderRect);
        break;
    case saturationMode:
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(saturationGradient));
        painter.drawRect(renderRect);
        painter.setBrush(QBrush(hsvGreyGradient));
        painter.drawRect(renderRect);
        break;
    case valueMode:
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(saturationGradient));
        painter.drawRect(renderRect);
        painter.setBrush(QBrush(hsvGreyGradient));
        painter.drawRect(renderRect);
        break;
    }
}

void KCColorDoubleBoardBase::resizeEvent(QResizeEvent *event)
{
    int widthElement=event->size().width(),
        heightElement=event->size().height();
    if(widthElement!=heightElement)
    {
        int minimumElement=heightElement<widthElement?
                    heightElement:
                    widthElement;
        event->ignore();
        resize(minimumElement,minimumElement);
        return;
    }
    hueLevelGradient.setCenter(widthElement,0);
    hueLevelGradient.setFocalPoint(widthElement,0);
    hueLevelGradient.setRadius(widthElement);
    hsvGreyGradient.setFinalStop(0,widthElement);
    saturationGradient.setFinalStop(widthElement,0);
    rgbHorizontalGradient.setFinalStop(widthElement, widthElement);
    QWidget::resizeEvent(event);
}

KCColorRingBoard::KCColorRingBoard(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(424,424);
    ringGradient.setColorAt(0.00, QColor(255,0,0));
    ringGradient.setColorAt(0.16, QColor(255,0,255));
    ringGradient.setColorAt(0.33, QColor(0,0,255));
    ringGradient.setColorAt(0.50, QColor(0,255,255));
    ringGradient.setColorAt(0.66, QColor(0,255,0));
    ringGradient.setColorAt(0.83, QColor(255,255,0));
    ringGradient.setColorAt(1.00, QColor(255,0,0));
}

void KCColorRingBoard::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QRect paintRect(2,2,width()-4,width()-4);
    QPainter painter(this);
    painter.setPen(QColor(0xcf, 0xcf, 0xcf));
    painter.drawEllipse(0,0,width()-1,width()-1);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(ringGradient));
    painter.drawEllipse(paintRect);
    painter.setBrush(QBrush(palette().color(QPalette::Window)));
    paintRect.setTopLeft(QPoint(ringWidth-1, ringWidth-1));
    paintRect.setBottomRight(QPoint(width()-ringWidth+1,
                                    width()-ringWidth+1));
    painter.drawEllipse(paintRect);
    painter.setPen(QColor(0xcf, 0xcf, 0xcf));
    paintRect.setTopLeft(QPoint(ringWidth, ringWidth));
    paintRect.setBottomRight(QPoint(width()-ringWidth,
                                    width()-ringWidth));
    painter.drawEllipse(paintRect);
}

void KCColorRingBoard::resizeEvent(QResizeEvent *event)
{
    int widthElement=event->size().width(),
        heightElement=event->size().height();
    if(widthElement!=heightElement)
    {
        int minimumElement=heightElement<widthElement?
                    heightElement:
                    widthElement;
        event->ignore();
        resize(minimumElement,minimumElement);
        return;
    }
    ringGradient.setCenter(widthElement/2,
                           widthElement/2);
    QWidget::resizeEvent(event);
}

KCColorHSVRing::KCColorHSVRing(QWidget *parent) :
    QWidget(parent)
{
    setContentsMargins(0,0,0,0);
    setFixedSize(424,424);
    ringBoard=new KCColorRingBoard(this);
    doubleBoard=new KCColorDoubleBoardBase(this);
    doubleBoard->move(83,83);
}

void KCColorHSVRing::setColorMode(QString elementName,
                                  int value,
                                  QColor color)
{
    doubleBoard->setColor(elementName,
                          color);
}

void KCColorHSVRing::syncColor(QColor color)
{
    doubleBoard->syncColor(color);
}

KCColorLevelRenderBase::KCColorLevelRenderBase(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(260,25);
    levelGradient.setStart(0,0);
    levelGradient.setFinalStop(width(),
                               height());
}

void KCColorLevelRenderBase::focusOnElement(QString elementName,
                                            QColor color)
{
    levelGradient=QLinearGradient(0,0,width(),height());
    //**RGB Mode**
    if(elementName=="R:")
    {
        levelGradient.setColorAt(0.0, QColor(0,color.green(),color.blue()));
        levelGradient.setColorAt(1.0, QColor(255,color.green(),color.blue()));
    }
    else if(elementName=="G:")
    {
        levelGradient.setColorAt(0.0, QColor(color.red(),0,color.blue()));
        levelGradient.setColorAt(1.0, QColor(color.red(),255,color.blue()));
    }
    else if(elementName=="B:")
    {
        levelGradient.setColorAt(0.0, QColor(color.red(),color.green(),0));
        levelGradient.setColorAt(1.0, QColor(color.red(),color.green(),255));
    }
    else if(elementName=="H:")
    {
        levelGradient.setColorAt(0.00, QColor(255,0,0));
        levelGradient.setColorAt(0.16, QColor(255,0,255));
        levelGradient.setColorAt(0.33, QColor(0,0,255));
        levelGradient.setColorAt(0.50, QColor(0,255,255));
        levelGradient.setColorAt(0.66, QColor(0,255,0));
        levelGradient.setColorAt(0.83, QColor(255,255,0));
        levelGradient.setColorAt(1.00, QColor(255,0,0));
    }
    else if(elementName=="S:")
    {
        QColor startColor, endColor;
        startColor.setHsl(color.hue(), 0, color.lightness());
        endColor.setHsl(color.hue(), 255, color.lightness());
        levelGradient.setColorAt(0.0, startColor);
        levelGradient.setColorAt(1.0, endColor);
    }
    else if(elementName=="L:")
    {
        QColor startColor, endColor;
        startColor.setHsl(color.hue(), color.saturation(), 0);
        endColor.setHsl(color.hue(), color.saturation(), 255);
        levelGradient.setColorAt(0.0, startColor);
        levelGradient.setColorAt(1.0, endColor);
    }
    else if(elementName=="V:")
    {
        QColor startColor, endColor;
        startColor.setHsv(color.hue(), color.saturation(), 0);
        endColor.setHsv(color.hue(), color.saturation(), 255);
        levelGradient.setColorAt(0.0, startColor);
        levelGradient.setColorAt(1.0, endColor);
    }
    else if(elementName=="C:")
    {
        QColor startColor, endColor;
        startColor.setCmyk(0, color.magenta(), color.yellow(), color.black());
        endColor.setCmyk(255, color.magenta(), color.yellow(), color.black());
        levelGradient.setColorAt(0.0, startColor);
        levelGradient.setColorAt(1.0, endColor);
    }
    else if(elementName=="M:")
    {
        QColor startColor, endColor;
        startColor.setCmyk(color.cyan(), 0, color.yellow(), color.black());
        endColor.setCmyk(color.cyan(), 255, color.yellow(), color.black());
        levelGradient.setColorAt(0.0, startColor);
        levelGradient.setColorAt(1.0, endColor);
    }
    else if(elementName=="Y:")
    {
        QColor startColor, endColor;
        startColor.setCmyk(color.cyan(), color.magenta(), 0, color.black());
        endColor.setCmyk(color.cyan(), color.magenta(), 255, color.black());
        levelGradient.setColorAt(0.0, startColor);
        levelGradient.setColorAt(1.0, endColor);
    }
    else if(elementName=="K:")
    {
        QColor startColor, endColor;
        startColor.setCmyk(color.cyan(), color.magenta(), color.yellow(), 0);
        endColor.setCmyk(color.cyan(), color.magenta(), color.yellow(), 255);
        levelGradient.setColorAt(0.0, startColor);
        levelGradient.setColorAt(1.0, endColor);
    }
    update();
}

void KCColorLevelRenderBase::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QColor(0xcf, 0xcf, 0xcf));
    painter.drawRect(QRect(0,0,259,23));
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(levelGradient));
    painter.drawRect(QRect(2,2,256,20));
}

void KCColorLevelRenderBase::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    levelGradient.setFinalStop(width(),
                               height());
}

void KCColorLevelRenderBase::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    isPressed=true;
    int haruka=event->pos().x()-2;
    if(haruka>-1 && haruka<257)
    {
        valueChanged(haruka);
    }
}

void KCColorLevelRenderBase::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if(isPressed)
    {
        int haruka=event->pos().x()-2;
        if(haruka<0)
        {
            valueChanged(0);
        }
        else if(haruka>256)
        {
            valueChanged(256);
        }
        else
        {
            valueChanged(haruka);
        }
    }
}

void KCColorLevelRenderBase::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    isPressed=false;
}

KCColorLevelSelector::KCColorLevelSelector(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(300,50);
    colorRender=new KCColorLevelRenderBase(this);
    colorRender->move(2,8);
    colorSelector=new QLabel(this);
    colorSelector->setPixmap(QPixmap(":/img/image/ColorPointer.png"));
    connect(colorRender, SIGNAL(valueChanged(int)),
            this, SLOT(slide(int)));
}

void KCColorLevelSelector::focusOnElement(QString elementName,
                                          int value,
                                          QColor color)
{
    slide(value);
    colorRender->focusOnElement(elementName, color);
}

void KCColorLevelSelector::slide(int position)
{
    colorSelector->move(position, 0);
}

void KCColorLevelSelector::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

KCColorSpinBox::KCColorSpinBox(QWidget *parent) :
    QSpinBox(parent)
{
    ;
}

void KCColorSpinBox::mousePressEvent(QMouseEvent *event)
{
    QSpinBox::mousePressEvent(event);
    emit spinPressed();
}

KCColorViewerBase::KCColorViewerBase(QWidget *parent) :
    QWidget(parent)
{
    currentViewer=new QWidget(this);
    currentViewer->setAutoFillBackground(true);
    originalViewer=new QWidget(this);
    originalViewer->setAutoFillBackground(true);
    currentPalette=currentViewer->palette();
    buildViewer();
}

void KCColorViewerBase::buildViewer()
{
    mainLayout=new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->addWidget(currentViewer);
    mainLayout->addWidget(originalViewer);
}

void KCColorViewerBase::setOriginalColor(QColor color)
{
    QPalette pal=originalViewer->palette();
    pal.setColor(QPalette::Window, color);
    originalViewer->setPalette(pal);
}

void KCColorViewerBase::setCurrentColor(QColor color)
{
    currentPalette.setColor(QPalette::Window, color);
    currentViewer->setPalette(currentPalette);
}

KCColorSliderItemBase::KCColorSliderItemBase(QWidget *parent,
                                             bool autoBuild) :
    QWidget(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(3);
    setLayout(mainLayout);

    elementCaption=new QRadioButton(this);
    elementSpinBox=new KCColorSpinBox(this);
    elementSlider=new QSlider(Qt::Horizontal, this);

    connect(elementCaption, SIGNAL(clicked()),
            this, SLOT(onActionClickElement()));

    if(autoBuild)
    {
        buildSlider();
    }
}

void KCColorSliderItemBase::buildSlider()
{
    mainLayout->addWidget(elementCaption);
    mainLayout->addWidget(elementSpinBox);
    mainLayout->addWidget(elementSlider,1);
    connect(elementSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(setValue(int)));
    connect(elementSlider, SIGNAL(valueChanged(int)),
            this, SLOT(setValue(int)));
    connect(elementSlider, SIGNAL(sliderPressed()),
            this, SLOT(onActionClickElement()));
    connect(elementSpinBox, SIGNAL(spinPressed()),
            this, SLOT(onActionClickElement()));
}

void KCColorSliderItemBase::setCaption(const QString &value)
{
    elementCaption->setText(value);
}

void KCColorSliderItemBase::setMinimum(const int &value)
{
    elementSlider->setMinimum(value);
    elementSpinBox->setMinimum(value);
}

void KCColorSliderItemBase::setMaximum(const int &value)
{
    elementSlider->setMaximum(value);
    elementSpinBox->setMaximum(value);
}

void KCColorSliderItemBase::setRange(const int &minimumValue,
                                     const int &maximumValue)
{
    elementSlider->setRange(minimumValue, maximumValue);
    elementSpinBox->setMinimum(minimumValue);
    elementSpinBox->setMaximum(maximumValue);
}

int KCColorSliderItemBase::getValue()
{
    return elementSpinBox->value();
}

void KCColorSliderItemBase::syncValue(const int &value)
{
    syncMode=true;
    setValue(value);
    syncMode=false;
}

void KCColorSliderItemBase::setValue(int value)
{
    elementSpinBox->setValue(value);
    elementSlider->setValue(value);
    if(!syncMode)
    {
        emit requireElementChanged(elementCaption->text(),
                                   value);
    }
}

void KCColorSliderItemBase::setEraseFocus()
{
    if(focusSignalSent)
    {
        focusSignalSent=false;
    }
    else
    {
        elementCaption->setChecked(false);
    }
}

void KCColorSliderItemBase::onActionClickElement()
{
    elementCaption->setChecked(true);
    focusSignalSent=true;
    emit requireFocusOnElement(elementCaption->text(),
                               elementSpinBox->value());
}

KCColorSliderItemPercent::KCColorSliderItemPercent(QWidget *parent) :
    KCColorSliderItemBase(parent, false)
{
    setRange(0, 100);
    buildSlider();
}

void KCColorSliderItemPercent::setRealRange(int min, int max)
{
    if(max<min || min > max)
    {
        qWarning()<<"Invaild value.";
        return;
    }
    realMinimum=min;
    realMaximum=max;
    delta=realMaximum-realMinimum;
}

int KCColorSliderItemPercent::getOriginalValue()
{
    return calculateValue(elementSpinBox->value());
}

void KCColorSliderItemPercent::buildSlider()
{
    percentCaption=new QLabel("%", this);
    mainLayout->addWidget(elementCaption);
    mainLayout->addWidget(elementSpinBox);
    mainLayout->addWidget(percentCaption);
    mainLayout->addWidget(elementSlider,1);
    connect(elementSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(setOriginalValue(int)));
    connect(elementSlider, SIGNAL(valueChanged(int)),
            this, SLOT(setOriginalValue(int)));
    connect(elementSlider, SIGNAL(sliderPressed()),
            this, SLOT(onActionClickElement()));
    connect(elementSpinBox, SIGNAL(spinPressed()),
            this, SLOT(onActionClickElement()));
}

void KCColorSliderItemPercent::syncValue(const int &value)
{
    syncMode=true;
    setValue(value);
    syncMode=false;
}

void KCColorSliderItemPercent::setValue(int value)
{
    if(signalSentByMe)
    {
        signalSentByMe=false;
    }
    else
    {
        setOriginalValue((value-realMinimum)*100/delta);
    }
}

void KCColorSliderItemPercent::syncOriginalValue(const int &value)
{
    KCColorSliderItemBase::syncValue(value);
}

void KCColorSliderItemPercent::setOriginalValue(int value)
{
    elementSpinBox->setValue(value);
    elementSlider->setValue(value);
    if(!syncMode)
    {
        signalSentByMe=true;
        emit requireElementChanged(elementCaption->text(),
                                   calculateValue(value));
    }
}

int KCColorSliderItemPercent::calculateValue(int percent)
{
    return realMinimum+percent*delta/100;
}

KCColorSliderBase::KCColorSliderBase(QWidget *parent) :
    QWidget(parent)
{
    ;
}

KCColorSliderItemBase *KCColorSliderBase::addElement(const QString &name,
                                                     const int &min,
                                                     const int &max)
{
    KCColorSliderItemBase *currentElement=new KCColorSliderItemBase(this);
    currentElement->setCaption(name);
    currentElement->setRange(min, max);
    connect(currentElement, &KCColorSliderItemBase::requireFocusOnElement,
            this, &KCColorSliderBase::focusRequire);
    connect(this, SIGNAL(requireClearElementsFocus()),
            currentElement, SLOT(setEraseFocus()));
    return currentElement;
}

void KCColorSliderBase::syncColor(QColor color)
{
    currentColor=color;
}

void KCColorSliderBase::focusRequire(QString elementName,
                                     int value)
{
    emit requireFocusOnElement(elementName, value, currentColor);
}

KCColorSliderCMYKP::KCColorSliderCMYKP(QWidget *parent) :
    KCColorSliderBase(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    setLayout(mainLayout);
    cyanElement=addElement("C:", 0, 255);
    magentaElement=addElement("M:", 0, 255);
    yellowElement=addElement("Y:", 0, 255);
    blackElement=addElement("K:", 0, 255);

    connect(cyanElement, &KCColorSliderItemPercent::requireElementChanged,
            this, &KCColorSliderCMYKP::syncElement);
    connect(magentaElement, &KCColorSliderItemPercent::requireElementChanged,
            this, &KCColorSliderCMYKP::syncElement);
    connect(yellowElement, &KCColorSliderItemPercent::requireElementChanged,
            this, &KCColorSliderCMYKP::syncElement);
    connect(blackElement, &KCColorSliderItemPercent::requireElementChanged,
            this, &KCColorSliderCMYKP::syncElement);

    mainLayout->addWidget(cyanElement);
    mainLayout->addWidget(magentaElement);
    mainLayout->addWidget(yellowElement);
    mainLayout->addWidget(blackElement);
}

KCColorSliderItemPercent *KCColorSliderCMYKP::addElement(const QString &name,
                                                         const int &min,
                                                         const int &max)
{
    KCColorSliderItemPercent *currentElement=new KCColorSliderItemPercent(this);
    currentElement->setCaption(name);
    currentElement->setRealRange(min,max);
    connect(currentElement, &KCColorSliderItemPercent::requireFocusOnElement,
            this, &KCColorSliderCMYKP::focusRequire);
    connect(this, SIGNAL(requireClearElementsFocus()),
            currentElement, SLOT(setEraseFocus()));
    return currentElement;
}

void KCColorSliderCMYKP::syncElement(QString elementName, int value)
{
    if(elementName=="C:")
    {
        currentColor.setCmyk(value,
                             magentaElement->getOriginalValue(),
                             yellowElement->getOriginalValue(),
                             blackElement->getOriginalValue());
    }
    else if(elementName=="M:")
    {
        currentColor.setCmyk(cyanElement->getOriginalValue(),
                             value,
                             yellowElement->getOriginalValue(),
                             blackElement->getOriginalValue());
    }
    else if(elementName=="Y:")
    {
        currentColor.setCmyk(cyanElement->getOriginalValue(),
                             magentaElement->getOriginalValue(),
                             value,
                             blackElement->getOriginalValue());
    }
    else if(elementName=="K:")
    {
        currentColor.setCmyk(cyanElement->getOriginalValue(),
                             magentaElement->getOriginalValue(),
                             yellowElement->getOriginalValue(),
                             value);
    }
    else
    {
        //Here should never comes.
        qWarning()<<"Unexpected elements occur.";
        return;
    }
    signalSentByMe=true;
    emit requireSyncColor(currentColor);
}

void KCColorSliderCMYKP::syncColor(QColor color)
{
    if(signalSentByMe)
    {
        signalSentByMe=false;
        return;
    }
    KCColorSliderBase::syncColor(color);
    cyanElement->syncValue(color.cyan());
    magentaElement->syncValue(color.magenta());
    yellowElement->syncValue(color.yellow());
    blackElement->syncValue(color.black());
}

void KCColorSliderCMYKP::focusRequire(QString elementName, int value)
{
    emit requireFocusOnElement(elementName,
                               value,
                               currentColor);
}

KCColorSliderCMYK::KCColorSliderCMYK(QWidget *parent) :
    KCColorSliderBase(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    setLayout(mainLayout);
    cyanElement=addElement("C:", 0, 255);
    magentaElement=addElement("M:", 0, 255);
    yellowElement=addElement("Y:", 0, 255);
    blackElement=addElement("K:", 0, 255);

    connect(cyanElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderCMYK::syncElement);
    connect(magentaElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderCMYK::syncElement);
    connect(yellowElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderCMYK::syncElement);
    connect(blackElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderCMYK::syncElement);

    mainLayout->addWidget(cyanElement);
    mainLayout->addWidget(magentaElement);
    mainLayout->addWidget(yellowElement);
    mainLayout->addWidget(blackElement);
}

void KCColorSliderCMYK::syncElement(QString elementName, int value)
{
    if(elementName=="C:")
    {
        currentColor.setCmyk(value,
                             magentaElement->getValue(),
                             yellowElement->getValue(),
                             blackElement->getValue());
    }
    else if(elementName=="M:")
    {
        currentColor.setCmyk(cyanElement->getValue(),
                             value,
                             yellowElement->getValue(),
                             blackElement->getValue());
    }
    else if(elementName=="Y:")
    {
        currentColor.setCmyk(cyanElement->getValue(),
                             magentaElement->getValue(),
                             value,
                             blackElement->getValue());
    }
    else if(elementName=="K:")
    {
        currentColor.setCmyk(cyanElement->getValue(),
                             magentaElement->getValue(),
                             yellowElement->getValue(),
                             value);
    }
    else
    {
        //Here should never comes.
        qWarning()<<"Unexpected elements occur.";
        return;
    }
    signalSentByMe=true;
    emit requireSyncColor(currentColor);
}

void KCColorSliderCMYK::syncColor(QColor color)
{
    if(signalSentByMe)
    {
        signalSentByMe=false;
        return;
    }
    KCColorSliderBase::syncColor(color);
    cyanElement->syncValue(color.cyan());
    magentaElement->syncValue(color.magenta());
    yellowElement->syncValue(color.yellow());
    blackElement->syncValue(color.black());
}

KCColorSliderRGB::KCColorSliderRGB(QWidget *parent) :
    KCColorSliderBase(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    setLayout(mainLayout);
    redElement=addElement("R:", 0, 255);
    greenElement=addElement("G:", 0, 255);
    blueElement=addElement("B:", 0, 255);

    connect(redElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderRGB::syncElement);
    connect(greenElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderRGB::syncElement);
    connect(blueElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderRGB::syncElement);

    mainLayout->addWidget(redElement);
    mainLayout->addWidget(greenElement);
    mainLayout->addWidget(blueElement);
}

void KCColorSliderRGB::syncElement(QString elementName, int value)
{
    if(elementName=="R:")
    {
        currentColor.setRed(value);
    }
    else if(elementName=="G:")
    {
        currentColor.setGreen(value);
    }
    else if(elementName=="B:")
    {
        currentColor.setBlue(value);
    }
    else
    {
        //Here should never comes.
        qWarning()<<"Unexpected elements occur.";
        return;
    }
    signalSentByMe=true;
    emit requireSyncColor(currentColor);
}

void KCColorSliderRGB::syncColor(QColor color)
{
    if(signalSentByMe)
    {
        signalSentByMe=false;
        return;
    }
    KCColorSliderBase::syncColor(color);
    redElement->syncValue(color.red());
    greenElement->syncValue(color.green());
    blueElement->syncValue(color.blue());
}


KCColorSliderHSL::KCColorSliderHSL(QWidget *parent) :
    KCColorSliderBase(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    setLayout(mainLayout);
    hueElement=addElement("H:", 0, 359);
    saturationElement=addElement("S:", 0, 255);
    lightnessElement=addElement("L:", 0, 255);

    connect(hueElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderHSL::syncElement);
    connect(saturationElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderHSL::syncElement);
    connect(lightnessElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderHSL::syncElement);

    mainLayout->addWidget(hueElement);
    mainLayout->addWidget(saturationElement);
    mainLayout->addWidget(lightnessElement);
}

void KCColorSliderHSL::syncElement(QString elementName, int value)
{
    if(elementName=="H:")
    {
        currentColor.setHsl(value,
                            saturationElement->getValue(),
                            lightnessElement->getValue());
    }
    else if(elementName=="S:")
    {
        currentColor.setHsl(hueElement->getValue(),
                            value,
                            lightnessElement->getValue());
    }
    else if(elementName=="L:")
    {
        currentColor.setHsl(hueElement->getValue(),
                            saturationElement->getValue(),
                            value);
    }
    else
    {
        //Here should never comes.
        qWarning()<<"Unexpected elements occur.";
        return;
    }
    signalSentByMe=true;
    emit requireSyncColor(currentColor);
}

void KCColorSliderHSL::syncColor(QColor color)
{
    if(signalSentByMe)
    {
        signalSentByMe=false;
        return;
    }
    KCColorSliderBase::syncColor(color);
    hueElement->syncValue(color.hue());
    saturationElement->syncValue(color.saturation());
    lightnessElement->syncValue(color.lightness());
}

KCColorSliderHSV::KCColorSliderHSV(QWidget *parent) :
    KCColorSliderBase(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::TopToBottom, this);
    setLayout(mainLayout);
    hueElement=addElement("H:", 0, 359);
    saturationElement=addElement("S:", 0, 255);
    valueElement=addElement("V:", 0, 255);

    connect(hueElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderHSV::syncElement);
    connect(saturationElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderHSV::syncElement);
    connect(valueElement, &KCColorSliderItemBase::requireElementChanged,
            this, &KCColorSliderHSV::syncElement);

    mainLayout->addWidget(hueElement);
    mainLayout->addWidget(saturationElement);
    mainLayout->addWidget(valueElement);;
}

void KCColorSliderHSV::syncElement(QString elementName, int value)
{
    if(elementName=="H:")
    {
        currentColor.setHsv(value,
                            saturationElement->getValue(),
                            valueElement->getValue());
    }
    else if(elementName=="S:")
    {
        currentColor.setHsv(hueElement->getValue(),
                            value,
                            valueElement->getValue());
    }
    else if(elementName=="V:")
    {
        currentColor.setHsv(hueElement->getValue(),
                            saturationElement->getValue(),
                            value);
    }
    else
    {
        //Here should never comes.
        qWarning()<<"Unexpected elements occur.";
        return;
    }
    signalSentByMe=true;
    emit requireSyncColor(currentColor);
}

void KCColorSliderHSV::syncColor(QColor color)
{
    if(signalSentByMe)
    {
        signalSentByMe=false;
        return;
    }
    KCColorSliderBase::syncColor(color);
    hueElement->syncValue(color.hue());
    saturationElement->syncValue(color.saturation());
    valueElement->syncValue(color.value());
}

KCColorSelector::KCColorSelector(QWidget *parent) :
    QDialog(parent)
{
    mainLayout=new QBoxLayout(QBoxLayout::LeftToRight, this);
    setLayout(mainLayout);

    colorRingLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    KCColorHSVRing *colorRing=new KCColorHSVRing(this);
    registerHSVRing(colorRing);
    colorRingLayout->addWidget(colorRing);
    KCColorLevelSelector *levelSelector=new KCColorLevelSelector(this);
    registerLevelSelector(levelSelector);
    colorRingLayout->addWidget(levelSelector);
    mainLayout->addLayout(colorRingLayout);

    iroriModelLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    KCColorSliderHSV *hsv=new KCColorSliderHSV(this);
    registerSelector(hsv);
    iroriModelLayout->addWidget(hsv);
    KCColorSliderCMYK *cmyk=new KCColorSliderCMYK(this);
    registerSelector(cmyk);
    iroriModelLayout->addWidget(cmyk);
    KCColorSliderRGB *rgb=new KCColorSliderRGB(this);
    registerSelector(rgb);
    iroriModelLayout->addWidget(rgb);
    iroriModelLayout->addStretch();
    mainLayout->addLayout(iroriModelLayout);

    yayaModelLayout=new QBoxLayout(QBoxLayout::TopToBottom);
    KCColorSliderHSL *hsl=new KCColorSliderHSL(this);
    registerSelector(hsl);
    yayaModelLayout->addWidget(hsl);
    KCColorSliderCMYKP *cmykp=new KCColorSliderCMYKP(this);
    registerSelector(cmykp);
    yayaModelLayout->addWidget(cmykp);
    yayaModelLayout->addStretch();
    mainLayout->addLayout(yayaModelLayout);
    /*
    KCColorViewerBase *viewer=new KCColorViewerBase(this);
    registerViewer(viewer);
    mainLayout->addWidget(viewer);
    */
    emit requireSyncColor(QColor(0,0,0));
}

KCColorSelector::~KCColorSelector()
{
    colorRingLayout->deleteLater();
    iroriModelLayout->deleteLater();
    yayaModelLayout->deleteLater();
}

void KCColorSelector::registerSelector(KCColorSliderBase *selector)
{
    connect(selector, &KCColorSliderBase::requireSyncColor,
            this, &KCColorSelector::requireSyncColor);
    connect(selector, &KCColorSliderBase::requireFocusOnElement,
            this, &KCColorSelector::requireFocusOnElement);
    connect(selector, SIGNAL(requireFocusOnElement(QString,int,QColor)),
            this, SIGNAL(requireClearFocus()));
    connect(this, SIGNAL(requireSyncColor(QColor)),
            selector, SLOT(syncColor(QColor)));
    connect(this, &KCColorSelector::requireClearFocus,
            selector, &KCColorSliderBase::requireClearElementsFocus);
}

void KCColorSelector::registerViewer(KCColorViewerBase *viewer)
{
    connect(this, SIGNAL(requireSyncColor(QColor)),
            viewer, SLOT(setCurrentColor(QColor)));
}

void KCColorSelector::registerLevelSelector(KCColorLevelSelector *levelSelector)
{
    connect(this, &KCColorSelector::requireFocusOnElement,
            levelSelector, &KCColorLevelSelector::focusOnElement);
    /*connect(this, &KCColorSelector::requireSyncColor,
            levelSelector, &KCColorLevelSelector);*/
}

void KCColorSelector::registerHSVRing(KCColorHSVRing *hsvRing)
{
    connect(this, &KCColorSelector::requireFocusOnElement,
            hsvRing, &KCColorHSVRing::setColorMode);
    connect(this, &KCColorSelector::requireSyncColor,
            hsvRing, &KCColorHSVRing::syncColor);
}