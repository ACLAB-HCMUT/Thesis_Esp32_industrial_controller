var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

window.addEventListener('load', onLoad);

function onLoad(event) {
    initWebSocket();
}

function toggleButton(index) {
    var state = document.getElementById('state' + index).innerText;
    var newstate = state == 'ON' ? 'OFF' : 'ON';
    var mode = 'Manual';
    var message = JSON.stringify({
        mode: mode,
        index: index,
        state: newstate
    });
    websocket.send(message);
}

function onOpen(event) {
    console.log('Connection opened');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function initWebSocket() {
    console.log('Trying to open a WebSocket connection…');
    websocket = new WebSocket(gateway);
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onMessage(event) {
    var data;
    console.log(event.data);
    data = JSON.parse(event.data);
    if (data.index) {
        var index = data.index;
        var state = data.state;
        document.getElementById("state" + index).innerHTML = state;
    }
    if (data.getState1 && data.getState2 && data.getState3 && data.getState4) {
        document.getElementById("state1").innerHTML = data.getState1;
        document.getElementById("state2").innerHTML = data.getState2;
        document.getElementById("state3").innerHTML = data.getState3;
        document.getElementById("state4").innerHTML = data.getState4;
    }
    if (data.temperature && data.humidity) {
        document.getElementById('temperature').innerHTML = data.temperature.toFixed(2);
        document.getElementById('humidity').innerHTML = data.humidity.toFixed(2);
    }
    if (data.current) {
        document.getElementById('current').innerHTML = data.current;
    }
    if (data.latitude && data.longitude) {
        document.getElementById('latitude').innerHTML = data.latitude;
        document.getElementById('longitude').innerHTML = data.longitude;
    }
    if (data.schedule) {
        var scheduleContainer = document.getElementById('scheduleContainer');
        scheduleContainer.innerHTML = '';
        data.schedule.forEach(schedule => {
            var scheduleDiv = document.createElement('div');
            scheduleDiv.className = 'card';
            scheduleDiv.innerHTML = `
                <div class="schedule-card">
                    <h3>Schedule ${schedule.id}</h3>
                    <div class="schedule-details-horizontal">
                        <div class="detail-item">
                            <p><strong>State</strong></p>
                            <p>${schedule.state ? 'ON' : 'OFF'}</p>
                        </div>
                        <div class="detail-item">
                            <p><strong>Time</strong></p>
                            <p>${schedule.time}</p>
                        </div>
                        <div class="detail-item">
                            <p><strong>Days</strong></p>
                            <p>${schedule.days.join('<br>')}</p>
                        </div>
                        <div class="detail-item">
                            <p><strong>Actions</strong></p>
                            <p>${schedule.actions.map(action => `Relay ${action.relayId} ${action.action}`).join('<br>')}</p>
                        </div>
                    </div>
                </div>`;
            scheduleContainer.appendChild(scheduleDiv);
        });
    }
}