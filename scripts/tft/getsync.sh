#!/bin/bash
SYNCED=$(tfchainc consensus | grep Synced)

if [[ -z "$SYNCED" ]]; then
  tfchainc consensus | grep Progress | cut -d' ' -f3 | cut -d'%' -f1
else
  echo 100
fi