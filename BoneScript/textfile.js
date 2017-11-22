var b = require('bonescript');
var file='/var/lib/cloud9/mytext.txt';
var od = b.readTextFile(file);
console.log('Data = ' + od);
b.writeTextFile(file, 'Written content.', writeStatus);
b.readTextFile(file, printStatus);
function writeStatus(x) {
    console.log(JSON.stringify(x));
}
function printStatus(x) {
    console.log('x.data = ' + x.data);
    console.log('x.err = ' + x.err);
}