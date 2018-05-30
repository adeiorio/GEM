import os, commands
import ROOT
import optparse
import numpy
from array import array

infile = ROOT.TFile.Open("miniTreesGem.root")
tree = infile.Get("demo/RecHitAna")
maxlen = 300

ngems = array( 'i', [0])
gemring = array( 'd', maxlen*[0])
gemregion = array( 'd', maxlen*[0])
gemstation = array( 'd', maxlen*[0])
gemlayer = array( 'd', maxlen*[0])
gemetapart = array( 'd', maxlen*[0])
gemchamber = array( 'd', maxlen*[0])
gembunchx = array( 'd', maxlen*[0])
gemglobalx = array( 'd', maxlen*[0])
gemglobaly = array( 'd', maxlen*[0])
gemglobalz = array( 'd', maxlen*[0])
gemglobalr = array( 'd', maxlen*[0])

ncscs = array( 'i', [0])
cscregion = array( 'd', maxlen*[0])
cscring = array( 'd', maxlen*[0])
cscstation = array( 'd', maxlen*[0])
nRicHitsCSCSeg = array( 'd', maxlen*[0])
cscSegXo = array( 'd', maxlen*[0])
cscSegYo = array( 'd', maxlen*[0])
cscSegZo = array( 'd', maxlen*[0])
cscSegXi = array( 'd', maxlen*[0])
cscSegYi = array( 'd', maxlen*[0])
cscSegZi = array( 'd', maxlen*[0])
cscSegAngle = array( 'd', maxlen*[0])

tree.SetBranchAddress("ngems", ngems)
tree.SetBranchAddress("gemregion", gemregion)
tree.SetBranchAddress("gemring", gemring)
tree.SetBranchAddress("gemstation", gemstation)
tree.SetBranchAddress("gemlayer", gemlayer)
tree.SetBranchAddress("gemetapart", gemetapart)
tree.SetBranchAddress("gemchamber", gemchamber)
tree.SetBranchAddress("gembunchx", gembunchx)
tree.SetBranchAddress("gemglobalx", gemglobalx)
tree.SetBranchAddress("gemglobaly", gemglobaly)
tree.SetBranchAddress("gemglobalz", gemglobalz)
tree.SetBranchAddress("gemglobalr", gemglobalr)

tree.SetBranchAddress("ncscs", ncscs)
tree.SetBranchAddress("cscregion", cscregion)
tree.SetBranchAddress("cscring", cscring)
tree.SetBranchAddress("cscstation", cscstation)
tree.SetBranchAddress("nRecHitsCSCSeg", nRecHitsCSCSeg)
tree.SetBranchAddress("cscSegXo", cscSegXo)
tree.SetBranchAddress("cscSegYo", cscSegYo)
tree.SetBranchAddress("cscSegZo", cscSegZo)
tree.SetBranchAddress("cscSegXi", cscSegXi)
tree.SetBranchAddress("cscSegYi", cscSegYi)
tree.SetBranchAddress("cscSegZi", cscSegZi)
tree.SetBranchAddress("cscSegAngle", cscSegAngle)

for i in xrange(0, 2): # tree.GetEntries()
    tree.GetEntry(i)
    print ngems
for l in xrange(0, ):
    for j in xrange(0, ngems[-1]):
#        print "lenght gemregion ", len(gemregion)
        print "gemregion ", gemregion[j]
        print "gemglobalx ", gemglobalx[j]

