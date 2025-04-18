SUMMARY = "RTH Serial Reader App"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://read_serial.c"

S = "${WORKDIR}"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} -o read_serial read_serial.c
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 read_serial ${D}${bindir}
}