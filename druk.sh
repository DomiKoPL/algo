# Copyright 2004 Rutger E.W. van Beusekom.
# Distributed under the Boost Software License, Version 1.0. (See
# accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

# outfile=$1
# shift

# a2ps -1 --highlight=normal --pretty-print=cxx --line-numbers=1 -M a4 -L80 -g \
# -o $outfile $* --prologue=color --right-title=%p. --left-title \
# --left-footer --right-footer --header --medium=a4


#!/bin/bash
test "x$1" == "x" && echo "usage: $0 <sourcefiles>" && exit 0

for f in "$@" ; do enscript $f -o $f.ps -E -C ; done

for f in *.ps ; do echo ps2pdf $f ; ps2pdf $f && rm $f ; done

rm OUTPUT.pdf 2>/dev/null
pdfjam *.pdf && mv *pdfjam.pdf OUTPUT.pdf

echo
echo DONE:
echo OUTPUT.pdf