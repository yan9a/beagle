var b = require('bonescript');
b.pinMode('P8_19', b.INPUT);
b.pinMode('P8_13', b.OUTPUT);
setInterval(check,100);

function check(){
    var val = b.digitalRead('P8_19');
    b.digitalWrite('P8_13', val);
}