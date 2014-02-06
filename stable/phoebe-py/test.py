import phoebeBackend as phoebe

# This is a must:
phoebe.init()
phoebe.configure()

# Open parameter file:
phoebe.open("test.phoebe")

# Original LD coefficients:
xbol1 = phoebe.getpar("phoebe_ld_xbol1")
ybol1 = phoebe.getpar("phoebe_ld_ybol1")
xbol2 = phoebe.getpar("phoebe_ld_xbol2")
ybol2 = phoebe.getpar("phoebe_ld_ybol2")
print "Original bolometric LD coefficients:", xbol1, ybol1, xbol2, ybol2

# Update limb darkening coefficients:
phoebe.updateLD()

xbol1 = phoebe.getpar("phoebe_ld_xbol1")
ybol1 = phoebe.getpar("phoebe_ld_ybol1")
xbol2 = phoebe.getpar("phoebe_ld_xbol2")
ybol2 = phoebe.getpar("phoebe_ld_ybol2")
print " Updated bolometric LD coefficients:", xbol1, ybol1, xbol2, ybol2

# Get parameter value:
pot1 = phoebe.getpar("phoebe_pot1")
print "Original pot1 value:", pot1

pmin, pmax = phoebe.getlim("phoebe_pot1")
print "Original limits:", pmin, pmax

# Let's try automatic passband luminosity computation:
print "Without passband luminosity computed: ", phoebe.cfval("lc", 0, 0)
print "With passband luminosity computed: ", phoebe.cfval("lc", 0, 1)

exit()

print "LC  cost function:", phoebe.cfval("lc", 0)
print "RV1 cost function:", phoebe.cfval("rv", 0)
print "RV2 cost function:", phoebe.cfval("rv", 1)

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
