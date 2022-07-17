#include "physical_hands.h"

PhysicalHands::PhysicalHands()
{

}

void PhysicalHands::update()
{
    if(isEnabled() && isVisible()) {
        if(m_watchModeTarget)
        {
            QFile watch_mode_file("/sys/devices/sop716/watch_mode");
            if(!watch_mode_file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug("Unable to open file for write. Check permissions");
            }
            QTextStream out(&watch_mode_file);
            out << 1;
            watch_mode_file.close();
            qDebug() << "reset hands to watch mode" << parentItem() << parentItem()->objectName();
        } else {
            QFile motor_move_all_file("/sys/devices/sop716/motor_move_all");
            if(!motor_move_all_file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug("Unable to open file for write. Check permissions");
            }
            QTextStream out(&motor_move_all_file);
            out << m_hourHandTarget << ":" << m_minuteHandTarget;
            motor_move_all_file.close();
            qDebug() << "moved hands to requested position" << parentItem();
        }
    }
}

int PhysicalHands::hourHandPosition()
{
    QFile position("/sys/devices/sop716/position");
    if (!position.open(QIODevice::WriteOnly | QIODevice::Text))
        return(0);
    QTextStream read(&position);
    return(read.read(7).split(":")[0].toInt());
}

int PhysicalHands::minuteHandPosition()
{
    QFile position("/sys/devices/sop716/position");
     if (!position.open(QIODevice::WriteOnly | QIODevice::Text))
        return(0);
    QTextStream read(&position);
    return(read.read(7).split(":")[1].toInt());
}

void PhysicalHands::setHourHandPosition(int newHourHandPosition)
{
    m_watchModeTarget = 0;
    m_hourHandTarget = newHourHandPosition;
    qDebug() << "hourHandTarget = " << m_hourHandTarget;
//     QFile motor_move_file("/sys/devices/sop716/motor_move");
//     if(!motor_move_file.open(QIODevice::WriteOnly | QIODevice::Text))
//     {
//         qDebug("Unable to open file for write. Check permissions");
//     }
//     QTextStream out(&motor_move_file);
//     out << "1:" << m_hourHandTarget;
//     motor_move_file.close();
    update();
    qDebug() << "moved hands to requested position" << parentItem();

}

void PhysicalHands::setMinuteHandPosition(int newMinuteHandPosition)
{
    m_watchModeTarget = 0;
    m_minuteHandTarget = newMinuteHandPosition;
    qDebug() << "minuteHandTarget = " << m_minuteHandTarget;
//     QFile motor_move_file("/sys/devices/sop716/motor_move");
//     if(!motor_move_file.open(QIODevice::WriteOnly | QIODevice::Text))
//     {
//         qDebug("Unable to open file for write. Check permissions");
//     }
//     QTextStream out(&motor_move_file);
//     out << "0:" << m_minuteHandTarget;
//     motor_move_file.close();
    update();
    qDebug() << "moved hands to requested position" << parentItem();
}

void PhysicalHands::setWatchMode(int newWatchMode = 1)
{
    m_watchModeTarget = newWatchMode;
    if(m_watchModeTarget)
    {
        QFile watch_mode_file("/sys/devices/sop716/watch_mode");
        if(!watch_mode_file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug("Unable to open file for write. Check permissions");
        }
        QTextStream out(&watch_mode_file);
        out << 1;
        watch_mode_file.close();
        qDebug() << "reset hands to watch mode" << parentItem();
    }
}

void PhysicalHands::setHourHandPositionStealth(int newHourHandPosition)
{
    m_watchModeTarget = 0;
    m_hourHandTarget = newHourHandPosition;
    qDebug() << "hourHandTarget = " << m_hourHandTarget;
    update();
    qDebug() << "queued hands move request" << parentItem();
}

void PhysicalHands::setMinuteHandPositionStealth(int newMinuteHandPosition)
{
    m_watchModeTarget = 0;
    m_minuteHandTarget = newMinuteHandPosition;
    qDebug() << "minuteHandTarget = " << m_minuteHandTarget;
    update();
    qDebug() << "queued hands move request" << parentItem();
}

void PhysicalHands::setWatchModeStealth(int newWatchMode = 1)
{
    m_watchModeTarget = newWatchMode;
    if(isEnabled())
    {
        if(m_watchModeTarget)
        {
            QFile watch_mode_file("/sys/devices/sop716/watch_mode");
            if(!watch_mode_file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug("Unable to open file for write. Check permissions");
            }
            QTextStream out(&watch_mode_file);
            out << 1;
            watch_mode_file.close();
        }
    }
    qDebug() << "queued watch mode change" << parentItem();
}


void PhysicalHands::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    QQuickItem::itemChange(change, data);
    switch (change) {
    case ItemOpacityHasChanged:
        if (qFuzzyIsNull(data.realValue))
            setVisible(false);
        break;
    case ItemVisibleHasChanged:
//         if(!(data.boolValue == last_visible)) {
//             update();
//         }
        last_visible == isVisible();
        break;
    case ItemEnabledHasChanged:
       if(!(data.boolValue == last_enabled)) {
           update();
       }
        last_enabled == isEnabled();
        break;
    default:
        break;
    }
}

/*
void PhysicalHands::setVisible(bool visibility)
{
    m_visibility = visibility;
    qDebug() << "set visibility to " << m_visibility;
    if(m_visibility) {
        if(m_watchModeTarget)
        {
            QFile watch_mode_file("/sys/devices/sop716/watch_mode");
            if(!watch_mode_file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug("Unable to open file for write. Check permissions");
            }
            QTextStream out(&watch_mode_file);
            out << 1;
            qDebug("reset hands to watch mode");
        } else {
            QFile motor_move_all_file("/sys/devices/sop716/motor_move_all");
            if(!motor_move_all_file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug("Unable to open file for write. Check permissions");
            }
            QTextStream out(&motor_move_all_file);
            out << m_hourHandTarget << ":" << m_minuteHandTarget;
            motor_move_all_file.close();
            qDebug("moved hands to requested position");
        }
    }
}*/
/*
bool PhysicalHands::visible()
{
    return m_visibility;
}*/
/*
void PhysicalHands::setEffectiveVisibleRecur(bool newEffectiveVisible) {
    setVisible(newEffectiveVisible);
    qDebug("setEffectiveVisibleRecur triggered - running setVisible with new value");
}*/

