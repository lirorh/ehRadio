#include "options.h"
#ifdef MQTT_ENABLE // ============================== Everything ignored if not defined ==============================

#include <WiFi.h>
#include "config.h"
#include "mqtt.h"
#include "player.h"

void Mqtt::zeroBuf() { memset(topic, 0, sizeof(topic)); memset(status, 0, sizeof(status)); }

void Mqtt::_connectCb() { mqtt.connect(); }

void Mqtt::connect() { mqttClient.connect(); }

void Mqtt::init() {
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(_connectCb));
  mqttClient.onConnect(_onConnect);
  mqttClient.onDisconnect(_onDisconnect);
  mqttClient.onMessage(_onMessage);
  if (strlen(config.store.mqttuser)>0) mqttClient.setCredentials(config.store.mqttuser, config.store.mqttpass);
  mqttClient.setServer(config.store.mqtthost, config.store.mqttport);
  connect();
}

void Mqtt::_onConnect(bool sessionPresent) {
  mqtt.zeroBuf();
  sprintf(mqtt.topic, "%s%s", config.store.mqtttopic, "command");
  mqtt.mqttClient.subscribe(mqtt.topic, 2);
  mqtt.publishStatus();
  mqtt.publishVolume();
  mqtt.publishPlaylist();
}

void Mqtt::publishStatus() {
  if (mqttClient.connected()) {
    zeroBuf();
    sprintf(topic, "%s%s", config.store.mqtttopic, "status");
    char name[BUFLEN/2];
    char title[BUFLEN/2];
    config.escapeQuotes(config.station.name, name, sizeof(name)-10);
    config.escapeQuotes(config.station.title, title, sizeof(title)-10);
    snprintf(status, sizeof(status), "{\"status\": %d, \"station\": %d, \"name\": \"%s\", \"title\": \"%s\", \"on\": %d}", player.status()==PLAYING?1:0, config.lastStation(), name, title, config.store.dspon);
    mqttClient.publish(topic, 0, true, status);
  }
}

void Mqtt::publishPlaylist() {
  if (mqttClient.connected()) {
    zeroBuf();
    sprintf(topic, "%s%s", config.store.mqtttopic, "playlist");
    sprintf(status, "http://%s%s", WiFi.localIP().toString().c_str(), PLAYLIST_PATH);
    mqttClient.publish(topic, 0, true, status);
  }
}

void Mqtt::publishVolume() {
  if (mqttClient.connected()) {
    zeroBuf();
    char vol[5];
    memset(vol, 0, 5);
    sprintf(topic, "%s%s", config.store.mqtttopic, "volume");
    sprintf(vol, "%d", config.store.volume);
    mqttClient.publish(topic, 0, true, vol);
  }
}

void Mqtt::_onDisconnect(AsyncMqttClientDisconnectReason reason) {
  if (WiFi.isConnected()) {
    xTimerStart(mqtt.mqttReconnectTimer, 0);
  }
}

void Mqtt::_onMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  if (len == 0) return;
  if (len<20) {
    char buf[len+1];
    strncpy(buf, payload, len);
    buf[len]='\0';
    if (strcmp(buf, "prev") == 0) { player.sendCommand({PR_PREV, 0}); return; }
    if (strcmp(buf, "next") == 0) { player.sendCommand({PR_NEXT, 0}); return; }
    if (strcmp(buf, "toggle") == 0) { player.sendCommand({PR_TOGGLE, 0}); return; }
    if (strcmp(buf, "stop") == 0) { player.sendCommand({PR_STOP, 0}); return; }
    if (strcmp(buf, "start") == 0 || strcmp(buf, "play") == 0) { player.sendCommand({PR_PLAY, config.lastStation()}); return; }
    if (strcmp(buf, "boot") == 0 || strcmp(buf, "reboot") == 0) { ESP.restart(); return; }
    if (strcmp(buf, "voldown") == 0 || strcmp(buf, "volm") == 0) { player.stepVol(false); return; }
    if (strcmp(buf, "volup")   == 0 || strcmp(buf, "volp") == 0) { player.stepVol(true);  return; }
    if (strcmp(buf, "turnoff") == 0) {
      bool sst = config.store.smartstart;
      config.setDspOn(0);
      player.sendCommand({PR_STOP, 0});
      delay(100);
      config.saveValue(&config.store.smartstart, sst);
      return;
    }
    if (strcmp(buf, "turnon") == 0) {
      config.setDspOn(1);
      if (config.store.smartstart) player.sendCommand({PR_PLAY, config.lastStation()});
      return;
    }
    int volume;
    if (sscanf(buf, "vol %d", &volume) == 1) {
      if (volume < 0) volume = 0;
      if (volume > 254) volume = 254;
      player.setVol(volume);
      return;
    }
    int sb;
    if (sscanf(buf, "play %d", &sb) == 1) {
      if (sb < 1) sb = 1;
      uint16_t cs = config.playlistLength();
      if (sb >= cs) sb = cs;
      player.sendCommand({PR_PLAY, (uint16_t)sb});
      return;
    }
  } else {
    if (len>MQTT_BURL_SIZE) return;
    strncpy(player.burl, payload, len);
    player.burl[len]='\0';
    player.sendCommand({PR_BURL, 0});
    return;
  }
  /*if (strstr(buf, "http")==0) {
    if (len+1>sizeof(player.burl)) return;
    strlcpy(player.burl, payload, len+1);
    return;
  }*/
}

Mqtt mqtt;

#endif //  #ifdef MQTT_ENABLE