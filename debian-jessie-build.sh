#!/bin/sh
#
#

apt-get install -y git make build-essential qt5-qmake libqt5serialport5-dev libqt5opengl5-dev qt5-default libqt5svg5-dev libqt5webkit5-dev qtmultimedia5-dev libudev-dev qttools5-dev libsdl1.2-dev

qmake qgroundcontrol_aq.pro
make $@
cp -a files/styles bin/files/

echo "./bin/qgroundcontrol_aq"

