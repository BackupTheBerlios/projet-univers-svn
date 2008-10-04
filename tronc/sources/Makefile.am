# recursion
SUBDIRS = \
kernel \
model \
physic \
artificial_intelligence \
display \
input \
gui \
sound \
demonstration 

# headers installation
nobase_include_HEADERS = plateform.h projet_univers.h	

# media installation 
install-data-local:
	mkdir -p $(pkgdatadir)
	find media ! -regex ".*/\.svn/.*" -type f -exec cp --parents {} $(pkgdatadir) \;
	