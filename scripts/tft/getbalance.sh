#!/bin/bash
tfchainc wallet balance | grep Confirmed | cut -d' ' -f 5