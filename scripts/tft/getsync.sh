#!/bin/bash
tfchainc consensus | grep Progress | cut -d' ' -f3 | cut -d'%' -f1