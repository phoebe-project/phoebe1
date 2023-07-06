#!/bin/bash
tar xzf wd_F.tar.gz
cat *.F > wdF
mv wdF wd.F
f2c wd.F
rm *.F
