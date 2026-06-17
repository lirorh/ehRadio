// script2.js replaces formerly 4 .js files and is used in various places outside of the main player.html


// ===== i18n loader: loads locale.json for translations =====
var i18n = {};

// Check if we need to load locale.json
// If uiLocale === htmlLocale, we're using hardcoded firmware locale (no file needed)
var shouldLoadLocale = true;
if (typeof uiLocale !== 'undefined' && typeof htmlLocale !== 'undefined') {
  if (uiLocale === htmlLocale) {
    console.log('Using hardcoded locale (' + htmlLocale + '), no need to fetch locale.json');
    shouldLoadLocale = false;
  }
}

// Only fetch locale.json if needed; expose promise so other scripts can chain on it
var localePromise = Promise.resolve();
if (shouldLoadLocale) {
  localePromise = fetch('locale.json')
      .then(function(r){ return r.ok ? r.json() : Promise.reject('not-ok'); })
      .then(function(data){ 
          i18n = data;
          applyI18n(); // Only apply translations when successfully loaded
      })
      .catch(function(){
          console.warn('locale.json not found or failed to load, using hardcoded HTML text');
          // Don't run applyI18n() - let HTML fallbacks handle it
      });
}

function t(key) {
  // If only key provided, use old behavior (backward compatibility)
  if (arguments.length === 1) { return (i18n && i18n[key]) ? i18n[key] : key; }
  // With defaultText as second arg: use translation or fallback to English
  var defaultText = arguments[1];
  var args = Array.prototype.slice.call(arguments, 2);
  var s = (i18n && i18n[key]) ? i18n[key] : (defaultText || key);
  args.forEach(function(a, i){ s = s.replace('{' + i + '}', a); });
  return s;
}

function applyI18n(root) {
  (root || document).querySelectorAll('[data-i18n]').forEach(function(el) {
    var key = el.dataset.i18n;
    var val = i18n[key];
    if (!val) return;
    if (el.hasAttribute('title')) {
      el.title = val;
    } else if (el.hasAttribute('alt')) {
      el.alt = val;
    } else if (el.tagName === 'INPUT' && (el.type === 'button' || el.type === 'submit')) {
      el.value = val;
    } else if (el.tagName === 'INPUT' && el.placeholder !== undefined) {
      el.placeholder = val;
    } else {
      el.textContent = val;
    }
  });
  // Update knob on/off labels via CSS variables (must be quoted for content property)
  document.documentElement.style.setProperty('--knob-off', '"' + t('lbl_off', 'Off') + '"');
  document.documentElement.style.setProperty('--knob-on', '"' + t('lbl_on', 'On') + '"');
}

// ===== IR Recorder functionality for ir.html =====

var irloaded=false;
function checkSelect(){
  var elements = document.getElementsByClassName("irradio");
  var chkid = 0;
  for (var i = 0; i < elements.length; i++) {
      elements[i].classList.remove("active");
      elements[i].parentElement.getElementsByClassName("irrecordvalue")[0].classList.remove("active");
      if(elements[i]===this) chkid=i;
  }
  var ts = this!==window?this:elements[0];
  ts.classList.add("active");
  ts.parentElement.getElementsByClassName("irrecordvalue")[0].classList.add("active");
  if(this!==window) websocket.send('chkid='+chkid);
  document.getElementById('protocol').innerText="";
}

