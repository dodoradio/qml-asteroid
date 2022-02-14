/*
 * All rights reserved.
 *
 * You may use this file under the terms of BSD license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PHYSICAL_HANDS_H
#define PHYSICAL_HANDS_H

#include <QtQuick/qquickitem.h>
#include <QFile>
#include <QSaveFile>

class PhysicalHands : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(int hourHandPosition READ hourHandPosition WRITE setHourHandPosition NOTIFY hourHandPositionChanged)
    Q_PROPERTY(int minuteHandPosition READ minuteHandPosition WRITE setMinuteHandPosition NOTIFY minuteHandPositionChanged)
    //Q_PROPERTY(int handsPosition[2] Read handsPosition WRITE setHandsPosition NOTIFY handsPositionChanged)
    Q_PROPERTY(int watchMode READ watchMode WRITE setWatchMode NOTIFY watchModeChanged)

    Q_PROPERTY(int hourHandPositionStealth READ hourHandPosition WRITE setHourHandPositionStealth NOTIFY hourHandPositionChanged)
    Q_PROPERTY(int minuteHandPositionStealth READ minuteHandPosition WRITE setMinuteHandPositionStealth NOTIFY minuteHandPositionChanged)
    //Q_PROPERTY(int handsPositionStealth[2] Read handsPositionStealth WRITE setHandsPositionStealth NOTIFY handsPositionChanged)
    Q_PROPERTY(int watchModeStealth READ watchMode WRITE setWatchModeStealth NOTIFY watchModeChanged)

public:
    PhysicalHands();

    void setPosition(int,int);

    void setHourHandPosition(int);
    void setMinuteHandPosition(int);

    int minuteHandPosition();
    int hourHandPosition();

    void setHandsPosition(int);
    int* handsPosition();

    void setWatchMode(int);
    int watchMode();

    //void setVisible(bool);

    //bool visible();

    void setHourHandPositionStealth(int);
    void setMinuteHandPositionStealth(int);

    void setWatchModeStealth(int);

    //void paint(QPainter *painter) override;
    //void setEffectiveVisibleRecur(bool);
    void update();

signals:
    void hourHandPositionChanged();
    void minuteHandPositionChanged();

    void watchModeChanged();

    //void visibleChanged();
protected:
    void itemChange(ItemChange change, const ItemChangeData &data) override;

private:
    int m_hourHandTarget = -1;
    int m_minuteHandTarget = -1;
    int m_watchModeTarget;
    bool m_visibility = false;
    bool last_visible;
    bool last_enabled;

};

#endif // PHYSICAL_HANDS_H
