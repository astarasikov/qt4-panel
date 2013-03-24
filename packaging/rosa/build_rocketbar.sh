#!/bin/bash

PKGNAME=rocketbarv2
PKGVER=1.0
BUILDDIR=~/rpmbuild

rm -rf "$BUILDDIR"
mkdir -p "$BUILDDIR"/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}
cp $PKGNAME.spec "$BUILDDIR"/SPECS/
pushd .
  cd ../../
  git archive --prefix=$PKGNAME-$PKGVER/ HEAD | gzip > "$BUILDDIR"/SOURCES/$PKGNAME-$PKGVER.tar.gz
popd

pushd .
  cd "$BUILDDIR"
  rm -r BUILD/$PKGNAME-$PKGVER
  rpmbuild -ba SPECS/$PKGNAME.spec
popd