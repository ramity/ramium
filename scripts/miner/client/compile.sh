INC="/root/sonicash/include"
TGT="/root/sonicash/src/miner/client/main.cpp"
BIN="/root/sonicash/bin/minerClient"

g++ -Wall -I $INC $TGT -o $BIN -lpthread

$BIN