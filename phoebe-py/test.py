import phoebeBackend as phoebe

# This is a must:
phoebe.init()
phoebe.configure()

# Open parameter file:
phoebe.open("test.phoebe")

# Get parameter value:
pot1 = phoebe.getpar("phoebe_pot1")
print "Original pot1 value:", pot1

# Compute the cost function for passband 0:
print "Cost function:", phoebe.cfval(0)

# Set parameter limits:
phoebe.setlim("phoebe_pot1", 3.0, 5.0)

# Use the 'check' method to see if the parameter is within bounds:
print "Is pot1 within bounds:", phoebe.check("phoebe_pot1")
phoebe.setpar("phoebe_pot1", 2.99)
print "How about now:        ", phoebe.check("phoebe_pot1")

if not phoebe.check("phoebe_pot1"):
    print "Penalize cost function"
    print "      before:", phoebe.cfval(0)
    print "       after:", (1-phoebe.check("phoebe_pot1"))*(1+(phoebe.getpar("phoebe_pot1")-pot1)**2)**10*phoebe.cfval(0)

# This is a must:
phoebe.quit()

