#!/usr/bin/python3

import os;
import glob;
import re;

pattern=re.compile(r".*hoh.*|.*lazy.*");
for filename in glob.glob("*"):
    print(filename);
    found=pattern.match(filename);
    if found == None:
        replace_opt_arg = "sed \"s/OPT_ARGS/-x 1 /g\" ../runme_orig.sh > /tmp/runme_new.sh" 
    else:
        replace_opt_arg = "sed \"s/OPT_ARGS//g\" ../runme_orig.sh > /tmp/runme_new.sh" 
    print(replace_opt_arg);
    os.system(replace_opt_arg);
    rename_cmd = "sed \"s/TEST/" + filename + "/g\" /tmp/runme_new.sh > runme.sh";
    print(rename_cmd);
    os.system(rename_cmd);
    tar_cmd = "tar -cvf" + filename + ".tar " + filename + " runme.sh";
    os.system(tar_cmd);
    os.system("rm -f runme.sh");
