TEMPLATE = subdirs

SUBDIRS += \
    gallery-core \
    gallery-deskptop

gallery-deskptop.depends = gallery-core
