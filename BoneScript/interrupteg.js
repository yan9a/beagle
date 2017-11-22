var b = require('bonescript');
var inputPin = 'P8_19';
var outputPin = 'P8_13';
b.pinMode(inputPin, b.INPUT);
b.pinMode(outputPin, b.OUTPUT);
b.attachInterrupt(inputPin, true, b.CHANGE, interruptCallback);
setTimeout(detach, 30000);
function interruptCallback(x) {
    console.log(JSON.stringify(x));
    b.digitalWrite(outputPin,x.value);
}
function detach() {
    b.detachInterrupt(inputPin);
    console.log('Interrupt detached');
}