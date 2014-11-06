Summary: A lite-weight scripting interface.
Name: scriptix
Version: 0.18
Release: 1
Copyright: MIT/X
Group: Libraries/Interpreters
Source: http://prdownloads.sourceforge.net/awemud/scriptix-0.18.tar.gz
BuildRoot: /var/tmp/%{name}-buildroot

%description
Scriptix is a lite-weight scripting interface designed solely for
embedding in applications.

%prep
rm -rf $RPM_BUILD_ROOT
%setup
./configure --prefix=/usr

%build
make RPM_OPT_FLAGS="$RPM_OPT_FLAGS"

%install
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc README COPYING

/usr/bin/scriptix
/usr/bin/scriptix-conf
/usr/include/scriptix/scriptix.h
/usr/include/scriptix/config.h
/usr/include/scriptix/parser.h
/usr/include/scriptix/system.h
/usr/lib/libscriptix.a
/usr/lib/libsxparse.a
/usr/lib/libscriptix.so.0.18
/usr/lib/libsxparse.so.0.18

%changelog
* Wed Apr 03 2002 Sean Middleditch <elanthis@awesomeplay.com>
- initial release
