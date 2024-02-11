args = commandArgs(trailingOnly=T)[1]
fname <- args[1]


library(igraph)


g <- read.graph(fname, format="gml")


g.ebet <- edge.betweenness(g, directed=F, weights=E(g)$weight)
g.ebet <- sprintf("%f", g.ebet)
write(g.ebet, "~/Desktop/cnst_use_cent_4/ebet.dat", append=T, ncol=1)

g.deg <- degree(g)
write(g.deg, "~/Desktop/cnst_use_cent_4/vdeg.dat", append=T, ncol=1)

g.eig <- evcent(g, directed=F, scale=F, weights=E(g)$weight)$vector
g.eig <- sprintf("%f", g.eig)
write(g.eig, "~/Desktop/cnst_use_cent_4/veig.dat", append=T, ncol=1)

g.clo <- closeness(g, mode="all", weights=E(g)$weight)
g.clo <- sprintf("%f", g.clo)
write(g.clo, "~/Desktop/cnst_use_cent_4/vclo.dat", append=T, ncol=1)

g.bet <- betweenness(g, directed=F, weights=E(g)$weight)
g.bet <- sprintf("%f", g.bet)
write(g.bet, "~/Desktop/cnst_use_cent_4/vbet.dat", append=T, ncol=1)
