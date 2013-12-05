import phoebeBackend as phoebe

# This is a must:
phoebe.init()
phoebe.configure()

# Open parameter file:
phoebe.open("test.phoebe")

# Get parameter value:
pot1 = phoebe.getpar("phoebe_pot1")
print "Original pot1 value:", pot1

pmin, pmax = phoebe.getlim("phoebe_pot1")
print "Original limits:", pmin, pmax

# Compute the cost function for all passbands:
sigLC  = phoebe.getpar("phoebe_lc_sigma", 0)
sigRV1 = phoebe.getpar("phoebe_rv_sigma", 0)
sigRV2 = phoebe.getpar("phoebe_rv_sigma", 1)

print "LC  cost function:", phoebe.cfval("lc", 0)/sigLC**2
print "RV1 cost function:", phoebe.cfval("rv", 0)/sigRV1**2
print "RV2 cost function:", phoebe.cfval("rv", 1)/sigRV2**2

# Set parameter limits:
phoebe.setlim("phoebe_pot1", 3.0, 5.0)

pmin, pmax = phoebe.getlim("phoebe_pot1")
print "New limits:", pmin, pmax

# Use the 'check' method to see if the parameter is within bounds:
print "Is pot1 within bounds:", phoebe.check("phoebe_pot1")
phoebe.setpar("phoebe_pot1", 2.99)
print "How about now:        ", phoebe.check("phoebe_pot1")

if not phoebe.check("phoebe_pot1"):
    print "Penalize cost function"
    print "      before:", phoebe.cfval("lc", 0)
    print "       after:", (1-phoebe.check("phoebe_pot1"))*(1+(phoebe.getpar("phoebe_pot1")-pot1)**2)**10*phoebe.cfval("lc", 0)

# This is a must:
phoebe.quit()

