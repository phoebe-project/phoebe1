import libphoebe_legacy

import os 
pathDATA = os.path.dirname(libphoebe_legacy.__file__) + "/phoebe_legacy/tables"

from libphoebe_legacy import *

# data is the sub-directory tables
pathWD=pathDATA + "/wd"
pathPTF=pathDATA + "/ptf"
pathLD=pathDATA + "/ld"
pathVH=pathDATA + "/vanhamme"

# load the data

