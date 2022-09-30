import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

PageTheme {

    toolbarTitle: "Albums"
    toolbarButtons: ToolButton {

        height: 50
        width: 50

        background: Image {
            source: "qrc:/icons/icons/plus.svg"
        }

        onClicked: {
            newAlbumDialog.open()
        }
    }

    InputDialog {
        id: newAlbumDialog
        title: "New album"
        label: "Album name:"
        hint: "My Album"

        onAccepted: {
            editText.focus = false;
            albumModel.addAlbumFromName(editText.text)
        }
    }

    ListView {
        id: albumList
        model: albumModel
        spacing: 5
        anchors.fill: parent

        delegate: Rectangle {
            width: parent.width
            height: 120
            color: Style.buttonBackground

            Text {
                text: name
                font.pointSize: 16
                color: Style.text
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    albumList.currentIndex = index
                    pictureModel.setAlbumId(id)
                    pageStack.push("qrc:/AlbumPage.qml", {albumName: name, albumRowIndex: index })
                }
            }
        }
    }
}
