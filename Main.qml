import QtQuick
Window {
  width: 1080; height: 640; visible: true; color: "white"
  title: "Prius Cluster";
  FontLoader { id: geist_bold; source: "./assets/fonts/GeistMonoBold.otf" }
  FontLoader { id: clash; source: "./assets/fonts/ClashDisplay-Variable.ttf"}
  
  property int speed: 0;
  property string gear: "D";

  Column {
    spacing: 32;
    anchors.centerIn: parent;
    
    
    Text { text: "0 mph"; font.family: geist_bold.font.family; font.pixelSize: 64; color: "black";height: 64 }
    Text {
    text: gear === "P" ? "Parked" : "Driving";
    color: gear === "P" ? "green" : "black";
    font.pixelSize: 32;
    font.family: clash.font.family;
    font.variableAxes: { "wght": 650 }
  }
} 
}
