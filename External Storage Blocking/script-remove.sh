#!/bin/bash
USER_NAME=$(who | awk '{print $1}')
sudo chmod 750 /run/media/$USER_NAME
