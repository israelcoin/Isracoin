
Debian
====================
This directory contains files used to package isracoind/isracoin-qt
for Debian-based Linux systems. If you compile isracoind/isracoin-qt yourself, there are some useful files here.

## isracoin: URI support ##


isracoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install isracoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your isracoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/isracoin128.png` to `/usr/share/pixmaps`

isracoin-qt.protocol (KDE)

