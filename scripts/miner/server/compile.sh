INC="/root/ramium/include"
TGT="/root/ramium/src/miner/server/main.cpp"
BIN="/root/ramium/bin/minerServer"

g++ -Wall -I $INC $TGT -o $BIN -lpthread

$BIN