import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

import "."

Page {

    property alias toolbarButtons:
        buttonsLoader.sourceComponent
    property alias toolbarTitle: titleLabel.text

    header: ToolBarTheme {

        RowLayout {
            anchors.fill: parent

            ToolButton {

                Layout.preferredHeight: 50
                Layout.preferredWidth: 50

                background: Image {
                    anchors.fill: parent
                    source: "qrc:/icons/icons/arrow-left.svg"
                }

                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop()
                    }
                }
            }

            Label {
                id: titleLabel
                Layout.fillWidth: true
                color: Style.text
                elide: Text.ElideRight
                font.pointSize: 30
            }

            Loader {
                Layout.alignment: Qt.AlignRight
                id: buttonsLoader
            }
        }
    }

    Rectangle {
        color: Style.pageBackground
        anchors.fill: parent
    }
}
