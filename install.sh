#!/bin/bash

# install dwm
cd dwm
sudo make uninstall
sudo make clean install
cd ..


# install st
cd st
sudo make uninstall
sudo make clean install
cd ..

# install dwmblocks
cd dwmblocks
sudo make uninstall
sudo make clean install
cd ..
