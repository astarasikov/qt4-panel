Name:           rocketbarv2
Version:        1.0
Release:        %mkrel 1
Summary:        ROSA RocketBar QML
Group:          Graphical desktop/KDE
License:        GPL v2
URL:            http://rosalab.ru/
Source0:        %{name}-%{version}.tar.gz
BuildRequires:  qt4-devel >= 4:4.7.0

%description
ROSA RocketBar QML Panel

%files
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop

%prep
%setup -qn %{name}-%{version}

%build
%qmake_qt4
%make

%install
%{__rm} -rf %{buildroot}
%{__mkdir_p} %{buildroot}%{_bindir}
%{__mkdir_p} %{buildroot}%{_datadir}/applications
%{__cp} %{name} %{buildroot}%{_bindir}/%{name}
%{__chmod} 755 %{buildroot}%{_bindir}/%{name}
%{__cat} > %{buildroot}%{_datadir}/applications/%{name}.desktop << EOF
[Desktop Entry]
Name=Rocket Bar V2
Comment=RocketBar on QML
Exec=rocketbarv2
Categories=Qt;KDE;System;
Type=Application
Terminal=false
Icon=preferences-desktop
StartupNotify=true
EOF

%clean
%__rm -rf %{buildroot}
 
%changelog
* Mon Mar 25 2013 Alexander Tarasikov <alexander.tarasikov@gmail.com> 1.0-1
- Initial version
