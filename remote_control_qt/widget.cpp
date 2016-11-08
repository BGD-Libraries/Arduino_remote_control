#include "widget.h"
#include "ui_widget.h"
#include "crc_check.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }
    //设置波特率下拉菜单默认显示第三项
    //ui->BaudBox->setCurrentIndex(3);
    //启用定时器
    m_SerialTimerId = startTimer(15);
    qDebug() << tr("界面设定成功！");
}

Widget::~Widget()
{
    if ( m_SerialTimerId != 0 )
        killTimer(m_SerialTimerId);
    delete ui;
}

/*----读取接收到的数据--------------------------------------------------------------*/
void Widget::read_data(void)
{
    QByteArray buf;
    buf = serial->readAll();
    if(!buf.isNull())
    {
        QString str = ui->textBrowser->toPlainText();
        str+=tr(buf);
        ui->textBrowser->clear();
        ui->textBrowser->append(str);
    }
    buf.clear();
}
/*-----清空接收窗口 ----------------------------------------------------------------------------*/
void Widget::on_clearButton_clicked()
{
    ui->textBrowser->clear();
}
/*----打开串口按钮-------------------------------------------------------------------*/
void Widget::on_openButton_clicked()
{
    if(ui->openButton->text()==tr("打开串口"))
    {
        serial = new QSerialPort;
        //设置串口名
        serial->setPortName(ui->PortBox->currentText());
        //打开串口
        serial->open(QIODevice::ReadWrite);
        //设置波特率
        serial->setBaudRate(ui->BaudBox->currentText().toInt());
        //设置数据位数
        switch(ui->BitNumBox->currentText().toInt())
        {
        case 5:
            serial->setDataBits(QSerialPort::Data5);
            qDebug() << tr("设置数据位5");
            break;
        case 6:
            serial->setDataBits(QSerialPort::Data6);
            qDebug() << tr("设置数据位6");
            break;
        case 7:
            serial->setDataBits(QSerialPort::Data7);
            qDebug() << tr("设置数据位7");
            break;
        case 8:
            serial->setDataBits(QSerialPort::Data8);
            qDebug() << tr("设置数据位8");
            break;
        default:
            break;
        }
        //设置奇偶校验
        switch(ui->ParityBox->currentIndex())
        {
        case 0:
            serial->setParity(QSerialPort::NoParity);
            qDebug() << tr("无校验");
            break;
        case 1:
            serial->setParity(QSerialPort::OddParity);
            qDebug() << tr("奇校验");
            break;
        case 2:
            serial->setParity(QSerialPort::EvenParity);
            qDebug() << tr("偶校验");
            break;
        default: break;
        }
        //设置停止位
        switch(ui->StopBox->currentText().toInt())
        {
        case 1:
            serial->setStopBits(QSerialPort::OneStop);
            qDebug() << tr("停止位1");
            break;
        case 2:
            serial->setStopBits(QSerialPort::TwoStop);
            qDebug() << tr("停止位2");
            break;
        default: break;
        }
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->BitNumBox->setEnabled(false);
        ui->ParityBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        ui->openButton->setText(tr("关闭串口"));
        SerialStateOn = true;

        //连接信号槽
        QObject::connect(serial, &QSerialPort::readyRead, this, &Widget::read_data);
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        //恢复设置使能
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->BitNumBox->setEnabled(true);
        ui->ParityBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        ui->openButton->setText(tr("打开串口"));
        SerialStateOn = false;
    }
}
/*----键盘按下事件-------------------------------------------------------------------*/
void Widget::keyPressEvent( QKeyEvent* event )
{
    if (!event->isAutoRepeat()) {
        switch ( event->key( ) ) {
        case Qt::Key_0:       SaveKeyPressed( KEY_0 ); break;
        case Qt::Key_1:       SaveKeyPressed( KEY_1 ); break;
        case Qt::Key_2:       SaveKeyPressed( KEY_2 ); break;
        case Qt::Key_3:       SaveKeyPressed( KEY_3 ); break;
        case Qt::Key_4:       SaveKeyPressed( KEY_4 ); break;
        case Qt::Key_5:       SaveKeyPressed( KEY_5 ); break;
        case Qt::Key_6:       SaveKeyPressed( KEY_6 ); break;
        case Qt::Key_7:       SaveKeyPressed( KEY_7 ); break;
        case Qt::Key_8:       SaveKeyPressed( KEY_8 ); break;
        case Qt::Key_9:       SaveKeyPressed( KEY_9 ); break;

        case Qt::Key_A:       SaveKeyPressed( KEY_A ); break;
        case Qt::Key_B:       SaveKeyPressed( KEY_B ); break;
        case Qt::Key_C:       SaveKeyPressed( KEY_C ); break;
        case Qt::Key_D:       SaveKeyPressed( KEY_D ); break;
        case Qt::Key_E:       SaveKeyPressed( KEY_E ); break;
        case Qt::Key_F:       SaveKeyPressed( KEY_F ); break;
        case Qt::Key_G:       SaveKeyPressed( KEY_G ); break;
        case Qt::Key_H:       SaveKeyPressed( KEY_H ); break;
        case Qt::Key_I:       SaveKeyPressed( KEY_I ); break;
        case Qt::Key_J:       SaveKeyPressed( KEY_J ); break;
        case Qt::Key_K:       SaveKeyPressed( KEY_K ); break;
        case Qt::Key_L:       SaveKeyPressed( KEY_L ); break;
        case Qt::Key_M:       SaveKeyPressed( KEY_M ); break;
        case Qt::Key_N:       SaveKeyPressed( KEY_N ); break;
        case Qt::Key_O:       SaveKeyPressed( KEY_O ); break;
        case Qt::Key_P:       SaveKeyPressed( KEY_P ); break;
        case Qt::Key_Q:       SaveKeyPressed( KEY_Q ); break;
        case Qt::Key_R:       SaveKeyPressed( KEY_R ); break;
        case Qt::Key_S:       SaveKeyPressed( KEY_S ); break;
        case Qt::Key_T:       SaveKeyPressed( KEY_T ); break;
        case Qt::Key_U:       SaveKeyPressed( KEY_U ); break;
        case Qt::Key_V:       SaveKeyPressed( KEY_V ); break;
        case Qt::Key_W:       SaveKeyPressed( KEY_W ); break;
        case Qt::Key_X:       SaveKeyPressed( KEY_X ); break;
        case Qt::Key_Y:       SaveKeyPressed( KEY_Y ); break;
        case Qt::Key_Z:       SaveKeyPressed( KEY_Z ); break;

        case Qt::Key_Control: SaveKeyPressed( KEY_CTRL ); break;
        case Qt::Key_Shift:   SaveKeyPressed( KEY_SHIFT ); break;
        case Qt::Key_Alt:     SaveKeyPressed( KEY_ALT ); break;
        case Qt::Key_Tab:     SaveKeyPressed( KEY_TAB ); break;
        case Qt::Key_Space:   SaveKeyPressed( KEY_SPACE ); break;
        case Qt::Key_Escape:  SaveKeyPressed( KEY_ESCAPE ); break;

        case Qt::Key_Up:      SaveKeyPressed( KEY_UP ); break;
        case Qt::Key_Down:    SaveKeyPressed( KEY_DOWN ); break;
        case Qt::Key_Left:    SaveKeyPressed( KEY_LEFT ); break;
        case Qt::Key_Right:   SaveKeyPressed( KEY_RIGHT ); break;
        default: break;
        }
        m_KeyPressedList.append( event->key( ) );
        ShowText();
        qDebug() << tr( "The key %1 pressed." ).arg( event->key( ) );
    }
}
/*-----键盘释放事件------------------------------------------------------------------*/
void Widget::keyReleaseEvent( QKeyEvent* event )
{
    if (!event->isAutoRepeat()) {
        switch ( event->key( ) )
        {
        case Qt::Key_0:       SaveKeyReleased( KEY_0 ); break;
        case Qt::Key_1:       SaveKeyReleased( KEY_1 ); break;
        case Qt::Key_2:       SaveKeyReleased( KEY_2 ); break;
        case Qt::Key_3:       SaveKeyReleased( KEY_3 ); break;
        case Qt::Key_4:       SaveKeyReleased( KEY_4 ); break;
        case Qt::Key_5:       SaveKeyReleased( KEY_5 ); break;
        case Qt::Key_6:       SaveKeyReleased( KEY_6 ); break;
        case Qt::Key_7:       SaveKeyReleased( KEY_7 ); break;
        case Qt::Key_8:       SaveKeyReleased( KEY_8 ); break;
        case Qt::Key_9:       SaveKeyReleased( KEY_9 ); break;

        case Qt::Key_A:       SaveKeyReleased( KEY_A ); break;
        case Qt::Key_B:       SaveKeyReleased( KEY_B ); break;
        case Qt::Key_C:       SaveKeyReleased( KEY_C ); break;
        case Qt::Key_D:       SaveKeyReleased( KEY_D ); break;
        case Qt::Key_E:       SaveKeyReleased( KEY_E ); break;
        case Qt::Key_F:       SaveKeyReleased( KEY_F ); break;
        case Qt::Key_G:       SaveKeyReleased( KEY_G ); break;
        case Qt::Key_H:       SaveKeyReleased( KEY_H ); break;
        case Qt::Key_I:       SaveKeyReleased( KEY_I ); break;
        case Qt::Key_J:       SaveKeyReleased( KEY_J ); break;
        case Qt::Key_K:       SaveKeyReleased( KEY_K ); break;
        case Qt::Key_L:       SaveKeyReleased( KEY_L ); break;
        case Qt::Key_M:       SaveKeyReleased( KEY_M ); break;
        case Qt::Key_N:       SaveKeyReleased( KEY_N ); break;
        case Qt::Key_O:       SaveKeyReleased( KEY_O ); break;
        case Qt::Key_P:       SaveKeyReleased( KEY_P ); break;
        case Qt::Key_Q:       SaveKeyReleased( KEY_Q ); break;
        case Qt::Key_R:       SaveKeyReleased( KEY_R ); break;
        case Qt::Key_S:       SaveKeyReleased( KEY_S ); break;
        case Qt::Key_T:       SaveKeyReleased( KEY_T ); break;
        case Qt::Key_U:       SaveKeyReleased( KEY_U ); break;
        case Qt::Key_V:       SaveKeyReleased( KEY_V ); break;
        case Qt::Key_W:       SaveKeyReleased( KEY_W ); break;
        case Qt::Key_X:       SaveKeyReleased( KEY_X ); break;
        case Qt::Key_Y:       SaveKeyReleased( KEY_Y ); break;
        case Qt::Key_Z:       SaveKeyReleased( KEY_Z ); break;

        case Qt::Key_Control: SaveKeyReleased( KEY_CTRL ); break;
        case Qt::Key_Shift:   SaveKeyReleased( KEY_SHIFT ); break;
        case Qt::Key_Alt:     SaveKeyReleased( KEY_ALT ); break;
        case Qt::Key_Tab:     SaveKeyReleased( KEY_TAB ); break;
        case Qt::Key_Space:   SaveKeyReleased( KEY_SPACE ); break;
        case Qt::Key_Escape:  SaveKeyReleased( KEY_ESCAPE ); break;

        case Qt::Key_Up:      SaveKeyReleased( KEY_UP ); break;
        case Qt::Key_Down:    SaveKeyReleased( KEY_DOWN ); break;
        case Qt::Key_Left:    SaveKeyReleased( KEY_LEFT ); break;
        case Qt::Key_Right:   SaveKeyReleased( KEY_RIGHT ); break;

        default: break;
        }
        m_KeyPressedList.removeAll( event->key( ) );
        ShowText();
        qDebug() << tr( "The key %1 release." ).arg( event->key( ) );
    }
}
/*-----显示按键-----------------------------------------------------------------*/
void Widget::ShowText( void )
{
    m_ShowText.clear();
    foreach ( int key, m_KeyPressedList )
    {
        switch (key)
        {
        case Qt::Key_Control: m_ShowText += "ctrl "; break;
        case Qt::Key_Shift:   m_ShowText += "Shift "; break;
        case Qt::Key_Alt:     m_ShowText += "Alt "; break;
        case Qt::Key_Tab:     m_ShowText += "Tab "; break;
        case Qt::Key_Space:   m_ShowText += "Space "; break;
        case Qt::Key_Escape:  m_ShowText += "Esc "; break;
        case Qt::Key_Up:      m_ShowText += "Up "; break;
        case Qt::Key_Down:    m_ShowText += "Down "; break;
        case Qt::Key_Left:    m_ShowText += "Left "; break;
        case Qt::Key_Right:   m_ShowText += "Right "; break;
        default:
            m_ShowText += key;
            m_ShowText += ' ';
            break;
        }
    }
    ui->key_textBrowser->clear();
    ui->key_textBrowser->append(m_ShowText);
    if (SerialStateOn)
        setFocus();  //锁定焦点在主窗口
    qDebug() << tr( "m_PressedKeys =%1" ).arg( m_PressedKeys );
    //update( );
}
/*-------------------------------------------------------------------------------*/
void Widget::timerEvent( QTimerEvent *event )
{
    if (event->timerId() == m_SerialTimerId)
        send_date();
}
/*-------------------------------------------------------------------------------*/
void Widget::send_date(void)
{
    #pragma pack(1)
    struct
    {
        const quint8 head = 0x5A;
        quint64 temp_data;
        quint8  crc_check;
    }tx_data;
    //qDebug() << tr( "sizeof(tx_data)=%1" ).arg( sizeof(tx_data) );
    tx_data.temp_data = m_PressedKeys;
    Append_CRC8_Check_Sum((quint8 *)&tx_data, sizeof(tx_data));
    if (SerialStateOn) {
        serial->write((char *)&tx_data, sizeof(tx_data));
    }
}
/*--------------------------------------------------------------------------------*/
inline void Widget::SaveKeyPressed( Interested_Keys key )
{
    m_PressedKeys |= ( (quint64)1 << key );
}
inline void Widget::SaveKeyReleased( Interested_Keys key )
{
    m_PressedKeys &= ~( (quint64)1 << key );
}
inline bool Widget::KeyPressed( Interested_Keys key )
{
    return m_PressedKeys & ( (quint64)1 << key );
}
