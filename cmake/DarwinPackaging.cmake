# support creating some basic binpkgs via `make package`

set(CPACK_SET_DESTDIR ON)
set(CPACK_GENERATOR TGZ)

set(CPACK_PACKAGE_VERSION_MAJOR ${LIBIIO_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${LIBIIO_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH g${LIBIIO_VERSION_GIT})
set(CPACK_BUNDLE_NAME libiio)
set(CPACK_PACKAGE_VERSION ${LIBIIO_VERSION})

include(CPack)
