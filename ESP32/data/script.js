var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

var tempGauge, humiGauge;

// MAP
var map, marker;

window.addEventListener('load', onLoad);

function onLoad() {
    initWebSocket();
    initGauges();
    initMap();
}

/* ---------------- MAP ---------------- */
function initMap() {
    map = L.map('map').setView([0, 0], 2);

    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        maxZoom: 19
    }).addTo(map);

    marker = L.marker([0, 0]).addTo(map);
}

/* ---------------- MODERN GAUGES ---------------- */
function initGauges() {
    tempGauge = new JustGage({
        id: "tempGauge",
        value: 0,
        min: 0,
        max: 100,
        symbol: "°C",
        gaugeWidthScale: 0.6,
        counter: true,
        pointer: true,
        customSectors: [
            { color: "#6FD57F", lo: 0, hi: 35 },
            { color: "#FFD93D", lo: 35, hi: 60 },
            { color: "#FF6B6B", lo: 60, hi: 100 }
        ]
    });

    humiGauge = new JustGage({
        id: "humiGauge",
        value: 0,
        min: 0,
        max: 100,
        symbol: "%",
        gaugeWidthScale: 0.6,
        counter: true,
        pointer: true,
        customSectors: [
            { color: "#6FD57F", lo: 0, hi: 40 },
            { color: "#FFD93D", lo: 40, hi: 70 },
            { color: "#FF6B6B", lo: 70, hi: 100 }
        ]
    });
}

/* ---------------- WEBSOCKET ---------------- */
function initWebSocket() {
    websocket = new WebSocket(gateway);
    websocket.onmessage = onMessage;
}

function toggleRelay(index) {
    let card = document.getElementById("card" + index);
    let state = card.dataset.state === "ON" ? "OFF" : "ON";

    updateRelayUI(index, state);

    websocket.send(JSON.stringify({
        mode: "Manual",
        index: index,
        state: state
    }));

    card.dataset.state = state;
}

function updateRelayUI(index, state) {
    let card = document.getElementById("card" + index);

    if (state === "ON") {
        card.style.backgroundColor = "#C9F7D7";
    } else {
        card.style.backgroundColor = "#EDEDED";
    }
}

/* ---------------- ON MESSAGE ---------------- */
function onMessage(event) {
    let data = JSON.parse(event.data);

    if (data.current)
        document.getElementById('current').innerText = data.current;

    if (data.temperature)
        tempGauge.refresh(data.temperature);

    if (data.humidity)
        humiGauge.refresh(data.humidity);

    if (data.latitude && data.longitude) {
        let lat = parseFloat(data.latitude);
        let lon = parseFloat(data.longitude);

        document.getElementById("latitude").innerText = lat.toFixed(5);
        document.getElementById("longitude").innerText = lon.toFixed(5);

        marker.setLatLng([lat, lon]);
        map.setView([lat, lon], 15);
    }

    if (data.index)
        updateRelayUI(data.index, data.state);
}
