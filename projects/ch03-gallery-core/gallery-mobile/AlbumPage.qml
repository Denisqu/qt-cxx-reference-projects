import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2

import "."

PageTheme {

    property string albumName
    property int albumRowIndex

    toolbarTitle: albumName
    toolbarButtons: RowLayout {

        ToolButton {
            Layout.preferredHeight: 50
            Layout.preferredWidth: 50

            background: Image {
                source: "qrc:/icons/icons/plus.svg"
            }
            onClicked: {
                dialog.open()
            }
        }
    }

    FileDialog {
        id: dialog
        title: "Open file"
        folder: shortcuts.pictures
        onAccepted: {
            var pictureUrl = dialog.fileUrl
            pictureModel.addPictureFromUrl(pictureUrl)
            dialog.close()
        }
    }

    GridView {
        id: thumbnailList
        model: pictureModel
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        cellWidth : thumbnailSize
        cellHeight: thumbnailSize

        delegate: Rectangle {
            width: thumbnailList.cellWidth - 10
            height: thumbnailList.cellHeight - 10
            color: "transparent"

            Image {
                id: thumbnail
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                cache: false // we use our own caching
                source: "image://pictures/" + index +
                        "/thumbnail"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    thumbnailList.currentIndex = index
                    pageStack.push("qrc:/PicturePage.qml",
                                   { pictureName: name, pictureIndex: index })
                }
            }
        }
    }
}
