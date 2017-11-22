var b = require('bonescript');
setInterval(rdAnalog,1000);
function rdAnalog(){
    var val = b.analogRead('P9_36');
    console.log('Value = ' + val)
    b.analogWrite('P9_14', val);
}