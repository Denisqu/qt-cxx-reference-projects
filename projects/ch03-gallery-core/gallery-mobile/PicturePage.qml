import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

import "."

PageTheme {

    property string pictureName
    property int pictureIndex
    toolbarTitle: pictureName

    ListView {
        id: pictureListView
        model: pictureModel
        anchors.fill: parent
        spacing: 5
        orientation: Qt.Horizontal
        snapMode: ListView.SnapOneItem
        currentIndex: pictureIndex

        Component.onCompleted: {
            positionViewAtIndex(currentIndex,
                                ListView.SnapPosition)
        }

        delegate: Rectangle {
            property int itemIndex: index
            property string itemName: name
            width: ListView.view.width === 0 ?
                       parent.width : ListView.view.width
            height: pictureListView.height
            color: "transparent"

            Image {
                fillMode: Image.PreserveAspectFit
                cache: false
                width: parent.width
                height: parent.height
                source: "image://pictures/" + index +
                        "/full"
            }
        }

        onMovementEnded: {
            currentIndex = itemAt(contentX,
                                  contentY).itemIndex
        }

        onCurrentItemChanged: {
            toolbarTitle = currentItem.itemName
        }

    }
}
