var b = require('bonescript');
var state = 0;
b.pinMode("P8_13", b.OUTPUT);
var timer = setInterval(toggle,500);
setTimeout(stopTimer,5000);
function toggle() {
    state ^= 1;
    b.digitalWrite("P8_13", state);
}
function stopTimer() {
    clearInterval(timer);
}
