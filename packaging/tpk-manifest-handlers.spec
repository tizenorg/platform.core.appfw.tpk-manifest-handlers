Name:           tpk-manifest-handlers
Summary:        tpk-manifest-handlers
Version:        1.5
Release:        1
Group:          Application Framework/Package Management
License:        Apache-2.0 and BSD-3-Clause
Source0:        %{name}-%{version}.tar.gz
Source100:      %{name}.manifest

BuildRequires:  boost-devel
BuildRequires:  cmake
BuildRequires:  gtest-devel
BuildRequires:  pkgconfig(pkgmgr-parser)
BuildRequires:  pkgconfig(pkgmgr-info)
BuildRequires:  pkgconfig(libiri)
BuildRequires:  pkgconfig(libxml-2.0)
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(xdgmime)
BuildRequires:  pkgconfig(manifest-parser)

Requires: ca-certificates-tizen
Requires: libtzplatform-config

%description
Installs tpk parser and handlers based on manifest-parser

%package devel
Summary:    Manifest parser development files
Group:      Application Framework/Package Management
Requires:   %{name} = %{version}
Requires:   boost-devel
Provides:   tpk-manifest-handlers

%description devel
This package contains necessaary files for manifest-parser development

%prep
%setup -q
cp %{SOURCE100} .

%build
export CFLAGS="$(echo $CFLAGS | sed 's/-Wl,--as-needed//g')"
export CXXFLAGS="$(echo $CXXFLAGS | sed 's/-Wl,--as-needed//g')"
export FFLAGS="$(echo $FFLAGS | sed 's/-Wl,--as-needed//g')"
# BUILD_PARSER macro is defined so we can build two separate projects
# with cmake, which are on one repository. Later this macro
# is used in CMakeLists.txt files to distinguish, which project
# is currently being build.
%cmake . -DCMAKE_BUILD_TYPE=%{?build_type:%build_type} \
         -DTIZEN_VERSION=%{tizen_version} \
         -DTIZEN_PROFILE=%{profile}

make %{?_smp_mflags}

%install
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest %{name}.manifest
%defattr(-,root,root)
%{_libdir}/libtpk-manifest-handlers.so*
%license LICENSE LICENSE-xwalk

%files devel
%manifest %{name}.manifest
%{_libdir}/pkgconfig/*.pc
%{_includedir}/tpk_manifest_handlers/*.h
%{_includedir}/tpk_manifest_handlers/common/*.h
