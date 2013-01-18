// Default empty project template
import bb.cascades 1.0

// creates one page with a label
Page {
        
    Container {
        layout: DockLayout {}
        TextArea {
            id: uuid
            text: qsTr("uuid: " + malcom.uuid + "\n Secret Key: " + malcom.secretKey )
            textStyle.base: SystemDefaults.TextStyles.MediumText
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            objectName: "uuid"
        }
        
    }
}

