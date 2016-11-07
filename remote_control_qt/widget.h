#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QKeyEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void keyPressEvent( QKeyEvent* event );
    void keyReleaseEvent( QKeyEvent* event );
    void ShowText( void );
    void timerEvent( QTimerEvent *event );

private slots:
    void on_openButton_clicked();
    void on_clearButton_clicked();
    void read_data(void);
    void send_date(void);

private:
    Ui::Widget *ui;
    QSerialPort *serial;

    enum Interested_Keys
    {
        KEY_0,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        KEY_CTRL,
        KEY_SHIFT,
        KEY_ALT,
        KEY_TAB,
        KEY_SPACE,
        KEY_ESCAPE,
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
    };

    inline void SaveKeyPressed( Interested_Keys key )
    {
        m_PressedKeys |= ( 1 << key );
    }
    inline void SaveKeyReleased( Interested_Keys key )
    {
        m_PressedKeys &= ~( 1 << key );
    }
    inline bool KeyPressed( Interested_Keys key )
    {
        return m_PressedKeys & ( 1 << key );
    }

    quint64      m_PressedKeys;
    QList<int>   m_KeyPressedList;
    bool         SerialStateOn = false;
    int          m_SerialTimerId;
    QString      m_ShowText;
};

#endif // WIDGET_H
