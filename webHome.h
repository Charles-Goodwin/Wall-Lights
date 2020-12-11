#include <stdlib.h>
#include <string.h>
#include <ArduinoJson.h>

StaticJsonDocument<250> doc;

/********************** HTML Page wrapping Style, content(HTML Body) and code(Script) ******************************/
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 600px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    padding-top:10px;
    padding-bottom:20px;
  }

  </style>
  
<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="topnav">
    <h1>Wall of Lights Controler</h1>
  </div>
  <div class="content">
    <div class="card">
      <h2>Current Pattern</h2> 
      <p><select style="width: 280px" id="pattern" name="pattern">
      %PATTERN_LIST%
      </select></p>
    </div>
    <div class="card">
      <h2>Current Palette</h2> 
      <p><select style="width: 280px" id="palette" name="palette">
      %PALETTE_LIST%
      </select></p>
    </div>
  </div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
    document.getElementById('pattern').selectedIndex = event.data;
  }
  function onLoad(event) {
    initWebSocket();
    initSelect();
  }

  function initSelect() {
    document.getElementById('pattern').addEventListener('change', selectPattern);
  }
  
  function selectPattern(){
    console.log('Sending Pattern Index');
    console.log(document.getElementById('pattern').selectedIndex);
    var message = '{"patternIndex":"' + document.getElementById('pattern').selectedIndex + '"}';
    console.log(message);
    websocket.send(message);
  }

</script>
</body>
</html>
)rawliteral";

void notifyClients() {
  ws.textAll(String(patternIndex));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  Serial.println("handle web socket");
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0; 
    String message = (char*)data;
    Serial.print("Jason Message: ");
    Serial.println(message);
    DeserializationError error = deserializeJson(doc, message);
    patternIndex = (int)doc["patternIndex"];
    Serial.print("patternIndex: ");
    Serial.println(patternIndex);
    
    notifyClients();
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  Serial.print("-------------------------------------var");
  Serial.println(var);

  if (var=="PATTERN_LIST") {
    String list = "";
    for (int i =0; i < MAX_PATTERNS; i++){
      list += "<option value='" + (String)i + "' ";
      if (i == patternIndex){
        list += "selected";
      }
      list += ">" + patterns[i].name + "</option>";
    }
    return list;
  }    
}
