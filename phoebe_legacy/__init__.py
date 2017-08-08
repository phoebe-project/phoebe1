import libphoebe_legacy

import os 
pathHOME=os.path.dirname(libphoebe_legacy.__file__)+"/phoebe_legacy"

from libphoebe_legacy import *

# data is the sub-directory tables
pathWD=pathHOME+"/tables/wd"
pathPTF=pathHOME+"/tables/ptf"


# load the data

