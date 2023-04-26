INC="/root/sonicash/include"
TGT="/root/sonicash/src/miner/server/main.cpp"
BIN="/root/sonicash/bin/minerServer"

g++ -Wall -I $INC $TGT -o $BIN -lpthread

$BIN