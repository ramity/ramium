INC="/root/ramium/include"
TGT="/root/ramium/src/miner/client/main.cpp"
BIN="/root/ramium/bin/minerClient"

g++ -Wall -I $INC $TGT -o $BIN -lpthread

$BIN