#/bin/bash
cd /home/foo/code/cil/cil-1.4.0/
./configure EXTRASRCDIRS=/home/foo/code/ii/apk/analysis EXTRAFEATURES="DeadCode FunCall" && make && cd /home/foo/code/ii/apk && /home/foo/code/cil/cil-1.4.0/bin/cilly --doFunCall test1.c
