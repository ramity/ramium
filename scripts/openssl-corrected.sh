TGT="/root/sonicash/reference/chatgpt/rsa-examples/openssl-corrected.cpp"
BIN="/root/sonicash/bin/test"

g++ -Wall $TGT -o $BIN -lssl -lcrypto

$BIN