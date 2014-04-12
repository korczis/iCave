var ow = null;
var sensor = null;

function Sensor() {
    init: function() {
    }

    acquire: function() {
    }
}

var scaleValue = function(v, vMax) {
    return v * vMax;
};

var acquireData = function() {
    var lightRaw = analogRead(A1);

    return {
        light: scaleValue(1 - lightRaw, 40),
        temp:  sensor.getTemp()
    };
};

var drawText = function(g, data) {
    var msg = '';

    msg = "Light: " + data.light;
    g.drawString(msg, 0, 20);

    msg = "Temp: " + data.temp;
    g.drawString(msg, 0, 30);
};

var drawLine = function(g, data) {
    g.drawLine(0, data.light, 80, data.light);
};


var displayData = function(g, data) {
    g.clear();

    drawText(g, data);

    drawLine(g, data);

    g.flip();
};

var tick = function(g) {
    console.log("tick()");
    var data = acquireData();

    console.log(JSON.stringify(data, null, 4));

    displayData(g, data);
};

var initLcd = function() {
    console.log('initLcd()');

    SPI1.setup({ baud: 1000000, sck:B3, mosi:B5 });

    var g = require("PCD8544").connect(SPI1,B6,B7,B8);
    g.setContrast(1);
    return g;
};

var initTempSensor = function() {
    console.log('initTempSensor()');

    ow = new OneWire(B15);
    sensor = require("DS18B20").connect(ow);
};

var init = function() {
    console.log("init()");

    var g = initLcd();

    initTempSensor();

    setInterval(function() { tick(g); }, 500);
};

init();