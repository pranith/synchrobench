#!/usr/bin/python3

import os;
import glob;
import re;

writefreq = 20;
pattern = re.compile(r'.*hoh.*|.*lazy.*');
args = " -d 20000 -f 1 -u " + str(writefreq) + " -t "
optargs = " -x 1 "

for filename in glob.glob('*'):
    bench = pattern.search(filename);
    benchargs = args;
    if bench == None:
        benchargs = optargs + args;
    for i in range(1, 5):
        command = "./" + filename + benchargs + str(i) + " | tee -a " + \
        os.path.splitext(filename)[0] +"_" + str(writefreq) + ".txt";
        os.system(command);
        
