var g = null;

var scaleValue = function(v, vMax) {
    return v * vMax;
};

var tick = function() {
    console.log("tick()");

    var light = analogRead(A1);
    var val = scaleValue(1 - light, 40);

    msg = "Light: " + val;
    console.log(JSON.stringify({
        light: msg
    }, null, 4));

    g.clear();

    g.drawString(msg, 0, 20);
    g.drawLine(0, val, 80, val);

    g.flip();
};

var init = function() {
    console.log("init()");

    SPI1.setup({ baud: 1000000, sck:B3, mosi:B5 });
    g = require("PCD8544").connect(SPI1,B6,B7,B8);
    setInterval(function() { tick(); }, 500);
};

init();
