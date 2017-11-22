var b = require('bonescript');
var state = 0;//initialize LED state
b.pinMode("USR3", b.OUTPUT);//define USR3 as output

setInterval(toggle, 1000);//set timer 
//to call toggle function every 1 second

//toggle USR3 led
function toggle() {
    state ^= 1;//toggle the LED state
    b.digitalWrite("USR3", state);//write the resulting state
}