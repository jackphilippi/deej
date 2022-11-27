package deej

import (
	"github.com/lxn/walk"
	. "github.com/lxn/walk/declarative"
)

func (d *Deej) openGUIWindow() {
	var mw *walk.MainWindow

	// var dd = d.config.userConfig.GetString(configKeyCOMPort)

	MainWindow{
		AssignTo: &mw,
		Title:    "Deej Config GUI",
		MinSize:  Size{Width: 240, Height: 320},
		Layout:   VBox{},
		Children: []Widget{
			GroupBox{
				Title:  "Connection Details",
				Layout: Grid{Columns: 2},
				Children: []Widget{
					Label{Text: "Something"},
					LineEdit{Text: " ", ReadOnly: true}, // LineEdit doesn't work with ints
				},
			},
			GroupBox{
				Title:  "Programs",
				Layout: VBox{},
				Children: []Widget{
					Label{Text: "XXXX"},
					LineEdit{Text: " ", ReadOnly: true}, // LineEdit doesn't work with ints
				},
			},
			PushButton{
				Text: "SCREAM",
				OnClicked: func() {
					var err = d.config.userConfig.WriteConfig()
					if err != nil {
						panic(err)
					}
				},
			},
		},
	}.Run()
}
