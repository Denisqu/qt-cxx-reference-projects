TEMPLATE = subdirs

SUBDIRS += \
    gallery-core \
    gallery-mobile
    #gallery-deskptop


#gallery-deskptop.depends = gallery-core
gallery-mobile.depends = gallery-core
