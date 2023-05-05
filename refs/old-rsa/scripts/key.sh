INC="/root/ramium/include/rsa"
TGT="/root/ramium/src/rsa.cpp"
BIN="/root/ramium/bin/rsa"

g++ -Wall -I $INC $TGT -o $BIN

$BIN