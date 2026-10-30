import QtQuick
Window {
  width: 1080; height: 640; visible: true; color: "white"
  
  property int speed: 0;
  property string gear: "P";

  Column {
    spacing: 32;
    anchors.centerIn: parent;
    
    Text { text: "0 mph"; color: "black"; font.pixelSize: 64; height: 64 }
    Text {
    text: gear === "P" ? "Parked" : "Driving";
    color: gear === "P" ? "green" : "black";
    font.pixelSize: 32 }
  }
   
}
