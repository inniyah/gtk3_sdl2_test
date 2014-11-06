EXTRA_DIST=bootstrap

DIST_SUBDIRS=include lib bin test tools
SUBDIRS=include lib bin test tools

docsdir=${prefix}/share/doc/@PACKAGE_TARNAME@-@VERSION@/
docs_DATA=README COPYING

rpm: dist
	rpmbuild -ta "${PACKAGE_TARNAME}-${PACKAGE_VERSION}.tar.gz"

clean-local:
	rm -f scriptix-@INTERFACE_VERSION@.pc
