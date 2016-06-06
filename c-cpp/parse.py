#!/usr/bin/python3

import os;
import sys;
import re;
import glob;

pattern = re.compile(r'#txs.*: (.*) \(.*');

for filename in glob.glob('*.txt'):
    with open(filename) as f:
        results = list();
        for line in f:
            result = pattern.search(line);
            if result != None:
                results.append(result.group(1));
        print(os.path.splitext(filename)[0], end=',');
        print(*results, sep=', ');
