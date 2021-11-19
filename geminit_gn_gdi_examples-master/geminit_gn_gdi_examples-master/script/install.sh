#!/bin/bash
FONT_DIR=/usr/share/fonts/bdf
cp lib/libgeminit-gn-gdi.so /usr/lib

if [ ! -d ${FONT_DIR} ] ; then
	mkdir -p ${FONT_DIR}
fi

cp fonts/* ${FONT_DIR}
