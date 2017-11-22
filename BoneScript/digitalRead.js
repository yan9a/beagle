var b = require('bonescript');
b.pinMode('P8_19', b.INPUT);
var val = b.digitalRead('P8_19');
if(val) console.log('HIGH');
else console.log('LOW');