#!/bin/bash
GnomeVerFILE="/usr/share/gnome/gnome-version.xml"
if test -e $GnomeVerFILE; then
tmpFILE="/tmp/gnome-version"
cat $GnomeVerFILE | grep platform | sed s'/[<>]/ /g' | sed "s/\bplatform\b//g" > $tmpFILE
cat $GnomeVerFILE | grep minor | sed s'/[<>]/ /g' | sed "s/\bminor\b//g" >> $tmpFILE
cat $GnomeVerFILE | grep micro | sed s'/[<>]/ /g' | sed "s/\bmicro\b//g" >> $tmpFILE
sed -i ':a;N;$!ba;s/\n//g' $tmpFILE
sed -i '/^$/d;s/[[:blank:]]//g' $tmpFILE
sed -i 's/\//./g' $tmpFILE
sed -r 's/.{1}$//' $tmpFILE
else
echo "?.??.?"
fi
exit 0

