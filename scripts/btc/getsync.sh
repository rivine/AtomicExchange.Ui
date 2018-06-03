#!/bin/bash
calc() { awk "BEGIN{ printf \"%.2f\n\", $* }"; }
BLOCKCOUNT=`curl -s 'https://testnet.blockexplorer.com/api/status?q=getBlockCount' | python -c "import sys, json; print json.load(sys.stdin)['blockcount']"` 
MYBLOCKCOUNT=$(bitcoin-cli getblockcount) 
ONONE=`calc $MYBLOCKCOUNT / $BLOCKCOUNT`
calc $ONONE*100