function irbuttonClick(){
  var elements = document.getElementsByClassName("irbutton");
  var hasactive = this.classList.contains("active");
  var btnid = -1;
  for (var i = 0; i < elements.length; i++) {
    elements[i].classList.remove("active");
    if(!hasactive && elements[i]==this) btnid=i;
  }
  if(!hasactive) {
    document.getElementById("irrecordtitle").innerHTML = t('msg_codes_for_button', 'Codes for button') + ' <span>'+this.innerHTML+'</span>';
    document.getElementById("irrecord").classList.remove("hidden");
    document.getElementById("irstartrecord").classList.add("hidden");
    this.classList.add("active");
    checkSelect();
  }else{
    document.getElementById("irrecord").classList.add("hidden");
    document.getElementById("irstartrecord").classList.remove("hidden");
  }
  document.getElementById('protocol').innerText="";
  websocket.send('irbtn='+btnid);
}
function backRecord(){
  var elements = document.getElementsByClassName("irbutton");
  for (var i = 0; i < elements.length; i++) {
    elements[i].classList.remove("active");
  }
  document.getElementById("irrecord").classList.add("hidden");
  document.getElementById("irstartrecord").classList.remove("hidden");
  websocket.send('irbtn=-1');
}
function irClear(el){
  el.parentElement.getElementsByClassName("irrecordvalue")[0].innerText="";
  document.getElementById('protocol').innerText="";
  websocket.send('irclr='+el.parentElement.getElementsByClassName("irradio")[0].getAttribute('data-id'));
}
function initControls(){
  if(irloaded) return;
  irloaded=true;
  var elements = document.getElementsByClassName("irbutton");
  for (var i = 0; i < elements.length; i++) {
      elements[i].addEventListener('click', irbuttonClick, false);
  }
  elements = document.getElementsByClassName("irradio");
  for (var i = 0; i < elements.length; i++) {
      elements[i].addEventListener('click', checkSelect, false);
  }
}

// ===== Online update checker functionality for update.html =====

function initOnlineUpdateChecker() {
  if (onlineUpdCapable) {
    getId('check_online_update').classList.remove('hidden');
    getId('check_online_update').value = t('btn_check_online', 'Check for Online Update');
    getId('check_online_update').disabled = false;
    console.log("Online Update is available");
  } else {
    getId('check_online_update').classList.add('hidden');
    console.log("Online Update not available");
  }
}

function checkOnlineUpdate(button) {
  if (button.value === t('btn_check_online', 'Check for Online Update')) {
    console.log("Checking for online update");
    button.value = t('lbl_checking', 'Checking...');
    button.disabled = true;
    fetch('/onlineupdatecheck')
      .then(response => response.text())
      .then(data => {
        console.log("Check update response:", data);
        // The server will send WebSocket messages with the actual results so just wait
      })
      .catch(error => {
        console.error("Error checking for updates:", error);
        button.value = t('btn_check_online', 'Check for Online Update');
        button.disabled = false;
      });
  } else if (button.value.startsWith("Update to")) {
    console.log("Starting online update via HTTP");
    // Show and reset progress bar
    const bar = getId('updateprogress');
    if (bar) { bar.hidden = false; bar.value = 0; }

    button.disabled = true;
    fetch('/onlineupdatestart')
      .then(response => response.text())
      .then(data => {
        console.log("Start update response:", data);
        // Prepare UI: hide form, show status and progress bar
        const status = getId('uploadstatus');
        
        if(status) status.innerHTML = getId('check_online_update').value;

        getId("uploadstatus").innerHTML = t('lbl_starting_online_update', 'Starting online update...');
        getId('updateform').classList.add('hidden');
        getId("updateprogress").value = 0;
        getId('updateprogress').hidden=false;
        getId('update_cancel_button').hidden=true;
        getId('check_online_update').classList.add('hidden');
        // WebSocket messages will drive progress
      })
      .catch(error => {
        console.error("Error starting update:", error);
        button.value = t('btn_check_online', 'Check for Online Update');
        button.disabled = false;
        getId("uploadstatus").innerHTML = t('lbl_error_starting_online_update', 'Error starting online update');
        getId('updateform').classList.remove('hidden');
        getId('updateprogress').hidden=true;
        getId("updateprogress").value = 0;
        getId('update_cancel_button').hidden=false;
        getId('check_online_update').classList.remove('hidden');
      });
  }
}

// ===== Shared station preview/play functionality for search and playlist editor =====

function sendStationAction(name, url, addtoplaylist) {
  if (!name || !url) {
    console.error('Invalid station data:', { name, url });
    return;
  }
  
  const label = addtoplaylist ? "Added to playlist: " : "Preview: ";
  const formData = new URLSearchParams();
  formData.append('name', name);
  formData.append('url', url);
  formData.append('addtoplaylist', addtoplaylist);
  
  fetch('/search', {
    method: 'POST',
    headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
    body: formData
  })
  .then(response => {
    if (!response.ok) throw new Error('Action failed');
    return response.text();
  })
  .then(responseText => {
    console.log(label + name, 'Response:', responseText);
  })
  .catch(error => console.error('Error sending station action:', error));
}
