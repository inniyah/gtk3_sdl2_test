EXTRA_DIST=scriptix.pc.in bootstrap

DIST_SUBDIRS=doc include lib bin test tools
SUBDIRS=doc include lib bin test tools

docsdir=${prefix}/share/doc/@PACKAGE_TARNAME@-@VERSION@/
docs_DATA=README COPYING

pkgconfdir=${prefix}/lib/pkgconfig
pkgconf_DATA=scriptix-@INTERFACE_VERSION@.pc

scriptix-@INTERFACE_VERSION@.pc: scriptix.pc
	cp -f scriptix.pc scriptix-@INTERFACE_VERSION@.pc

rpm: dist
	rpmbuild -ta "${PACKAGE_TARNAME}-${PACKAGE_VERSION}.tar.gz"

clean-local:
	rm -f scriptix-@INTERFACE_VERSION@.pc
