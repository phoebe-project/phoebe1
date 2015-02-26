import phoebeBackend as phoebe

# This is a must:
phoebe.init()
phoebe.configure()

# Open parameter file:
phoebe.open("test.phoebe")

# Get parameter values:
print "Original:"
print "phoebe_indep:", phoebe.getpar("phoebe_indep")
print "phoebe_atm1_switch:", phoebe.getpar("phoebe_atm1_switch")

# Set parameter values:
phoebe.setpar("phoebe_indep", "Time (HJD)")
phoebe.setpar("phoebe_atm1_switch", False)

# Get parameter values:
print "Modified:"
print "phoebe_indep:", phoebe.getpar("phoebe_indep")
print "phoebe_atm1_switch:", phoebe.getpar("phoebe_atm1_switch")

# Get data from phoebe:
x, y, z = phoebe.data("lc", 0)
print("First 5 data points from the LC file:")
for i in range(5):
    print("%12.6f"*3 % (x[i], y[i], z[i]))

# Compute a light curve with meshes exported:
phoebe.setpar("phoebe_indep", "Phase")
lc, mesh = phoebe.lc((0.0,), 0, 1)
print lc
print mesh['rad1']
print len(mesh['rad1'])
exit()

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

# Compute a radial velocity curve:
phs = tuple([-0.5+float(i)/29 for i in range(30)])
rv1 = phoebe.rv1(phs, 0)
rv2 = phoebe.rv2(phs, 1)
print("Computed RV curves:")
for i in range(len(rv1)):
    print phs[i], rv1[i], rv2[i]

# Try parameter role reversal for primary <--> secondary:
print("# Star role reversal:")
phs = tuple([-0.5+float(i)/100 for i in range(101)])
lc1 = phoebe.lc(phs, 0)

print "hla=", phoebe.getpar("phoebe_plum1", 0)
print "cla=", phoebe.getpar("phoebe_plum2", 0)
print "pot1=", phoebe.getpar("phoebe_pot1")
print "pot2=", phoebe.getpar("phoebe_pot2")
print "T1=", phoebe.getpar("phoebe_teff1")
print "T2=", phoebe.getpar("phoebe_teff2")
print "q=", phoebe.getpar("phoebe_rm")
phoebe.role_reverse()
phoebe.setpar("phoebe_hla", phoebe.getpar("phoebe_plum2"), 0)
lc2 = phoebe.lc(phs, 0)
print "hla=", phoebe.getpar("phoebe_hla", 0)
print "cla=", phoebe.getpar("phoebe_cla", 0)
print "pot1=", phoebe.getpar("phoebe_pot1")
print "pot2=", phoebe.getpar("phoebe_pot2")
print "T1=", phoebe.getpar("phoebe_teff1")
print "T2=", phoebe.getpar("phoebe_teff2")
print "q=", phoebe.getpar("phoebe_rm")
for x in zip(phs, lc1, lc2):
    print("%f\t%f\t%f" % (x[0], x[1], x[2]))
exit()

# Get parameter value:
pot1 = phoebe.getpar("phoebe_pot1")
print "Original pot1 value:", pot1

pmin, pmax = phoebe.getlim("phoebe_pot1")
print "Original limits:", pmin, pmax

# Let's try automatic passband luminosity computation:
print "Without passband luminosity computed: ", phoebe.cfval("lc", 0, 0)
print "With passband luminosity computed: ", phoebe.cfval("lc", 0, 1)

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

