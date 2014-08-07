#!/bin/sh

# if no daemon , then should adde &
`pwd`/redis-server redis.conf&
echo "start fake node client , just for test"
sleep 10
python `pwd`/../mytest/fakeTemperature.py&


