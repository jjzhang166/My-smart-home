#!/bin/sh

SRCDIR=`pwd`
SERVDIR=$SRCDIR/../

echo  $SERVDIR
echo "stop server"

cd $SERVDIR/bin
./stop.sh

echo "build server"
cd $SERVDIR
make && make install
echo "start server"
cd $SERVDIR/bin
./start.sh
