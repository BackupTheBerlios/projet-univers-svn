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

all-local:ressources.cfg plugins.cfg

# generates a correct ressources.cfg from main template
ressources.cfg:ressources.cfg.in
	cat ressources.cfg.in | sed 's,@MEDIA_FOLDER\@,@MEDIA_FOLDER@,' > ressources.cfg

plugins.cfg:plugins.cfg.in
	cat plugins.cfg.in \
	| sed 's,@INSTALL_OGRE_PLUGIN_FOLDER\@,@INSTALL_OGRE_PLUGIN_FOLDER@,' \
	| sed 's,@OGRE_PLUGIN_RENDER_SYSTEM\@,@OGRE_PLUGIN_RENDER_SYSTEM@,' \
	| sed 's,@OGRE_PLUGIN_EXTENSION\@,@OGRE_PLUGIN_EXTENSION@,'> plugins.cfg

# headers installation
nobase_include_HEADERS = plateform.h projet_univers.h	

# media installation 
install-data-local:
	mkdir -p $(pkgdatadir)
	find media ! -regex ".*/\.svn/.*" -type f -exec cp --parents {} $(pkgdatadir) \;
	