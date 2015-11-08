#!/bin/sh
#
#

DIR="`pwd`"

mkdir -p build

cat <<EOF > Dockerfile
FROM debian:jessie
ENV DEBIAN_FRONTEND noninteractive
RUN sed -i "s|^deb-src|#deb-src|g" /etc/apt/sources.list
RUN echo "deb http://http.debian.net/debian jessie-backports main" >> /etc/apt/sources.list
RUN apt-get update && apt-get -y upgrade
RUN apt-get install -y git make build-essential qt5-qmake libqt5serialport5-dev libqt5opengl5-dev
EOF
echo "RUN apt-get install -y qt5-default libqt5svg5-dev libqt5webkit5-dev qtmultimedia5-dev libudev-dev qttools5-dev libsdl1.2-dev" >> Dockerfile


echo "#!/bin/sh" > build/build.sh
echo "(cd /usr/src/qgroundcontrol_aq ; qmake qgroundcontrol_aq.pro)" >> build/build.sh
echo "(cd /usr/src/qgroundcontrol_aq ; make \$@)" >> build/build.sh
echo "(cd /usr/src/qgroundcontrol_aq ; cp -a files/styles bin/files/)" >> build/build.sh
chmod 755 build/build.sh

docker build -t qgroundcontrol_aq .
#docker run --privileged=true -i -t  --rm  -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v /dev/dri:/dev/dri -v /dev/video0:/dev/video0 -v $HOME/.Xauthority:/home/cammill/.Xauthority -v "$DIR":/usr/src/qgroundcontrol_aq qgroundcontrol_aq /bin/bash /usr/src/qgroundcontrol_aq/build/build.sh $@
docker run -i -t  --rm -v "$DIR":/usr/src/qgroundcontrol_aq qgroundcontrol_aq /bin/bash /usr/src/qgroundcontrol_aq/build/build.sh $@

rm -rf Dockerfile
rm -rf build/build.sh

