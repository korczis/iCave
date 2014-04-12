var g = null;
var ow = null;
var sensor = null;

var scaleValue = function(v, vMax) {
    return v * vMax;
};

var tick = function() {
    console.log("tick()");

    var light = analogRead(A1);
    var val = scaleValue(1 - light, 40);
    var temp = sensor.getTemp();

    g.clear();

    console.log(JSON.stringify({
        light: val,
        temp: temp
    }, null, 4));


    msg = "Light: " + val;
    g.drawString(msg, 0, 20);

    msg = "Temp: " + temp;
    g.drawString(msg, 0, 30);

    g.drawLine(0, val, 80, val);

    g.flip();
};

var initLcd = function() {
  console.log('initLcd()');

  SPI1.setup({ baud: 1000000, sck:B3, mosi:B5 });
  g = require("PCD8544").connect(SPI1,B6,B7,B8);
  g.setContrast(1);
};

var initTempSensor = function() {
  console.log('initTempSensor()');

  ow = new OneWire(B15);
  sensor = require("DS18B20").connect(ow);
};

var init = function() {
    console.log("init()");

    initLcd();

    initTempSensor();

    setInterval(function() { tick(); }, 500);
};

init();
