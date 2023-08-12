#!/bin/bash

USER_NAME=$(who | awk '{print $1}')

sudo chmod 000 /run/media/$USER_NAME


