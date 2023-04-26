INC="/root/sonicash/include/rsa"
TGT="/root/sonicash/src/rsa.cpp"
BIN="/root/sonicash/bin/rsa"

g++ -Wall -I $INC $TGT -o $BIN

$BIN